#ifndef PING_H
#define PING_H

#include <vector>
#include <string>
#include <limits>
#include <fstream>
#include <deque>
#include <iostream>

using std::vector;
using std::string;
using std::cout;
using std::cin;

int getPing(int ipLength);
std::fstream& goToLine(std::fstream& file, int num);
int getInt(string line, int start);
void setAllPoints(std::deque<int>& pingHistory, vector<vector<std::string>>& display, int avg, string replace);
void setPoint(vector<vector<string>>& display, int ping, int avg, int location, string replace);
bool isIP(string line);
int getIPLength(std::string line);
int getPolling(void);

#endif