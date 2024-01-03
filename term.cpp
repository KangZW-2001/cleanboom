#include <cstddef>
#include <iostream>
#include <cstdlib>
#include <ctype.h>
#include <stdio.h>
#include <sys/termios.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string>
#include <array>
#include "term.h"

#ifndef DEBUG_MODE
#define DEBUG_MODE
#endif // !
/**
 * 这个文件用来包含使用AT100序列控制命令行的相关函数
 *
 *
 *
 *
 * */


// 终端最原始的设置，保存起来，后面用于恢复终端
struct termios orig_termios_config; // 

TermInfo terminfo;

void die(const char* error_info){
    std::cout << error_info << std::endl;
    exit(1);
}


void enableRawMode(){
    struct termios raw;
    tcgetattr(STDIN_FILENO, &orig_termios_config);// 将标准输入的属性读取到raw中
    atexit([](){tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios_config);}); // 将恢复命令行原始配置使用atexit注册一下，确保退出程序时候命令行正常

    raw = orig_termios_config;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON); // 以下都是一些设置
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG); // 禁用回显echo功能(敲的字符被打印在屏幕上)；ICANON可以使得term按照char读取输入
    // raw.c_lflag &= ~(ICANON | IEXTEN | ISIG);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void getWindowSize(int& rows, int& cols)
{
    struct winsize ws;
    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
        die("ERROR : Can't get window size");
    else{
        rows = ws.ws_col;
        cols = ws.ws_row;
    }
}

// 控制光标移动，direction代表方向
void moveCursor(char direction, int distance){
    // A：上， B：下，C：forward右，D：backward左
    char dir;
    switch(direction){
        case 'w':
            dir = 'A';
            break;
        case 'a':
            dir = 'D';
            break;
        case 's':
            dir = 'B';
            break;
        case 'd':
            dir = 'C';
            break;
    }
    std::string order = std::string("\x1b[") + std::to_string(distance) + dir;
    COUT(order);
}
// '\x1b[行数;列数f' 可以将光标移动到指定为止，实现该函数

// 控制清除屏幕的函数
void cleanWindow(int mode){
    switch(mode){
        case 1:
            COUT("\x1b[2J"); // 清除整个屏幕
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
    }
}

// 返回鼠标的位置[rows, cols]
void getCursorPos(int& rows, int& cols){
    COUT("\x1b[6n"); // 向终端输入控制序列，返回光标信息
    char cursor_info[10]; // 前两个字符是 ESC [ 最后以 R结尾
    unsigned int i = 0;
    while(i < sizeof(cursor_info)){
        std::cin.get(cursor_info[i]);
        if(cursor_info[i] == 'R') break; // 到R直接退出
        i ++;
    }
    cursor_info[i] = '\0';
    char* cursor_begin = cursor_info + 2;
    std::string str = cursor_begin;
    
    int part_pos = str.find(';');
    std::size_t size;
    rows = std::stoi(str.substr(0, part_pos+1));
    cols = std::stoi(str.substr(part_pos+1, str.size()));
}

// void drawBoard(){
//     int xbegin = (terminfo.winCols - terminfo.boardCols) / 2;
//     int ybegin = (terminfo.winRows - terminfo.cursorRows) / 2;
//     for (int i = 0; i < terminfo.boardCols; i++){
//         moveCursor('d', xbegin);
//         std::cout << "|";
//         for(int j = 0; j < terminfo.boardRows; j++){
//             std::cout << "--";
//         }
//         std::cout << "|\r\n";
//     }

void handlePlayerInput(){
    char c;
    while(true){
        std::cin.get(c);
        switch(c){
            case 'q':
                exit(1);
                break;
            case 'w':
                moveCursor('w', 1);
                break;
            case 'a':
                moveCursor('a', 1);
                break;
            case 's':
                moveCursor('s', 1);
                break;
            case 'd':
                moveCursor('d', 1);
                break;
            case 'c':
                getCursorPos(terminfo.cursorRows,terminfo.cursorCols);
#ifdef DEBUG_MODE
    std::cout << "CURSOR SIZE: " << terminfo.cursorRows << " ," <<terminfo.cursorCols<< "\r\n"; 
#endif // DEBUG
               break;
            case 'z':
               getWindowSize(terminfo.winCols, terminfo.winRows);
#ifdef DEBUG_MODE
    std::cout << "WINDOW SIZE : " << terminfo.winRows << " ," <<terminfo.winCols<< "\r\n"; 
#endif // DEBUG
               break;
        }
    }
}



