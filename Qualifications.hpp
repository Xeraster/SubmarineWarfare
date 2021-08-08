qualification :: qualification()
{

}

qualification :: qualification(vector<string> fileData, SDL_Renderer *ren)
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
			string textureFolder = "Textures/Qualifications/" + textureName;

			//load the small texture. avoid having the computer resize on draw which is expensive
			qualificationIcons->push_back(new textureEntry(textureFolder, textureName, ren));
			//set the qualification texture pointer to the value of the thing we just loaded
			m_icon = qualificationIcons->back()->getTexture();
		}
		else if (fileData.at(i).substr(0,21) == "relevant_compartment=") 
		{
			//cout << "type is" << fileData.at(i).substr(21, fileData.at(i).size()) << endl;
			m_type = stoi(fileData.at(i).substr(21, fileData.at(i).size()));
		}
		//cout << fileData.at(i) << endl;
		i++;
	}

	m_dragging = false;
	m_canClick = false;;
}

void qualification :: draw(SDL_Renderer *ren, int posX, int posY, int sizeX, int sizeY)
{
	renderTextureEx(m_icon, ren, posX, posY, sizeX, sizeY, 0);
}

void qualification :: drawDraggable(SDL_Renderer *ren, int posX, int posY, int sizeX, int sizeY, int mouseX, int mouseY, Uint32 lastMouse, qualification **selectedQual)
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
		*selectedQual = this;
	}
	else if (m_dragging && lastMouse != SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		m_dragging = false;
		m_canClick = false;
	}

	renderTextureEx(m_icon, ren, posX, posY, sizeX, sizeY, 0);
}

qualification& qualification :: operator=(const qualification& other)
{
	m_name = other.name();
	m_description = other.desc();
	m_type = other.type();
	m_icon = other.tex();
}

int loadQualificationFile(string filePath, SDL_Renderer *ren)
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
	qualification newQual(linesOfFile, ren);

	//textures are loaded and pointers are set. Put this into the registry
	qualificationRegistry->push_back(newQual);

	return 0;
}

int loadAllQualifications(SDL_Renderer *ren)
{
	//make a list of all present qualification file paths
	string qualificationPath = "Data/qualifications";
	vector<string> filePaths;

	for (const auto & entry : std::filesystem::directory_iterator(qualificationPath))
	{
        std::cout << entry.path() << std::endl;
        filePaths.push_back(entry.path());
	}

	//for each encountered qualification file, load them
	for (int i = 0; i < filePaths.size(); i++)
	{
		loadQualificationFile(filePaths.at(i), ren);
	}

	return 0;
}

qualification* getQualificationById(int qualId)
{
	int i = 0;
	bool foundMatch = false;
	while (i < qualificationRegistry->size() && !foundMatch)
	{
		if (qualificationRegistry->at(i).type() == qualId)
		{
			foundMatch = true;
		}
		else
		{
			i++;
		}
		
	}

	if (foundMatch)
	{
		return &qualificationRegistry->at(i);
	}
	else
	{
		return nullptr;
	}
}