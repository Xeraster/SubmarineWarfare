playerInfo :: playerInfo()
{

}

playerInfo :: playerInfo(campaign *newCampaign, string captainName, string shipName, SDL_Renderer *ren)
{	
	m_playerName = captainName;
	m_submarines.push_back(*newCampaign->startSub());
	//m_submarines.at(0) = *newCampaign->startSub();
	m_tonnageSunk = 0;
	m_rank = 9;
	m_budget =  newCampaign->getFunds();
	m_payRate = newCampaign->payRate();
	m_faction = newCampaign->getFaction();
	m_submarines.at(0).loadExtraSubmarineIcons(ren);

	//note: I probably need to use a different data container than this.
	m_playerEmployees.resize(120);
	m_playerEmployees.clear();
	m_selectedSubmarineIndex = 0;
	m_qualsToHandout = 0;

	//crashes without this here
	//m_playerTorpedos->resize(1024);
	m_playerTorpedos->clear();

	//get all player-assignable awards and add their pointers to a vector
	vector<award*> awardList;
	getAwardsOfType(9, &awardList);
	for (int i = 0; i < awardList.size(); i++)
	{
		awardData thisAward;
		thisAward.amount = 0;
		thisAward.listedAward = awardList.at(i);
		assignableAwardInfo.push_back(thisAward);
	}

	cout << "loaded " << assignableAwardInfo.size() << " player-assignable awards" << endl;

	//position in the initializer doesn't matter that much since its onl for the nonexistent 2d sprite of the room
	//64 is the biggest size it can be on a 800x600 screen and seems like a good number anyway
	submarineCompartment tmpComp("barracks", 7, 64, 0, 1, 130 * gscreenx / 800, 1);
	m_barracks = tmpComp;
	//make a pointer to the selected submarine in the player's garage
	m_selectedSubmarine = &m_submarines.at(0);
	m_selectedSubmarine->setShipName(shipName);
	m_startingCampaign = newCampaign;
}

playerInfo :: ~playerInfo()
{
	//be sure not to delete the faction pointer upon destroy but you WILL need to destroy the submarine vector upon destroy
	//also, m_playerEmployees and m_recruitableEmployees will need to be deleted
	delete m_playerTorpedos;
}

void playerInfo :: generateEmployableCrew(int quantity)
{
	//clear the crew pointer before clearing the data being pointed to in order to prevent segfaults
	m_infoCardCrew = nullptr;

	m_recruitableEmployees.clear();
	cout << "cleared " << endl;
	for (int i = 0; i < quantity; i++)
	{
		m_recruitableEmployees.push_back(crewMember(crewNameGeneratorObject));
		//cout << m_recruitableEmployees.back().getFirstName() << " " << m_recruitableEmployees.back().getLastName() << ", " << m_recruitableEmployees.back().getRankString() << endl;
	}

}

//use this one to hire crew from the m_recruitableEmployees pool.
//intended for normal gameplay
void playerInfo :: hireCrew(int indexNum)
{
	m_playerEmployees.push_back(m_recruitableEmployees.at(indexNum));
	//m_playerEmployees.at(0) = m_recruitableEmployees.at(indexNum);
	//crewMember poop;
	//poop = m_recruitableEmployees.at(indexNum);
	//m_playerEmployees.push_back(poop);
	//m_playerEmployees.push_back(crewMember());
	//m_playerEmployees.back() = poop;
	//cout << m_playerEmployees.back() << endl;
	//cout << "size = " << m_playerEmployees.size() << endl;
	/*if (!m_submarines.at(0).crewToRandomCompartment(&m_recruitableEmployees.at(indexNum)))
	{
		m_playerEmployees.pop_back();
		cout << false << endl;
	}*/
	if (!m_selectedSubmarine->crewToRandomCompartment(&m_playerEmployees.back()))
	{
		m_playerEmployees.pop_back();
		cout << "false" << endl;
	}
	/*for (int i = 0; i < m_playerEmployees.size(); i++)
	{
		cout << m_playerEmployees.at(i).getFirstName() + m_playerEmployees.at(i).getLastName() << endl;
	}*/
	cout << "num hired crew = " << m_playerEmployees.size() << endl;

	m_recruitableEmployees.erase(m_recruitableEmployees.begin() + indexNum);

	m_selectedSubmarine->updateCrewCounts();

	return void();

}

//use this one to hire crew from somewhere other than the m_recruitableEmployees pool
//anything passed through this will copy the given crew person direfctly into the m_playerEmployees vector, bypassing the normal hiring system
//intended to be used for dev commands or for loading from a save
//if putInBarracks = false, crew will be spawned in the active submarine. Otherwise, the crew person will be spawned in barracks
void playerInfo :: hireSpawnedCrew(crewMember employee, bool putInBarracks)
{
	m_playerEmployees.push_back(employee);

	int slotNum;
	m_barracks.moveCrewToAnySlot(&m_playerEmployees.back(), &slotNum);
	cout << "moved loaded crew person into slot " << slotNum << " in barracks" << endl;

	return void();
}

int playerInfo :: numEmployedCrew()
{
	int count = 0;
	for (int i = 0; i < m_playerEmployees.size(); i++)
	{
		if (m_playerEmployees.at(i).isInitialized()) count++;
	}

	return count;
}

awardData* playerInfo :: getAwardData(int index)
{
	if (index > assignableAwardInfo.size()) return nullptr;
	else
	{
		return &assignableAwardInfo.at(index);
	}
}

void playerInfo :: decrementAward(award *award)
{
	int i = 0;
	while(award != assignableAwardInfo.at(i).listedAward && i < assignableAwardInfo.size())
	{
		i++;
	}

	assignableAwardInfo.at(i).amount--;
}

//=======================================================================================================
////I promise, after I get the crew barracks feature fully working, no more shitty hack fuck ass shits
//=======================================================================================================

//draw the player's barrack box
//this is basically a place to temporarily put crew if you go to a smaller submarine for a little bit
void playerInfo :: drawPlayerBarrack(SDL_Renderer *ren, int posX, int posY, int sizeX, int mouseX, int mouseY, Uint32 lastMouse, crewMember **selected)
{
	m_barracksPx = posX;
	m_barracksPy = posY;
	m_barracksSx = sizeX;
	m_barracksSy = 200;
	m_barracks.drawCrewBoxBarracks(ren, posX, posY, sizeX, mouseX, mouseY, lastMouse, selected);
}

bool playerInfo :: putCrewInBarrack(crewMember* person, int posX, int posY, int screenX)
{
	bool found = false;
	if (!isInsideBarracksBox(posX, posY))
	{
		return false;
	}

	//if didn't loop through all compartments, that means it found a match. Call that compartment's crewToSpecificSlot() function and return result
	int compartmentNum = -1;
	int slotNum = 0;
	crewMember *replacementCrew = nullptr;

	m_barracks.crewToSpecificSlotInBarracks(person, posX, posY, screenX, &slotNum, &replacementCrew);
	if (replacementCrew == nullptr)
	{
		//not replacing a crew member. Erase the duplicate pointer
		m_selectedSubmarine->findAndEraseDuplicateCrew(person, compartmentNum, slotNum);
		findAndEraseDuplicateCrew(person, slotNum);
	}
	else
	{
		//replacing a valid crew member. Set the duplicate pointer to the value of the crew member who's position got replaced
		m_selectedSubmarine->findAndReplaceDuplicateCrew(person, compartmentNum, slotNum, replacementCrew);
		findAndReplaceDuplicateCrew(person, slotNum, replacementCrew);
	}

	m_selectedSubmarine->updateCrewCounts();

	//findAndEraseDuplicateCrew(playerCampaignInfo->getInfoCardCrewPointer(), compartmentNum, slotNum);
	return true;
}

bool playerInfo :: isInsideBarracksBox(int x, int y)
{
	int xMin = m_barracksPx;
	int xMax = m_barracksPx + m_barracksSx;
	int yMin = m_barracksPy;
	int yMax = m_barracksPy + m_barracksSy;

	cout << "[b]is " << x << ", " << y << " inside of " << xMin << "-" << xMax << ", " << yMin << "-" << yMax << "?" << endl;

	if (x > xMin && x < xMax && y > yMin && y < yMax)
	{
		cout << "yes" << endl;
		return true;
	}
	else
	{
		cout << "no" << endl;
		return false;
	}
}

void playerInfo :: findAndEraseDuplicateCrew(crewMember* person, int excludeSlot)
{
	bool foundMatch = false;
	foundMatch = m_barracks.eraseDuplicateCrew(person, excludeSlot);
}

void playerInfo :: findAndReplaceDuplicateCrew(crewMember* person, int excludeSlot, crewMember* replacement)
{
	bool foundMatch = false;
	foundMatch = m_barracks.replaceDuplicateCrew(person, excludeSlot, replacement);
}

bool playerInfo :: buySubmarine(SDL_Renderer *ren, submarine *subPointer, string shipName)
{
	if (m_budget >= subPointer->cost())
	{
		m_budget -= subPointer->cost();

		m_submarines.push_back(*subPointer);
		m_submarines.back().loadExtraSubmarineIcons(ren);
		m_submarines.back().setShipName(shipName);
		cout << "player now owns " << m_submarines.size() << " submarines" << endl;
		m_selectedSubmarine = &m_submarines.back();
		return true;
	}
	else
	{
		return false;
	}
}

bool playerInfo :: getInSubmarine(int index)
{
	if (index < m_submarines.size())
	{
		m_selectedSubmarine = &m_submarines.at(index);
		return true;
	}
	else
	{
		return false;
	}
}

bool playerInfo :: canBuySubmarine(submarine *subPointer)
{
	if (m_budget >= subPointer->cost())
	{
		return true;
	}
	else
	{
		return false;
	}
}

//moves crew from barracks to the current submarine
bool playerInfo :: barracksToSubmarine()
{
	int subSailors = m_selectedSubmarine->sailors();
	int subPOs = m_selectedSubmarine->pettyOfficers();
	int subOfficers = m_selectedSubmarine->officers();
	int subTotal = subSailors + subPOs + subOfficers;

	int sailorsSoFar = 0;
	int POsSoFar = 0;
	int officersSoFar = 0;
	m_selectedSubmarine->getCrewCounts(&sailorsSoFar, &POsSoFar, &officersSoFar);
	int randomsSoFar = 0;

	//first, move each sailor to the submarine
	//do it until either there are no more sailors in barracks or the submarine has the correct amount of sailors
	for (int i = 0; i < m_barracks.numSlots(); i++)
	{
		if (m_barracks.crewInSlot(i) != nullptr)
		{
			if (m_barracks.crewInSlot(i)->getRank() < 6 && sailorsSoFar < subSailors)
			{
				m_selectedSubmarine->crewToRandomCompartment(m_barracks.crewInSlot(i));
				m_selectedSubmarine->updateCrewCounts();
				m_barracks.eraseDuplicateCrew(m_barracks.crewInSlot(i), -1);
				sailorsSoFar++;
			}
			else if (m_barracks.crewInSlot(i)->getRank() > 5 && m_barracks.crewInSlot(i)->getRank() < 9 && POsSoFar < subPOs)
			{
				m_selectedSubmarine->crewToRandomCompartment(m_barracks.crewInSlot(i));
				m_selectedSubmarine->updateCrewCounts();
				m_barracks.eraseDuplicateCrew(m_barracks.crewInSlot(i), -1);
				POsSoFar++;
			}
			else if (m_barracks.crewInSlot(i)->getRank() > 10 && officersSoFar < subOfficers)
			{
				m_selectedSubmarine->crewToRandomCompartment(m_barracks.crewInSlot(i));
				m_selectedSubmarine->updateCrewCounts();
				m_barracks.eraseDuplicateCrew(m_barracks.crewInSlot(i), -1);
				officersSoFar++;
			}
		}
	}

	//if after this is done and the submarine still doesn't have the required number of crew, more even if they aren't of the required class
	for (int i = 0; i < m_barracks.numSlots(); i++)
	{
		if (m_barracks.crewInSlot(i) != nullptr && sailorsSoFar + POsSoFar + officersSoFar + randomsSoFar < subTotal)
		{
			m_selectedSubmarine->crewToRandomCompartment(m_barracks.crewInSlot(i));
			m_selectedSubmarine->updateCrewCounts();
			m_barracks.eraseDuplicateCrew(m_barracks.crewInSlot(i), -1);
			randomsSoFar++;
		}
	}
}

bool playerInfo :: addTorpedoToSubmarine(torpedo *torpedoType)
{
	bool foundSpot = false;
	int i = 0;
	while (!foundSpot && playerEquippedSubmarine()->torpedoStorage->size() > i)
	{
		if (playerEquippedSubmarine()->torpedoStorage->at(i) == nullptr)
		{
			torpedo newTorpedo = *torpedoType;
			//cout << newTorpedo.name() << endl;
			m_playerTorpedos->push_back(newTorpedo);
			playerEquippedSubmarine()->torpedoStorage->at(i) = &m_playerTorpedos->back();
			foundSpot = true;
		}
		i++;
	}
	return foundSpot;
}

//adds a torpedo to a specific slot in the submarine. Returns 0 if success. Returns 1 if torpedo already in slot. Returns 2 if invalid slot given. If a torpedo is already in slot, it doesn't do it
int playerInfo :: addTorpedoToSubmarineSlot(torpedo *torpedoType, submarine *whichSub, int torpedoSlot)
{
	int numSubTorps = whichSub->bowTorpedoTubes() + whichSub->sternTorpedoTubes() + whichSub->bowReserve() + whichSub->sternReserve();
	
	if (numSubTorps < torpedoSlot) 
	{
		cout << "Error. Invalid torpedo slot given in playerInfo::addTorpedoToSubmarineSlot" << endl;
		return 2;
	}

	if (whichSub->torpedoStorage->at(torpedoSlot) == nullptr)
	{
		torpedo newTorpedo = *torpedoType;
		m_playerTorpedos->push_back(newTorpedo);
		whichSub->torpedoStorage->at(torpedoSlot) = &m_playerTorpedos->back();
		return 0;
	}
	else
	{
		cout << "Cannot add torpedo to slot " << torpedoSlot << " in playerInfo::addTorpedoToSubmarineSlot. Slot already occupied." << endl;
		return 1;
	}
}

bool playerInfo :: buyTorpedo(torpedo *torpedoType)
{
	if (m_budget >= torpedoType->cost())
	{
		if (addTorpedoToSubmarine(torpedoType))
		{
			m_budget -= torpedoType->cost();
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		cout << "not enough money" << endl;
		return false;
	}
}

void playerInfo :: sellTorpedo(torpedo *pointer)
{
	m_budget += pointer->cost();
	pointer->markForDeletion();
	deleteTorpedosNotify = true;
	//deletePlayerTorpedos(m_playerTorpedos);
}

int playerInfo :: applyUpgradeToSubmarine(upgradePart *upgrade)
{
	if (upgrade == nullptr)
	{
		//given part was nullptr
		return 4;
	}
	else if (m_selectedSubmarine->alreadyHasPart(upgrade))
	{
		//submarine already has the exact same part
		return 2;
	}
	else if (!m_selectedSubmarine->canHavePart(upgrade))
	{
		//submarine is not compatible with given part
		return 3;
	}
	else if (m_budget < upgrade->getCost())
	{	
		//player doesn't have enough money
		return 0;
	}
	else
	{
		//subtract cost of part from player's funds
		m_budget -= upgrade->getCost(); 

		//add the part to the submarine
		m_selectedSubmarine->putPartInSubmarine(upgrade);
	}
}

//return 0 = success. 1 = failure
//dataElement is the pointer to the element containing the player info data
int playerInfo :: playerInfoToSaveXml(XMLElement *dataElement)
{

	//first, write the basic single-line variables
	writeElement(dataElement, "playerName", m_playerName);
	writeElement(dataElement, "playerRank", m_rank);
	writeElement(dataElement, "money", m_budget);
	writeElement(dataElement, "payrate", m_payRate);
	writeElement(dataElement, "tonnageSunk", m_tonnageSunk);

	//selected submarine index isn't normally used
	writeElement(dataElement, "selectedSubmarineId", m_selectedSubmarine->makeIdHashSalt());
	writeElement(dataElement, "qualsToHandout", m_qualsToHandout);
	if (m_startingCampaign == nullptr) 
	{
		cout << "fuck campaign is nullptr" << endl;
	}
	else
	{
		//campaign type causes crash but it doesn't really matter so I'm commenting this out for now
		writeElement(dataElement, "startingCampaign", m_startingCampaign->getName());
	}
	writeElement(dataElement, "faction", m_faction->name());

	//if there are awards that need to be given out, make a new child element for it
	//if (assignableAwardInfo.size() > 0)
	//{
		XMLElement *awardsToGiveOut = dataElement->InsertNewChildElement("awardsToGiveOut");
		for (int ad = 0; ad < assignableAwardInfo.size(); ad++)
		{
			XMLElement *awardNode = awardsToGiveOut->InsertNewChildElement("award");
			writeElement(awardNode, "awardType", assignableAwardInfo.at(ad).listedAward->name());
			writeElement(awardNode, "amount", assignableAwardInfo.at(ad).amount);
			awardsToGiveOut->InsertEndChild(awardNode);
		}

		dataElement->InsertEndChild(awardsToGiveOut);

	//}

	//time for the complicated stuff.

	//crew members is within playerinfo, so the saving of this part must be managed from inside the playerinfo class
	XMLElement *hiredCrew = dataElement->InsertNewChildElement("hiredCrew");

	//for each hired crew person, get them to create their own xml section
	for (int i = 0; i < m_playerEmployees.size(); i++)
	{
		m_playerEmployees.at(i).toSaveXml(hiredCrew);
	}

	//hiredCrew->InsertEndChild(dataElement);
	dataElement->InsertEndChild(hiredCrew);

	//crew members saved. Now, it's time to save submarine data

	XMLElement *ownedSubmarines = dataElement->InsertNewChildElement("ownedSubmarines");

	for (int i = 0; i < m_submarines.size(); i++)
	{
		m_submarines.at(i).toSaveXml(ownedSubmarines, i);
	}

	//ownedSubmarines->InsertEndChild(dataElement);
	dataElement->InsertEndChild(ownedSubmarines);

	return 0;

}

//return 0 = success. 1 = failure
//dataElement is the pointer to the element containing the player info data
int playerInfo :: playerInfoFromXml(XMLElement *dataElement, SDL_Renderer *ren)
{
	m_rank = atoi(dataElement->FirstChildElement("playerRank")->GetText());
	m_budget = atof(dataElement->FirstChildElement("money")->GetText());
	m_payRate = atof(dataElement->FirstChildElement("payrate")->GetText());
	m_tonnageSunk = atof(dataElement->FirstChildElement("tonnageSunk")->GetText());
	string selectedSubmarineId = dataElement->FirstChildElement("selectedSubmarineId")->GetText();
	m_qualsToHandout = atoi(dataElement->FirstChildElement("qualsToHandout")->GetText());
	string factionName = dataElement->FirstChildElement("faction")->GetText();
	m_faction = getFactionByName(factionName);

	//load assignable awards
	XMLElement *awardsToGiveOutElement = dataElement->FirstChildElement("awardsToGiveOut")->FirstChildElement("award");
	while (awardsToGiveOutElement != nullptr)
	{
		string type = awardsToGiveOutElement->FirstChildElement("awardType")->GetText();
		int amount = atoi(awardsToGiveOutElement->FirstChildElement("amount")->GetText());
		for (int az = 0; az < assignableAwardInfo.size(); az++)
		{
			if (assignableAwardInfo.at(az).listedAward->name() == type)
			{
				assignableAwardInfo.at(az).amount = amount;
			}
		}
		awardsToGiveOutElement = awardsToGiveOutElement->NextSiblingElement("award");
	}

	//that was the simple stuff. Now, to do the complicated stuff

	//let's do hired crew first
	//step 1. for each crew person in the <hiredCrew> element, instantiate them from their respective <crewMember> node and move them to m_barracks
		XMLElement *hiredCrewElement = dataElement->FirstChildElement("hiredCrew")->FirstChildElement("crewMember");
		while (hiredCrewElement != nullptr)
		{
			//replicate crew person and add to barracks
			hireSpawnedCrew(crewMember(hiredCrewElement), true);
			//set pointer to next element in preparation for next iteration
			hiredCrewElement = hiredCrewElement->NextSiblingElement("crewMember");
		}
		//step 1a. create crew person, add them to submarine whatever submarine is loaded into index 0 in the current instance
		//step 1b. run moveEveryoneToBarracks() on the index 0 submarine instance

	//step 2. import the submarines from the ownedSubmarines node

	//clear current list of submarines. Be sure to check this for bugs because it seems like the type of thing that would cause lots of bugs
	m_submarines.clear();

	XMLElement *submarineNodes = dataElement->FirstChildElement("ownedSubmarines")->FirstChildElement("submarine");
	while (submarineNodes != nullptr)
	{
		//add submarine to list of player's owned submarines

		m_submarines.push_back(*getSubmarineByName(submarineNodes->FirstChildElement("class")->GetText()));
		m_submarines.back().loadExtraSubmarineIcons(ren);
		m_submarines.back().setShipName(submarineNodes->FirstChildElement("shipname")->GetText());

		//now, load the torpedos from the xml file into the submarine
		int t=0;
		XMLElement *subTorps = submarineNodes->FirstChildElement("torpedoStorage")->FirstChildElement("torpedo");
		while (subTorps != nullptr)
		{

			torpedo *newTorpedo = getTorpedoByName(subTorps->GetText());
			if (newTorpedo != nullptr) addTorpedoToSubmarineSlot(newTorpedo, &m_submarines.back(), t);

			//set pointer to next element (if it exists)
			subTorps = subTorps->NextSiblingElement("torpedo");

			//increment pointer to keep the torpedo slots correct
			t++;
		}

		//torpedos have been loaded. Now, load submarine upgrades
		//the last remaining variables (currently just upgrades) get loaded using the submarine class
		m_submarines.back().loadRestOfStuffFromXml(submarineNodes);

		cout << "there are now " << m_submarines.size() << " submarines loaded into this save file" << endl;
		m_selectedSubmarine = &m_submarines.back();

/*
================================================================================================================
		warning: the code in this block is a big ugly annoying ass fuck
================================================================================================================
*/

		//if the submarine being loaded has the same id hash as "selectedSubmarineId", then it may be occupied with crew
		//in this case, figure out which crew go where
		if (selectedSubmarineId == m_submarines.back().makeIdHashSalt())
		{
			cout << "selected submarine id = " << selectedSubmarineId << endl;
			XMLElement *compartmentNodes = submarineNodes->FirstChildElement("compartmentData")->FirstChildElement("compartment");
			while (compartmentNodes != nullptr)
			{
				int compIndex = atoi(compartmentNodes->FirstChildElement("index")->GetText());
				//cout << compartmentNodes->FirstChildElement("slot0")->GetText() << endl;;
				//cout << "compartment index to check = " << compIndex << endl; 
				//m_selectedSubmarine->compartmentList.at(compIndex)
				for (int p=0; p < m_selectedSubmarine->compartmentList.at(compIndex).numSlots(); p++)
				{
					//compartmentList.
					//cout << "checking slot" << p << endl;
					string correctSlotName = "slot"+to_string(p);
					if (compartmentNodes->FirstChildElement(correctSlotName.c_str()) != nullptr)
					{
						string crewIdHash = compartmentNodes->FirstChildElement(correctSlotName.c_str())->GetText();
						//cout << "checking slot" << p << " = "<< crewIdHash << endl;
						if (crewIdHash != "0")
						{
							//cout << "crewidhash = " << crewIdHash << endl;
							//1. find crew with same id in barracks
							int foundIndexMatch = -1;
							for (int c = 0; c < m_barracks.numSlots(); c++)
							{
								if (m_barracks.crewInSlot(c) != nullptr && m_barracks.crewInSlot(c)->makeIdHashSalt() == crewIdHash)
								{
									cout << "is " << crewIdHash << " == " << m_barracks.crewInSlot(c)->makeIdHashSalt() << endl;
									foundIndexMatch = c;
									c = m_barracks.numSlots() + 1;
								}
							}

							//2. copy pointer into this position in this compartment
							m_selectedSubmarine->compartmentList.at(compIndex).crewToSlotNumber(m_barracks.crewInSlot(foundIndexMatch), p);

							//3. set original position in barracks to nullptr
							m_barracks.eraseDuplicateCrew(m_barracks.crewInSlot(foundIndexMatch), -1);
						}
					}
				}
				
				//advance the pointer to the next compartment to process
				compartmentNodes = compartmentNodes->NextSiblingElement("compartment");
			}
			//finally, update the submarine display variables to reflect any crew position loading that may have happened
			m_selectedSubmarine->updateCrewCounts();

/*
================================================================================================================
		ok that's the end of the big ugly annoying ass fuck
================================================================================================================
*/

		}
		//set pointer to next element in preparation for next iteration
		submarineNodes = submarineNodes->NextSiblingElement("submarine");
	}

	//switch to whatever the saved submarine index is
	//Be sure to check this for bugs because it seems like the type of thing that would cause lots of bugs
	m_selectedSubmarine = findSubmarineFromHash(selectedSubmarineId);
	if (m_selectedSubmarine == nullptr) m_selectedSubmarine = &m_submarines.back();

}

submarine* playerInfo :: findSubmarineFromHash(string hash)
{
	for (int i = 0; i < m_submarines.size(); i++)
	{
		if (m_submarines.at(i).makeIdHashSalt() == hash)
		{
			return &m_submarines.at(i);
		}
	}

	cout << "error. Could not find submarine with requested id hash" << endl;
	return nullptr;
}