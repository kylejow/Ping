//References
//clear screen    https://cplusplus.com/forum/beginner/18191/

#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>
#include <iostream>
#include <windows.h>

using std::vector;

void printDisplay(vector<vector<std::string>>& Display);
void printVect(vector<int>& vect);
void clearScreen();
void updateAxis(vector<vector<std::string>>& Display, int avg);

#endif