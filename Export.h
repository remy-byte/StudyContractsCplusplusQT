#pragma once
#include "contract.h"
#include "repository_contract.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::endl;
//Exports the list of products in a .csv file
void exportToCSV(string fileName, const vector <Contract>& all);