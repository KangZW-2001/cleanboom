#include <iostream>
#include "term.h"
#include "board.h"

extern TermInfo terminfo;
extern BoardInfo boardinfo;

int main(){
    // TermInfo terminfo;
    std::cout << "请输入你想要创建的行数：";
    std::cin >> boardinfo.board_rows;
    std::cout << "请输入你想要创建的列数：";
    std::cin >> boardinfo.board_cols;

    cleanWindow(1);
    getWindowSize(terminfo.winCols, terminfo.winRows);
    enableRawMode();
    initBoard();
    drawBoard();
    handlePlayerInput();
    return 0;
}
