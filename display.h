//References
//clear screen    https://cplusplus.com/forum/beginner/18191/
//set cursor      https://www.codegrepper.com/code-examples/cpp/c%2B%2B+hide+cursor+in+console

#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>
#include <iostream>
#include <windows.h>

using std::vector;

void printDisplay(vector<vector<std::string>>& display);
void printVect(vector<int>& vect);
void clearScreen();
void updateAxis(vector<vector<std::string>>& display, int avg);
void setCursor(bool visible);

#endif