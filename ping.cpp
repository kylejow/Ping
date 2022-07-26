#include "ping.h"

int systemPing(const char* c, int ipLength){
    std::string line;
    system(c);
    std::fstream file("pings.txt");
    goToLine(file, 3);
    getline(file, line);
    file.close();
    
    if(line.substr(0, 5) == "Reply"){
        return getInt(line, 26+ipLength);
    }
    return -1;
}

std::fstream& goToLine(std::fstream& file, int num){
    file.seekg(std::ios::beg);
    for(int i=0; i < num - 1; ++i){
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return file;
}

int getInt(string& line, int start){
    int i = start;
    while(isdigit(line[i])){
        i++;
    }
    return std::stoi(line.substr(start, i-start));
}

void setAllPoints(std::deque<int>& pingHistory, vector<vector<string>>& display, int avg, string replace){
    for(int i = 1; i < 50; i++){
        if(pingHistory[i] == -1){
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

bool isIP(string& line){
    for(long long unsigned int i = 0; i < line.size(); i++){
        if(!isdigit(line[i]) && line[i] != '.'){
            return false;
        }
    }
    return true;
}

int getIPLength(string& line){
    int start = 11;
    int i = start;
    while(isdigit(line[i]) || line[i] == '.'){
        i++;
    }
    return i-start;
}

int getIntInput(string& prompt){
    system("cls");
    int i;
    cout << prompt;
    cin >> i;
    while(cin.fail()){
        system("cls");
        cout << prompt;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        cin >> i;
    }
    system("cls");
    return i;
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

void toCSV(vector<string>& savedTargets, string& filename){
    std::string line;
    std::ofstream file(filename, std::ofstream::trunc);
    for(long long unsigned int i = 0; i < savedTargets.size(); i++){
        file << savedTargets[i] << ",";
    }
    file.close();
    return;
}

bool noSavedTargets(vector<string>& savedTargets){
    if(savedTargets.size() == 0){
        system("cls");
        cout << "No saved targets\n\n\n";
        system("pause");
        return true;
    }
    return false;
}