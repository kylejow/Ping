/*References
seek to line    https://stackoverflow.com/questions/5207550/in-c-is-there-a-way-to-go-to-a-specific-line-in-a-text-file
deque           https://en.cppreference.com/w/cpp/container/deque
*/

#include <iostream>
#include <limits>
#include <stdio.h>
#include <fstream>
#include <windows.h>
#include <vector>
#include <deque>

#include "display.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

std::fstream& goToLine(std::fstream& file, int num);
int getInt(string line, int start);
void set(int ping, vector<vector<string>>& display, int avg, int x, string replace);

int main(){
    std::string line;
    int ping, min = INT_MAX, max = INT_MIN, sum = 0, avg = 0, prevAvg = 0;
    system("clear");

    vector<vector<string>> display(21, vector<string>(30, " "));
    std::deque<int> pingHistory(30, 0);

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
            pingHistory.push_back(ping);
        }else{
            continue;
        }

        cout << "ping: " << ping << "\nmin: " << min << "\nmax: " << max << "\navg: " << avg << "\n\n";

        if(avg != prevAvg){
            prevAvg = avg;
            updateAxis(display, avg);
        }

        for(int i = 1; i < 30; i++){
            set(pingHistory[i], display, avg, i, " ");
        }
        pingHistory.pop_front();
        for(int i = 1; i < 30; i++){
            set(pingHistory[i], display, avg, i, "*");
        }

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

void set(int ping, vector<vector<string>>& display, int avg, int x, string replace){
    if(ping > avg + 10){
        display[0][x] = replace;
    }else if(ping < avg - 10){
        display[20][x] = replace;
    }else{
        display[ping-10][x] = replace;
    }
}