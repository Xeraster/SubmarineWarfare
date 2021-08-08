void loadSettingsFile(string filePath)
{
	//load the contents of the provided file into ram
	ifstream itemFile(filePath);
	vector<string> linesOfFile;

	string line;
	while (getline(itemFile, line))
	{
		istringstream iss(line);
		if (line.at(0) != '#')
		{
    		linesOfFile.push_back(line);
    		//cout << line << endl;
    	}
	}
	itemFile.close();

	int i = 0;
	while (i < linesOfFile.size())
	{
		if (linesOfFile.at(i).substr(0,8) == "screenx=") 
		{
			gscreenx = stoi(linesOfFile.at(i).substr(8, linesOfFile.at(i).size()));
			if (gscreenx < minResX) 
			{
				gscreenx = minResX;
				cout << "screen resolution x was set either too low or invalid. Setting to lowest allowable value of " << minResX << endl;
			}
		}
		else if (linesOfFile.at(i).substr(0,8) == "screeny=") 
		{
			gscreeny = stoi(linesOfFile.at(i).substr(8, linesOfFile.at(i).size()));
			if (gscreeny < minResY) 
			{
				gscreeny = minResY;
				cout << "screen resolution y was set either too low or invalid. Setting to lowest allowable value of " << minResY << endl;
			}
		}
		else if (linesOfFile.at(i).substr(0,12) == "menuquality=") 
		{
			menu_quality = stoi(linesOfFile.at(i).substr(12, linesOfFile.at(i).size()));
		}
		else if (linesOfFile.at(i).substr(0,10) == "3dquality=") 
		{
			graphics_quality = stoi(linesOfFile.at(i).substr(10, linesOfFile.at(i).size()));
		}

		i++;
	}

	return void();
}