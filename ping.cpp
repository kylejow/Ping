#include "ping.h"

int systemPing(int ipLength, string& target){
    std::string line;
    const string call = "ping /n 1 /l 1 " + target + " > pings.txt";
    const char *c = call.c_str();
    system(c);
    std::fstream file("pings.txt");
    goToLine(file, 3);
    getline(file, line);
    file.close();
    
    if(line.substr(0, 5) == "Reply"){
        return getInt(line, 26+ipLength);
    }
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

void setAllPoints(std::deque<int>& pingHistory, vector<vector<string>>& display, int avg, string replace){
    for(int i = 1; i < 50; i++){
        if(pingHistory[i] == 0){
            continue;
        }
        setPoint(display, pingHistory[i], avg, i, replace);
    }
}

void setPoint(vector<vector<string>>& display, int ping, int avg, int location, string replace){
    if(ping > avg + 10){
        display[0][location] = replace;
    }else if(ping < avg - 10){
        display[20][location] = replace;
    }else{
        display[avg-ping+10][location] = replace;
    }
}

bool isIP(string line){
    for(long long unsigned int i = 0; i < line.size(); i++){
        if(!isdigit(line[i]) && line[i] != '.'){
            return false;
        }
    }
    return true;
}

int getIPLength(std::string line){
    int start = 11;
    int i = start;
    while(isdigit(line[i]) || line[i] == '.'){
        i++;
    }
    return i-start;
}

int getPolling(void){
    system("cls");
    int polling;
    cout << "Enter polling rate in milliseconds: ";
    cin >> polling;
    while(cin.fail()){
        system("cls");
        cout << "Enter polling rate in milliseconds: ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        cin >> polling;
    }
    system("cls");
    return polling;
}

vector<string> loadSaved(void){
    vector<string> savedTargets;
    std::string line, target;
    std::fstream file("saved.csv");
    getline(file, line);
    std::stringstream s(line);
    while(getline(s, target, ',')){ 
        savedTargets.push_back(target);
    }
    return savedTargets;
}

int chooseFromSaved(vector<string>& savedTargets){
    int chosen = 0;
    int numSaved = savedTargets.size();

    system("cls");
    printSavedTargets(savedTargets);
    cin >> chosen;
    while(cin.fail() || chosen < 1 || chosen > numSaved){
        system("cls");
        printSavedTargets(savedTargets);
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        cin >> chosen;
    }
    return chosen-1;
}

void printSavedTargets(vector<string>& savedTargets){
    int i = 1;
    for(auto iter = savedTargets.begin(); iter != savedTargets.end(); iter++){
        cout << i << ". " << *iter << "\n";
        i++;
    }
    cout << "\n";
}

void toCSV(vector<string>& savedTargets, string filename){
    std::string line;
    std::ofstream file(filename, std::ofstream::trunc);
    for(long long unsigned int i = 0; i < savedTargets.size(); i++){
        file << savedTargets[i] << ",";
    }
    file.close();
    return;
}
