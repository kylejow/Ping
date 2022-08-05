/*References
seek to line    https://stackoverflow.com/questions/5207550/in-c-is-there-a-way-to-go-to-a-specific-line-in-a-text-file
deque           https://en.cppreference.com/w/cpp/container/deque
*/

#include <iostream>
#include <windows.h>
#include <deque>

#include "display.h"
#include "ping.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

int main(){
    std::string line;
    int ping, min = INT_MAX, max = INT_MIN, sum = 0, avg = 0, prevAvg = 0;
    system("clear");

    vector<vector<string>> display(21, vector<string>(30, " "));
    std::deque<int> pingHistory(30, 0);

    int count = 0;
    while(count < 50){
        ping = getPing();
        if(ping == -1){
            continue;
        }
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