/*References
seek to line          https://stackoverflow.com/questions/5207550/in-c-is-there-a-way-to-go-to-a-specific-line-in-a-text-file
deque                 https://en.cppreference.com/w/cpp/container/deque
multithread interrupt https://stackoverflow.com/questions/41470942/stop-infinite-loop-in-different-thread
thread constructor    https://en.cppreference.com/w/cpp/thread/thread/thread
*/

#include <iostream>
#include <iomanip>
#include <windows.h>
#include <thread>
#include <atomic>

#include "display.h"
#include "ping.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::thread;
using std::ref;

void stopProgram(std::atomic_bool& stop);

int main(){
    system("clear");
    setCursor(false);
    cout << std::fixed << std::setprecision(5);
    std::string line;
    int ping, min = INT_MAX, max = INT_MIN, avg = 0, prevAvg = 0;
    long double jitter = 0;
    unsigned long long int sum = 0, count = 0;

    vector<vector<string>> display(21, vector<string>(50, " "));
    std::deque<int> pingHistory(50, 0);

    std::atomic_bool stop = false;
    thread stopThread(stopProgram, std::ref(stop));
    
    while(!stop){
        thread removePoints(setAllPoints, std::ref(pingHistory), std::ref(display), prevAvg, " ");
        ping = getPing();
        removePoints.join();

        if(ping == 0){
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

        if(avg != prevAvg){
            prevAvg = avg;
            updateAxis(display, avg);
        }

        jitter -= abs(pingHistory[1] - pingHistory[0]);
        pingHistory.pop_front();    // shift queue
        jitter += abs(pingHistory[49] - pingHistory[48]);

        setAllPoints(pingHistory, display, prevAvg, "*");  // replace points

        printDisplay(display);
        cout << "\nping: "   << ping <<"     "
             << "\nmin: "    << min  <<"     "
             << "\nmax: "    << max  <<"     "
             << "\navg: "    << avg  <<"     "
             << "\njitter: " << jitter/49  <<"     "
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
