ship :: ship()
{

}

ship :: ship(XMLElement *shipElement)
{
	worldPosX = 0;
	worldPosY = 0;
	worldPosZ = 0;

	worldRotX = 0;
	worldRotY = 0;
	worldRotZ = 0;

	m_meshName = shipElement->FirstChildElement("mesh")->GetText();
	m_className = shipElement->FirstChildElement("className")->GetText();
	m_classString = shipElement->FirstChildElement("classString")->GetText();
	m_description = shipElement->FirstChildElement("description")->GetText();
	m_textureFolder = shipElement->FirstChildElement("texture")->GetText();
	m_meshName = shipElement->FirstChildElement("mesh")->GetText();

	m_tier = atoi(shipElement->FirstChildElement("tier")->GetText());
	m_topSpeed = atof(shipElement->FirstChildElement("top_speed")->GetText());
	m_acceleration = atof(shipElement->FirstChildElement("acceleration")->GetText());
	m_turnRate = atof(shipElement->FirstChildElement("turn_rate")->GetText());
	m_range = atoi(shipElement->FirstChildElement("range")->GetText());
	//m_hydrophones = 
	//m_sonar = 
	//m_radar = 
	m_length = atof(shipElement->FirstChildElement("length")->GetText()); 
	m_beam = atof(shipElement->FirstChildElement("beam")->GetText());
	m_draft = atof(shipElement->FirstChildElement("draft")->GetText());

	m_numFloodableCompartments = atoi(shipElement->FirstChildElement("flood_compartments")->GetText());
	m_pathfinding = atof(shipElement->FirstChildElement("pathfinding")->GetText());
	m_tonnage = atoi(shipElement->FirstChildElement("tonnage")->GetText());
}

ship :: ~ship()
{

}

void ship :: loadShipMesh(SDL_Renderer *ren, SDL_Window *win)
{
	m_shipMesh.LoadFromObjectFile(ren, win, "Mesh/Ships/"+m_meshName, "Textures/Ships/"+m_textureFolder+"/"+m_textureFolder+"_texture_1024.png", true);

	return void();
}

ship& ship :: operator=(ship& other)
{
	worldPosX = other.worldPosX;
	worldPosY = other.worldPosY;
	worldPosZ = other.worldPosZ;

	worldRotX = other.worldRotX;
	worldRotY = other.worldRotY;
	worldRotZ = other.worldRotZ;

	m_shipMesh = other.m_shipMesh;

	m_className = other.className();
	m_classString = other.classString();
	m_description = other.desc();
	m_textureFolder = other.textureName();
	m_meshName = other.meshName();

	m_tier = other.getTier();
	m_topSpeed = other.getTopSpeed();
	m_acceleration = other.getAcceleration();
	m_turnRate = other.getTurnRate();
	m_range = other.getRange();
	m_hydrophones = other.hasHydrophones();
	m_sonar = other.hasSonar();
	m_radar = other.hasRadar();
	m_length = other.getLength();
	m_beam = other.getBeam();
	m_draft = other.getDraft();

	m_numFloodableCompartments = other.getNumFloodableComps();
	m_pathfinding = other.pathingPreference();
	m_tonnage = other.getTonnage();

	return *this;
}

//non member functions below this line
int loadShipFile(string filePath, SDL_Renderer *ren, SDL_Window *win)
{
	XMLDocument doc;
	doc.LoadFile(filePath.c_str());

	if (doc.RootElement() == nullptr)
	{
		cout << "warning: a save file with no root element was loaded" << endl;
		return 1;
	}

	XMLElement *rootElement = doc.RootElement();

	//set up a pointer to the playerInfo element

	//XMLElement *shipDataElement = rootElement->FirstChildElement("Ship");
	//if (shipDataElement == nullptr)
	//{
	//	cout << "shipDataElement = nullptr" << endl;
	//}
	//now that the contents of the file have been loaded into ram, make a new submarine object
	//the submarine's vector<string> constructor deals with the parsing
	ship newShip(rootElement);
	newShip.loadShipMesh(ren, win);
	cout << "loading ship of class " << newShip.className() << endl;

	//newShip.loadShipMesh(ren, win);

	//textures are loaded and pointers are set. Put this into the registry
	shipRegistry->push_back(newShip);
}

int loadAllShips(SDL_Renderer *ren, SDL_Window *win)
{
	//make a list of all present ship file paths
	string shipPath = "Data/ships";
	vector<string> filePaths;

	for (const auto & entry : std::filesystem::directory_iterator(shipPath))
	{
        std::cout << entry.path() << std::endl;
        filePaths.push_back(entry.path());
	}

	//for each encountered submarine file, load them
	for (int i = 0; i < filePaths.size(); i++)
	{
		loadShipFile(filePaths.at(i), ren, win);
	}

	return 0;
}

ship* getShipByName(string name)
{
	bool foundMatch = false;
	int i = 0;
	while (!foundMatch)
	{
		if (shipRegistry->at(i).className() == name)
		{
			foundMatch = true;
		}
		else
		{
			i++;
		}
	}

	return &shipRegistry->at(i);
}