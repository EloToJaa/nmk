#pragma once

#include "Header.hpp"

struct Node {
    int score;
    int number_of_children;
    int player;
    int depth;
    Node** children;

    void save_winner(int winner);
};