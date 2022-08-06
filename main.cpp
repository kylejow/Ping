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

unsigned long long int getPingCount();

int main(){
    setCursor(false);
    std::string line;
    int ping, min = INT_MAX, max = INT_MIN, avg = 0, prevAvg = 0;
    unsigned long long int sum = 0;
    system("clear");

    vector<vector<string>> display(21, vector<string>(30, " "));
    std::deque<int> pingHistory(30, 0);
    unsigned long long int pingCount = getPingCount();

    unsigned long long int count = 0;
    while(count < pingCount){
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

        if(avg != prevAvg){
            prevAvg = avg;
            updateAxis(display, avg);
        }

        for(int i = 1; i < 30; i++){    // remove previous points
            setPoint(display, pingHistory[i], avg, i, " ");
        }
        pingHistory.pop_front();    // shift queue
        for(int i = 1; i < 30; i++){    // replace points
            setPoint(display, pingHistory[i], avg, i, "*");
        }

        printDisplay(display);
        cout << "\nping: " << ping << "\nmin: " << min << "\nmax: " << max << "\navg: " << avg;
        clearScreen();
    }
    system("clear");
    setCursor(true);
    return 0;
}

unsigned long long int getPingCount(){
    unsigned long long int numPings;
    system("cls");
    cout << "Number of pings: ";
    cin >> numPings;
    while(cin.fail()){
        system("cls");
        cout << "Number of pings: ";
        cin.clear();
        cin.ignore(256,'\n');
        cin >> numPings;
    }
    system("cls");
    return numPings;
}