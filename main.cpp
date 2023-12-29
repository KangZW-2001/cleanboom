#include <cstdlib>
#include <iostream>
#define DEBUG_MODE

void enableRawMode();
void getWindowSize(int&, int&);
void getCursorPos(int&, int&);
char getUserInput();
#ifndef COUT
#define COUT(x) std::cout << x << std::endl;
#endif // !COUT

int main(){
    while(true){
        char c = getUserInput();
        if(c == 'q') exit(1);
        else{
            enableRawMode();
            int rows, cols;
            getCursorPos(rows, cols);
            return 0;
        }
    }
}
