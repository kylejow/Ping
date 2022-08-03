//References
//clear screen    https://cplusplus.com/forum/beginner/18191/

#include "display.h"

void PrintDisplay(vector<vector<std::string>>& Display){
    int length = Display[0].size();
    for(auto iter = Display.begin(); iter != Display.end(); iter++){
        for(int i = 0; i < length; i++){
            std::cout << (*iter)[i] << " ";
        }
        std::cout << "\n";
    }
}

void Printvect(vector<int>& vect){
    auto iter = vect.begin();
    while(iter != vect.end()){
        std::cout << *iter << ", ";
        iter++;
    }
    std::cout << "\n";
}

void ClearScreen(){
    HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}