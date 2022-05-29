#pragma once

#include "Header.hpp"

struct MinMax {
    Node* root;
    int test_count;

    void init(Board& board);
    void init_util(Node* node, Board& board);
    void destroy();
    void destroy_util(Node* node);
    void print_winner();
    void solve_game_state(Board& board);
};
