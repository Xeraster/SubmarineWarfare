award :: award()
{

}

award :: award(vector<string> fileData, SDL_Renderer *ren)
{
	//loop through the file contents
	int i = 0;
	while (i < fileData.size())
	{
		if (fileData.at(i).substr(0,5) == "name=") 
		{
			//cout << "name is" << fileData.at(i).substr(5, fileData.at(i).size()) << endl;
			m_name = fileData.at(i).substr(5, fileData.at(i).size());
		}
		else if (fileData.at(i).substr(0,5) == "desc=") 
		{
			//cout << "desc is" << fileData.at(i).substr(5, fileData.at(i).size()) << endl;
			m_description = fileData.at(i).substr(5, fileData.at(i).size());
		}
		else if (fileData.at(i).substr(0,8) == "texture=") 
		{
			//cout << "texture is" << fileData.at(i).substr(8, fileData.at(i).size()) << endl;
			//specify image file name
			string textureName = fileData.at(i).substr(8, fileData.at(i).size());

			//specify texture folder path
			string textureFolder = "Textures/Awards/" + textureName;

			//load the small texture. avoid having the computer resize on draw which is expensive
			awardIcons->push_back(new textureEntry(textureFolder, textureName, ren));
			//set the qualification texture pointer to the value of the thing we just loaded
			m_icon = awardIcons->back()->getTexture();
		}
		else if (fileData.at(i).substr(0,12) == "conditionId=") 
		{
			//cout << "type is" << fileData.at(i).substr(21, fileData.at(i).size()) << endl;
			m_type = stoi(fileData.at(i).substr(12, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,16) == "conditionAmount=") 
		{
			//cout << "type is" << fileData.at(i).substr(21, fileData.at(i).size()) << endl;
			m_amount = stoi(fileData.at(i).substr(16, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,13) == "playerIssued=") 
		{
			//cout << "type is" << fileData.at(i).substr(21, fileData.at(i).size()) << endl;
			m_playerIssued = stringToBool(fileData.at(i).substr(13, fileData.at(i).size()));
		}
		//cout << fileData.at(i) << endl;
		i++;
	}

	bool m_dragging = 0;
	bool m_canClick = 0;
}

void award :: draw(SDL_Renderer *ren, int posX, int posY, int sizeX, int sizeY)
{
	renderTextureEx(m_icon, ren, posX, posY, sizeX, sizeY, 0);
}

void award :: drawDraggable(SDL_Renderer *ren, int posX, int posY, int sizeX, int sizeY, int mouseX, int mouseY, Uint32 lastMouse, award **selectedAward)
{
	if (mouseX > posX && mouseX < posX + sizeX && mouseY > posY && mouseY < posY + sizeY && lastMouse == SDL_BUTTON(SDL_BUTTON_LEFT) && m_canClick)
	{
		m_dragging = true;
	}

	if (mouseX > posX && mouseX < posX + sizeX && mouseY > posY && mouseY < posY + sizeY && lastMouse != SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		m_canClick = true;
	}
	else
	{
		m_canClick = false;
	}

	if (m_dragging && lastMouse == SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		posX = mouseX - (sizeX / 2);
		posY = mouseY - (sizeY / 2);
		*selectedAward = this;
	}
	else if (m_dragging && lastMouse != SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		m_dragging = false;
		m_canClick = false;
	}

	renderTextureEx(m_icon, ren, posX, posY, sizeX, sizeY, 0);
}

award& award :: operator=(const award& other)
{
	m_name = other.name();
	m_description = other.desc();
	m_type = other.type();
	m_amount = other.amount();
	m_playerIssued = other.playerIssued();

	m_icon = other.tex();
}

int loadAwardFile(string filePath, SDL_Renderer *ren)
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
	//now that the contents of the file have been loaded into ram, make a new submarine object
	//the submarine's vector<string> constructor deals with the parsing
	award newAward(linesOfFile, ren);

	//textures are loaded and pointers are set. Put this into the registry
	awardRegistry->push_back(newAward);

	return 0;
}

int loadAllAwards(SDL_Renderer *ren)
{
	//make a list of all present qualification file paths
	string qualificationPath = "Data/awards";
	vector<string> filePaths;

	for (const auto & entry : std::filesystem::directory_iterator(qualificationPath))
	{
        std::cout << entry.path() << std::endl;
        filePaths.push_back(entry.path());
	}

	//for each encountered qualification file, load them
	for (int i = 0; i < filePaths.size(); i++)
	{
		loadAwardFile(filePaths.at(i), ren);
	}

	return 0;
}

void getAwardsOfType(int type, vector<award*> *awardArray)
{
	for (int i = 0; i < awardRegistry->size(); i++)
	{
		if (awardRegistry->at(i).type() == type)
		{
			awardArray->push_back(&awardRegistry->at(i));
		}
	}
}

award* getAwardByName(string name)
{
	for (int i = 0; i < awardRegistry->size(); i++)
	{
		if (awardRegistry->at(i).name() == name)
		{
			//i = awardRegistry->size() + 1;
			return &awardRegistry->at(i);
		}
	}

	return nullptr;
}