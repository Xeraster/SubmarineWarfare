campaign :: campaign()
{

}

campaign :: campaign(vector<string> fileContents)
{
	int i = 0;
	while (i < fileContents.size())
	{
		if (fileContents.at(i).substr(0,5) == "name=") 
		{
			//cout << "name is" << fileData.at(i).substr(5, fileData.at(i).size()) << endl;
			m_name = fileContents.at(i).substr(5, fileContents.at(i).size());
		}
		else if (fileContents.at(i).substr(0,5) == "desc=") 
		{
			//cout << "desc is" << fileData.at(i).substr(5, fileData.at(i).size()) << endl;
			m_desc = fileContents.at(i).substr(5, fileContents.at(i).size());
		}
		else if (fileContents.at(i).substr(0,6) == "money=") 
		{
			//cout << "desc is" << fileData.at(i).substr(5, fileData.at(i).size()) << endl;
			m_funds = stod(fileContents.at(i).substr(6, fileContents.at(i).size()));
		}
		else if (fileContents.at(i).substr(0,8) == "payrate=") 
		{
			//cout << "desc is" << fileData.at(i).substr(5, fileData.at(i).size()) << endl;
			m_payRate = stod(fileContents.at(i).substr(8, fileContents.at(i).size()));
		}
		else if (fileContents.at(i).substr(0,13) == "startingrank=") 
		{
			//cout << "desc is" << fileData.at(i).substr(5, fileData.at(i).size()) << endl;
			m_startingRank = stoi(fileContents.at(i).substr(13, fileContents.at(i).size()));
		}
		else if (fileContents.at(i).substr(0,10) == "submarine=") 
		{
			//cout << "desc is" << fileData.at(i).substr(5, fileData.at(i).size()) << endl;
			string submarine = fileContents.at(i).substr(10, fileContents.at(i).size());
			m_startSubmarine = getSubmarineByName(submarine);
		}
		else if (fileContents.at(i).substr(0,8) == "faction=") 
		{
			//cout << "desc is" << fileData.at(i).substr(5, fileData.at(i).size()) << endl;
			string factionString = fileContents.at(i).substr(8, fileContents.at(i).size());
			m_faction = getFactionByName(factionString);
		}
		i++;
	}
}

void campaign :: drawInfoCard(SDL_Renderer *ren, int posX, int posY)
{
	//the text on this thingy is dependent on y size not x size
	int txtSize = 8 * gscreeny / 600;

	color darkBlack(0,0,0,100);
	color white(255,255,255,255);
	drawRectFilled(ren, darkBlack, posX, posY, 420 * gscreenx / 800, 300 * gscreeny / 600);
	drawText(ren, txtSize, white, "faction: " + m_faction->name(), posX + 5, posY + 5);
	renderTextureEx(m_faction->m_factionflag, ren, posX + 250, posY, 64, 32, 0);
	drawText(ren, txtSize, white, "starting funds: $" + to_string(m_funds).substr(0, to_string(m_funds).size() - 4), posX + 5, posY + getTextYSize(txtSize));
	drawText(ren, txtSize, white, "payrate: $" + to_string(m_payRate).substr(0, to_string(m_payRate).size() - 4) + " / ton", posX + 5, posY + (2*getTextYSize(txtSize)));
	drawText(ren, txtSize, white, "starting submarine: " + m_startSubmarine->name(), posX + 5, posY + (3*getTextYSize(txtSize)));
	renderTexture(m_startSubmarine->getSmallIcon(), ren, (posX + 5), (posY + (4*getTextYSize(txtSize))));
	//drawText(ren, 8, white, "description: " + m_desc, posX + 5, posY + 175);
	drawTextWrapped(ren, txtSize, white, "description: " + m_desc, (posX + 5), posY + 6*getTextYSize(txtSize), 400 * gscreenx / 800);
}

campaign& campaign :: operator=(campaign& other)
{
	m_name = other.getName();
	m_desc = other.getDesc();
	m_faction = other.getFaction();
	m_funds = other.getFunds();
	m_payRate = other.payRate();
	m_startingRank = other.startingRank();
	m_startSubmarine = other.startSub();

	return *this;
}

void loadCampaignFile(string filePath)
{
	//load the contents of the provides file into ram
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
	campaign newCampaign(linesOfFile);

	//variable are initialized and pointers are set. Put this into the registry
	campaignDatabase->push_back(newCampaign);

}

void loadAllCampaigns()
{
	//make a list of all present faction file paths
	string factionPath = "Data/campaigns";
	vector<string> filePaths;

	for (const auto & entry : std::filesystem::directory_iterator(factionPath))
	{
		//i should really make it so that it only loads *.faction files
		string poop = entry.path();
		//std::cout << poop.substr(poop.size() - 9, poop.size()) << std::endl;
		if (poop.substr(poop.size() - 9, poop.size()) == ".campaign")
		{
			std::cout << entry.path() << std::endl;
        	filePaths.push_back(entry.path());
		}
	}

	//for each encountered submarine file, load them
	for (int i = 0; i < filePaths.size(); i++)
	{
		loadCampaignFile(filePaths.at(i));
	}
}

campaign* getCampaignByName(string name)
{
	bool foundMatch = false;
	int i = 0;
	while (!foundMatch)
	{
		if (campaignDatabase->at(i).getName() == name)
		{
			foundMatch = true;
		}
		else
		{
			i++;
		}
	}

	return &campaignDatabase->at(i);
}

int getCampaignIndexByName(string name)
{
	bool foundMatch = false;
	int i = 0;
	while (!foundMatch)
	{
		if (campaignDatabase->at(i).getName() == name)
		{
			foundMatch = true;
		}
		else
		{
			i++;
		}
	}

	return i;
}