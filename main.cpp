/*References
seek to line    https://stackoverflow.com/questions/5207550/in-c-is-there-a-way-to-go-to-a-specific-line-in-a-text-file
*/

#include <iostream>
#include <limits>
#include <stdio.h>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::string;

std::fstream& goToLine(std::fstream& file, int num);
int getPing(string line);

int main(){
    std::string line;
    int ping;
    while(1){
        system("main.bat");
        std::fstream file("pings.txt");
        goToLine(file, 3);
        getline(file, line);

        // if(line.substr(0, 7) == "Request"){
        //     exit(0);
        // }

        if(line.substr(0, 5) == "Reply"){
            ping = getPing(line);
        }
        cout << ping << endl;
    }
}

std::fstream& goToLine(std::fstream& file, int num){
    file.seekg(std::ios::beg);
    for(int i=0; i < num - 1; ++i){
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return file;
}

int getPing(string line){
    int i = 33;
    while(isdigit(line[i])){
        i++;
    }
    return std::stoi(line.substr(33, i-33));
}