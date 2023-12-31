#include <iostream>
#include "term.h"

extern TermInfo terminfo;

int main(){
    // TermInfo terminfo;
    std::cout << "请输入你想要创建的行数：";
    std::cin >> terminfo.boardRows; 
    std::cout << "请输入你想要创建的列数：";
    std::cin >> terminfo.boardCols;

    enableRawMode();
    cleanWindow(1);
    handlePlayerInput();
    return 0;
}
