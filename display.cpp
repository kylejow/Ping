//References
//clear screen    https://cplusplus.com/forum/beginner/18191/
//set cursor      https://www.codegrepper.com/code-examples/cpp/c%2B%2B+hide+cursor+in+console

#include "display.h"

void printDisplay(vector<vector<std::string>>& display){
    int length = display[0].size();
    for(auto iter = display.begin(); iter != display.end(); iter++){
        for(int i = 0; i < length; i++){
            std::cout << (*iter)[i] << " ";
        }
        std::cout << "\n";
    }
}

void printVect(vector<int>& vect){
    auto iter = vect.begin();
    while(iter != vect.end()){
        std::cout << *iter << ", ";
        iter++;
    }
    std::cout << "\n";
}

void clearScreen(){
    HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

void updateAxis(vector<vector<std::string>>& display, int avg){
    for(int i = 0; i < 21; i++){
        display[i][0] = std::to_string(avg+10);
        avg--;
    }
    return;
}

void setCursor(bool visible){
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = visible;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}