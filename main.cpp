/*References
seek to line          https://stackoverflow.com/questions/5207550/in-c-is-there-a-way-to-go-to-a-specific-line-in-a-text-file
deque                 https://en.cppreference.com/w/cpp/container/deque
multithread interrupt https://stackoverflow.com/questions/41470942/stop-infinite-loop-in-different-thread
thread constructor    https://en.cppreference.com/w/cpp/thread/thread/thread
batch ping            https://docs.microsoft.com/en-us/windows-server/administration/windows-commands/ping
                      filename cannot be the same as command to be redirected
overwrite file        https://cplusplus.com/forum/beginner/195138/
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
void reachFailure(string target);

int main(){
    int polling = 0;
    vector<string> savedTargets = loadSaved();

    while(1){
        string input;
        string target = "NULL";
        string type;

        while(1){
            system("cls");
            cout << "1. Ping Google (8.8.8.8)\n"
                 << "2. Ping custom IP address or Hostname\n"
                 << "3. View saved targets\n"
                 << "4. Ping from saved targets\n"
                 << "5. Add saved target\n"
                 << "6. Delete saved target\n"
                 << "7. Change polling rate (Current: " << polling << "ms)\n"
                 << "\n\nq to exit\n\n";
            cin >> input;
            if(input == "1"){
                target = "8.8.8.8";
                type = "ip";
                break;
            }else if(input == "2"){
                system("cls");
                cout << "Ping custom IP address or Hostname: ";
                cin >> target;
                break;
            }else if(input == "3"){
                if(savedTargets.size() == 0){
                    system("cls");
                    cout << "No saved targets\n\n\n";
                    system("pause");
                    continue;
                }
                system("cls");
                printSavedTargets(savedTargets);
                system("pause");
                continue;
            }else if(input == "4"){
                if(savedTargets.size() == 0){
                    system("cls");
                    cout << "No saved targets\n\n\n";
                    system("pause");
                    continue;
                }
                target = savedTargets[chooseFromSaved(savedTargets)];
                break;
            }else if(input == "5"){
                system("cls");
                string addToSaved;
                cout << "Save custom IP address or Hostname: ";
                cin >> addToSaved;
                savedTargets.push_back(addToSaved);
                toCSV(savedTargets, "saved.csv");
            }else if(input == "6"){
                if(savedTargets.size() == 0){
                    system("cls");
                    cout << "No saved targets\n\n\n";
                    system("pause");
                    continue;
                }
                savedTargets.erase(savedTargets.begin() + chooseFromSaved(savedTargets));
                toCSV(savedTargets, "saved.csv");
            }else if(input == "7"){
                polling = getPolling();
            }else if(input == "q"){
                system("cls");
                exit(0);
            }else{
                continue;
            }
        }

        if(isIP(target)){
            type = "ip";
        }else{
            type = "hostname";
        }

        //verify input can be pinged and set length
        string line;
        int ipLength;
        const string call = "ping /n 1 /l 1 " + target + " > pings.txt";
        const char *c = call.c_str();
        system(c);
        fstream file("pings.txt");
        getline(file, line);
        if(!line.empty()){
            file.close();
            reachFailure(target);
            continue;
        }
        if(type == "ip"){
            goToLine(file, 3);
            getline(file, line);
            //check secondary fail occuring from invalid ip
            if(line.substr(15, 6) == "failed"){
                file.close();
                reachFailure(target);
                continue;
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
            ping = systemPing(ipLength, target);
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

void reachFailure(string target){
    system("rm pings.txt");
    system("clear");
    cout << "Could not reach " << target << ".\n\n\n";
    system("pause");
}
