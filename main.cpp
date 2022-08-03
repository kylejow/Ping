/*References
seek to line    https://stackoverflow.com/questions/5207550/in-c-is-there-a-way-to-go-to-a-specific-line-in-a-text-file
*/

#include <iostream>
#include <limits>
#include <stdio.h>
#include <fstream>
#include <windows.h>
#include <vector>

#include "display.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

std::fstream& goToLine(std::fstream& file, int num);
int getInt(string line, int start);

int main(){
    std::string line;
    int ping, min = INT_MAX, max = INT_MIN, sum = 0, avg = 0, prevAvg = 0;
    system("clear");

    vector<vector<string>> display(21, vector<string>(30, "*"));
    
    int count = 0;
    while(count < 50){
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
            sum += ping;
            count++;
            avg = sum/count;
        }else{
            continue;
        }

        cout << "ping: " << ping << "\nmin: " << min << "\nmax: " << max << "\navg: " << avg << "\n\n";

        if(avg != prevAvg){
            prevAvg = avg;
            updateAxis(display, avg);
        }
        
        ////////////
        for(int i = 0; i < 21; i++){
            display[i][29] = " ";
        }
        if(ping > avg + 10){
            display[0][29] = "*";
        }else if(ping < avg - 10){
            display[20][29] = "*";
        }else{
            display[ping-10][29] = "*";
        }
        ////////////

        printDisplay(display);
        Sleep(10);
        clearScreen();
    }
    system("pause");
    system("clear");
    return 0;
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