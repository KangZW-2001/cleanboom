#include <iostream>
#include <cstdlib>
#include <ctype.h>
#include <stdio.h>
#include <sys/termios.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string>

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
#define COUT(x) std::cout << x;

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

void getCursorPos(char * pointer){
    char * a = pointer;
    COUT("\x1b[6n");
    char cursor_info[10];
    unsigned int i = 0;
    while(i < sizeof(cursor_info)){
        std::cin.get(*a);
        a ++;
        // std::cout << cursor_info[i];
        if(cursor_info[i] == 'R') break;
        i ++;
    }
    *a = '\0';
}

// 控制光标移动，direction代表方向
void moveCursor(char direction){
    switch(direction){
        case 1:
            COUT("\x1b[1A");
            break;
        case 2:
            COUT("\x1b[1D");
            break;
        case 3:
            COUT("\x1b[1B");
            break;
        case 4:
            COUT("\x1b[1C");
            break;
    }
}

void getUserInput(char& c){
    std::cin.get(c);
}

// 控制清除屏幕的函数
void clearWindow(int mode){
    switch(mode){
        case 1:
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

int main(){
    enableRawMode();
    COUT("Test ECHO");
    while(true){
        char c;
        getUserInput(c);
        if(c == 'q'){
            exit(1);
        }else if(c == 'c'){
            char a[20];
            getCursorPos(a);
            std::string s = a;
            std::cout << s << std::endl;
        }else if(c == 'z'){
            int winrows, wincols;
            getWindowSize(winrows, wincols);
            std::cout << "WINDOWS: " << winrows << " " << wincols << std::endl;
        }else if(c == 'w'){
            moveCursor('w');
        }else if(c == 'a'){
            moveCursor('a');
        }else if(c == 's'){
            moveCursor('s');
        }else if(c == 'd'){
            moveCursor('d');
        }
    }
    return 0;
}
