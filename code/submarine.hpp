submarine :: submarine()
{
	m_sourceSlotNum = -1;
	m_destSlotNum = -1;

	upgradePointersNull();
}

submarine :: submarine(vector<string> fileData)
{
	//loop through the file contents
	int compartmentBlockStartLine = 0;
	int i = 0;
	bool foundCompartmentBlock = false;
	bool endOfFile = false;
	while (i < fileData.size() && !foundCompartmentBlock)
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
			m_textureName = fileData.at(i).substr(8, fileData.at(i).size());
		}
		else if (fileData.at(i).substr(0,9) == "mesh_low=") 
		{
			//cout << "low poly is" << fileData.at(i).substr(9, fileData.at(i).size()) << endl;
			m_mesh_low = fileData.at(i).substr(9, fileData.at(i).size());
		}
		else if (fileData.at(i).substr(0,10) == "mesh_high=") 
		{
			//cout << "high poly is" << fileData.at(i).substr(10, fileData.at(i).size()) << endl;
			m_mesh_high = fileData.at(i).substr(10, fileData.at(i).size());
		}
		else if (fileData.at(i).substr(0,11) == "surf_speed=") 
		{
			//cout << "surf speed is" << fileData.at(i).substr(11, fileData.at(i).size()) << endl;
			m_topspeed_surface = stod(fileData.at(i).substr(11, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,16) == "submerged_speed=") 
		{
			//cout << "submerged speed is" << fileData.at(i).substr(16, fileData.at(i).size()) << endl;
			m_topspeed_submerged = stod(fileData.at(i).substr(16, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,13) == "acceleration=") 
		{
			//cout << "acceleration is" << fileData.at(i).substr(13, fileData.at(i).size()) << endl;
			m_acceleration = stod(fileData.at(i).substr(13, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,5) == "tier=") 
		{
			//cout << "tier is" << fileData.at(i).substr(5, fileData.at(i).size()) << endl;
			m_tier = stoi(fileData.at(i).substr(5, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,7) == "length=") 
		{
			//cout << "length is" << fileData.at(i).substr(7, fileData.at(i).size()) << endl;
			m_length = stod(fileData.at(i).substr(7, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,8) == "draught=") 
		{
			//cout << "draught: " << fileData.at(i).substr(8, fileData.at(i).size()) << endl;
			m_draught = stod(fileData.at(i).substr(8, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,5) == "beam=") 
		{
			//cout << "beam is" << fileData.at(i).substr(5, fileData.at(i).size()) << endl;
			m_beam = stod(fileData.at(i).substr(5, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,5) == "disp=") 
		{
			//cout << "displacement is" << fileData.at(i).substr(5, fileData.at(i).size()) << endl;
			m_displacement = stod(fileData.at(i).substr(5, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,9) == "fuel_mpg=") 
		{
			//cout << "mpg is" << fileData.at(i).substr(9, fileData.at(i).size()) << endl;
			m_mpg = stod(fileData.at(i).substr(9, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,11) == "power_type=") 
		{
			//cout << "drivetrain type is" << fileData.at(i).substr(11, fileData.at(i).size()) << endl;
			m_powerType = stoi(fileData.at(i).substr(11, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,6) == "range=") 
		{
			//cout << "range is" << fileData.at(i).substr(6, fileData.at(i).size()) << endl;
			m_range = stoi(fileData.at(i).substr(6, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,14) == "fuel_capacity=") 
		{
			//cout << "fuel capacity is" << fileData.at(i).substr(14, fileData.at(i).size()) << endl;
			m_fuelCapacity = stod(fileData.at(i).substr(14, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,13) == "bat_amphours=") 
		{
			//cout << "battery amp hours is" << fileData.at(i).substr(13, fileData.at(i).size()) << endl;
			m_ampHours = stod(fileData.at(i).substr(13, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,10) == "bat_range=") 
		{
			//cout << "battery range is" << fileData.at(i).substr(10, fileData.at(i).size()) << endl;
			m_batrange = stoi(fileData.at(i).substr(10, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,8) == "sailors=") 
		{
			//cout << "num sailors is" << fileData.at(i).substr(8, fileData.at(i).size()) << endl;
			m_sailors = stoi(fileData.at(i).substr(8, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,4) == "pos=") 
		{
			//cout << "num pettyofficers is" << fileData.at(i).substr(4, fileData.at(i).size()) << endl;
			m_pettyOfficers = stoi(fileData.at(i).substr(4, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,9) == "officers=") 
		{
			//cout << "num officers is" << fileData.at(i).substr(9, fileData.at(i).size()) << endl;
			m_officers = stoi(fileData.at(i).substr(9, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,10) == "bow_tubes=") 
		{
			//cout << "bow tubes: " << fileData.at(i).substr(10, fileData.at(i).size()) << endl;
			m_bowTorpedoTubes = stoi(fileData.at(i).substr(10, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,12) == "stern_tubes=") 
		{
			//cout << "stern tubes: " << fileData.at(i).substr(12, fileData.at(i).size()) << endl;
			m_sternTorpedoTubes = stoi(fileData.at(i).substr(12, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,12) == "bow_reserve=") 
		{
			//cout << "bow reserve: " << fileData.at(i).substr(12, fileData.at(i).size()) << endl;
			m_bowReserve = stoi(fileData.at(i).substr(12, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,14) == "stern_reserve=") 
		{
			//cout << "stern reserve: " << fileData.at(i).substr(14, fileData.at(i).size()) << endl;
			m_sternReserve = stoi(fileData.at(i).substr(14, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,9) == "nuke_pwr=") 
		{
			//cout << "nuke power: " << fileData.at(i).substr(9, fileData.at(i).size()) << endl;
			m_nukeOutput = stod(fileData.at(i).substr(9, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,16) == "nuke_efficiency=") 
		{
			//cout << "nuke efficiency: " << fileData.at(i).substr(16, fileData.at(i).size()) << endl;
			m_nukeEfficiency = stod(fileData.at(i).substr(16, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,17) == "can_have_nuclear=") 
		{
			//cout << "can have nuclear: " << fileData.at(i).substr(17, fileData.at(i).size()) << endl;
			m_canGoNuclear = stringToBool(fileData.at(i).substr(17, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,11) == "oxygen_gen=") 
		{
			//cout << "oxygen generator: " << fileData.at(i).substr(11, fileData.at(i).size()) << endl;
			m_oxygenGen = stoi(fileData.at(i).substr(11, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,14) == "passive_sonar=") 
		{
			//cout << "passive sonar: " << fileData.at(i).substr(14, fileData.at(i).size()) << endl;
			m_passiveSonar = stoi(fileData.at(i).substr(14, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,13) == "active_sonar=") 
		{
			//cout << "active sonar: " << fileData.at(i).substr(13, fileData.at(i).size()) << endl;
			m_activeSonar = stoi(fileData.at(i).substr(13, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,6) == "radar=") 
		{
			//cout << "radar: " << fileData.at(i).substr(6, fileData.at(i).size()) << endl;
			m_rader = stoi(fileData.at(i).substr(6, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,6) == "lidar=") 
		{
			//cout << "lidar: " << fileData.at(i).substr(6, fileData.at(i).size()) << endl;
			m_lidar = stoi(fileData.at(i).substr(6, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,8) == "snorkel=") 
		{
			//cout << "snorkel: " << fileData.at(i).substr(8, fileData.at(i).size()) << endl;
			m_snorkel = stoi(fileData.at(i).substr(8, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,18) == "diesels_mult_water=") 
		{
			//cout << "diesel underwater speed multiplier: " << fileData.at(i).substr(18, fileData.at(i).size()) << endl;
			m_diesels_mult_water = stod(fileData.at(i).substr(18, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,15) == "submarine_size=") 
		{
			//cout << "submarine size: " << fileData.at(i).substr(15, fileData.at(i).size()) << endl;
			m_submarine_size = stoi(fileData.at(i).substr(15, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,8) == "deckgun=") 
		{
			//cout << "deckgun: " << fileData.at(i).substr(8, fileData.at(i).size()) << endl;
			m_canHaveDeckgun = stringToBool(fileData.at(i).substr(8, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,9) == "deckgunX=") 
		{
			//cout << "deckgunx: " << fileData.at(i).substr(9, fileData.at(i).size()) << endl;
			m_deckGunPosX = stoi(fileData.at(i).substr(9, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,9) == "deckgunY=") 
		{
			//cout << "deckguny: " << fileData.at(i).substr(9, fileData.at(i).size()) << endl;
			m_deckGunPosY = stoi(fileData.at(i).substr(9, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,5) == "cost=") 
		{
			//cout << "cost: " << fileData.at(i).substr(5, fileData.at(i).size()) << endl;
			m_cost = stod(fileData.at(i).substr(5, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,10) == "max_depth=") 
		{
			//cout << "crush depth: " << fileData.at(i).substr(10, fileData.at(i).size()) << endl;
			m_crushDepth = stoi(fileData.at(i).substr(10, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,11) == "safe_depth=") 
		{
			//cout << "safe depth: " << fileData.at(i).substr(11, fileData.at(i).size()) << endl;
			m_safeDepth = stoi(fileData.at(i).substr(11, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,11) == "air_amount=") 
		{
			//cout << "days of air: " << fileData.at(i).substr(11, fileData.at(i).size()) << endl;
			m_air = stod(fileData.at(i).substr(11, fileData.at(i).size()));
		}
		else if (fileData.at(i).substr(0,6) == "cargo=") 
		{
			//cout << "cargo slots: " << fileData.at(i).substr(6, fileData.at(i).size()) << endl;
			m_cargoSlots = stoi(fileData.at(i).substr(6, fileData.at(i).size()));
		}
		else if (fileData.at(i) == "compartment")
		{
			//wait.. what?
			compartmentBlockStartLine = i;
			foundCompartmentBlock = true;
			//ok I totally forgot why this is here but I bet it's to ensure the list is initialized so when the clear command clears it, it increases the chances of it not crashing
			//Don't really want to investigate right but (but I will at some point)
			//submarineCompartment newCompartment;
			//compartmentList.push_back(newCompartment);
		}

		//cout << fileData.at(i) << endl;
		i++;
	}
	/*normal data has all been found. Now, start loading compartment data
	compartment block are in the following format:
	"compartment" (line denotes compartment keyword)
	display name
	room type
	crew
	officers
	required manpower
	*/
	compartmentList.clear();
	i = compartmentBlockStartLine;
	while (!endOfFile && (i + 8) < fileData.size())
	{
		if (fileData.at(i) == "compartment")
		{	
			//cout << "compartment name: " << fileData.at(i+1) << endl;
			//cout << "room type: " << fileData.at(i+2) << endl;
			//cout << "crew slots: " << fileData.at(i+3) << endl;
			//cout << "officer slots: " << fileData.at(i+4) << endl;
			//cout << "required manpower: " << fileData.at(i+5) << endl;
			submarineCompartment newCompartment(fileData.at(i+1), stoi(fileData.at(i+2)), stoi(fileData.at(i+3)), stoi(fileData.at(i+4)), stod(fileData.at(i+5)), stoi(fileData.at(i+6)), stoi(fileData.at(i+7)));
			//newCompartment.setParent(this);
			compartmentList.push_back(newCompartment);
		}
		else
		{
			endOfFile = true;
		}
		i+=8;
	}

	//make torpedoStorage equal in size to total number of torpedos and set them all to nullptr
	torpedoStorage->clear();
	int amountOfTorpedos = m_bowTorpedoTubes + m_sternTorpedoTubes + m_bowReserve + m_sternReserve;
	for (int i = 0; i < amountOfTorpedos; i++)
	{
		torpedoStorage->push_back(nullptr);
	}


	color greenish(20,235,20,255);
	color white(255,255,255);
	color darkBlack(50,50,50,50);
	progressBar setupBar(0, 0, 100, 20, greenish, m_sailors, true);
	m_crewOccupancy = setupBar;
	setupBar.setMax(m_pettyOfficers);
	m_poOccupancy = setupBar;
	setupBar.setMax(m_officers);
	m_officerOccupancy = setupBar;
	button tempButton("purchase", white, 200, 200, 8 * gscreeny / 600);
	purchaseButton = tempButton;
	purchaseButton.setBackgroundColor(darkBlack);
	purchaseButton.setBorder(true);

	m_sourceSlotNum = -1;
	m_destSlotNum = -1;

	//set all the upgrade pointers to null just so that they're a known value
	upgradePointersNull();

	//now, give the submarine the correct upgrade parts based on its information
	applyCorrectParts();

	//set all the world stuff to zero
	worldPosX = 0;
	worldPosY = 0;
	worldPosZ = 0;
	worldRotX = 0;
	worldRotY = 0;
	worldRotZ = 0;
	m_periscopeHeight = 0;

}

submarine :: ~submarine()
{
	for (int i = 0; i < torpedoStorage->size(); i++)
	{
		torpedoStorage->at(i) = nullptr;
	}
}

//set all the upgrade part pointers to null
void submarine :: upgradePointersNull()
{
	//set all the upgrade pointers to null
	m_batteryUpgrade = nullptr;
	m_engineUpgrade = nullptr;
	m_electricEngineUpgrade = nullptr;
	m_nuclearReactor = nullptr;
	m_fuelTank = nullptr;
	m_oxygenGenerator = nullptr;
	m_radarUpgrade = nullptr;
	m_radarDetector = nullptr;
	m_activeSonarUpgrade = nullptr;
	m_hydrophones = nullptr;
	//m_batteryUpgrade = other.getUpgradeConst(10);
	m_hullUpgrade = nullptr;
	m_stealthMisc = nullptr;
	//m_batteryUpgrade = other.getUpgradeConst(12);
}

//if the submarine class "comes with" certain upgrade parts by default, find out what they are, find them in the database and then apply their pointers
void submarine :: applyCorrectParts()
{
	//if submarine is a nuclear sub, give it a nuclear reactor of the correct size
	if (m_powerType == 2)
	{
		if (m_submarine_size == 0)
		{
			m_nuclearReactor = findUpgradePartByName(inventoryItemDatabase, "Radioisotope thermoelectric generator");
		}
		else if (m_submarine_size == 1)
		{
			m_nuclearReactor = findUpgradePartByName(inventoryItemDatabase, "Advanced small modular reactor");
		}
		else
		{
			m_nuclearReactor = findUpgradePartByName(inventoryItemDatabase, "Large nuclear reactor");
		}
	}

	//if submarine is supposed to have an oxygen generator, find a suitable oxygen generator in the database, choosing from the 3 default basegame ones
	if (m_oxygenGen == 2)
	{
		//find total crew in ship
		int sailors = 0;
		int pos = 0;
		int officers = 0;
		getCrewCounts(&sailors, &pos, &officers);
		int totalCrew = sailors + pos + officers;
		if (totalCrew < 11)
		{
			m_oxygenGenerator = findUpgradePartByName(inventoryItemDatabase, "Oxygen generator");
		}
		else if (totalCrew < 41)
		{
			m_oxygenGenerator = findUpgradePartByName(inventoryItemDatabase, "High capacity oxygen generator");
		}
		else
		{
			m_oxygenGenerator = findUpgradePartByName(inventoryItemDatabase, "Ultra capacity oxygen generator");
		}
	}

	//if submarine is supposed to come with a radar detector already installed
	if (m_lidar == 2)
	{
		if (m_tier < 2)
		{
			m_radarDetector = findUpgradePartByName(inventoryItemDatabase, "Metox radar detector");
		}
		else
		{
			m_radarDetector = findUpgradePartByName(inventoryItemDatabase, "XCF-80 radar detector");
		}
	}

	//damn I just realized I spelled that variable name wrong. lol it's much, much too late to change that
	if (m_rader == 2)
	{
		if (m_tier < 2)
		{
			m_radarUpgrade = findUpgradePartByName(inventoryItemDatabase, "Fumo 30 radar");
		}
		else
		{
			m_radarUpgrade = findUpgradePartByName(inventoryItemDatabase, "Loran submarine radar");
		}
	}

	if (m_activeSonar == 2)
	{
		if (m_tier < 2)
		{
			m_activeSonarUpgrade = findUpgradePartByName(inventoryItemDatabase, "ASDIC based active sonar system");
		}
		else if (m_tier < 3)
		{
			m_activeSonarUpgrade = findUpgradePartByName(inventoryItemDatabase, "AN/SQS 10 active sonar");
		}
		else
		{
			m_activeSonarUpgrade = findUpgradePartByName(inventoryItemDatabase, "BQQ-5 active sonar system");
		}
	}

	if (m_passiveSonar == 2)
	{
		
		if (m_tier < 3)
		{
			m_hydrophones = findUpgradePartByName(inventoryItemDatabase, "GHB hydrophones");
		}
		else
		{
			m_hydrophones = findUpgradePartByName(inventoryItemDatabase, "BQQ 5 hydrophone system");
		}
	}
}

//compartment getters
//0 = battery. 1 = diesel engine. 2 = electric engine. 3 = nuclear. 4 = fuel tank. 5 = oxygen generator.
//6 = radar. 7 = radar detector. 8 = sonar. 9 = hydrophone. 10 = deck gun. 11 = hull strength. 12 = detection related. 13 = fun
upgradePart* submarine :: getUpgradeConst(int index) const
{
	if (index == 0)
	{
		return m_batteryUpgrade;
	}
	else if (index == 1)
	{
		return m_engineUpgrade;
	}
	else if (index == 2)
	{
		return m_electricEngineUpgrade;
	}
	else if (index == 3)
	{
		return m_nuclearReactor;
	}
	else if (index == 4)
	{
		return m_fuelTank;
	}
	else if (index == 5)
	{
		return m_oxygenGenerator;
	}
	else if (index == 6)
	{
		return m_radarUpgrade;
	}
	else if (index == 7)
	{
		return m_radarDetector;
	}
	else if (index == 8)
	{
		return m_activeSonarUpgrade;
	}
	else if (index == 9)
	{
		return m_hydrophones;
	}
	else if (index == 10)
	{
		return m_engineUpgrade;
	}
	else if (index == 11)
	{
		return m_hullUpgrade;
	}
	else if (index == 12)
	{
		return m_stealthMisc;
	}
	else if (index == 13)
	{
		return m_stealthMisc;
	}
}

upgradePart* submarine :: getUpgrade(int index)
{
	if (index == 0)
	{
		return m_batteryUpgrade;
	}
	else if (index == 1)
	{
		return m_engineUpgrade;
	}
	else if (index == 2)
	{
		return m_electricEngineUpgrade;
	}
	else if (index == 3)
	{
		return m_nuclearReactor;
	}
	else if (index == 4)
	{
		return m_fuelTank;
	}
	else if (index == 5)
	{
		return m_oxygenGenerator;
	}
	else if (index == 6)
	{
		return m_radarUpgrade;
	}
	else if (index == 7)
	{
		return m_radarDetector;
	}
	else if (index == 8)
	{
		return m_activeSonarUpgrade;
	}
	else if (index == 9)
	{
		return m_hydrophones;
	}
	else if (index == 10)
	{
		return m_engineUpgrade;
	}
	else if (index == 11)
	{
		return m_hullUpgrade;
	}
	else if (index == 12)
	{
		return m_stealthMisc;
	}
	else if (index == 13)
	{
		return m_stealthMisc;
	}
}

//size x = screen size X, size y = screen size Y
//returns selected crew member
void submarine :: drawInfoScreen(SDL_Renderer *ren, int sizeX, int sizeY, int mouseX, int mouseY, Uint32 lastMouse, int *yBottom, crewMember **selected)
{	
	int texSizeX;
	int texSizeY;
	SDL_QueryTexture(m_interiorTexture, NULL, NULL, &texSizeX, &texSizeY);

	//used if scaling has to be put in place to keep the submarine interior sprite from being comically large in wide aspect ratios
	int horizontalOffset = 0;

	//after testing various screen sizes, expanding the submarine sprite the entire horiztonal size of the screen makes it comically too large on 16:9 ratios.
	//at 4:3 (on 1024 x 768 at least), it's reasonable
	//so I'm implementing some code to draw the submarine smaller and centered when in 16:9 (I'm only testing and therefore supporting 16:9 resolutions between 1024x600 - 3840x2160)
	//

	//calculate the aspect ratio so it can be preserved when the texture is resized
	//not actually an "aspect ratio". Both of the brain cells I was utilizing when I wrote this code were smoking crack. Still works correctly though
	double aspectRatio = static_cast<double>(sizeX) / static_cast<double>(texSizeX);
	//if aspect ratio (and the actual aspect ratio not the stupid above variable called "aspectRatio" that isnt actually the aspect ratio) is greater than a little more than 4:3
	if (static_cast<double>(sizeX)/static_cast<double>(sizeY) > 1.4)
	{
		//take only span this percent of the horizontal size and not 100% the horizontal size of the screen
		aspectRatio *= 0.7;
		//ensure it stays centered
		horizontalOffset = (sizeX - (texSizeX * aspectRatio))/2;
	}
	//cout << "texSizeX=" << texSizeX << " texSizeY=" << texSizeY << " aspect ratio=" << aspectRatio << endl;

	renderTextureEx(m_interiorTexture, ren, horizontalOffset, 50, texSizeX * aspectRatio, texSizeY * aspectRatio, 0);
	//cout << "# compartments" << compartmentList.size() << endl;

	int lowestYcoord = 0; 	//use the for loop to note the lowest screenspace y coordinate
	//check mouse collisions for each compartment in submarine
	for (int i = 0; i < compartmentList.size(); i++)
	{	
		compartmentList.at(i).doDrawing(ren, aspectRatio, horizontalOffset, 50, mouseX, mouseY, lastMouse);
		//now draw each compartment crew box thingy or whatever
		int testYcoord = compartmentList.at(i).drawCrewBox(ren, sizeX, sizeY, 50 + (texSizeY * aspectRatio), i, compartmentList.size(), mouseX, mouseY, lastMouse, selected);
		if (testYcoord > lowestYcoord)
		{
			lowestYcoord = testYcoord;
		}

		//if compartment got left clicked on
		if (compartmentList.at(i).getFunctionType() == 2)
		{
			//execute the "move crew to rest" function
			sendCompartmentToRest(compartmentList.at(i));
			cout << "move crew to rest" << endl;
		}
		else if (compartmentList.at(i).getFunctionType() == 1)
		{
			//execute the auto populate function
			autoPopulateCompartment(&compartmentList.at(i));
			cout << "auto populate compartment" << endl;
		}
	}
	*yBottom = lowestYcoord;
	//cout << "lowest y coord = " << lowestYcoord << endl;

	color background(50,60,50,150);
	drawRectFilled(ren, background, 15, 15, 300, 90);

	//draw the crew status bars
	m_crewOccupancy.setPos(20, 80);
	m_poOccupancy.setPos(20, 50);
	m_officerOccupancy.setPos(20, 20);

	m_crewOccupancy.draw(ren);
	m_poOccupancy.draw(ren);
	m_officerOccupancy.draw(ren);

	color white(255,255,255,255);
	drawText(ren, 7, white, "sailors " + to_string(m_crewOccupancy.getValue()) + "/" + to_string(m_sailors), 130, 80);
	drawText(ren, 7, white, "pettyofficers " + to_string(m_poOccupancy.getValue()) + "/" + to_string(m_pettyOfficers), 130, 50);
	drawText(ren, 7, white, "officers " + to_string(m_officerOccupancy.getValue()) + "/" + to_string(m_officers), 130, 20);


}

//loads each of the submarine's compartment textures. Only done when the player "selects" a submarine.
//This way, having a modlist of 200+ modded submarines won't lag the game out from the stupid search algorithms and/or a massive ram hit
int submarine :: loadExtraSubmarineIcons(SDL_Renderer *ren)
{
	for (int i = 0; i < compartmentList.size(); i++)
	{
		compartmentList.at(i).loadTextures(ren, m_textureName);
		//extraSubmarineSprites->push_back(new textureEntry(textureFolder + "MainIcon_interior.bmp", m_textureName + ".Interior",ren));
		//m_interiorTexture = submarineSprites->back()->getTexture();
	}

	return 0;
}

//recursively removes each texture pointer in the submarine's compartment list. Then, deletes all textures in extraSubmarineSprites
int submarine :: clearExtraSubmarineIcons(SDL_Renderer *ren)
{
	for (int i = 0; i < compartmentList.size(); i++)
	{
		compartmentList.at(i).clearTextures();
	}

	for (int i = 0; i < extraSubmarineSprites->size(); i++)
	{
		delete [] extraSubmarineSprites->at(i);
	}
	delete [] extraSubmarineSprites;
	extraSubmarineSprites = new vector<textureEntry*>;

	return 0;
}

submarine& submarine :: operator=(submarine& other)
{
	m_name = other.name();
	m_description = other.description();

	//ex: USS Nautilus, Queen Ann's Revenge, HMS boob
	m_shipName = other.shipName();

	m_textureName = other.textureName();
	m_mesh_low = other.mesh_low();
	m_mesh_high = other.mesh_high();

	m_topspeed_surface = other.topspeed_surface();
	m_topspeed_submerged = other.topspeed_submerged();
	m_acceleration = other.acceleration();
	m_diesels_mult_water = other.diesels_mult_water();

	//tier 0 = potato. 1 = ww2 capability. 2 = early cold war. 3 = late cold war and modern. 4 = advanced futuristic
	m_tier = other.tier();

	m_length = other.length();
	m_beam = other.beam();
	m_draught = other.draught();
	m_displacement = other.displacement();

	m_submarine_size = other.getSize();

	m_mpg = other.mpg();
	m_powerType = other.powerType(); 		//0 = diesel electric. 1 = diesel electric except the electric engines are always used and diesel only generates power. 2 = nuclear
	m_fuelCapacity = other.fuelCapacity();
	m_ampHours = other.ampHours();
	m_range = other.range();
	m_batrange = other.batRange();

	//crew information
	m_sailors = other.sailors();
	m_pettyOfficers = other.pettyOfficers();
	m_officers = other.officers();

	//torpedo information
	m_bowTorpedoTubes = other.bowTorpedoTubes();
	m_sternTorpedoTubes = other.sternTorpedoTubes();
	m_bowReserve = other.bowReserve();
	m_sternReserve = other.sternReserve();

	m_nukeOutput = other.nukeOutput();	//in MW
	m_nukeEfficiency = other.nukeEfficiency();	//number of years it takes a fuel rod to run down
	
	//upgrade and parts information
	m_canGoNuclear = other.canGoNuclear();
	m_oxygenGen = other.canHaveOxygenGen();
	m_passiveSonar = other.canHavePassiveSonar();
	m_activeSonar = other.canHaveActiveSonar();
	m_rader = other.canHaveRader();
	m_lidar = other.canHaveLidar();
	m_snorkel = other.canHaveSnorkel();
	m_canHaveDeckgun = other.canHaveDeckGun();
	m_deckGunPosX = other.deckGunX();
	m_deckGunPosY = other.deckGUnY();

	m_cost = other.cost();
	m_crushDepth = other.crushDepth();
	m_safeDepth = other.safeDepth();

	m_air = other.air();
	m_cargoSlots = other.numCargoSlots();

	//now for the loop that copies the compartments
	compartmentList.clear();
	for (int i = 0; i < other.compartmentList.size(); i++)
	{
		cout << "in copy" << endl;
		compartmentList.push_back(compartmentList.at(i));
	}
	//compartmentList = other.compartmentList;

	//now situating all the pointers and shit
	smallIcon = other.getSmallIcon();

	m_crewOccupancy = other.getCrewBar();
	m_poOccupancy = other.getpoBar();
	m_officerOccupancy = other.getOfficerBar();

	//set the upgrades equal
	m_batteryUpgrade = other.getUpgradeConst(0);
	m_engineUpgrade = other.getUpgradeConst(1);
	m_electricEngineUpgrade = other.getUpgradeConst(2);
	m_nuclearReactor = other.getUpgradeConst(3);
	m_fuelTank = other.getUpgradeConst(4);
	m_oxygenGenerator = other.getUpgradeConst(5);
	m_radarUpgrade = other.getUpgradeConst(6);
	m_radarDetector = other.getUpgradeConst(7);
	m_activeSonarUpgrade = other.getUpgradeConst(8);
	m_hydrophones = other.getUpgradeConst(9);
	//m_batteryUpgrade = other.getUpgradeConst(10);
	m_hullUpgrade = other.getUpgradeConst(11);
	m_stealthMisc = other.getUpgradeConst(12);
	//m_batteryUpgrade = other.getUpgradeConst(12);

	color white(255,255,255);
	color darkBlack(50,50,50,50);
	button tempButton("purchase", white, 200, 200, 8 * gscreeny / 600);
	purchaseButton = tempButton;
	purchaseButton.setBackgroundColor(darkBlack);
	purchaseButton.setBorder(true);

	m_sourceSlotNum = -1;
	m_destSlotNum = -1;

	//need to copy torpedo pointers as well
	torpedoStorage->resize(other.torpedoStorage->size());
	for (int t = 0; t < other.torpedoStorage->size(); t++)
	{
		torpedoStorage->at(t) = other.torpedoStorage->at(t);
	}

	submarineMesh = other.submarineMesh;

	//set all the world stuff to zero
	worldPosX = other.worldPosX;
	worldPosY = other.worldPosY;
	worldPosZ = other.worldPosZ;
	worldRotX = other.worldRotX;
	worldRotY = other.worldRotY;
	worldRotZ = other.worldRotZ;
	m_periscopeHeight = other.m_periscopeHeight;

	return *this;
}

void submarine :: drawIconSmall(SDL_Renderer *ren, int posX, int posY)
{
	renderTexture(smallIcon, ren, posX, posY);
}

void submarine :: drawIconLarge(SDL_Renderer *ren, int posX, int posY)
{
	renderTexture(largeIcon, ren, posX, posY);
}

int loadSubmarineFile(string filePath, SDL_Renderer *ren, SDL_Window *win)
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
	submarine newSub(linesOfFile);

	//now load the menu textures
	newSub.loadSubmarineIcons(ren, false);
	newSub.loadSubmarineMesh(ren, win);

	//textures are loaded and pointers are set. Put this into the registry
	submarineRegistry->push_back(newSub);

	return 0;
}

int submarine :: loadSubmarineIcons(SDL_Renderer *ren, bool useCompressed)
{
	string textureFolder = "Textures/Submarines/" + m_textureName + "/";

	//load the small texture. avoid having the computer resize on draw which is expensive
	submarineSprites->push_back(new textureEntry(textureFolder + "MainIcon_small.bmp", m_textureName + ".MainIcon_small",ren));
	smallIcon = submarineSprites->back()->getTexture();

	//load the larger texture. Will require resize on draw due to varying and large size. The performance hit won't be as bad when using this
	//since there will never be more than one "large" texture on the screen
	submarineSprites->push_back(new textureEntry(textureFolder + "MainIcon.bmp", m_textureName + ".MainIcon",ren));
	largeIcon = submarineSprites->back()->getTexture();

	//interior texture for crew and submarine management screens.
	/*I know it would be less memory expensive to load this later (when a player "selects" a submarine for example) but this may make things
	more suceptible to segfault crashes when people start making mods.
	This is why I prefer to load all the submarine textures together. The compartment textures will still be loaded only when a player "selects" a submarine
	*/
	submarineSprites->push_back(new textureEntry(textureFolder + "MainIcon_interior.bmp", m_textureName + ".Interior",ren));
	m_interiorTexture = submarineSprites->back()->getTexture();

	cout << "loaded " << textureFolder << endl;

	return 0;

}

void submarine :: loadSubmarineMesh(SDL_Renderer *ren, SDL_Window *win)
{
	submarineMesh.LoadFromObjectFile(ren, win, "Mesh/Submarines/"+m_mesh_high, "Textures/Submarines/"+m_textureName+"/"+m_textureName+"_texture_1024.png", true);
}

bool submarine :: crewToRandomCompartment(crewMember *person)
{
	bool isSubmarineFull;
	if (totalCrewSlots() > totalCrewInSub())
	{
		isSubmarineFull = false;
	}
	else
	{
		isSubmarineFull = true;
	}
	bool operationCompleted = false;

	while (!isSubmarineFull && !operationCompleted)
	{
		int compartmentIndex = rand() % compartmentList.size();
		if (compartmentList.at(compartmentIndex).addCrewToAnySlot(person))
		{
			operationCompleted = true;
		}
	}

	return operationCompleted;
	//while (!compartmentList.at(compartmentIndex).addCrewToAnySlot(person))
	//{
		//compartmentIndex = rand() % compartmentList.size();
	//}
	//return true;
}

bool submarine :: putCrewInCompartment(crewMember* person, int posX, int posY, int screenX, crewMember **replacement, int *slotNumb)
{
	bool found = false;
	int i = 0;
	while (i < compartmentList.size() && !compartmentList.at(i).isInside(posX, posY))
	{
		i++;
	}

	//if looped through all compartments and found no match, return false
	if (i == compartmentList.size()) return false;

	//if didn't loop through all compartments, that means it found a match. Call that compartment's crewToSpecificSlot() function and return result
	else 
	{
		int compartmentNum = i;
		int slotNum = 0;
		crewMember *replacementCrew = nullptr;
		//*compartmentNum = i;
		//return compartmentList.at(i).crewToSpecificSlot(person, posX, posY, screenX, slotNum, crewToPutInPlace);
		//compartmentList.at(i).crewToSpecificSlot(person, posX, posY, screenX, slotNum, crewToPutInPlace);
		//if (&crewToPutInPlace == nullptr)
		//{
			//not replacing a crew member. Erase the duplicate pointer
		//	findAndEraseDuplicateCrew(person, *compartmentNum, *slotNum);
		//}
		//else
		//{
			//replacing a valid crew member. Set the duplicate pointer to the value of the crew member who's position got replaced
		//	findAndReplaceDuplicateCrew(person, *compartmentNum, *slotNum, *crewToPutInPlace);
		//}

		compartmentList.at(i).crewToSpecificSlot(person, posX, posY, screenX, &slotNum, &replacementCrew);
		if (replacementCrew == nullptr)
		{
			//not replacing a crew member. Erase the duplicate pointer
			findAndEraseDuplicateCrew(person, compartmentNum, slotNum);
		}
		else
		{
			//replacing a valid crew member. Set the duplicate pointer to the value of the crew member who's position got replaced
			findAndReplaceDuplicateCrew(person, compartmentNum, slotNum, replacementCrew);
		}

		updateCrewCounts();

		*replacement = replacementCrew;
		*slotNumb = slotNum;

		//findAndEraseDuplicateCrew(playerCampaignInfo->getInfoCardCrewPointer(), compartmentNum, slotNum);
		return true;
	}
}

void submarine :: findAndEraseDuplicateCrew(crewMember* person, int excludeCompartment, int excludeSlot)
{
	bool foundMatch = false;
	int i = 0;
	while (!foundMatch && i < compartmentList.size())
	{
		if (i == excludeCompartment)
		{
			foundMatch = compartmentList.at(i).eraseDuplicateCrew(person, excludeSlot);
		}
		else
		{
			foundMatch = compartmentList.at(i).eraseDuplicateCrew(person, -1);
		}

		i++;
	}

}

void submarine :: findAndReplaceDuplicateCrew(crewMember* person, int excludeCompartment, int excludeSlot, crewMember* replacement)
{
	bool foundMatch = false;
	int i = 0;
	while (!foundMatch && i < compartmentList.size())
	{
		if (i == excludeCompartment)
		{
			foundMatch = compartmentList.at(i).replaceDuplicateCrew(person, excludeSlot, replacement);
		}
		else
		{
			foundMatch = compartmentList.at(i).replaceDuplicateCrew(person, -1, replacement);
		}

		i++;
	}
}

/*
sends all crew from the source compartment (compartment) to crew quarters.
if there isn't room in crew quarters for everyone, it just moves some of them.
if the source compartment is a crew quarters compartment, it evenly distributes them to different parts of the submarine
*/
void submarine :: sendCompartmentToRest(submarineCompartment compartment)
{
	//step 1. locate a non-full crew quarters compartment

	//step 2. for each crew in "compartment", move to the found crew quarters compartment
		//a. if crew quarters compartment full, find another one and move crew to that
		//b. if cycled through all compartments and there are still crew to be sent to rest, give up
		//c. if there are no more crew in "compartment", the operation has finished. Quit and return

	bool moveCompleted = false;
	int i = 0;
	int p = 0;
	while (i < compartmentList.size() && !moveCompleted)
	{
		//locate a compartment that is crew quarters.
		//type 4 is bow quarters and type 14 is stern quarters
		if (compartmentList.at(i).type() == 4 || compartmentList.at(i).type() == 14)
		{	
			//probably computationally expensive to do this but meh. Algorithm efficency number crunching doesn't give me a hard-on like it does some people.
			//this is something that isn't going to happen very often so it probably won't make a difference
			int slotNum = 0;
			while (compartmentList.at(i).moveCrewToAnySlot(compartment.crewInSlot(p), &slotNum) && p < compartment.numSlots())
			{
				findAndEraseDuplicateCrew(compartment.crewInSlot(p), i, slotNum);
				p++;
			}

			//sort the crew into a nice and semi organized arrangement
			compartmentList.at(i).sortCrew();
		}

		i++;
	}
}

/*
populates the provided compartment to the inputted percentage using crew from crew quarters
if there is not enough available crew to achieve the inputted compartment manpower percentage, it will do as many crew as it can
if there is no available crew in any of the crew quarters compartments, it does nothing
if the provided compartment is crew quarters, takes any tired or unneeded crew from other compartments and transfers them into the provided compartment
*/
void submarine :: autoPopulateCompartment(submarineCompartment *compartment, double targetPercentage)
{
	//step 1. Does compartment already have the requested amount of manpower
		//if yes, exit
		//if no, continue

	//step 2. Locate a crew quarters compartment
		//a. if compartment is empty, look for a different one.
		//b. if there are no non-empty crew quarters compartments, give up and return
		//c. if compartment is not empty, transfer a random crew from that compartment to the target compartment
			//I. if the target compartment now has the requested amount of manpower, exit
			//II. if the target compartment does not has the requested amount of manpower, keep moving crew at random from the located crew quarters to the new one
			//and do that until either the crew quarters compartment is empty or the target compartment has the requested amount of manpower

	int i = 0;
	while (compartment->currentManpower() / compartment->requiredManpower() < (targetPercentage) && i < compartmentList.size()) 
	{
		//locate a compartment that is crew quarters.
		//type 4 is bow quarters and type 14 is stern quarters
		if (compartmentList.at(i).type() == 4 || compartmentList.at(i).type() == 14)
		{
			int slotNum = 0;
			bool validMove = true;
			while (compartment->currentManpower() / compartment->requiredManpower() < (targetPercentage) && validMove)
			{
				crewMember *randomCrew = compartmentList.at(i).randomCrew();
				if (randomCrew == nullptr)
				{
					validMove = false;
				}
				else
				{
					//i should consider making code to add a compartment's number before getting drawn the first time to reduce weird bugs later down the line
					validMove = compartment->moveCrewToAnySlot(randomCrew, &slotNum);

					//only run the find and erase duplicate crew function if the move is valid (i.e. there is room in the compartment for 1 more crew)
					//not performing this check causes the crew pointer to get lost and no longer be in the current submarine
					if (validMove) findAndEraseDuplicateCrew(randomCrew, compartment->compartmentNumber(), slotNum);
				}
			}
		}

		i++;

	}

	compartment->sortCrew();
}

//moves all crew in the submarine to the provided barracks compartment pointer
//true = finished
//false = not enough room in barracks for everyone
bool submarine :: moveEveryoneToBarracks(submarineCompartment *barracks)
{
	bool success = true;
	//for each compartment in submarine
	for (int i = 0; i < compartmentList.size(); i++)
	{	
		bool validMove = true;
		while (compartmentList.at(i).numCrew() != 0 && validMove && success)
		{
			//fetch random crew in compartment
			crewMember *crewPointer = compartmentList.at(i).randomCrew();
			if (crewPointer != nullptr)
			{	
				//add crew to any slot in barracks
				success = barracks->addCrewToAnySlot(crewPointer);

				//erase crew pointer from previous submarine compartment slot
				compartmentList.at(i).eraseDuplicateCrew(crewPointer, -1);
			}
			else
			{
				validMove = false;
			}
		}
	}

	updateCrewCounts();
	barracks->sortCrew();

	return success;
}

//currently only updates the "progress" bars that show crew count. Will do more in the future
void submarine :: updateCrewCounts()
{
	int numSailors = 0;
	int numPos = 0;
	int numOfficers = 0;


	getCrewCounts(&numSailors, &numPos, &numOfficers);
	/*for (int i = 0; i < compartmentList.size(); i++)
	{
		compartmentList.at(i).numCrewTypes(&numSailors, &numPos, &numOfficers);
	}*/

	m_crewOccupancy.setValue(numSailors);
	m_poOccupancy.setValue(numPos);
	m_officerOccupancy.setValue(numOfficers);
}

void submarine :: getCrewCounts(int *sailors, int *pos, int *officers)
{
	int numSailors = 0;
	int numPos = 0;
	int numOfficers = 0;

	for (int i = 0; i < compartmentList.size(); i++)
	{
		compartmentList.at(i).numCrewTypes(&numSailors, &numPos, &numOfficers);
	}

	*sailors = numSailors;
	*pos = numPos;
	*officers = numOfficers;
}

int submarine :: totalCrewSlots()
{
	int slotsSoFar = 0;
	for (int i = 0; i < compartmentList.size(); i++)
	{
		slotsSoFar += compartmentList.at(i).numSlots();
	}

	return slotsSoFar;
}

int submarine :: totalCrewInSub()
{
	int crewSoFar = 0;
	for (int i = 0; i < compartmentList.size(); i++)
	{
		crewSoFar += compartmentList.at(i).numCrew();
	}

	return crewSoFar;
}

//recalculates manpower values for every compartment in the submarine
void submarine :: recalculateManpower()
{
	for (int i = 0; i < compartmentList.size(); i++)
	{
		compartmentList.at(i).updateManpower();
	}
}

submarine* submarine :: drawPurchaseInfoCard(SDL_Renderer *ren, int posX, int posY, int sizeX, int sizeY, int mouseX, int mouseY, Uint32 lastMouse)
{
	int font_size = 8 * static_cast<double>(sizeX) / static_cast<double>(200);
	int texSizeX;
	int texSizeY;
	SDL_QueryTexture(smallIcon, NULL, NULL, &texSizeX, &texSizeY);
	//what x has to be multiplied by to fit in the given size
	double texMultiplier = static_cast<double>(sizeX) / static_cast<double>(texSizeX);

	int posYWhereTextShouldStart = posY + (texSizeY * texMultiplier);

	color cardBackground(20,20,20,100);
	color white(255,255,255,255);
	drawRectFilled(ren, cardBackground, posX, posY, sizeX, posYWhereTextShouldStart + (getTextYSize(font_size)*5) - posY);
	renderTextureEx(smallIcon, ren, posX, posY, sizeX, texSizeY * texMultiplier, 0);

	int numTorpedos = m_bowTorpedoTubes + m_sternTorpedoTubes + m_sternReserve + m_bowReserve;
	int numTubes = m_bowTorpedoTubes + m_sternTorpedoTubes;
	string powerWhatever = "diesel / electric";
	if (m_powerType == 2) powerWhatever = "nuclear";

	drawText(ren, font_size, white, m_name, posX, posYWhereTextShouldStart);
	drawText(ren, font_size, white, powerWhatever, posX, posYWhereTextShouldStart + (getTextYSize(font_size)*1));
	drawText(ren, font_size, white, "Torpedo tubes: " + to_string(numTubes), posX, posYWhereTextShouldStart + (getTextYSize(font_size)*2));
	drawText(ren, font_size, white, "Torpedos: " + to_string(numTorpedos), posX, posYWhereTextShouldStart + (getTextYSize(font_size)*3));
	drawText(ren, font_size, white, "Price: " + doubleToMoney(m_cost), posX, posYWhereTextShouldStart + (getTextYSize(font_size)*4));

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

//displays some of the basic, user-upgradable information 
void submarine :: basicSubmarineInfo(SDL_Renderer *ren, int posX, int posY, int sizeX, int sizeY)
{
	int textSize = 7 * gscreeny / 600;
	int textSizeSmall = 6 * gscreeny / 600;
	drawText(ren, textSize, color(255,255,255), "poop", posX, posY);
}

//displays more info than the purchase infocard alone does.
//returns true if user pressed the purchase button
bool submarine :: moreDetailedSubmarineInfo(SDL_Renderer *ren, int posX, int posY, int sizeX, int sizeY, int mouseX, int mouseY, Uint32 lastMouse, submarine *compareSub, bool showBuyButton)
{
	int textSize = 7 * gscreeny / 600;
	int textSizeSmall = 6 * gscreeny / 600;
	color white(255,255,255,255);
	//drawText(ren, textSize, white, "poop", posX, posY + (getTextYSize(textSize)*0));

	//2 columns
	if (compareSub == nullptr)
	{
		//column 1
		drawText(ren, textSize, white, "Class: " + m_name, posX, posY + (getTextYSize(textSize)*1));
		drawText(ren, textSize, white, "Safe depth: " + to_string(static_cast<int>(m_safeDepth * getHullMultiplier())) + "m", posX, posY + (getTextYSize(textSize)*2));
		drawText(ren, textSize, white, "Bow torpedo tubes: " + to_string(m_bowTorpedoTubes), posX, posY + (getTextYSize(textSize)*3));
		drawText(ren, textSize, white, "Bow torpedo reserves: " + to_string(m_bowReserve), posX, posY + (getTextYSize(textSize)*4));
		drawText(ren, textSize, white, "Aft torpedo tubes: " + to_string(m_sternTorpedoTubes), posX, posY + (getTextYSize(textSize)*5));
		drawText(ren, textSize, white, "Aft torpedo reserves: " + to_string(m_sternReserve), posX, posY + (getTextYSize(textSize)*6));
		drawText(ren, textSize, white, "Max speed (surface): " + doubleToString(m_topspeed_surface * getDieselMultiplier()) + " knots", posX, posY + (getTextYSize(textSize)*7));
		drawText(ren, textSize, white, "Max speed (submerged): " + doubleToString(m_topspeed_submerged * getElectricNultiplier()) + " knots", posX, posY + (getTextYSize(textSize)*8));
		drawText(ren, textSize, white, "Surface range: " + to_string(static_cast<int>(m_range*getFuelMultiplier())) + "nmi", posX, posY + (getTextYSize(textSize)*9));
		drawText(ren, textSize, white, "Underwater range: " + to_string(static_cast<int>(m_batrange*getBatteryMultiplier())) + "nmi", posX, posY + (getTextYSize(textSize)*10));
		drawText(ren, textSize, white, "days of air: " + doubleToString(m_air, 0), posX, posY + (getTextYSize(textSize)*11));

		int col2Xpos = posX + getTextXSize(textSize, 36);
		//column 2
		drawText(ren, textSize, white, "Length: " + doubleToString(m_length) + "m", col2Xpos, posY + (getTextYSize(textSize)*1));
		drawText(ren, textSize, white, "Beam: " + doubleToString(m_beam) + "m", col2Xpos, posY + (getTextYSize(textSize)*2));
		drawText(ren, textSize, white, "Draught: " + doubleToString(m_draught) + "m", col2Xpos, posY + (getTextYSize(textSize)*3));
		drawText(ren, textSize, white, "Displacement: " + doubleToString(m_displacement) + " tons", col2Xpos, posY + (getTextYSize(textSize)*4));
		drawText(ren, textSize, white, "Sailors: " + to_string(m_sailors), col2Xpos, posY + (getTextYSize(textSize)*5));
		drawText(ren, textSize, white, "Pettyofficers: " + to_string(m_pettyOfficers), col2Xpos, posY + (getTextYSize(textSize)*6));
		drawText(ren, textSize, white, "Officers: " + to_string(m_officers), col2Xpos, posY + (getTextYSize(textSize)*7));
		drawText(ren, textSize, white, "Cargo slots: " + to_string(m_cargoSlots), col2Xpos, posY + (getTextYSize(textSize)*8));
		drawText(ren, textSize, white, "Cost: " + doubleToMoney(m_cost), col2Xpos, posY + (getTextYSize(textSize)*9));
		drawTextWrapped(ren, textSizeSmall,  white, "Description: " + m_description, col2Xpos, posY + (getTextYSize(textSize)*10), (gscreenx - col2Xpos)*0.75);
	}
	else
	{
		//recalculating the colored strings every frame is just too goddamn expensive
		//I need 486 DX2 levels of optimization. recalculating colored strings every frame alone adds 4% cpu usage on a 3ghz cpu even after fixing memory leaks. Unacceptable.
		//column 1
		drawText(ren, textSize, white, "Class: " + m_name, posX, posY + (getTextYSize(textSize)*1));
		//depthString += " ( " + to_string(m_safeDepth - compareSub->safeDepth()) + ")";
		//depthString.setColor(1, positiveGreen);

		drawText(ren, textSize, depthString, posX, posY + (getTextYSize(textSize)*2));
		drawText(ren, textSize, bowTorpedoString, posX, posY + (getTextYSize(textSize)*3));
		drawText(ren, textSize, bowTorpedoReserve, posX, posY + (getTextYSize(textSize)*4));
		drawText(ren, textSize, aftTorpedoString, posX, posY + (getTextYSize(textSize)*5));
		drawText(ren, textSize, aftTorpedoReserve, posX, posY + (getTextYSize(textSize)*6));
		drawText(ren, textSize, maxSpeedString, posX, posY + (getTextYSize(textSize)*7));
		drawText(ren, textSize, maxSpeedSubmergedString, posX, posY + (getTextYSize(textSize)*8));
		drawText(ren, textSize, surfaceRange, posX, posY + (getTextYSize(textSize)*9));
		drawText(ren, textSize, underwaterRange, posX, posY + (getTextYSize(textSize)*10));
		//drawText(ren, textSize, daysOFair, posX, posY + (getTextYSize(textSize)*11));
		drawText(ren, textSize, devices, posX, posY + (getTextYSize(textSize)*11));

		int col2Xpos = posX + getTextXSize(textSize, 42);
		//column 2
		drawText(ren, textSize, white, "Length: " + doubleToString(m_length) + "m", col2Xpos, posY + (getTextYSize(textSize)*1));
		drawText(ren, textSize, white, "Beam: " + doubleToString(m_beam) + "m", col2Xpos, posY + (getTextYSize(textSize)*2));
		drawText(ren, textSize, white, "Draught: " + doubleToString(m_draught) + "m", col2Xpos, posY + (getTextYSize(textSize)*3));
		drawText(ren, textSize, white, "Displacement: " + doubleToString(m_displacement) + " tons", col2Xpos, posY + (getTextYSize(textSize)*4));
		drawText(ren, textSize, white, "Sailors: " + to_string(m_sailors), col2Xpos, posY + (getTextYSize(textSize)*5));
		drawText(ren, textSize, white, "Pettyofficers: " + to_string(m_pettyOfficers), col2Xpos, posY + (getTextYSize(textSize)*6));
		drawText(ren, textSize, white, "Officers: " + to_string(m_officers), col2Xpos, posY + (getTextYSize(textSize)*7));
		drawText(ren, textSize, cargoSlotsString, col2Xpos, posY + (getTextYSize(textSize)*8));
		drawText(ren, textSize, white, "Cost: " + doubleToMoney(m_cost), col2Xpos, posY + (getTextYSize(textSize)*9));
		drawTextWrapped(ren, textSizeSmall,  white, "Description: " + m_description, col2Xpos, posY + (getTextYSize(textSize)*10), (gscreenx - col2Xpos)*0.75);

		purchaseButton.setPos(posX + (sizeX / 3), posY);
		purchaseButton.draw(ren, mouseX, mouseY, lastMouse);
	}

}

void submarine :: drawTorpedoArming(SDL_Renderer *ren, int posX, int posY, int sizeX, int sizeY, int mouseX, int mouseY, Uint32 lastMouse, torpedo **torpedoToSell)
{
	if (m_sourceSlotNum != -1 && m_destSlotNum != -1 && lastMouse != SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		if (m_destSlotNum == torpedoStorage->size())
		{
			//sell the current torpedo instead of swap it or move it to a different location
			*torpedoToSell = torpedoStorage->at(m_sourceSlotNum);
			torpedoStorage->at(m_sourceSlotNum) = nullptr;
		}
		else
		{
			torpedo *sourcePointer = torpedoStorage->at(m_sourceSlotNum);
			torpedo *destPointer = torpedoStorage->at(m_destSlotNum);
			torpedoStorage->at(m_sourceSlotNum) = destPointer;
			torpedoStorage->at(m_destSlotNum) = sourcePointer;
		}
	}

	m_sourceSlotNum = -1;
	m_destSlotNum = -1;

	int font_size = 8 * static_cast<double>(sizeX) / static_cast<double>(900);
	int texSizeX;
	int texSizeY;
	SDL_QueryTexture(smallIcon, NULL, NULL, &texSizeX, &texSizeY);
	double texMultiplier = static_cast<double>(sizeX / 2) / static_cast<double>(texSizeX);

	renderTextureEx(largeIcon, ren, posX + (texSizeX * texMultiplier / 2), posY, texSizeX * texMultiplier, texSizeY * texMultiplier, 0);

	int bowTubeStart = 0;
	int bowReserveStart = m_bowTorpedoTubes;
	int sternTubeStart = m_bowTorpedoTubes + m_bowReserve;
	int sternReserveStart = m_bowTorpedoTubes + m_bowReserve + m_sternTorpedoTubes;

	int torpedoSizeX = 173 * gscreenx / 1366;
	int torpedoSizeY = 33 * gscreenx / 1366;
	cout << "torpedoSizeX = " << torpedoSizeX << endl;
	cout << "torpedoSizeY = " << torpedoSizeY << endl;

	int sellTorpedoIndex = m_bowTorpedoTubes + m_bowReserve + m_sternTorpedoTubes + m_sternReserve;
	int sellTorpedoPosX = gscreenx - (torpedoSizeX * 1.2);
	int sellTorpedoPosY = gscreeny - (torpedoSizeY * 1.5);
	//int torpedoIconX = 160 * gscreenx / 1366;
	//int torpedoIconY = 15 * gscreenx / 1366;
	//int torpedoXOffset = (torpedoSizeX - torpedoIconX) / 2;
	//int torpedoYOffset = (torpedoSizeY - torpedoIconY) / 2;

	//draw the recycle torpedo thingy
	drawText(ren, font_size, color(255,255,255), "sell", sellTorpedoPosX, sellTorpedoPosY - getTextYSize(font_size));
	renderTextureEx(torpedoSlotOrange, ren, sellTorpedoPosX, sellTorpedoPosY, torpedoSizeX, torpedoSizeY, 0);
	if (isColliding2D(sellTorpedoPosX, sellTorpedoPosY, torpedoSizeX, torpedoSizeY, mouseX, mouseY))
	{
		m_destSlotNum = sellTorpedoIndex;
	}

	//draw bow tube background
	drawText(ren, font_size, color(255,255,255), "bow tubes", posX + sizeX - torpedoSizeX - (torpedoSizeX / 2), posY);
	for (int i = 0; i < m_bowTorpedoTubes; i++)
	{
		renderTextureEx(torpedoSlot, ren, posX + sizeX - torpedoSizeX - (torpedoSizeX / 2), posY + (i*torpedoSizeY) + getTextYSize(font_size), torpedoSizeX, torpedoSizeY, 0);
		if (isColliding2D(posX + sizeX - torpedoSizeX - (torpedoSizeX / 2), posY + (i*torpedoSizeY) + getTextYSize(font_size), torpedoSizeX, torpedoSizeY, mouseX, mouseY))
		{
			m_destSlotNum = i;
		}
		/*if (torpedoStorage->at(i) != nullptr)
		{
			torpedoStorage->at(i)->drawTorpedoIcon(ren, posX + sizeX - torpedoSizeX - (torpedoSizeX / 2), posY + (i*torpedoSizeY) + getTextYSize(font_size), torpedoSizeX, torpedoSizeY, mouseX, mouseY, lastMouse);
		}*/
	}

	//draw bow reserve background
	int bowStartX = posX + sizeX - (torpedoSizeX*2) - (torpedoSizeX / 2);
	int bowStartY = posY + (texSizeY * texMultiplier);
	int torpedoColumnHeight = (gscreeny - bowStartY - getTextYSize(font_size)) / torpedoSizeY;

	//if for some reason you wanted to make a joke submarine that sucks so bad it doesn't even have bow torpedo reloads, the game suports it
	if (m_bowReserve > 0)
	{
		drawText(ren, font_size, color(255,255,255), "bow reserve", bowStartX, bowStartY);
		//cout << "column height is " << torpedoColumnHeight << endl;
		int y = 0;
		for (int i = 0; i < m_bowReserve; i++)
		{
			y = i / torpedoColumnHeight;
			renderTextureEx(torpedoSlot, ren, bowStartX - (y*torpedoSizeX), bowStartY + getTextYSize(font_size) + ((i%torpedoColumnHeight)*torpedoSizeY), torpedoSizeX, torpedoSizeY, 0);

			if (isColliding2D(bowStartX - (y*torpedoSizeX), bowStartY + getTextYSize(font_size) + ((i%torpedoColumnHeight)*torpedoSizeY), torpedoSizeX, torpedoSizeY, mouseX, mouseY))
			{
				m_destSlotNum = i + bowReserveStart;
			}
			/*if (torpedoStorage->at(i + bowReserveStart) != nullptr)
			{
				torpedoStorage->at(i + bowReserveStart)->drawTorpedoIcon(ren, bowStartX - (y*torpedoSizeX), bowStartY + getTextYSize(font_size) + ((i%torpedoColumnHeight)*torpedoSizeY), torpedoSizeX, torpedoSizeY, mouseX, mouseY, lastMouse);
			}*/
		}
	}

	//draw stern tube background
	if (m_sternTorpedoTubes > 0)
	{
		drawText(ren, font_size, color(255,255,255), "stern tubes", posX + (torpedoSizeX / 3), posY);
		int sternTubeStartX = posX + (torpedoSizeX / 3);
		for (int i = 0; i < m_sternTorpedoTubes; i++)
		{
			renderTextureEx(torpedoSlot, ren, sternTubeStartX, posY + (i*torpedoSizeY) + getTextYSize(font_size), torpedoSizeX, torpedoSizeY, 180);

			if (isColliding2D(sternTubeStartX, posY + (i*torpedoSizeY) + getTextYSize(font_size), torpedoSizeX, torpedoSizeY, mouseX, mouseY))
			{
				m_destSlotNum = i + sternTubeStart;
			}
			/*if (torpedoStorage->at(i + sternTubeStart) != nullptr)
			{
				torpedoStorage->at(i + sternTubeStart)->drawTorpedoIcon(ren, sternTubeStartX, posY + (i*torpedoSizeY) + getTextYSize(font_size), torpedoSizeX, torpedoSizeY, mouseX, mouseY, lastMouse, true);
			}*/
		}
	}

	//draw stern reserve background
	if (m_sternReserve > 0)
	{
		int y = 0;
		int sternReserveStartX = posX + (torpedoSizeX / 3);
		int sternReserveStartY = bowStartY + getTextYSize(font_size);
		drawText(ren, font_size, color(255,255,255), "stern reserve", sternReserveStartX, bowStartY);
		for (int i = 0; i < m_sternReserve; i++)
		{
			y = i / torpedoColumnHeight;
			renderTextureEx(torpedoSlot, ren, sternReserveStartX + (y*torpedoSizeX), bowStartY + getTextYSize(font_size) + ((i%torpedoColumnHeight)*torpedoSizeY), torpedoSizeX, torpedoSizeY, 180);
			if (isColliding2D(sternReserveStartX + (y*torpedoSizeX), bowStartY + getTextYSize(font_size) + ((i%torpedoColumnHeight)*torpedoSizeY), torpedoSizeX, torpedoSizeY, mouseX, mouseY))
			{
				m_destSlotNum = i + sternReserveStart;
			}
			/*if (torpedoStorage->at(i + sternReserveStart) != nullptr)
			{
				torpedoStorage->at(i + sternReserveStart)->drawTorpedoIcon(ren, sternReserveStartX + (y*torpedoSizeX), bowStartY + getTextYSize(font_size) + ((i%torpedoColumnHeight)*torpedoSizeY), torpedoSizeX, torpedoSizeY, mouseX, mouseY, lastMouse, true);
			}*/
		}
	}

	//draw bow tube icon
	drawText(ren, font_size, color(255,255,255), "bow tubes", posX + sizeX - torpedoSizeX - (torpedoSizeX / 2), posY);
	for (int i = 0; i < m_bowTorpedoTubes; i++)
	{
		//renderTextureEx(torpedoSlot, ren, posX + sizeX - torpedoSizeX - (torpedoSizeX / 2), posY + (i*torpedoSizeY) + getTextYSize(font_size), torpedoSizeX, torpedoSizeY, 0);
		if (torpedoStorage->at(i) != nullptr)
		{
			if (torpedoStorage->at(i)->drawTorpedoIcon(ren, posX + sizeX - torpedoSizeX - (torpedoSizeX / 2), posY + (i*torpedoSizeY) + getTextYSize(font_size), torpedoSizeX, torpedoSizeY, mouseX, mouseY, lastMouse))
			{
				m_sourceSlotNum = i;
			}
		}
	}

	//bow reserve torpedos
	if (m_bowReserve > 0)
	{
		//drawText(ren, font_size, color(255,255,255), "bow reserve", bowStartX, bowStartY);
		//cout << "column height is " << torpedoColumnHeight << endl;
		int y = 0;
		for (int i = 0; i < m_bowReserve; i++)
		{
			y = i / torpedoColumnHeight;
			//renderTextureEx(torpedoSlot, ren, bowStartX - (y*torpedoSizeX), bowStartY + getTextYSize(font_size) + ((i%torpedoColumnHeight)*torpedoSizeY), torpedoSizeX, torpedoSizeY, 0);

			if (torpedoStorage->at(i + bowReserveStart) != nullptr)
			{
				if (torpedoStorage->at(i + bowReserveStart)->drawTorpedoIcon(ren, bowStartX - (y*torpedoSizeX), bowStartY + getTextYSize(font_size) + ((i%torpedoColumnHeight)*torpedoSizeY), torpedoSizeX, torpedoSizeY, mouseX, mouseY, lastMouse))
				{
					m_sourceSlotNum = i + bowReserveStart;
				}
			}
		}
	}
	
	//draw stern tubes
	if (m_sternTorpedoTubes > 0)
	{
		//drawText(ren, font_size, color(255,255,255), "stern tubes", posX + (torpedoSizeX / 3), posY);
		int sternTubeStartX = posX + (torpedoSizeX / 3);
		for (int i = 0; i < m_sternTorpedoTubes; i++)
		{
			//renderTextureEx(torpedoSlot, ren, sternTubeStartX, posY + (i*torpedoSizeY) + getTextYSize(font_size), torpedoSizeX, torpedoSizeY, 180);
			if (torpedoStorage->at(i + sternTubeStart) != nullptr)
			{
				if (torpedoStorage->at(i + sternTubeStart)->drawTorpedoIcon(ren, sternTubeStartX, posY + (i*torpedoSizeY) + getTextYSize(font_size), torpedoSizeX, torpedoSizeY, mouseX, mouseY, lastMouse, true))
				{
					m_sourceSlotNum = i + sternTubeStart;
				}
			}
		}
	}

	//draw stern reserve
	if (m_sternReserve > 0)
	{
		int y = 0;
		int sternReserveStartX = posX + (torpedoSizeX / 3);
		int sternReserveStartY = bowStartY + getTextYSize(font_size);
		//drawText(ren, font_size, color(255,255,255), "stern reserve", sternReserveStartX, bowStartY);
		for (int i = 0; i < m_sternReserve; i++)
		{
			y = i / torpedoColumnHeight;
			//renderTextureEx(torpedoSlot, ren, sternReserveStartX + (y*torpedoSizeX), bowStartY + getTextYSize(font_size) + ((i%torpedoColumnHeight)*torpedoSizeY), torpedoSizeX, torpedoSizeY, 180);
			if (torpedoStorage->at(i + sternReserveStart) != nullptr)
			{
				if (torpedoStorage->at(i + sternReserveStart)->drawTorpedoIcon(ren, sternReserveStartX + (y*torpedoSizeX), bowStartY + getTextYSize(font_size) + ((i%torpedoColumnHeight)*torpedoSizeY), torpedoSizeX, torpedoSizeY, mouseX, mouseY, lastMouse, true))
				{
					m_sourceSlotNum = i + sternReserveStart;
				}
			}
		}
	}

	//if a torpedo is selected draw it again right here (last) so it's on top of stuff and doesn't look stupid
	if (m_sourceSlotNum != -1 && lastMouse == SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		bool isRearTorpedo = false;
		if (m_sourceSlotNum >= sternTubeStart) isRearTorpedo = true;
		torpedoStorage->at(m_sourceSlotNum)->drawTorpedoIcon(ren, 0, 0, torpedoSizeX, torpedoSizeY, mouseX, mouseY, lastMouse, isRearTorpedo);
	}

	//cout << "source slot num = " << m_sourceSlotNum << endl;
	//cout << "dest slot num = " << m_destSlotNum << endl;	
}

//checks if the submarine is compatible with a certain part
bool submarine :: canHavePart(upgradePart *part)
{
	int typeIndex = part->getUpgradeType();
	//cout << "typeIndex = " << typeIndex << endl;
	if (typeIndex == 0)
	{
		return true;
	}
	else if (typeIndex == 1)
	{
		return true;
	}
	else if (typeIndex == 2)
	{
		return true;
	}
	else if (typeIndex == 3)
	{
		return m_canGoNuclear;
	}
	else if (typeIndex == 4)
	{
		return true;
	}
	else if (typeIndex == 5)
	{
		if (m_oxygenGen > 0) return true;
		else return false;
	}
	else if (typeIndex == 6)
	{
		if (m_rader > 0) return true;
		else return false;
	}
	else if (typeIndex == 7)
	{
		if (m_lidar > 0) return true;
		else return false;
	}
	else if (typeIndex == 8)
	{
		//cout << "active sonar = " << m_activeSonar << endl;
		if (m_activeSonar > 0) return true;
		else return false;
	}
	else if (typeIndex == 9)
	{
		//cout << "passive sonar = " << m_passiveSonar << endl;
		if (m_passiveSonar > 0) return true;
		else return false;
	}
	else if (typeIndex > 9)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//checks if the submarine already has a certain part
bool submarine :: alreadyHasPart(upgradePart *part)
{
	//if (m_activeSonarUpgrade == nullptr) cout << "m_activeSonarUpgrade == nullptr" << endl;
	//else cout << "is " << m_activeSonarUpgrade->getName() << " the same as " << part->getName() << "?" << endl;
	
	if (m_batteryUpgrade == part)
	{
		return true;	
	}
	else if (m_engineUpgrade == part)
	{
		return true;
	}
	else if (m_electricEngineUpgrade == part)
	{
		return true;
	}
	else if (m_nuclearReactor == part)
	{
		return true;
	}
	else if (m_fuelTank == part)
	{
		return true;
	}
	else if (m_oxygenGenerator == part)
	{
		return true;
	}
	else if (m_radarUpgrade == part)
	{
		return true;
	}
	else if (m_radarDetector == part)
	{
		return true;
	}
	else if (m_activeSonarUpgrade == part)
	{
		return true;
	}
	else if (m_hydrophones == part)
	{
		return true;
	}
	else if (m_hullUpgrade == part)
	{
		return true;
	}
	else if (m_stealthMisc == part)
	{
		return true;
	}

	else
	{
		return false;
	}
}

void submarine :: putPartInSubmarine(upgradePart *part)
{
	int typeIndex = part->getUpgradeType();

	//battery
	if (typeIndex == 0)
	{
		m_batteryUpgrade = part;
	}
	//diesel engine
	else if (typeIndex == 1)
	{
		m_engineUpgrade = part;
	}
	//electric engines
	else if (typeIndex == 2)
	{
		m_electricEngineUpgrade = part;
	}
	//nuclear reactor
	else if (typeIndex == 3)
	{
		m_nuclearReactor = part;
	}
	//fuel tank
	else if (typeIndex == 4)
	{
		m_fuelTank = part;
	}
	//oxygen generator
	else if (typeIndex == 5)
	{
		m_oxygenGenerator = part;
	}
	//radar
	else if (typeIndex == 6)
	{
		m_radarUpgrade = part;
	}
	//radar detector
	else if (typeIndex == 7)
	{
		m_radarDetector = part;
	}
	//active sonar
	else if (typeIndex == 8)
	{
		m_activeSonarUpgrade = part;
	}
	//hydrophones
	else if (typeIndex == 9)
	{
		m_hydrophones = part;
	}
	//deck gun
	else if (typeIndex == 10)
	{
		//not implemented
	}
	//hull strength
	else if (typeIndex == 11)
	{
		m_hullUpgrade = part;
	}
	//detection related (ex: anti-sonar coating)
	else if (typeIndex == 12)
	{
		m_stealthMisc = part;
	}
}

//called on every frame where the periscope needs to be going up or down. positive numbers = up. negative numbers = down
void submarine :: periscopeRaise(double speed)
{
	if (m_periscopeHeight < 13.0f && speed > 0)
	{
		m_periscopeHeight += speed;
	}

	else if (m_periscopeHeight > 0.0f && speed < 0)
	{
		m_periscopeHeight += speed;
	}

	return void();
}

//called on every frame where the periscope need to rotate left or right. positive values for right, negative values for left
void submarine :: periscopeRotate(double spdMult)
{
	m_periscopeRotation += spdMult;
	if (m_periscopeRotation < 0) m_periscopeRotation = static_cast<int>((m_periscopeRotation + 360)) % 360;
	else if (m_periscopeRotation > 360) m_periscopeRotation = static_cast<int>(m_periscopeRotation) % 360;

	return void();
}

//returns a mostly unique id used for saving and loading based on the submarines's info
//it's not impossible for 2 submarines to have the same id, just highly unlikely. In the future, the way this function works may change
string submarine :: makeIdHashSalt()
{
	string firstPart = m_name;
	firstPart += to_string(betterRand(numberFromString(m_shipName)));

	return firstPart;
}

//takes a submarine and saves it to xml in the game-saving function
int submarine :: toSaveXml(XMLElement *dataElement, int subIndex)
{
	XMLElement *submarineData = dataElement->InsertNewChildElement("submarine");

	writeElement(submarineData, "index", subIndex);
	writeElement(submarineData, "class", m_name);
	writeElement(submarineData, "shipname", m_shipName);

	progressUpgradeSaving(submarineData, "batteryUpgrade", m_batteryUpgrade);
	progressUpgradeSaving(submarineData, "engineUpgrade", m_engineUpgrade);
	progressUpgradeSaving(submarineData, "electricEngineUpgrade", m_electricEngineUpgrade);
	progressUpgradeSaving(submarineData, "nuclearReactor", m_nuclearReactor);
	progressUpgradeSaving(submarineData, "fuelTank", m_fuelTank);
	progressUpgradeSaving(submarineData, "oxygenGenerator", m_oxygenGenerator);
	progressUpgradeSaving(submarineData, "radarUpgrade", m_radarUpgrade);
	progressUpgradeSaving(submarineData, "radarDetector", m_radarDetector);
	progressUpgradeSaving(submarineData, "activeSonarUpgrade", m_activeSonarUpgrade);
	progressUpgradeSaving(submarineData, "hydrophones", m_hydrophones);
	progressUpgradeSaving(submarineData, "hullUpgrade", m_hullUpgrade);
	progressUpgradeSaving(submarineData, "stealthMisc", m_stealthMisc);

	//create another child node and save the torpedos
	XMLElement *torpedoStorageNode = submarineData->InsertNewChildElement("torpedoStorage");

	for (int i = 0; i < torpedoStorage->size(); i++)
	{
		//XMLElement *torpedoNode = torpedoStorageNode->InsertNewChildElement("torpedo");
		if (torpedoStorage->at(i) == nullptr) writeElement(torpedoStorageNode, "torpedo", 0);
		else writeElement(torpedoStorageNode, "torpedo", torpedoStorage->at(i)->name());
		//torpedoStorageNode->InsertEndChild(torpedoNode);
	}

	submarineData->InsertEndChild(torpedoStorageNode);
	//done saving torpedo data

	XMLElement *compartmentNode = submarineData->InsertNewChildElement("compartmentData");

	for (int i=0; i < compartmentList.size(); i++)
	{
		compartmentList.at(i).toSaveXml(compartmentNode, i);
	}

	submarineData->InsertEndChild(compartmentNode);

	dataElement->InsertEndChild(submarineData);

	return 0;
}

void submarine :: loadRestOfStuffFromXml(XMLElement *dataElement)
{
	//the only stuff not already loaded at this point are
	//1. ship upgrades
	//2. crew slot locations
	//3. torpedos
	m_batteryUpgrade = findUpgradePartByName(inventoryItemDatabase,dataElement->FirstChildElement("batteryUpgrade")->GetText());
	m_engineUpgrade = findUpgradePartByName(inventoryItemDatabase,dataElement->FirstChildElement("engineUpgrade")->GetText());
	m_electricEngineUpgrade = findUpgradePartByName(inventoryItemDatabase,dataElement->FirstChildElement("electricEngineUpgrade")->GetText());
	m_nuclearReactor = findUpgradePartByName(inventoryItemDatabase,dataElement->FirstChildElement("nuclearReactor")->GetText());
	m_fuelTank = findUpgradePartByName(inventoryItemDatabase,dataElement->FirstChildElement("fuelTank")->GetText());
	m_oxygenGenerator = findUpgradePartByName(inventoryItemDatabase,dataElement->FirstChildElement("oxygenGenerator")->GetText());
	m_radarUpgrade = findUpgradePartByName(inventoryItemDatabase,dataElement->FirstChildElement("radarUpgrade")->GetText());
	m_radarDetector = findUpgradePartByName(inventoryItemDatabase,dataElement->FirstChildElement("radarDetector")->GetText());
	m_activeSonarUpgrade = findUpgradePartByName(inventoryItemDatabase,dataElement->FirstChildElement("activeSonarUpgrade")->GetText());
	m_hydrophones = findUpgradePartByName(inventoryItemDatabase,dataElement->FirstChildElement("hydrophones")->GetText());
	m_hullUpgrade = findUpgradePartByName(inventoryItemDatabase,dataElement->FirstChildElement("hullUpgrade")->GetText());
	m_stealthMisc = findUpgradePartByName(inventoryItemDatabase,dataElement->FirstChildElement("stealthMisc")->GetText());
	return void();
}

void submarine :: progressUpgradeSaving(XMLElement *dataElement, string keyName, upgradePart *part)
{
	if (part != nullptr) writeElement(dataElement, keyName.c_str(), part->getName());
	else writeElement(dataElement, keyName.c_str(), 0);

	return void();
}

double submarine :: getBatteryMultiplier()
{
	if (m_batteryUpgrade == nullptr)
	{
		return 1;
	}
	else
	{
		return m_batteryUpgrade->getRelevantStat();
	}
}

double submarine :: getDieselMultiplier()
{
	if (m_engineUpgrade == nullptr)
	{
		return 1;
	}
	else
	{
		return m_engineUpgrade->getRelevantStat();
	}
}

double submarine :: getElectricNultiplier()
{
	if (m_electricEngineUpgrade == nullptr)
	{
		return 1;
	}
	else
	{
		return m_electricEngineUpgrade->getRelevantStat();
	}
}

double submarine :: getFuelMultiplier()
{
	if (m_fuelTank == nullptr)
	{
		return 1;
	}
	else
	{
		return m_fuelTank->getRelevantStat();
	}
}

double submarine :: getHullMultiplier()
{
	if (m_hullUpgrade == nullptr)
	{
		return 1;
	}
	else
	{
		return m_hullUpgrade->getRelevantStat();
	}
}

void submarine :: setupDetailsStrings(submarine *compareSub)
{
	//updateUpgradeMultipliers();
	//cout << "running setupDetailsStrings()" << endl;
	depthString = "Safe depth " + to_string(m_safeDepth) + "m";
	depthString += lessOrBigger(m_safeDepth, static_cast<int>(compareSub->safeDepth() * compareSub->getHullMultiplier()));
	bowTorpedoString = "Bow torpedo tubes: " + to_string(m_bowTorpedoTubes);
	bowTorpedoString += lessOrBigger(m_bowTorpedoTubes, compareSub->bowTorpedoTubes());
	bowTorpedoReserve = "Bow torpedo reserves: " + to_string(m_bowReserve);
	bowTorpedoReserve += lessOrBigger(m_bowReserve, compareSub->bowReserve());
	aftTorpedoString = "Aft torpedo tubes: " + to_string(m_sternTorpedoTubes);
	aftTorpedoString += lessOrBigger(m_sternTorpedoTubes, compareSub->sternTorpedoTubes());
	aftTorpedoReserve = "Aft torpedo reserves: " + to_string(m_sternReserve);
	aftTorpedoReserve += lessOrBigger(m_sternReserve, compareSub->sternReserve());
	maxSpeedString = "Max speed (surface): " + doubleToString(m_topspeed_surface) + " knots";
	maxSpeedString += lessOrBigger(m_topspeed_surface, compareSub->topspeed_surface() * compareSub->getDieselMultiplier());
	maxSpeedSubmergedString = "Max speed (submerged): " + doubleToString(m_topspeed_submerged) + " knots";
	maxSpeedSubmergedString += lessOrBigger(m_topspeed_submerged, compareSub->topspeed_submerged() * compareSub->getElectricNultiplier());
	surfaceRange = "Surface range: " + to_string(m_range) + "nmi";
	surfaceRange += lessOrBigger(m_range, static_cast<int>(compareSub->range() * compareSub->getFuelMultiplier()));
	underwaterRange = "Underwater range: " + to_string(m_batrange) + "nmi";
	underwaterRange += lessOrBigger(m_batrange, static_cast<int>(compareSub->batRange() * compareSub->getBatteryMultiplier()));
	daysOFair = "days of air: " + doubleToString(m_air, 0);
	daysOFair += lessOrBigger(m_air, compareSub->air());
	cargoSlotsString = "Cargo slots: " + to_string(m_cargoSlots);
	cargoSlotsString += lessOrBigger(m_cargoSlots, compareSub->numCargoSlots());
	devices = "Sensors: ";
	bool hasASensor = false;
	if (m_radarUpgrade != nullptr)
	{
		devices += "radar, ";
		hasASensor = true;
	}
	if (m_activeSonarUpgrade != nullptr) 
	{
		devices += "sonar, ";
		hasASensor = true;
	}
	if (m_hydrophones != nullptr)
	{
		devices += "hydrophones";
		hasASensor = true;
	}
	if (!hasASensor)
	{
		devices += "None";
	}
}

int loadAllSubmarines(SDL_Renderer *ren, SDL_Window *win)
{
	//make a list of all present submarine file paths
	string submarinePath = "Data/submarines";
	vector<string> filePaths;

	for (const auto & entry : std::filesystem::directory_iterator(submarinePath))
	{
        std::cout << entry.path() << std::endl;
        filePaths.push_back(entry.path());
	}

	//for each encountered submarine file, load them
	for (int i = 0; i < filePaths.size(); i++)
	{
		loadSubmarineFile(filePaths.at(i), ren, win);
	}

	return 0;
}

submarine* getSubmarineByName(string name)
{
	bool foundMatch = false;
	int i = 0;
	while (!foundMatch)
	{
		if (submarineRegistry->at(i).name() == name)
		{
			foundMatch = true;
		}
		else
		{
			i++;
		}
	}

	return &submarineRegistry->at(i);
}