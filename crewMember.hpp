crewMember :: crewMember()
{
	//cout << "creating blank crewmember object" << endl;

	m_init = false;
}

crewMember :: crewMember(crewNameGenerator *randomNameObject)
{
	//fake a seed by just making it random
	uint32_t blepSeed = rand() % 1000000;

	//assign a name and gender
	initialSetupStep(randomNameObject, blepSeed);

	//generate a rank
	rank = randomRank(blepSeed + 1);

	//generate a general skill level (will proabably change in the future)
	generateSkillset(blepSeed);

	//generate wage based on rank
	wage = randomWage(blepSeed + 6);

	setupButtons();
	m_employedByPlayer = false;
	m_isSelected = false;
	m_selectable = false;
	m_slotNumber = -1;
	m_init = true;
	m_infoCardCanDrop = false;

	crewQualifications = new vector<qualification*>;
	crewAwards = new vector<award*>;
}

crewMember :: crewMember(crewNameGenerator *randomNameObject, uint32_t seed)
{	
	//assign a name and gender
	initialSetupStep(randomNameObject, seed);

	//generate a rank
	rank = randomRank(seed);

	//generate a general skill level (will proabably change in the future)
	generateSkillset(seed);

	//generate wage based on rank
	wage = randomWage(seed + 1);

	setupButtons();
	m_employedByPlayer = false;
	m_isSelected = false;
	m_selectable = false;
	m_slotNumber = -1;
	m_init = true;
	m_infoCardCanDrop = false;

	crewQualifications = new vector<qualification*>;
	crewAwards = new vector<award*>;
}

//assign name and gender
void crewMember :: initialSetupStep(crewNameGenerator *randomNameObject, uint32_t seed)
{
	if (betterRand(seed + 69420) % 1000 > 510)
	{
		gender = 1;
	}
	else
	{
		gender = 0;
	}

	firstname = randomNameObject->randomName(gender, seed + 69421);
	lastname = randomNameObject->randomLastName(seed + 69422);
	age = randomAge(seed + 42152, 15, 42);
	generateSexProperties(seed);
}

void crewMember :: generateSexProperties(uint32_t seed)
{
	penisLength = generatePenisLength(seed);
	breastSize = generateBreastSize(seed);
	stripperVariant = betterRand(seed+4252) % 4;
	anusType = returnAnusType(seed);
	pubicHair = returnHairType(seed);
	sexualityIndex = betterRand(seed + 696969) % (sexualities->size());
	fetishIndex = betterRand(seed + 6969696969) % (fetishes->size() );
}

string crewMember :: returnAnusType(uint32_t seed)
{
	int anusCoeficient = betterRand(seed+69) % 11;
	switch(anusCoeficient)
	{
		case 0:
			return "Hairy";
		case 1:
			return "Micro";
		case 2:
			return "Tight";
		case 3:
			return "Sweaty";
		case 4:
			return "Smelly";
		case 5:
			return "Bleached";
		case 6:
			return "Small";
		case 7:
			return "Average";
		case 8:
			return "Large";
		case 9:
			return "Gaping";
		case 10:
			return "Clean Shaven";
		default:
			return "Shitty";
	}
}

string crewMember :: returnHairType(uint32_t seed)
{
	int hairCoeficient = betterRand(seed+420000) % 8;

	switch(hairCoeficient)
	{
		case 0:
			return "Large bush";
		case 1:
			return "Trimmed bush";
		case 2:
			return "Greasy and hairy";
		case 3:
			return "Bikini waxed";
		case 4:
			return "Clean shaven";
		case 5:
			return "Landing strip";
		case 6:
			return "Partial bikini wax";
		case 7:
			return "The heart (waxed)";
		default:
			return "Medium bush";
	}
}

int crewMember :: randomRank(uint32_t seed)
{
	return betterRand(seed + 3) % (11-1) + 1;
}

//generate a payrate that loosely corresponds with the crew member's rank
//prisoner: nothing
//prostitutes / assistant clowns: 100
//strippers / clowns: 120
//recruit: 200
//sailor apprentice: 250
//sailor: 350
//po 3rd class: 450
//po 2nd class: 550
//po 1st class: 650
//above 650
double crewMember :: randomWage(uint32_t seed)
{
	switch (rank)
	{
		case 0:
			return 0;
		case 1:
			return 100 + (betterRand(seed) % 15);
		case 2:
			return 120 + (betterRand(seed) % 70);
		case 3:
			return 200 + (betterRand(seed) % 50);
		default:
			return 350 + 100*(rank - 4) + (betterRand(seed) % 75);
	}
}

int crewMember :: randomAge(uint32_t seed, int minAge, int maxAge)
{
	return (betterRand(seed) % (maxAge - minAge)) + minAge;
}

//0 = prisoner. 1 = entertainer lvl 1. 2 = entertainer lvl 2. 3 = recruit. 4 = apprentice. 5 = seaman
//6 = pettyofficer 3rd class. 7 = pettyofficer 2nd class. 8 = pettyofficer 1st class. 9 = chief pettyofficer. 10 = senior chief pettyofficer. 11 = master chief pettyofficer
//12 = command master chief pettyofficer. 13 = fleet master chief pettyofficer. 14 = master chief pettyofficer of the navy
string crewMember :: getRankString()
{
	switch(rank)
	{
		case 0:
			return "Prisoner";
		case 1:
			if (gender == 0) return "Prostitute";
			else return "Assistant Clown";
		case 2:
			if (gender == 0) return "Stripper";
			else return "Clown";
		case 3:
			return "Seaman Recruit";
		case 4:
			return "Seaman Apprentice";
		case 5:
			return "Seaman";
		case 6:
			return "Petty Officer 3rd class";
		case 7:
			return "Petty Officer 2nd class";
		case 8:
			return "Petty Officer 1st class";
		case 9:
			return "Chief Petty Officer";
		case 10:
			return "Senior Chief Petty Officer";
		case 11:
			return "Master Chief Petty Officer";
		case 12:
			return "Command Master Chief Petty Officer";
		case 13:
			return "Fleet Master Chief Petty Officer";
		case 14:
			return "Fleet Master Chief Petty Officer";

		default:
			return "Professional dumbass";
	}
}

string crewMember :: generateBreastSize(uint32_t seed)
{
	if (gender == 1)
	{ 
		return "N/A";
	}
	else
	{
		string size = to_string((betterRand(seed + 66) % (38 - 30)) + 30);
		string sizeToAdd;
		int boobLetter = betterRand(seed + 552) % 7;
		switch (boobLetter)
		{
			case 0:
				sizeToAdd = "A";
				break;
			case 1:
				sizeToAdd = "B";
				break;
			case 2:
				sizeToAdd = "C";
				break;
			case 3:
				sizeToAdd = "D";
				break;
			case 4:
				sizeToAdd = "DD";
				break;
			case 5:
				sizeToAdd = "DDD";
				break;
			case 6:
				sizeToAdd = "DDDD";
				break;
			case 7:
				sizeToAdd = "DDDDD";
				break;
			default:
				sizeToAdd = "DDDDDD";
		}
		return size + sizeToAdd;
	}
}

double crewMember :: generatePenisLength(uint32_t seed)
{
	double newpenisLength = (betterRand(seed) % 11) + 1;
	double penisInchesDecimal = betterRand(seed + 1) % 100;
	penisInchesDecimal /= 100.0f;
	newpenisLength += penisInchesDecimal;

	//if person does not have penis, the penis variable will instead measure their vagina depth
	if (!hasPenis()) newpenisLength *= -1; 

	return newpenisLength;
}

int crewMember :: generateSkillset(uint32_t seed)
{	
	if (rank < 6) skill = (betterRand(seed + 99) % 7) + 1; //if rank is at or below seaman
	else if (rank < 9) skill = (betterRand(seed+101) % 14 - 5) + 5; 	//if rank is at or below pettyofficer 1st class
	else skill = (betterRand(seed+45) % 20) + 1;

	//no one should have a seafaring skill below 1
	if (skill < 1) skill = 1;

	//random intelligence, Entirely random regardless of class. Minimum generated value is 1
	intelligence = (betterRand(seed+169) % 20) + 1;

	//prostitutes have a better chance of having a high sex skill
	//it's still possible to have a prostitute that "has barely head of" sex. It intend to keep it that way because it's funny
	sexiness = (betterRand(seed+170) % 17) + 1;
	if (gender == 0 && rank > 0 && rank < 3) 
	{
		if (betterRand(seed+4) % 10 > 5) sexiness = (betterRand(seed+170) % 14) + 7;
		else sexiness = (betterRand(seed+170) % 20) + 1;
	}

	//gets recalculated in configureSpecialJobType()
	wizardingSkill = betterRand(seed + 926) % 3;

	configureSpecialJobType(seed+2);
}

void crewMember :: configureSpecialJobType(uint32_t seed)
{
	if (rank < 10)
	{
		wizard = false;
		scientist = false;
	}
	else
	{
		if (betterRand(seed+9) % 1000 > 600)
		{
			if (isCapableOfWitchcraft() == true) 
			{
					wizard = true; 
					scientist = false;
					wizardingSkill = (betterRand(seed + 444) % (15)) + 6;
					//cout << wizardingSkill << endl;
			}
			else
			{
					wizard = false; 
					scientist = true;
			}
		}
		else
		{
			wizard = false;
			scientist = false;
		}
	}
}

string crewMember :: printVaginaSize()
{
	if (penisLength > -2) return "micro";
	else if (penisLength > -4) return "tight";
	else if (penisLength > -5) return "tight";
	else if (penisLength > -7) return "average";
	else if (penisLength > -9) return "large";
	else if (penisLength > -11) return "gaping";
	else return "enourmous";
}

string crewMember :: getFetishString()
{
	return fetishes->at(fetishIndex);
}

string crewMember :: getSexualityString()
{
	return sexualities->at(sexualityIndex);
}

//if mouseX = -1 or mouseY = -1, icon is not selectable via mouse pointer collision
void crewMember :: drawIcon(SDL_Renderer *ren, int posX, int posY, int sizeX, int sizeY, int mouseX, int mouseY, Uint32 lastMouse, crewMember **selected, bool draggableIcon)
{
	int spriteIndex = 0;
	if (rank == 0)
	{
		spriteIndex = 0;
		if (hasPenis()) spriteIndex++;
	}
	else if (rank < 3)
	{
		spriteIndex = getStripperVariant() + 2;
		if (hasPenis()) spriteIndex = 6;
	}
	else if (rank < 6)
	{
		spriteIndex = 7;
		if (hasPenis()) spriteIndex++;
	}
	else if (rank < 9)
	{
		spriteIndex = 9;
		if (hasPenis()) spriteIndex++;
	}
	else
	{
		spriteIndex = 11;
		if (isWizard()) spriteIndex += 2;
		else if (isScientist()) spriteIndex += 4;
		if (hasPenis()) spriteIndex++;
	}

	//if neither mouseX or mouseY are -1, that means the icon is selectable via mouse collision
	
	if (m_isSelected && m_selectable && lastMouse == SDL_BUTTON(SDL_BUTTON_LEFT) && draggableIcon)
	{
		posX = mouseX - (sizeX / 2);
		posY = mouseY - (sizeY / 2);
	}

	else if (lastMouse != SDL_BUTTON(SDL_BUTTON_LEFT) && m_isSelected && m_selectable && draggableIcon)
	{
		m_isSelected = false;
		m_selectable = false;
	}

	else if (mouseX > -1 && mouseY > -1)
	{
		if (mouseX > posX && mouseX < posX + sizeX && mouseY > posY && mouseY < posY + sizeY)
		{
			//if mouse over and click
			if (lastMouse == SDL_BUTTON(SDL_BUTTON_LEFT) && m_selectable)
			{
				color clickColor(255,150,0,255);
				drawRect(ren, clickColor, posX, posY, sizeX, sizeY);
				*selected = this;
				posX = mouseX - (sizeX / 2);
				posY = mouseY - (sizeY / 2);
				m_isSelected = true;

			}
			//if mouse over but not click
			else if (lastMouse != SDL_BUTTON(SDL_BUTTON_LEFT))
			{
				if (selectedQual != nullptr)
				{
					//cout << "selectedQual is not a nullptr" << endl;
					menuDecrementQualification = giveQualification(selectedQual);
				}
				if (selectedAward != nullptr)
				{
					//cout << "selectedQual is not a nullptr" << endl;
					menuDecrementAward = giveAward(selectedAward);
				}
				m_selectable = true;
				m_isSelected = false;
				color selectionColor(255,255,0,255);
				drawRect(ren, selectionColor, posX, posY, sizeX, sizeY);
			}
		}
		else
			{
				m_selectable = false;
				m_isSelected = false;
			}

	}
	/*else if (lastMouse != SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		m_isSelected = false;
		m_selectable = false;
	}*/

	renderTextureEx(crewicons_Large.at(spriteIndex), ren, posX, posY, sizeX, sizeY, 0);

	for (int i = 0; i < crewQualifications->size(); i++)
	{
		//draw the qualification icon
		crewQualifications->at(i)->draw(ren, posX + (sizeX/2), posY + ((2*sizeY/3)) - (sizeX/1.5*i), sizeX/1.3, sizeX/1.3);
	}
}

//return = is player pressing "hire" button or not (true for yes, false for no)
crewMember* crewMember :: drawRecruitmentInfoCard(SDL_Renderer *ren, int posX, int posY, int sizeX, int sizeY, int mouseX, int mouseY, Uint32 lastMouse, bool *mouseClicked)
{
	int textSize = 7 * (sizeY/50);
	color darkBlack(0,0,0,150);
	color white(255,255,255,255);
	drawRectFilled(ren, darkBlack, posX, posY, sizeX, sizeY);
	int calculatedX = static_cast<double>(sizeY) * 15.00 / 40.00;
	drawIcon(ren, posX, posY, calculatedX, sizeY, -1, -1, lastMouse, nullptr);
	//drawTextWrapped - a stupid but easy way to draw 3 scalable lines
	drawText(ren, textSize, white, firstname + " " + lastname, posX + calculatedX + 1, posY - 2);
	drawText(ren, textSize, white, getRankString(), posX + calculatedX + 1, posY + (sizeY / 3) - 2);
	drawText(ren, textSize, white, "$" + to_string(getWage()).substr(0, to_string(getWage()).size() - 4) + "/week", posX + calculatedX + 1, posY + ((sizeY / 3) * 2) - 2);

	hiringButton.setPos(posX + sizeX, posY);
	*mouseClicked = hiringButton.draw(ren, mouseX, mouseY, lastMouse);

	//check mouse collisions
	if (mouseX > posX && mouseX < posX + sizeX && mouseY > posY && mouseY < posY + sizeY)
	{
		if (lastMouse == SDL_BUTTON(SDL_BUTTON_LEFT))
		{	
			//reset tab index
			//commented out because it got changed to a global variable
			//m_infoType = 0;
			color yellow(255,255,0,255);
			drawRect(ren, yellow, posX - 1, posY - 1, sizeX + 2, sizeY + 2);
			m_isSelected = true;

			return this;
		}
		else
		{
			color orange(255,150,0,255);
			drawRect(ren, orange, posX - 1, posY - 1, sizeX + 2, sizeY + 2);
		}
	}
	else
	{
		m_isSelected = false;
	}

	return nullptr;
}

//return true if "close infocard" button clicked
bool crewMember :: drawInfoCard(SDL_Renderer *ren, int posX, int posY, int sizeX, int sizeY, int mouseX, int mouseY, Uint32 lastMouse)
{
	//give it the correct ratio for all screen sizes
	int textSize = 8 * (static_cast<double>(sizeY) / static_cast<double>(195));
	int iconSize = 20 * (static_cast<double>(sizeY) / static_cast<double>(195));
	int tabTextSize = 6 * (sizeY / 195);
	if (textSize < 3) textSize = 5;
	if (tabTextSize < 2) tabTextSize = 4; 

	color white(255,255,255,255);
	color darkBlack(0,0,0,150);
	drawRectFilled(ren, darkBlack, posX, posY, sizeX, sizeY);
	drawIcon(ren, posX + 2, posY + 2, 30, 80, -1, -1, lastMouse, nullptr);

	defaultTab.setFontSize(tabTextSize);
	skillsTab.setFontSize(tabTextSize);
	sexTab.setFontSize(tabTextSize);
	personnelButton.setFontSize(tabTextSize);

	personnelButton.setPos(skillsTab.posX() - personnelButton.sizeX() - 5, posY);
	defaultTab.setPos(personnelButton.posX() - defaultTab.sizeX() - 5, posY);
	skillsTab.setPos(sexTab.posX() - skillsTab.sizeX() - 5, posY);
	sexTab.setPos(posX + sizeX - sexTab.sizeX() - 5, posY);

	if (defaultTab.draw(ren, mouseX, mouseY, lastMouse)) m_infoType = 0;
	else if (skillsTab.draw(ren, mouseX, mouseY, lastMouse)) m_infoType = 1;
	else if (sexTab.draw(ren, mouseX, mouseY, lastMouse)) m_infoType = 2;
	else if (personnelButton.draw(ren, mouseX, mouseY, lastMouse)) m_infoType = 3;

	if (m_infoType == 0)
	{
		if (textSize < 6)
		{
			drawText(ren, tabTextSize, white, firstname + " " + lastname, posX + 35, posY + getTextYSize(tabTextSize));
			drawText(ren, tabTextSize, white, getRankString(), posX + 35, posY + (getTextYSize(tabTextSize))*2);
			drawText(ren, tabTextSize, white, "$" + to_string(getWage()).substr(0, to_string(getWage()).size() - 4) + " per week", posX + 35, posY + (getTextYSize(tabTextSize))*3);
			drawText(ren, tabTextSize, white, to_string(getAge()) + " years old", posX + 35, posY + (getTextYSize(tabTextSize))*4);
		}
		else
		{
			drawText(ren, textSize, white, firstname + " " + lastname, posX, posY + 90);
			drawText(ren, textSize, white, getRankString(), posX, posY + 90 + getTextYSize(textSize));
			drawText(ren, textSize, white, "$" + to_string(getWage()).substr(0, to_string(getWage()).size() - 4) + " per week", posX, posY + 90 + (getTextYSize(textSize) * 2));
			drawText(ren, textSize, white, to_string(getAge()) + " years old", posX, posY + 90 + (getTextYSize(textSize) * 3));
		}
	}
	else if (m_infoType == 1)
	{
		/*if (textSize > 5)
		{
			drawText(ren, textSize, white, firstname + " " + lastname, posX, posY + 90);
			drawText(ren, textSize, white, getRankString(), posX, posY + 90 + getTextYSize(textSize));
			drawText(ren, textSize, white, "$" + to_string(getWage()).substr(0, to_string(getWage()).size() - 4) + " per week", posX, posY + 90 + (getTextYSize(textSize) * 2));
			drawText(ren, textSize, white, to_string(getAge()) + " years old", posX, posY + 90 + (getTextYSize(textSize) * 3));
		}*/

		drawText(ren, tabTextSize, white, "Seafaring: " + skillAsString(skill) + "(" + to_string(skill) + ")", posX + 45, posY + getTextYSize(tabTextSize));
		drawText(ren, tabTextSize, white, "Witchcraft: " + skillAsString(wizardingSkill) + "(" + to_string(wizardingSkill) + ")", posX + 45, posY + (getTextYSize(tabTextSize))*2);
		drawText(ren, tabTextSize, white, "Intelligence: " + skillAsString(intelligence) + "(" + to_string(intelligence) + ")", posX + 45, posY + (getTextYSize(tabTextSize))*3);
		drawText(ren, tabTextSize, white, "Sex: " + skillAsString(sexiness) + "(" + to_string(sexiness) + ")", posX + 45, posY + (getTextYSize(tabTextSize))*4);
		if (crewQualifications->size() > 0)
		{
			drawText(ren, tabTextSize, white, "Qualifications:", posX + 45, posY + (getTextYSize(tabTextSize))*5);
			for (int i = 0; i < crewQualifications->size(); i++)
			{
				//crewQualifications->at(i)->draw(ren, posX + 45, posY + (getTextYSize(tabTextSize))*(6+i), 20 * gscreeny / 600, 20 * gscreeny / 600);
				//drawText(ren, tabTextSize, white, "  " + crewQualifications->at(i)->name() , posX + 45 + (20 * gscreeny / 600), posY + (getTextYSize(tabTextSize))*(6+i));
				crewQualifications->at(i)->draw(ren, posX + 45, posY + (getTextYSize(tabTextSize)*6)+(20 * gscreeny / 600 * i), 20 * gscreeny / 600, 20 * gscreeny / 600);
				drawText(ren, tabTextSize, white, "  " + crewQualifications->at(i)->name() , posX + 45 + (20 * gscreeny / 600), posY + (getTextYSize(tabTextSize)*6)+(20 * gscreeny / 600 * i));
			}
		}
	}
	else if (m_infoType == 2)
	{
		//why include this? Someone was just going to make a sex mod anyway whether I like it or not. I merely saved people the trouble of doing it themselves
		drawText(ren, textSize, white, "Gender: " + genderToString(), posX + 35, posY + getTextYSize(tabTextSize));
		drawText(ren, textSize, white, "Sexuality: " + getSexualityString(), posX + 35, posY + getTextYSize(tabTextSize) + (getTextYSize(textSize)*1));
		drawText(ren, textSize, white, "Fetish: " + getFetishString(), posX + 35, posY + getTextYSize(tabTextSize) + (getTextYSize(textSize)*2));
		drawText(ren, textSize, white, "Pubic hair: " + getPubicHair(), posX + 35, posY + getTextYSize(tabTextSize) + (getTextYSize(textSize)*3));
		drawText(ren, textSize, white, "Anus: " + getAnusType(), posX + 35, posY + getTextYSize(tabTextSize) + (getTextYSize(textSize)*4));


		if (!hasPenis())
   		{
   			drawText(ren, textSize, white, "Breast size: " + getBreastSize(), posX + 35, posY + getTextYSize(tabTextSize) + (getTextYSize(textSize)*5));
   			drawText(ren, textSize, white, "Vagina type: " + printVaginaSize(), posX + 35, posY + getTextYSize(tabTextSize) + (getTextYSize(textSize)*6));
    	}
    	else
    	{
    		drawText(ren, textSize, white, "Penis length: " + to_string(getPenisLength()) + "in", posX + 35, posY + getTextYSize(tabTextSize) + (getTextYSize(textSize)*5));
    	}
	}
	else if (m_infoType == 3)
	{
		drawText(ren, textSize, white, firstname + " " + lastname, posX + 35, posY + getTextYSize(tabTextSize));
		drawText(ren, textSize, white, "Awards: ", posX + 35, posY + getTextYSize(tabTextSize) + (getTextYSize(textSize)*1));
		if (crewAwards->size() == 0) drawText(ren, textSize, white, "none", posX + 35, posY + getTextYSize(tabTextSize) + (getTextYSize(textSize)*2));
		for (int i = 0; i < crewAwards->size(); i++)
		{
			crewAwards->at(i)->draw(ren, posX + 35 + (iconSize*(i%12)), (posY + getTextYSize(tabTextSize) + (getTextYSize(textSize)*2)) + (static_cast<int>(i/12)*iconSize), iconSize, iconSize);
		}
	}

	if (mouseX > posX && mouseX < posX + sizeX && mouseY > posY && mouseY < posY + sizeY && lastMouse == SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		m_infoCardCanDrop = true;
	}
	else if (mouseX > posX && mouseX < posX + sizeX && mouseY > posY && mouseY < posY + sizeY && lastMouse != SDL_BUTTON(SDL_BUTTON_LEFT) && m_infoCardCanDrop)
	{
		m_infoCardCanDrop = false;
		if (selectedQual != nullptr)
		{
			menuDecrementQualification = giveQualification(selectedQual);
		}
		if (selectedAward != nullptr)
		{
			menuDecrementAward = giveAward(selectedAward);
		}
	}
	else
	{
		m_infoCardCanDrop = false;
	}


	return false;
}

string crewMember :: skillAsString(int skillLevel, bool isSexRelated)
{
	if(skillLevel > 20 || skillLevel < 0) return skillStringArray[21];
	else return skillStringArray[skillLevel];
}

int crewMember :: promote()
{
	if (rank < 14) 
	{
		rank++;
	}
	else return 1;
	return 0;
}

int crewMember :: demote()
{	
	if (rank > 0) 
	{
		rank--;
	}
	else return 1;
	return 0;
}

//returns the amount of "manpower" that a crew member is able to output
double crewMember :: manpower(int compartmentType)
{
	//how much a seafaring skill level of 20 multiplies the manpower
	double maxSkillMultiplier = 1.8;

	//how much a seafaring skill level of 1 multiplies the manpower
	double minSkillMultiplier = 0.3;

	double skillMultiplier = (((maxSkillMultiplier - minSkillMultiplier)/20)*skill) + minSkillMultiplier;

	double rankBounus = static_cast<double>(rank) * 3 / 14;

	double qualificationBonus = 0;

	int qualificationId = 0;

	switch (compartmentType)
	{
		//bow torpedo
		case 0:
			qualificationId = 12;
			break;
		//stern torpedo
		case 1:
			qualificationId = 12;
			break;
		//diesel engines
		case 2:
			qualificationId = 5;
			break;
		//electric engines
		case 3:
			qualificationId = 5;
			break;
		//bow crew quarters is also the medbay
		case 4:
			qualificationId = 6;
			break;
		//command room
		case 5:
			qualificationId = 4;
			break;
		//radio room
		case 6:
			qualificationId = 8;
			break;
		//cargo bay
		case 7:
			qualificationId = 14;
			break;
		case 8:
			qualificationId = 11;
			break;
		case 9:
			qualificationId = 9;
			break;
		case 10:
			qualificationId = 7;
			break;
		case 11:
			qualificationId = 3;
			break;
		//clowning center
		case 12:
			qualificationId = 15;
			break;
		//scorcery
		case 13:
			qualificationId = 10;
			break;
		//stern crew quarters gets the "medic" icon
		case 14:
			qualificationId = 6;
			break;

	}

	if (hasQualification(qualificationId)) qualificationBonus = 1;

	double finalResult = (1 * skillMultiplier) + rankBounus + qualificationBonus;

	return finalResult;
}

//prostitutes/strippers are only allowed to be given a sex qualification
//clowns/assistant clowns are only allowed to be given a clowning qualification
//sailors are not allowed to be given a qualification (but if they were a clown or prostitute and got promoted to sailor, they keep their qualification)
//pettyofficers are allowed 1 of any qualification as well as, in addition, either a sex or clowning qualification
//officers are allowed 3 of any qualification. Clowning and sex qualifications count against this limit of 3 the same way any other qualification does
//returns false if was unable to give qualification based on the above rules
//returns true if was able to give qualification and was still within the above rules
bool crewMember :: giveQualification(qualification *qual)
{
	//double qualifications are not allowed
	if (hasQualification(qual->type())) return false;

	if (rank < 3)
	{	
		//if trying to give sex qualification to a stripper or prostitute
		if (gender == 0 && qual->type() == 11)
		{
			crewQualifications->push_back(qual);
			return true;
		}
		//if trying to give clowning qualification to a clown or assistant clown
		else if (gender == 1 && qual->type() == 15)
		{
			crewQualifications->push_back(qual);
			return true;
		}
		//if person is a clown or prostitute and the attempt is to give a qualification other than clowning or sex
		else
		{	
			//no can do bruh
			return false;
		}
	}
	//if person is a sailor
	else if (rank > 2 && rank < 6)
	{
		//sailors can't have qualifications
		//if they had a sex or clowning qualification when they used to be a rank lower than seaman recruit, they keep their qualification
		return false;
	}
	//if person is a pettyofficer
	else if (rank > 5 && rank < 9)
	{
		//if a pettyofficer currently has 0 qualifications, they can be given any qualification
		if (crewQualifications->size() == 0)
		{
			crewQualifications->push_back(qual);
			return true;
		}
		else if (crewQualifications->size() == 1)
		{
			//if pettyofficer already has 1 qualification but its either a sex or clowning qualification
			if (crewQualifications->at(0)->type() == 15 || crewQualifications->at(0)->type() == 11)
			{
				crewQualifications->push_back(qual);
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	//if an officer and currently holds less than 3 qualifications
	else if (rank > 8 && crewQualifications->size() < 3)
	{
		crewQualifications->push_back(qual);
		return true;
	}

	return false;
}

bool crewMember :: hasQualification(int typeId)
{
	int i = 0;
	if (crewQualifications->size() == 0) return false;
	bool foundMatch = false;

	while (i < crewQualifications->size())
	{
		if (typeId == crewQualifications->at(i)->type())
		{
			foundMatch = true;
		}
		i++;
	}

	return foundMatch;
}

bool crewMember :: giveAward(award *awardPointer)
{
	if (!hasAward(awardPointer))
	{
		crewAwards->push_back(awardPointer);
		return true;
	}
	else
	{
		return false;
	}
}

bool crewMember :: hasAward(award *awardPointer)
{
	int i = 0;
	if (crewAwards->size() == 0) return false;
	bool foundMatch = false;

	while (i < crewAwards->size())
	{
		if (awardPointer->name() == crewAwards->at(i)->name())
		{
			foundMatch = true;
		}
		i++;
	}

	return foundMatch;
}

crewMember& crewMember :: operator=(const crewMember& other)
{
	//m_infoType = 0;
	setupButtons();

	firstname = other.getFirstName();
	lastname = other.getLastName();
	gender = other.getGender();

	skill = other.getSkill();
	wizardingSkill = other.getWitchcraftSkill();
	intelligence = other.getIntelligenceSkill();
	sexiness = other.getSexSkill();

	sexualityIndex = other.getSexIndex();
	fetishIndex = other.getFetishIndex();

	age = other.getAge();
	breastSize = other.getBreastSize();
	penisLength = other.getPenisLength();
	anusType = other.getAnusType();
	pubicHair = other.getPubicHair();
	stripperVariant = other.getStripperVariant();

	rank = other.getRank();
	wage = other.getWage();

	wizard = other.isWizard();
	scientist = other.isScientist();

	m_employedByPlayer = other.employedByPlayer();
	m_isSelected = false;
	m_selectable = false;
	m_slotNumber = other.m_slotNumber;

	m_init = true;
	m_infoCardCanDrop = false;

	setupButtons();

	crewQualifications = new vector<qualification*>;
	crewAwards = new vector<award*>;

	//copy the crew qualifications vector
	for (int i = 0; i < other.crewQualifications->size(); i++)
	{
		crewQualifications->push_back(other.crewQualifications->at(i));
	}

	//copy the awards vector
	for (int i = 0; i < other.crewAwards->size(); i++)
	{
		crewAwards->push_back(other.crewAwards->at(i));
	}

	return *this;
}

// Copy Constructor
/*crewMember :: crewMember(const crewMember& source)
{

 	m_infoType = 0;
	setupButtons();

	firstname = source.getFirstName();
	lastname = source.getLastName();
	gender = source.getGender();

	skill = source.getSkill();
	wizardingSkill = source.getWitchcraftSkill();
	intelligence = source.getIntelligenceSkill();
	sexiness = source.getSexSkill();

	sexualityIndex = source.getSexIndex();
	fetishIndex = source.getFetishIndex();

	age = source.getAge();
	breastSize = source.getBreastSize();
	penisLength = source.getPenisLength();
	anusType = source.getAnusType();
	pubicHair = source.getPubicHair();
	stripperVariant = source.getStripperVariant();

	rank = source.getRank();
	wage = source.getWage();

	wizard = source.isWizard();
	scientist = source.isScientist();

	m_employedByPlayer = source.employedByPlayer();
	m_isSelected = false;
	m_selectable = false;
	m_slotNumber = source.getSlotNumber();

}*/

//move constructor
/*crewMember :: crewMember(crewMember&& source)
{

	m_infoType = 0;
	setupButtons();

	firstname = source.getFirstName();
	lastname = source.getLastName();
	gender = source.getGender();

	skill = source.getSkill();
	wizardingSkill = source.getWitchcraftSkill();
	intelligence = source.getIntelligenceSkill();
	sexiness = source.getSexSkill();

	sexualityIndex = source.getSexIndex();
	fetishIndex = source.getFetishIndex();

	age = source.getAge();
	breastSize = source.getBreastSize();
	penisLength = source.getPenisLength();
	anusType = source.getAnusType();
	pubicHair = source.getPubicHair();
	stripperVariant = source.getStripperVariant();

	rank = source.getRank();
	wage = source.getWage();

	wizard = source.isWizard();
	scientist = source.isScientist();

	m_employedByPlayer = source.employedByPlayer();
	m_isSelected = false;
	m_selectable = false;
	m_slotNumber = source.getSlotNumber();
 	//cout << "move constructor" << endl;
    //cout << "Move Constructor for "
    //     << *source.data << endl;
    //source.data = nullptr;
    //source = nullptr;
}*/

bool crewMember :: isEqualTo(crewMember other)
{

	if (firstname != other.getFirstName()) return false;
	if (lastname != other.getLastName()) return false;
	if (gender != other.getGender()) return false;

	if (skill != other.getSkill()) return false;
	if (wizardingSkill != other.getWitchcraftSkill()) return false;
	if (intelligence != other.getIntelligenceSkill()) return false;
	if (sexiness != other.getSexSkill()) return false;

	if (sexualityIndex != other.getSexIndex()) return false;
	if (fetishIndex != other.getFetishIndex()) return false;

	if (age != other.getAge()) return false;
	if (breastSize != other.getBreastSize()) return false;
	if (penisLength != other.getPenisLength()) return false;
	if (anusType != other.getAnusType()) return false;
	if (pubicHair != other.getPubicHair()) return false;
	if (stripperVariant != other.getStripperVariant()) return false;

	if (rank != other.getRank()) return false;
	if (wage != other.getWage()) return false;

	if (wizard != other.isWizard()) return false;
	if (scientist != other.isScientist()) return false;

	if (m_employedByPlayer != other.employedByPlayer()) return false;

	return true;
}

ostream& operator<<(ostream& os, crewMember operandYeah)
{
    os << "Name: " << operandYeah.getFirstName() << " " << operandYeah.getLastName() << endl;
    os << "Gender: " << operandYeah.genderToString() << endl;
    os << "Age: " << operandYeah.getAge() << endl;
    os << "Rank: " << operandYeah.getRankString() << endl;
    os << "Salary: " << operandYeah.getWage() << endl;
    if (!operandYeah.hasPenis())
    {
    	os << "Breast size: " << operandYeah.getBreastSize() << endl;
    	os << "Vagina size: " << operandYeah.printVaginaSize() << endl;
    }
    else
    {
    	os << "Penis length: " << operandYeah.getPenisLength() << "in" << endl;
    }
    os << "Anus: " << operandYeah.getAnusType() << endl;
    os << "Pubic hair: " << operandYeah.getPubicHair() << endl;
    os << "Fetish: " << operandYeah.getFetishString() << endl;
	os << "Sexuality: " << operandYeah.getSexualityString() << " (" << operandYeah.getSexualityIndex() << ")" << endl;
    os << "Skills:" << endl;
    os << "  Seafaring: " << operandYeah.getSkill() << " (" << operandYeah.skillAsString(operandYeah.getSkill()) << ")" << endl;
    os << "  Witchcraft: " << operandYeah.getWitchcraftSkill() << " (" << operandYeah.skillAsString(operandYeah.getWitchcraftSkill()) << ")" << endl;
    os << "  Intelligence: " << operandYeah.getIntelligenceSkill() << " (" << operandYeah.skillAsString(operandYeah.getIntelligenceSkill()) << ")" << endl;
    os << "  Sex: " << operandYeah.getSexSkill() << " (" << operandYeah.skillAsString(operandYeah.getSexSkill()) << ")" << endl;
    os << "  capable of Witchcraft: " << boolToString(operandYeah.isCapableOfWitchcraft()) << endl;
    return os;
}

//==================================================
//helper functions are below this line
//=================================================

void drawCrewIconLarge(vector<SDL_Texture*> crewLargeTextures, crewMember crewPerson, SDL_Renderer *ren, int x, int y)
{
	int spriteIndex = 0;
	if (crewPerson.getRank() == 0)
	{
		spriteIndex = 0;
		if (crewPerson.hasPenis()) spriteIndex++;
	}
	else if (crewPerson.getRank() < 3)
	{
		spriteIndex = crewPerson.getStripperVariant() + 2;
		if (crewPerson.hasPenis()) spriteIndex = 6;
	}
	else if (crewPerson.getRank() < 6)
	{
		spriteIndex = 7;
		if (crewPerson.hasPenis()) spriteIndex++;
	}
	else if (crewPerson.getRank() < 9)
	{
		spriteIndex = 9;
		if (crewPerson.hasPenis()) spriteIndex++;
	}
	else
	{
		spriteIndex = 11;
		if (crewPerson.isWizard()) spriteIndex += 2;
		else if (crewPerson.isScientist()) spriteIndex += 4;
		if (crewPerson.hasPenis()) spriteIndex++;
	}

	renderTexture(crewLargeTextures.at(spriteIndex), ren, x, y);
}

int loadSkillStringsIntoRam()
{
	//initialize the array
	skillStringArray = new string[22];

	//load the file containing skill strings
	ifstream skillStringsFile("Data/crew/skillstrings.txt");

	//copy it into array line by line
	//only accept the first 21 lines of the file
	string line;
	int i = 0;
	while (getline(skillStringsFile, line) && i < 22)
	{
    	istringstream iss(line);
    	skillStringArray[i] = line;
    	i++;
	}

	skillStringsFile.close();

	return 0;
}

int loadMiscSexStuffIntoRam()
{
	sexualities = new vector<string>;
	fetishes = new vector<string>;

	//load the file containing skill strings
	ifstream fetishStringsFile("Data/crew/sex/fetish.txt");

	//copy it into array line by line
	//only accept the first 21 lines of the file
	string line;
	int i = 0;
	while (getline(fetishStringsFile, line))
	{
    	istringstream iss(line);
    	fetishes->push_back(line);
    	//fetishes[i] = line;
    	//i++;
	}

	//load the file containing skill strings
	ifstream sexualityStringsFile("Data/crew/sex/sexuality.txt");

	//copy it into array line by line
	//only accept the first 21 lines of the file
	string line2;
	i = 0;
	while (getline(sexualityStringsFile, line2))
	{
    	istringstream iss(line2);
    	//sexualities[i] = line2;
    	sexualities->push_back(line2);
    	//i++;
	}

	sexualityStringsFile.close();
	fetishStringsFile.close();

	return 0;
}