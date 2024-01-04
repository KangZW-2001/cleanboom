#ifndef BOARD_H
#define BOARD_H
#include <string>

typedef std::string celltype;
struct BoardInfo{
    int board_cols, board_rows; // 棋盘的大小，行数和列数
    int board_loc_rows, board_loc_cols;
    celltype ** cell_values;
    bool is_game_end;
};

struct BoardBound{
    int top,bottom,left,right;
};
void initBoard();
void destroyBoard();
void drawBoard();

#endif // !BOARD_H
