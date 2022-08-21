#include "ping.h"

int getPing(int ipLength){
    std::string line;
    system("main.bat");
    std::fstream file("pings.txt");
    goToLine(file, 3);
    getline(file, line);

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