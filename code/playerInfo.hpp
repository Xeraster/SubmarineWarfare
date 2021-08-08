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