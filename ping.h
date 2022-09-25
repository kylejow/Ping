#ifndef PING_H
#define PING_H

#include <vector>
#include <string>
#include <limits>
#include <fstream>
#include <deque>
#include <iostream>
#include <sstream>

using std::vector;
using std::string;
using std::cout;
using std::cin;

int systemPing(int ipLength, string& timeout, string& target);
std::fstream& goToLine(std::fstream& file, int num);
int getInt(string& line, int start);
void setAllPoints(std::deque<int>& pingHistory, vector<vector<std::string>>& display, int avg, string replace);
void setPoint(vector<vector<string>>& display, int ping, int avg, int location, string replace);
bool isIP(string& line);
int getIPLength(std::string& line);
int getIntInput(string& prompt);
vector<string> loadSaved(void);
int chooseFromSaved(vector<string>& savedTargets);
void printSavedTargets(vector<string>& savedTargets);
void toCSV(vector<string>& savedTargets, string& filename);
bool noSavedTargets(vector<string>& savedTargets);

#endif