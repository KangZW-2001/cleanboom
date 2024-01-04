
#ifndef TERM_H
#define TERM_H


#define COUT(x) std::cout << x;

#define WINDOW_CLEAN_ALL 1;

struct TermInfo{
    int winRows,winCols,cursorRows,cursorCols; // 分别存储窗口大小和鼠标位置
};

void die(const char* error_info);

void enableRawMode();

void getWindowSize(int& rows, int& cols);

void moveCursor(char direction, int distance);

void cleanWindow(int mode);

void getCursorPos(int& rows, int& cols);

void drawBoard();

void handlePlayerInput();

void moveCursorToLocation(const int rows, const int cols);

void setTextColor(char color);

#endif // !TERM_H 
