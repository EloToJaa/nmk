#include "Interface.hpp"


void Interface::handler() {
    while (true) {
        if(!handle_input()) break;
    }    
}

bool Interface::handle_input() {
    char input[40];
    int n, m, k, player;

    if(scanf("%s", input) == EOF) return false;
    scanf("%d %d %d %d", &n, &m, &k, &player);

    Board board;
    board.init(n, m, k, player);

    FOR(i, n) {
        FOR(j, m) {
            int value;
            scanf("%d", &value);
            board.set_field(i, j, value);
        }
    }

    deb {
        printf("STARTING BOARD:\n");
        board.print();
        printf("\n");
    }

    Solver solver;
    MinMax minmax;

    if(strcmp(input, "GEN_ALL_POS_MOV") == 0) {
        solver.gen_all_pos_mov(board);
        solver.destroy();
    }
    else if(strcmp(input, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER") == 0) {
        solver.gen_all_pos_mov_cut_if_game_over(board);
        solver.destroy();
    }
    else if(strcmp(input, "SOLVE_GAME_STATE") == 0) {
        minmax.solve_game_state(board);
        minmax.destroy();
    }

    board.destroy();

    deb printf("\n");

    return true;
}
