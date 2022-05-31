torpedo :: torpedo()
{
	m_markedForDeletion = false;
	m_selected = false;
	m_mouseOver = false;
	button temp("purchase", color(255,255,255), 0, 0, 8);
	purchaseButton = temp;
}

torpedo :: torpedo(vector<string> fileData)
{
	int i = 0;

	while (i < fileData.size())
	{
		if (fileData.at(i).substr(0,5) == "name=") 
		{
			m_name = fileData.at(i).substr(5, fileData.at(i).size());
		}
		else if (fileData.at(i).substr(0,5) == "desc=") 
		{
			m_description = fileData.at(i).substr(5, fileData.at(i).size());
		}
		else if (fileData.at(i).substr(0,15) == "texture_folder=") 
		{
			m_textureFolder = fileData.at(i).substr(15, fileData.at(i).size());
		}
		else if (fileData.at(i).substr(0,9) == "mesh_low=") 
		{
			m_mesh_low = fileData.at(i).substr(9, fileData.at(i).size());
		}
		else if (fileData.at(i).substr(0,10) == "mesh_high=") 
		{
			m_mesh_high = fileData.at(i).substr(10, fileData.at(i).size());
		}
		else if (fileData.at(i).substr(0,7) == "speed1=") 
		{
			m_speed1 = stoi(fileData.at(i).substr(7, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,7) == "speed2=") 
		{
			m_speed2 = stoi(fileData.at(i).substr(7, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,7) == "speed3=") 
		{
			m_speed3 = stoi(fileData.at(i).substr(7, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,7) == "range1=") 
		{
			m_range1 = stoi(fileData.at(i).substr(7, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,7) == "range2=") 
		{
			m_range2 = stoi(fileData.at(i).substr(7, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,7) == "range3=") 
		{
			m_range3 = stoi(fileData.at(i).substr(7, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,21) == "warheadTNTequivalent=") 
		{
			m_warheadpower = stod(fileData.at(i).substr(21, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,9) == "guidance=") 
		{
			m_guidance = stoi(fileData.at(i).substr(9, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,16) == "controlsurfaces=") 
		{
			m_controlSurfaces = stoi(fileData.at(i).substr(16, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,11) == "crushdepth=") 
		{
			m_crushdepth = stoi(fileData.at(i).substr(11, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,10) == "turnspeed=") 
		{
			m_turnspeed = stod(fileData.at(i).substr(10, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,5) == "cost=") 
		{
			m_cost = stod(fileData.at(i).substr(5, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,9) == "magnetic=") 
		{
			m_magnetic = stringToBool(fileData.at(i).substr(9, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,14) == "range_explode=") 
		{
			m_rangeExplode = stringToBool(fileData.at(i).substr(14, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,14) == "max_gyroangle=") 
		{
			m_maxGyroangle = stod(fileData.at(i).substr(14, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,9) == "loudness=") 
		{
			m_loudness = stod(fileData.at(i).substr(9, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,13) == "server_alert=") 
		{
			m_serverAlert = stringToBool(fileData.at(i).substr(13, fileData.at(i).size()));
		}

		else if (fileData.at(i).substr(0,13) == "arming_range=") 
		{
			m_armingRange = stoi(fileData.at(i).substr(13, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,5) == "type=") 
		{
			m_type = stoi(fileData.at(i).substr(5, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,9) == "has_wire=") 
		{
			m_serverAlert = stringToBool(fileData.at(i).substr(9, fileData.at(i).size()));
		}

		i++;
	}

	m_selected = false;
	m_mouseOver = false;
	m_markedForDeletion = false;

	int textSize = 8 * gscreenx / 800;
	button temp("purchase", color(255,255,255), 0, 0, textSize);
	temp.setBackgroundColor(color(20,20,20,100));
	temp.setBorder(true);
	purchaseButton = temp;
}

int torpedo :: largestSpeed()
{
	int spd = 0;
	if (m_speed1 > spd) spd = m_speed1;
	if (m_speed2 > spd) spd = m_speed2;
	if (m_speed3 > spd) spd = m_speed3;

	return spd;
}

int torpedo :: largestRange()
{
	int range = 0;
	if (m_range1 > range) range = m_range1;
	if (m_range2 > range) range = m_range2;
	if (m_range3 > range) range = m_range3;

	return range;
}

//loads the torpedo's textures
int torpedo :: loadTorpedoTextures(SDL_Renderer *ren)
{
	string textureFolder = "Textures/Torpedos/" + m_textureFolder + "/";

	//load the gui icon.
	torpedoSprites->push_back(new textureEntry(textureFolder + "gui_icon.bmp", m_textureFolder + ".gui_icon",ren));
	m_icon = torpedoSprites->back()->getTexture();

	cout << "loaded " << textureFolder << endl;

	return 0;
}

torpedo* torpedo :: drawPurchaseInfoCard(SDL_Renderer *ren, int posX, int posY, int sizeX, int sizeY, int mouseX, int mouseY, Uint32 lastMouse)
{
	int font_size = 8 * static_cast<double>(sizeX) / static_cast<double>(200);
	int texSizeX;
	int texSizeY;
	SDL_QueryTexture(m_icon, NULL, NULL, &texSizeX, &texSizeY);
	//what x has to be multiplied by to fit in the given size
	double texMultiplier = static_cast<double>(sizeX) / static_cast<double>(texSizeX);

	int posYWhereTextShouldStart = posY + (texSizeY * texMultiplier);

	color cardBackground(20,20,20,100);
	color white(255,255,255,255);
	drawRectFilled(ren, cardBackground, posX, posY, sizeX, posYWhereTextShouldStart + (getTextYSize(font_size)*5) - posY);
	renderTextureEx(m_icon, ren, posX, posY, sizeX, texSizeY * texMultiplier, 0);

	drawTextWrapped(ren, font_size, white, m_name, posX, posYWhereTextShouldStart, 3 * sizeX / 5);
	drawText(ren, font_size, white, "cost: " + doubleToMoney(m_cost), posX, posYWhereTextShouldStart + (getTextYSize(font_size)*2));
	drawText(ren, font_size, white, "max speed: " + to_string(largestSpeed()) + "kts", posX, posYWhereTextShouldStart + (getTextYSize(font_size)*3));
	//drawText(ren, font_size, white, "max range: " + to_string(largestRange()) + "m", posX, posYWhereTextShouldStart + (getTextYSize(font_size)*4));
	if (largestRange() == 0)
	{
		drawText(ren, font_size, white, "max range: infinite", posX, posYWhereTextShouldStart + (getTextYSize(font_size)*4));
	}
	else
	{
		drawText(ren, font_size, white, "max range: " + to_string(largestRange()) + "m", posX, posYWhereTextShouldStart + (getTextYSize(font_size)*4));
	}

	if (mouseX > posX && mouseX < posX + sizeX && mouseY > posY && mouseY < posY + posYWhereTextShouldStart + (getTextYSize(font_size)*5) - posY)
	{
		if (lastMouse == SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			color selectionClickedColor(255,255,0,255);
			drawRect(ren, selectionClickedColor, posX, posY, sizeX, posYWhereTextShouldStart + (getTextYSize(font_size)*5) - posY);
			return this;
		}
		else
		{
			color selectionColor(255,127,0,255);
			drawRect(ren, selectionColor, posX, posY, sizeX, posYWhereTextShouldStart + (getTextYSize(font_size)*5) - posY);
		}
	}

	return nullptr;
}

bool torpedo :: drawPurchaseButton(SDL_Renderer *ren, int posX, int posY, int mouseX, int mouseY, Uint32 lastMouse)
{
	purchaseButton.setPos(posX, posY);
	bool clicked = purchaseButton.draw(ren, mouseX, mouseY, lastMouse);
	int fontSize = 7 * gscreenx / 800;
	drawText(ren, fontSize, color(255,255,255), m_name, posX + purchaseButton.sizeX() + 20, posY);

	return clicked;
}

bool torpedo :: drawTorpedoIcon(SDL_Renderer *ren, int posX, int posY, int sizeX, int sizeY, int mouseX, int mouseY, Uint32 lastMouse, bool rear)
{
	//int torpedoSizeX = 173 * gscreenx / 1366;
	//int torpedoSizeY = 33 * gscreenx / 1366;
	int torpedoIconX = static_cast<double>(173) * 0.924855491 * static_cast<double>(sizeX) / 173;
	int torpedoIconY = static_cast<double>(33) * 0.454545455 * static_cast<double>(sizeX) / 173;
	cout << "torpedo x,y=" << torpedoIconX << ", " << torpedoIconY << endl;
	int torpedoXOffset = (sizeX - torpedoIconX) / 2;
	int torpedoYOffset = (sizeY - torpedoIconY) / 2;

	int spriteAngle = 0;
	if (rear) spriteAngle = 180;
	if (mouseX > posX && mouseX < posX + sizeX && mouseY > posY && mouseY < posY + sizeY)
	{
		if (lastMouse == SDL_BUTTON(SDL_BUTTON_LEFT) && m_mouseOver)
		{
			m_selected = true;
		}
		if (lastMouse != SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			m_mouseOver = true;
		}
	}
	else
	{
		m_mouseOver = false;
	}

	if (lastMouse != SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		m_selected = false;
	}

	if (m_selected)
	{
		posX = mouseX - (sizeX / 2);
		posY = mouseY - (sizeY / 2);
	}

	renderTextureEx(m_icon, ren, posX + torpedoXOffset, posY + torpedoYOffset, torpedoIconX, torpedoIconY, spriteAngle);

	return m_selected;
}

torpedo& torpedo :: operator=(const torpedo& other)
{
	m_name = other.name();
	m_description = other.description();
	m_textureFolder = other.textureFolder();
	m_mesh_low = other.mesh_low();
	m_mesh_high = other.mesh_high();

	m_speed1 = other.speed(0);
	m_speed2 = other.speed(1);
	m_speed3 = other.speed(2);
	m_range1 = other.range(0);
	m_range2 = other.range(1);
	m_range3 = other.range(2);

	m_warheadpower = other.warhead();
	m_guidance = other.guidance();
	m_controlSurfaces = other.controlSurfaces();
	m_crushdepth = other.crushDepth();
	m_turnspeed = other.turnSpeed();
	m_cost = other.cost();
	m_magnetic = other.magnetic();
	m_rangeExplode = other.rangeExplode();
	m_maxGyroangle = other.maxGyroangle();
	m_loudness = other.loudness();
	m_serverAlert = other.serverAlert();

	m_armingRange = other.armingRange();
	m_type = other.type();
	m_hasWire = other.hasWire();

	m_icon = other.getTex();

	m_selected = false;
	m_mouseOver = false;

	int textSize = 8 * gscreenx / 800;
	button temp("purchase", color(255,255,255), 0, 0, textSize);
	temp.setBackgroundColor(color(20,20,20,100));
	temp.setBorder(true);
	purchaseButton = temp;

	m_markedForDeletion = other.markedForDeletion();

	return *this;
}

//========================================================
// non member-functions below this line
//========================================================

int loadTorpedoFile(string filePath, SDL_Renderer *ren)
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
	torpedo newTorpedo(linesOfFile);

	//now load the menu textures
	newTorpedo.loadTorpedoTextures(ren);

	//textures are loaded and pointers are set. Put this into the registry
	torpedoRegistry->push_back(newTorpedo);

	return 0;
}

int loadAllTorpedos(SDL_Renderer *ren)
{
	//make a list of all present torpedo file paths
	string torpedoPath = "Data/torpedos";
	vector<string> filePaths;

	for (const auto & entry : std::filesystem::directory_iterator(torpedoPath))
	{
        std::cout << entry.path() << std::endl;
        filePaths.push_back(entry.path());
	}

	//for each encountered submarine file, load them
	for (int i = 0; i < filePaths.size(); i++)
	{
		loadTorpedoFile(filePaths.at(i), ren);
	}

	return 0;
}

//returns nullptr if none found
torpedo* getTorpedoByName(string name)
{
	for (int i = 0; i < torpedoRegistry->size(); i++)
	{
		if (torpedoRegistry->at(i).name() == name)
		{
			return &torpedoRegistry->at(i);
		}
	}
	return nullptr;
}

torpedo* randomTorpedo()
{
	int index = rand() % torpedoRegistry->size();
	return &torpedoRegistry->at(index);
}