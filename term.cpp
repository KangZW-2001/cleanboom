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

struct TermInfo{
    int winRows,winCols,cursorRows,cursorCols,boardRows,boardCols;
} terminfo;

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
void cleanWindow(int mode){
    switch(mode){
        case 1:
            COUT("\x1b[2i"); // 清除整个屏幕
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

void testDrawBoard(){
    int xbegin = (terminfo.winCols - terminfo.boardCols) / 2;
    int ybegin = (terminfo.winRows - terminfo.cursorRows) / 2;
    for (int i = 0; i < terminfo.boardCols; i++){
        std::cout << "|";
        for(int j = 0; j < terminfo.boardRows; j++){
            std::cout << "-";
        }
        std::cout << "|\r\n";
    }
}

int main(){
    // TermInfo terminfo;

    std::cout << "请输入你想要创建的行数：";
    std::cin >> terminfo.boardRows; 
    std::cout << "请输入你想要创建的列数：";
    std::cin >> terminfo.boardCols;

    enableRawMode();
    while(true){
        char c;
        getUserInput(c);
        switch(c){

        }
        if(c == 'q'){
            exit(1);
        }else if(c == 'c'){
            getCursorPos(terminfo.cursorRows,terminfo.cursorCols);
        }else if(c == 'z'){
            getWindowSize(terminfo.winRows, terminfo.winCols); // 获取到窗口的行数和列数
            std::cout << "WINDOW SIZE : " << terminfo.winRows << " ," <<terminfo.winCols<<std::endl; 
        }else if(c == 'w'){
            moveCursor('w');
        }else if(c == 'a'){
            moveCursor('a');
        }else if(c == 's'){
            moveCursor('s');
        }else if(c == 'd'){
            moveCursor('d');
        }else if(c == 'n'){
            testDrawBoard();
        }
    }
    return 0;
}
