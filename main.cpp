/*References
seek to line    https://stackoverflow.com/questions/5207550/in-c-is-there-a-way-to-go-to-a-specific-line-in-a-text-file
clear screen    https://cplusplus.com/forum/beginner/18191/
*/

#include <iostream>
#include <limits>
#include <stdio.h>
#include <fstream>
#include <windows.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;

std::fstream& goToLine(std::fstream& file, int num);
int getInt(string line, int start);
void ClearScreen();

int main(){
    std::string line;
    int ping, min = INT_MAX, max = INT_MIN;
    system("clear");
    while(1){
        system("main.bat");
        std::fstream file("pings.txt");
        goToLine(file, 3);
        getline(file, line);

        // if(line.substr(0, 7) == "Request"){
        //     exit(0);
        // }

        if(line.substr(0, 5) == "Reply"){
            ping = getInt(line, 33);
            if(ping > max){
                max = ping;
            }
            if(ping < min){
                min = ping;
            }
        }
        cout << "ping: " << ping << "\nmin: " << min << "\nmax: " << max << "\n";
        ClearScreen();
    }
}

std::fstream& goToLine(std::fstream& file, int num){
    file.seekg(std::ios::beg);
    for(int i=0; i < num - 1; ++i){
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return file;
}

int getInt(string line, int start){
    int i = start;
    while(isdigit(line[i])){
        i++;
    }
    return std::stoi(line.substr(start, i-start));
}

void ClearScreen(){
    HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}