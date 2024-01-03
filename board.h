

#ifndef BOARD_H
#define BOARD_H
#include <string>

typedef char32_t celltype;
struct BoardInfo{
    int board_cols, board_rows; // 棋盘的大小，行数和列数
    int board_loc_rows, board_loc_cols;
    celltype ** cell_values;

};

#endif // !BOARD_H
