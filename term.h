
#ifndef TERM_H
#define TERM_H

struct TermInfo{
    int winRows,winCols,cursorRows,cursorCols,boardRows,boardCols;
};

void die(const char* error_info);

void enableRawMode();

void getWindowSize(int& rows, int& cols);

void moveCursor(char direction, int distance);

void cleanWindow(int mode);

void getCursorPos(int& rows, int& cols);

void drawBoard();

void handlePlayerInput();

#endif // !TERM_H 
