#include "board.h"
#include "term.h"
#include <cstdlib>
#include <iostream>
/**
 * 关于棋盘board的各种函数
 *
 *
 * */
#define DEFAULT_CELL_VALUE "⏹"
// #define WINDOW_TOP_ROWS 20;

extern TermInfo terminfo;

BoardInfo boardinfo;
BoardBound boardbound;

void destroyBoard(){
    // 释放内存
    for(int i = 0; i < boardinfo.board_rows; ++i)
        delete[] boardinfo.cell_values[i];
    delete[] boardinfo.cell_values;
}

void initBoard(){
    boardinfo.cell_values = new celltype* [boardinfo.board_rows];
    for(int i = 0; i < boardinfo.board_rows; ++i)
    {
        boardinfo.cell_values[i] = new celltype [boardinfo.board_cols];
        for(int j = 0; j < boardinfo.board_cols; ++j)
            boardinfo.cell_values[i][j] = DEFAULT_CELL_VALUE;
    }
    boardinfo.board_loc_rows = (terminfo.winRows - boardinfo.board_rows) / 2;
    boardinfo.board_loc_cols = (terminfo.winCols - boardinfo.board_cols) / 2;
    boardinfo.is_game_end = false;
    boardinfo.cell_values[5][5] = "1";
    boardinfo.cell_values[4][5] = "5";
    boardinfo.cell_values[7][6] = "1";
    boardinfo.cell_values[2][4] = "3";
    boardinfo.cell_values[3][9] = "9";
    atexit(destroyBoard);
}


void drawBoard()
{
    moveCursorToLocation(boardinfo.board_loc_rows, boardinfo.board_loc_cols);

    COUT("\033[32m");
    for(int i = 0; i < boardinfo.board_cols + 1; i++) std::cout << "--"; std::cout << "-";
    COUT("\033[0m");

    boardbound.top = boardinfo.board_loc_rows + 1;
    for(int i = 0; i < boardinfo.board_rows; i++){
    moveCursorToLocation(boardinfo.board_loc_rows+i+1, boardinfo.board_loc_cols);
        COUT("\033[32m| \033[0m");
        for(int j = 0; j < boardinfo.board_cols; j++){
            std::cout << boardinfo.cell_values[i][j] << " ";
        }
        COUT("\033[32m| \033[0m");
    }
    boardbound.bottom = boardinfo.board_loc_rows + boardinfo.board_rows;

    moveCursorToLocation(boardinfo.board_loc_rows+boardinfo.board_rows+1, boardinfo.board_loc_cols);

    COUT("\033[32m");
    for(int i = 0; i < boardinfo.board_cols + 1; i++) std::cout << "--"; std::cout << "-";
    COUT("\033[0m");

    moveCursorToLocation(boardinfo.board_loc_rows + 1, boardinfo.board_loc_cols+2);
    COUT("\x1b[4;5m");
}
