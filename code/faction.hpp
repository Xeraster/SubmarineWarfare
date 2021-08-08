faction :: faction()
{

}

faction :: faction(vector<string> fileContents, SDL_Renderer *ren)
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
			m_description = fileContents.at(i).substr(5, fileContents.at(i).size());
		}
		else if (fileContents.at(i).substr(0,5) == "team=") 
		{
			//cout << "desc is" << fileData.at(i).substr(5, fileData.at(i).size()) << endl;
			m_team = stoi(fileContents.at(i).substr(5, fileContents.at(i).size()));
		}
		else if (fileContents.at(i).substr(0,5) == "flag=") 
		{
			//cout << "desc is" << fileData.at(i).substr(5, fileData.at(i).size()) << endl;
			m_textureName = fileContents.at(i).substr(5, fileContents.at(i).size());
		}
		else if (fileContents.at(i).substr(0,9) == "shipTier=") 
		{
			//cout << "desc is" << fileData.at(i).substr(5, fileData.at(i).size()) << endl;
			m_tier = stoi(fileContents.at(i).substr(9, fileContents.at(i).size()));
		}
		else if (fileContents.at(i).substr(0,11) == "submarines=") 
		{
			//cout << "desc is" << fileData.at(i).substr(5, fileData.at(i).size()) << endl;
			m_submarines = stringToBool(fileContents.at(i).substr(11, fileContents.at(i).size()));
		}
		i++;
	}

}

faction :: ~faction()
{
	//huh.. putting this here messes it up. Who woulda thunk
	//SDL_DestroyTexture(m_factionflag);
}

void faction :: loadTexture(SDL_Renderer *ren)
{

	string texturePath = "Textures/factions/" + m_textureName;
	cout << texturePath << endl;

	factionFlags->push_back(new textureEntry(texturePath, m_textureName,ren));
	m_factionflag = factionFlags->back()->getTexture();
}

void faction :: drawFlag(SDL_Renderer *ren, int posX, int posY)
{
	renderTexture(m_factionflag, ren, posX, posY);
}

void faction :: drawFlag(SDL_Renderer *ren, int posX, int posY, int sizeX, int sizeY)
{
	renderTextureEx(m_factionflag, ren, posX, posY, sizeX, sizeY, 0.0);
}

faction& faction :: operator=(faction& other)
{
	m_name = other.name();
	m_description = other.description();
	m_team= other.team();
	m_submarines = other.hasSubmarines();
	m_tier = other.tier();
	m_textureName = other.textureName();
	m_factionflag = other.m_factionflag;

	return *this;
}

void loadAllFactions(SDL_Renderer *ren)
{
	//make a list of all present faction file paths
	string factionPath = "Data/factions";
	vector<string> filePaths;

	for (const auto & entry : std::filesystem::directory_iterator(factionPath))
	{
		//i should really make it so that it only loads *.faction files
        std::cout << entry.path() << std::endl;
        filePaths.push_back(entry.path());
	}

	//for each encountered submarine file, load them
	for (int i = 0; i < filePaths.size(); i++)
	{
		loadFactionFile(filePaths.at(i), ren);
	}
}

void loadFactionFile(string filePath, SDL_Renderer *ren)
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
    		cout << line << endl;
    	}
	}
	itemFile.close();
	faction newFaction(linesOfFile, ren);

	//textures are loaded and pointers are set. Put this into the registry
	factionDatabase->push_back(newFaction);

	//load the texture (you have to do this step seperately)
	factionDatabase->back().loadTexture(ren);

}

faction* getFactionByName(string name)
{
	bool foundMatch = false;
	int i = 0;
	while (!foundMatch)
	{
		if (factionDatabase->at(i).name() == name)
		{
			foundMatch = true;
		}
		else
		{
			i++;
		}
	}

	return &factionDatabase->at(i);
}