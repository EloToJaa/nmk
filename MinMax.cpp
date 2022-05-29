#include "MinMax.hpp"


void MinMax::init(Board& board) {
    root = (Node *)malloc(sizeof(Node));
    root->depth = 0;
    init_util(root, board);
}

void MinMax::destroy() {
    destroy_util(root);
}

void MinMax::solve_game_state(Board& board) {
    mm_deb printf("STARING SOLVE_GAME_STATE\n");
    mm_deb test_count = 0;
    init(board);
    print_winner();
    mm_deb printf("INIT CALLS: %d\n\n", test_count);
}

void MinMax::init_util(Node* node, Board& board) {
    mm_deb test_count++;

    Solver solver;
    solver.save_all_pos_mov_cut_if_game_over(board);

    if(solver.board_count == 0) {
        node->save_winner(board.get_winner());
        node->number_of_children = 0;
        node->children = NULL;
        node->player = board.player;
        return;
    }

    node->number_of_children = solver.board_count;
    node->children = (Node**)malloc(sizeof(Node*) * node->number_of_children);
    node->player = board.player;
    node->score = 0;
    
    FOR(i, node->number_of_children) {
        Node* new_node = (Node*)malloc(sizeof(Node));

        new_node->depth = node->depth + 1;
        new_node->number_of_children = 0;
        new_node->children = NULL;
        new_node->player = (node->player == WHITE) ? BLACK : WHITE;

        node->children[i] = new_node;
    }

    FOR(i, node->number_of_children) {
        init_util(node->children[i], solver.boards[i]);
        // end min search in case of finding -1 and max seach in case of finding 1
        if (node->player == BLACK) {
            if (node->children[i]->score == -1) {
                node->score = -1;
                solver.destroy();
                return;
            }
        } else if(node->player == WHITE) {
            if (node->children[i]->score == 1) {
                node->score = 1;
                solver.destroy();
                return;
            }
        }
    }

    if(node->number_of_children > 0) {
        if(node->player == WHITE) {
            node->score = -1;
            FOR(i, node->number_of_children) {
                node->score = max(node->score, node->children[i]->score);
            }
        }
        else if(node->player == BLACK) {
            node->score = 1;
            FOR(i, node->number_of_children) {
                node->score = min(node->score, node->children[i]->score);
            }
        }
    }

    mm_deb {
        printf("DEPTH: %d\n", node->depth);
        printf("SCORE: %d\n", node->score);
        printf("NUMBER OF CHILDREN: %d\n", node->number_of_children);
        printf("PLAYER: %d\n", node->player);
        board.print();
        printf("\n");
    }

    solver.destroy();
}

void MinMax::destroy_util(Node* node) {
    FOR(i, node->number_of_children) {
        destroy_util(node->children[i]);
    }
    free(node->children);
    free(node);
}

void MinMax::print_winner() {
    int score = root->score;

    if(score == 1) {
        printf("FIRST_PLAYER_WINS\n");
    }
    else if(score == -1) {
        printf("SECOND_PLAYER_WINS\n");
    }
    else {
        printf("BOTH_PLAYERS_TIE\n");
    }
}
