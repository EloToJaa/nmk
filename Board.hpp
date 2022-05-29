#pragma once

#include "Header.hpp"

struct Board {
public:
    Field **fields;
    int n, m, k;
    int player;
    int winner;
    int black_count;
    int white_count;
    int empty_count;

public:
    void copy_from(Board& board);
    void init(int n, int m, int k, int player);
    void destroy();
    void print();
    void set_field(int x, int y, int value);
    int get_field(int x, int y);
    void swap_fields(int x, int y, int dx, int dy);
    void kth_zero(int& rx, int& ry, int x, int y, int k);
    void next(int& rx, int& ry, int x, int y, int k);
    bool on_board(int x, int y);
    bool win_check(int player);
    int get_winner();
    void next_player();
};