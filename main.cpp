/*References
seek to line          https://stackoverflow.com/questions/5207550/in-c-is-there-a-way-to-go-to-a-specific-line-in-a-text-file
deque                 https://en.cppreference.com/w/cpp/container/deque
multithread interrupt https://stackoverflow.com/questions/41470942/stop-infinite-loop-in-different-thread
thread constructor    https://en.cppreference.com/w/cpp/thread/thread/thread
*/

#include <iostream>
#include <windows.h>
#include <deque>
#include <thread>
#include <atomic>

#include "display.h"
#include "ping.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

void stopProgram(std::atomic_bool& stop);

int main(){
    system("clear");
    setCursor(false);
    std::string line;
    int ping, min = INT_MAX, max = INT_MIN, avg = 0, prevAvg = 0;
    unsigned long long int sum = 0, count = 0;
    
    vector<vector<string>> display(21, vector<string>(50, " "));
    std::deque<int> pingHistory(50, 0);

    std::atomic_bool stop = false;
    std::thread stopThread(stopProgram, std::ref(stop));
    
    while(!stop){
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

        for(int i = 1; i < 50; i++){    // remove previous points
            setPoint(display, pingHistory[i], prevAvg, i, " ");
        }

        if(avg != prevAvg){
            prevAvg = avg;
            updateAxis(display, avg);
        }

        pingHistory.pop_front();    // shift queue
        for(int i = 1; i < 50; i++){    // replace points
            setPoint(display, pingHistory[i], avg, i, "*");
        }

        printDisplay(display);
        cout << "\nping: " << ping <<"     "
             << "\nmin: "  << min  <<"     "
             << "\nmax: "  << max  <<"     "
             << "\navg: "  << avg  <<"     "
             << "\n\n\nPress Enter to exit.";
        clearScreen();
    }
    stopThread.join();
    system("clear");
    setCursor(true);
    return 0;
}

void stopProgram(std::atomic_bool& stop){
    std::cin.get();
    stop = true;
    return;
}