#include "Node.hpp"


void Node::save_winner(int winner) {
    if(winner == NONE) {
        score = 0;
    }
    else if(winner == WHITE) {
        score = 1;
    }
    else if(winner == BLACK) {
        score = -1;
    }
}
