//References
//clear screen    https://cplusplus.com/forum/beginner/18191/

#include "display.h"

void printDisplay(vector<vector<std::string>>& Display){
    int length = Display[0].size();
    for(auto iter = Display.begin(); iter != Display.end(); iter++){
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

void updateAxis(vector<vector<std::string>>& Display, int avg){
    for(int i = 0; i < 21; i++){
        Display[i][0] = std::to_string(avg+10);
        avg--;
    }
    return;
}