#include "board.h"
#include "term.h"
/**
 * 关于棋盘board的各种函数
 *
 *
 * */
#define DEFAULT_CELL_VALUE U'☐'
#define WINDOW_TOP_ROWS 20;

extern TermInfo termInfo;

BoardInfo boardinfo;

void initBoard(){
    boardinfo.cell_values = new celltype* [boardinfo.board_rows];
    for(int i = 0; i < boardinfo.board_rows; ++i)
    {
        boardinfo.cell_values[i] = new celltype [boardinfo.board_cols];
        for(int j = 0; j < boardinfo.board_cols; ++j)
            boardinfo.cell_values[i][j] = DEFAULT_CELL_VALUE;
    }
    boardinfo.board_loc_rows = termInfo.winRows - WINDOW_TOP_ROWS;
    boardinfo.board_loc_cols = (termInfo.winCols - boardinfo.board_cols) / 2;
}

void destroyBoard(){
    // 释放内存
    for(int i = 0; i < boardinfo.board_rows; ++i)
        delete[] boardinfo.cell_values[i];
    delete[] boardinfo.cell_values;
}

void drawBoard()
{

}
