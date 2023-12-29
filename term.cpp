#include <iostream>
#include <cstdlib>
#include <ctype.h>
#include <stdio.h>
#include <sys/termios.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

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
#define COUT(x) std::cout << x << std::endl;

// 定义一些输出到终端中的特殊序列（VT100 escape序列）
#define CURSOR_POS "\x1b[6n"

// 终端最原始的设置，保存起来，后面用于恢复终端
struct termios orig_termios_config; // 

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
    raw.c_oflag &= (OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG); // 禁用回显echo功能(敲的字符被打印在屏幕上)；ICANON可以使得term按照char读取输入
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

void getCursorPos(int& rows, int& cols){
    rows = 1;
    cols = 1;
    std::cout << "\x1b[6n";
   // COUT(CURSOR_POS); // 向终端输入想要获得光标位置的指令
   char cursor_info[10];
   unsigned int i = 0;
   while(i < sizeof(cursor_info)){
       std::cin.get(cursor_info[i]);
       if(cursor_info[i] == 'R') break;
       i ++;
   }
   cursor_info[i] = '\0';
    std::cout << cursor_info << std::endl;
// #ifdef DEBUG_MODE
// COUT(cursor_info);
// #endif // DEBUG
}

char getUserInput(){
    char c;
    std::cin.get(c);
    return c;
}
