crewNameGenerator :: crewNameGenerator()
{	
	//initialize the vectors that will contain the lists of names
	feminineNames = new vector<string>;
	masculineNames = new vector<string>;
	lastNames = new vector<string>;

	importantNames = new vector<string>;
	shipNouns = new vector<string>;
	shipAdjectives = new vector<string>;

	//load the file containing female names
	ifstream femaleNamesFile("Data/names/feminine_names.txt");

	string line;
	while (getline(femaleNamesFile, line))
	{
    	istringstream iss(line);
    	feminineNames->push_back(line);
	}
	femaleNamesFile.close();

	//load the file containing male names
	ifstream maleNamesFile("Data/names/masculine_names.txt");
	
	while (getline(maleNamesFile, line))
	{
    	istringstream iss(line);
    	masculineNames->push_back(line);
	}
	maleNamesFile.close();

	//load the file containing lastnames
	ifstream lastNamesFile("Data/names/lastnames.txt");
	
	while (getline(lastNamesFile, line))
	{
    	istringstream iss(line);
    	lastNames->push_back(line);
	}
	lastNamesFile.close();

	//ship name generator stuff below this line

	//load the file containing names of famous people
	ifstream importantNamesFile("Data/names/shipname/people.txt");
	
	while (getline(importantNamesFile, line))
	{
    	istringstream iss(line);
    	importantNames->push_back(line);
	}
	importantNamesFile.close();

	//load the file containing nouns
	ifstream nounsFile("Data/names/shipname/nouns.txt");
	
	while (getline(nounsFile, line))
	{
    	istringstream iss(line);
    	shipNouns->push_back(line);
	}

	nounsFile.close();

	//load the file containing adjectives
	ifstream adjectivesFile("Data/names/shipname/adjectives.txt");
	
	while (getline(adjectivesFile, line))
	{
    	istringstream iss(line);
    	shipAdjectives->push_back(line);
	}

	adjectivesFile.close();

	//this works seems to work well.. to well. That's suspicious.

}

crewNameGenerator :: ~crewNameGenerator()
{
	delete[] feminineNames;
	delete[] masculineNames;
	delete[] lastNames;

	delete[] importantNames;
	delete[] shipNouns;
	delete[] shipAdjectives;
}

string crewNameGenerator :: randomName(int gender)
{

	int MaxRandValue = 2;
	if (gender == 1)
	{
		MaxRandValue = masculineNames->size();
		return masculineNames->at(rand() % MaxRandValue);
	}
	else
	{
		MaxRandValue = feminineNames->size();
		return feminineNames->at(rand() % MaxRandValue);
	}
}

string crewNameGenerator :: randomName(int gender, uint32_t seed)
{
	int MaxRandValue = 2;
	if (gender == 1)
	{
		MaxRandValue = masculineNames->size();
		return masculineNames->at(betterRand(seed) % MaxRandValue);
	}
	else
	{
		MaxRandValue = feminineNames->size();
		return feminineNames->at(betterRand(seed) % MaxRandValue);
	}
}

string crewNameGenerator :: randomLastName()
{
	int MaxRandValue = 2;
	MaxRandValue = lastNames->size();
	return lastNames->at(rand() % MaxRandValue);
}

string crewNameGenerator :: randomLastName(uint32_t seed)
{
	int MaxRandValue = 2;
	MaxRandValue = lastNames->size();
	return lastNames->at(betterRand(seed + 1) % MaxRandValue);
}

string crewNameGenerator :: randomShipName(uint32_t seed)
{
	int newSeed;
	string newName;
	string part1 = "";
	string part2 = "";
	string part3 = "";

	if (seed == 0) newSeed = rand() % 10000;

	int importantMaxValue = importantNames->size();
	int nounMaxValue = shipNouns->size();
	int adjectiveMaxValue = shipAdjectives->size();

	//dedice if name should be prefixed with the, a proper name or nothing
	int num1 = betterRand(newSeed + 6) % 100;
	if (num1 > 66) part1 = (importantNames->at(betterRand(newSeed + 69) % importantMaxValue)) + "'s ";
	else if (num1 > 33) part1 = "The ";

	//decide if name should contain an adjective or not
	int num2 = betterRand(newSeed + 7) % 100;
	if (num2 > 75) part2 = (shipAdjectives->at(betterRand(newSeed + 723) % adjectiveMaxValue)) + " ";

	//now, generate the random noun to slap on
	part3 = shipNouns->at(betterRand(newSeed + 425) % nounMaxValue);

	capitalizeFirstLetter(part1);
	capitalizeFirstLetter(part2);
	capitalizeFirstLetter(part3);

	newName = part1 + part2 + part3;

	return newName;

}