#ifndef CREWNAMEGENERATOR_H
#define CREWNAMEGENERATOR_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>
using namespace std;
//I know this is called crewNameGenerator but guess what? it generated ship names too
uint32_t betterRand(uint32_t seed);

class crewNameGenerator
{
public:
	crewNameGenerator();

	~crewNameGenerator();

	string randomName(int gender);

	string randomName(int gender, uint32_t seed);

	string randomLastName();

	string randomLastName(uint32_t seed);

	string randomShipName(uint32_t seed = 0);

protected:
	//string *feminineNames;
	//string *masculineNames;
	//string *lastNames;
	vector<string> *feminineNames;
	vector<string> *masculineNames;
	vector<string> *lastNames;

	//ship names stuff
	vector<string> *importantNames;
	vector<string> *shipNouns;
	vector<string> *shipAdjectives;

};

#include "randomFunctions.h"
#include "crewNameGenerator.hpp"

#endif