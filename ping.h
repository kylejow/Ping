#ifndef PING_H
#define PING_H

#include <vector>
#include <string>
#include <limits>
#include <fstream>

using std::vector;
using std::string;

int getPing();
std::fstream& goToLine(std::fstream& file, int num);
int getInt(string line, int start);
void setPoint(vector<vector<string>>& display, int ping, int avg, int location, string replace);

#endif