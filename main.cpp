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

std::fstream& GotoLine(std::fstream& file, int num);

int main(){
    while(1){
        system("main.bat");
        std::fstream file("pings.txt");
        std::string line;
        GotoLine(file, 3);
        getline(file, line);
        cout << line << endl;
    }
}

std::fstream& GotoLine(std::fstream& file, int num){
    file.seekg(std::ios::beg);
    for(int i=0; i < num - 1; ++i){
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return file;
}