//References
//clear screen    https://cplusplus.com/forum/beginner/18191/

#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>
#include <iostream>
#include <windows.h>

using std::vector;

void PrintDisplay(vector<vector<std::string>>& Display);
void Printvect(vector<int>& vect);
void ClearScreen();

#endif