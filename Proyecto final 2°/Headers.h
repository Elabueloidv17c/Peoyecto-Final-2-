#pragma once
#include <windows.h>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <time.h>

using namespace std;

bool Exist(string words, vector <string> paths);
void Eraser(string word, vector <string> &inventory);
