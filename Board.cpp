#include "Board.hpp"

void Board::init(int n, int m, int k, int player) {
    this->n = n;
    this->m = m;
    this->k = k;
    this->fields = (Field **)malloc(sizeof(Field*) * n);
    FOR(i, n) {
        this->fields[i] = (Field *)malloc(sizeof(Field) * m);
    }
    FOR(i, n) {
        FOR(j, m) {
            set_field(i, j, 0);
        }
    }
    this->player = player;
    this->winner = 0;
    this->black_count = 0;
    this->white_count = 0;
    this->empty_count = n * m;
}

void Board::set_field(int x, int y, int value) {
    assert(value >= 0 && value <= 2);
    assert(x >= 0 && x < n);
    assert(y >= 0 && y < m);

    int prev_value = this->fields[x][y].get_value();
    this->fields[x][y].set_value(value);

    if (value == BLACK) {
        this->black_count++;
    } else if (value == WHITE) {
        this->white_count++;
    } else if (value == EMPTY) {
        this->empty_count++;
    }

    if(prev_value == BLACK) {
        this->black_count--;
    } else if(prev_value == WHITE) {
        this->white_count--;
    } else if(prev_value == EMPTY) {
        this->empty_count--;
    }
}

void Board::destroy() {
    FOR(i, n) {
        free(this->fields[i]);
    }
    free(this->fields);
}

void Board::print() {
    FOR(i, n) {
        FOR(j, m) {
            printf("%d ", this->fields[i][j].get_value());
        }
        printf("\n");
    }
}

void Board::swap_fields(int x, int y, int dx, int dy) {
    assert(on_board(x, y));
    assert(on_board(dx, dy));

    int value = get_field(x, y);
    set_field(x, y, get_field(dx, dy));
    set_field(dx, dy, value);
}

void Board::copy_from(Board& board) {
    init(board.n, board.m, board.k, board.player);
    FOR(i, n) {
        FOR(j, m) {
            set_field(i, j, board.get_field(i, j));
        }
    }
}

void Board::next(int& rx, int& ry, int x, int y, int k) {
    int col = x * m + y + k;
    int row = col / m;
    col %= m;

    assert(on_board(row, col));

    rx = row;
    ry = col;
}

void Board::kth_zero(int& rx, int& ry, int x, int y, int k) {
    assert(k > 0 && k <= empty_count);
    int dx, dy;
    while(k > 0) {
        next(dx, dy, x, y, 1);

        assert(on_board(dx, dy));

        if(get_field(dx, dy) == EMPTY) k--;
        else next(x, y, x, y, 1);
    }

    rx = dx;
    ry = dy;
}

bool Board::on_board(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;    
}

int Board::get_field(int x, int y) {
    assert(on_board(x, y));
    return this->fields[x][y].get_value();
}

bool Board::win_check(int player) {
    if(n == 0 && m == 0) {
        return false;
    }
    if(n == 1 && m == 1) {
        return get_field(0, 0) == player;
    }

    Utils utils;
    int calc_n = n + 2, calc_m = m + 2;
    int **calc = (int **)malloc(sizeof(int*) * calc_n);
    FOR(i, calc_n) {
        calc[i] = (int *)malloc(sizeof(int) * calc_m);
    }

    win_deb {
        printf("STARTING WIN CHECK\n");
        printf("PLAYER %d\n", player);
        print();
        printf("\n");
    }

    // Check rows
    utils.zero_calc_board(calc, calc_n, calc_m);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(get_field(i - 1, j - 1) == player) {
                calc[i][j] = calc[i][j - 1] + 1;
            }
            if(calc[i][j] >= k) {
                this->winner = player;
                utils.destroy_calc_board(calc, calc_n);
                return true;
            }
        }
    }
    win_deb {
        printf("ROWS\n");
        utils.print_calc_board(calc, calc_n, calc_m);
    }

    // Check columns
    utils.zero_calc_board(calc, calc_n, calc_m);
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(get_field(j - 1, i - 1) == player) {
                calc[j][i] = calc[j - 1][i] + 1;
            }
            if(calc[j][i] >= k) {
                this->winner = player;
                utils.destroy_calc_board(calc, calc_n);
                return true;
            }
        }
    }
    win_deb {
        printf("COLS\n");
        utils.print_calc_board(calc, calc_n, calc_m);
    }

    // Check diagonals 1
    utils.zero_calc_board(calc, calc_n, calc_m);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(get_field(i - 1, j - 1) == player) {
                calc[i][j] = calc[i - 1][j - 1] + 1;
            }
            if(calc[i][j] >= k) {
                this->winner = player;
                utils.destroy_calc_board(calc, calc_n);
                return true;
            }
        }
    }
    win_deb {
        printf("DIA1\n");
        utils.print_calc_board(calc, calc_n, calc_m);
    }

    // Check diagonals 2
    utils.zero_calc_board(calc, calc_n, calc_m);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(get_field(i - 1, j - 1) == player) {
                calc[i][j] = calc[i - 1][j + 1] + 1;
            }
            if(calc[i][j] >= k) {
                this->winner = player;
                utils.destroy_calc_board(calc, calc_n);
                return true;
            }
        }
    }
    win_deb {
        printf("DIA2\n");
        utils.print_calc_board(calc, calc_n, calc_m);
    }

    utils.destroy_calc_board(calc, calc_n);
    return false;
}

int Board::get_winner() {
    if(win_check(WHITE)) {
        return WHITE;
    } else if(win_check(BLACK)) {
        return BLACK;
    } else {
        return NONE;
    }
}

void Board::next_player() {
    if(player == WHITE) {
        player = BLACK;
    } else if(player == BLACK) {
        player = WHITE;
    }    
}
