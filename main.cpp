/*References
seek to line          https://stackoverflow.com/questions/5207550/in-c-is-there-a-way-to-go-to-a-specific-line-in-a-text-file
deque                 https://en.cppreference.com/w/cpp/container/deque
multithread interrupt https://stackoverflow.com/questions/41470942/stop-infinite-loop-in-different-thread
thread constructor    https://en.cppreference.com/w/cpp/thread/thread/thread
batch ping            https://docs.microsoft.com/en-us/windows-server/administration/windows-commands/ping
                      filename cannot be the same as command to be redirected
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <windows.h>
#include <thread>
#include <atomic>

#include "display.h"
#include "ping.h"

using std::cout;
using std::cin;
using std::ofstream;
using std::fstream;
using std::endl;
using std::string;
using std::vector;
using std::thread;
using std::ref;

void stopProgram(std::atomic_bool& stop);
void pauseAndExit(void);

int main(){

    int polling = 0;
    while(1){
        string input;
        string target = "NULL";
        string type;

        while(1){
            system("cls");
            cout << "1. Google (8.8.8.8)\n"
                << "2. Enter custom IP address\n"
                << "3. Enter custom hostname\n"
                << "4. Change polling rate (Default: 0)\n"
                << "\n\nq to exit\n\n";
            cin >> input;
            if(input == "1"){
                target = "8.8.8.8";
                type = "ip";
                break;
            }else if(input == "2"){
                while(!isIP(target)){
                    system("cls");
                    cout << "Enter IP address: ";
                    cin >> target;
                }
                type = "ip";
                break;
            }else if(input == "3"){
                system("cls");
                cout << "Enter Hostname: ";
                cin >> target;
                type = "hostname";
                break;
            }else if(input == "4"){
                polling = getPolling();
            }else if(input == "q"){
                system("cls");
                exit(0);
            }else{
                continue;
            }
        }

        //create bat
        ofstream createBat;
        createBat.open ("main.bat");
        createBat << "@echo off\nping /n 1 /l 1 " + target << " > pings.txt\n";
        createBat.close();

        //verify input can be pinged and set length
        string line;
        int ipLength;
        system("main.bat");
        fstream file("pings.txt");
        getline(file, line);
        if(!line.empty()){
            system("clear");
            cout << "Could not reach " << target << ".\n\n\n";
            file.close();
            pauseAndExit();
        }
        if(type == "ip"){
            goToLine(file, 3);
            getline(file, line);
            //check secondary fail occuring from invalid ip
            if(line.substr(15, 6) == "failed"){
                system("clear");
                cout << "Could not reach " << target << ".\n\n\n";
                file.close();
                pauseAndExit();
            }else{
                ipLength = target.size();
            }
        }
        if(type == "hostname"){
            goToLine(file, 3);
            getline(file, line);
            ipLength = getIPLength(line);
        }
        file.close();

        system("clear");
        setCursor(false);
        cout << std::fixed << std::setprecision(5);
        int ping, min = INT_MAX, max = INT_MIN, avg = 0, prevAvg = 0;
        long double jitter = 0, loss = 0;
        unsigned long long int sum = 0, count = 0;

        vector<vector<string>> display(21, vector<string>(50, " "));
        std::deque<int> pingHistory(50, 0);

        std::atomic_bool stop = false;
        thread stopThread(stopProgram, ref(stop));
        while(!stop){
            thread removePoints(setAllPoints, ref(pingHistory), ref(display), prevAvg, " ");
            ping = getPing(ipLength);
            removePoints.join();

            if(ping == 0){
                loss++;
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

            cout << "Pinging " << target << "\n\n";
            printDisplay(display);
            
            cout << "\nPing: "   << ping <<"     "
                << "\nMin: "    << min  <<"     "
                << "\nMax: "    << max  <<"     "
                << "\nAvg: "    << avg  <<"     "
                << "\nJitter: " << jitter/49  <<"     "
                << "\nPacket Loss: " << loss/count*100  <<"%     "
                << "\n\n\nPress Enter to exit.";

            Sleep(polling);
            clearScreen();
        }

        stopThread.join();
        system("clear");
        system("rm pings.txt");
        system("rm main.bat");
        setCursor(true);
    }
    return 0;
}

void stopProgram(std::atomic_bool& stop){
    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    cin.get();
    stop = true;
    return;
}

void pauseAndExit(void){
    system("rm pings.txt");
    system("rm main.bat");
    cout << "Press Enter to exit.";
    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    cin.get();
    system("clear");
    exit(0);
}