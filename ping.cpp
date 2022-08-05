#include "ping.h"

int getPing(void){
    std::string line;
    system("main.bat");
    std::fstream file("pings.txt");
    goToLine(file, 3);
    getline(file, line);

    if(line.substr(0, 5) == "Reply"){
        return getInt(line, 33);
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

int getInt(string line, int start){
    int i = start;
    while(isdigit(line[i])){
        i++;
    }
    return std::stoi(line.substr(start, i-start));
}

void setPoint(vector<vector<string>>& display, int ping, int avg, int location, string replace){
    if(ping > avg + 10){
        display[0][location] = replace;
    }else if(ping < avg - 10){
        display[20][location] = replace;
    }else{
        display[ping-10][location] = replace;
    }
}