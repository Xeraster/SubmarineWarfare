submarineCompartment :: submarineCompartment()
{

}

submarineCompartment :: submarineCompartment(string displayName, int type, int crewSlots, int officerSlots, double requiredManpower, int posX, int posY)
{
	m_name = displayName;
	m_type = type;
	m_crewSlots = crewSlots;
	m_officerSlots = officerSlots;
	m_requiredManpower = requiredManpower;
	m_posX = posX;
	m_posY = posY;
	m_isSelected = false;
	m_boxSelected = false;
	m_sizeMultiplier = 1;
	m_verticalOffset = 0;
	m_numCompartments = 1;
	m_compartmentNumber = 0;
	m_currentManpower = 0;
	m_screenX = 800;

	m_boxFunction = 0;
	m_crewBoxFunction = 0;
	m_framesSinceLastclick = 0;
	m_doubleclickReady = false;

	//create a new array of pointers then fill it with nullptr s
	//m_crewSlotArray = new vector<crewMember*>;
	m_crewSlotArray.clear();
	for (int i = 0; i < crewSlots; i++)
	{	
		//empty crew slots are denoted by nullptr
		m_crewSlotArray.push_back(nullptr);
	}
	//m_parentSubmarine = nullptr;

	//fuck it. the position of the bar will get recalculated each draw call
	color greenish(30,225,20,255);
	progressBar temp(0,0,20,100, greenish, static_cast<int>(m_requiredManpower * 100), true);
	m_compartmentEfficiency = temp;

	setQualificationIcon();
}

int submarineCompartment :: sizeX()
{
	int texSizeX;
	int texSizeY;
	SDL_QueryTexture(selectTexture, NULL, NULL, &texSizeX, &texSizeY);

	return texSizeX * m_sizeMultiplier;
}

int submarineCompartment :: sizeY()
{
	int texSizeX;
	int texSizeY;
	SDL_QueryTexture(selectTexture, NULL, NULL, &texSizeX, &texSizeY);

	return texSizeY * m_sizeMultiplier; 
}

void submarineCompartment :: loadTextures(SDL_Renderer *ren, string textureName)
{
	string texturePath = "Textures/Submarines/" + textureName + "/" + getTextureName() + ".bmp";
	extraSubmarineSprites->push_back(new textureEntry(texturePath, getTextureName() + "bmp",ren));
	selectTexture = extraSubmarineSprites->back()->getTexture();
}

//sets texture pointers to nullptr to avoid segfaults when they get deleted later
void submarineCompartment :: clearTextures()
{
	selectTexture = nullptr;
}

//0=bow torpedo. 1=stern torpedo. 2=diesel engines. 3=electric engines. 4=bow crew quarters. 5=command room. 6=radio room. 7=cargo. 8=stripper pole. 9=science lab. 10=nuclear reactor.
	//11 = hacking center. 12 = clowning center. 13 = witchcraft stuff. 14 = stern crew quarters
string submarineCompartment :: getTextureName()
{
	switch (m_type)
	{
		case 0:
			return "bowtorpedo";
		case 1:
			return "sterntorpedo";
		case 2:
			return "engineroom";
		case 3:
			return "electricengineroom";
		case 4:
			return "bowcrewquarters";
		case 5:
			return "commandroom";
		case 6:
			return "radioroom";
		case 7:
			return "cargo";
		case 8:
			return "stripclub";
		case 9:
			return "researchlab";
		case 10:
			return "reactorroom";
		case 11:
			return "hackingroom";
		case 12:
			return "clowingcenter";
		case 13:
			return "witchcraftstuff";
		case 14:
			return "sterncrewquarters";
		default:
			return "bowtorpedo";
	}
}

void submarineCompartment :: doDrawing(SDL_Renderer *ren, double sizeMultiplier, int horizontalOffset, int veritcalOffset, int mouseX, int mouseY, Uint32 lastmouse)
{	
	m_boxFunction = 0;
	//set size multiplier for later use by the size functions
	m_sizeMultiplier = sizeMultiplier;

	//query the size of the compartment selection texture to generate cursor collisions
	int texSizeX;
	int texSizeY;
	SDL_QueryTexture(selectTexture, NULL, NULL, &texSizeX, &texSizeY);
	
	int bsx = sizeMultiplier * texSizeX;
	int bsy = sizeMultiplier * texSizeY;
	int adjX = m_posX * sizeMultiplier;
	int adjY = m_posY * sizeMultiplier;

	//cout << "posX= " << adjX << " sizeX= " << texSizeX << " posY= " << adjY << "sizeY= " << texSizeY << endl;

	if (mouseX > adjX + horizontalOffset && mouseX < adjX + bsx + horizontalOffset && (mouseY - veritcalOffset) > adjY && (mouseY - veritcalOffset) < adjY + bsy)
	{
		renderTextureEx(selectTexture, ren, adjX + horizontalOffset, adjY + veritcalOffset, bsx, bsy, 0);
		m_isSelected = true;
		//SDL_BUTTON_RIGHT
		if (lastmouse == SDL_BUTTON(SDL_BUTTON_RIGHT) && m_framesSinceLastclick == 0)
		{
			m_framesSinceLastclick = 30;
			m_boxFunction = 2;
		}
		else if (lastmouse == SDL_BUTTON(SDL_BUTTON_LEFT) && m_framesSinceLastclick == 0 && !m_doubleclickReady)
		{
			//m_doubleclickReady = true;
			m_framesSinceLastclick = 30;
			//cout << "double click set ready" << endl;
		}
		else if (lastmouse != SDL_BUTTON(SDL_BUTTON_LEFT) && m_framesSinceLastclick > 0 && !m_doubleclickReady)
		{
			m_doubleclickReady = true;
		}
		else if (lastmouse == SDL_BUTTON(SDL_BUTTON_LEFT) && m_framesSinceLastclick > 0 && m_doubleclickReady)
		{
			m_boxFunction = 1;
			m_framesSinceLastclick = 30;
			m_doubleclickReady = false;
			//cout << "double click set not ready" << endl;
		}
		//cout << "mouse collision" << endl;
	}
	else if (m_boxSelected)
	{
		renderTextureEx(selectTexture, ren, adjX + horizontalOffset, adjY + veritcalOffset, bsx, bsy, 0);
	}
	else
	{
		m_isSelected = false;
	}

	//decrement right click timer counter
	if (m_framesSinceLastclick > 0)
	{
		m_framesSinceLastclick--;
	}
	else if (m_framesSinceLastclick == 0)
	{
		m_doubleclickReady = false;
	}

}

//oh dear what a shitfuck this is becoming
//returns y coordinate of bottom of box
int submarineCompartment :: drawCrewBox(SDL_Renderer *ren, int screenX, int screenY, int veritcalOffset, int compartmentNumber, int numCompartments, int mouseX, int mouseY, Uint32 lastmouse, crewMember **selected)
{	
	m_crewBoxFunction = 0;
	m_verticalOffset = veritcalOffset;
	m_screenX = screenX;
	m_numCompartments = numCompartments;
	m_compartmentNumber = compartmentNumber;
	int textSize = 6;
	color darkBlack(100,100,100,200);
	int posX = 20 + ((numCompartments - compartmentNumber - 1) * ((screenX - 20) / numCompartments));
	int posY = veritcalOffset + 10;
	int sizeX = ((screenX - 20) / numCompartments) - 20;
	int sizeY = 200;
	int rowsOfWrappedText = 0;
	//drawText(ren, textSize, white, m_name, posX , veritcalOffset);

	//if compartment is selected, draw the text in orange. Otherwise, draw it in white
	if (m_isSelected || m_boxSelected)
	{
		color orange(255,150,0,255);
		rowsOfWrappedText = drawTextWrapped(ren, textSize, orange, "     " + m_name, posX , veritcalOffset, sizeX / 2);
		if (lastmouse == SDL_BUTTON(SDL_BUTTON_RIGHT) && m_framesSinceLastclick == 0)
		{
			m_framesSinceLastclick = 40;
			m_crewBoxFunction = 2;
		}
		else if (lastmouse == SDL_BUTTON(SDL_BUTTON_LEFT) && m_framesSinceLastclick == 0 && !m_doubleclickReady)
		{
			//m_doubleclickReady = true;
			m_framesSinceLastclick = 30;
			//cout << "double click set ready" << endl;
		}
		else if (lastmouse != SDL_BUTTON(SDL_BUTTON_LEFT) && m_framesSinceLastclick > 0 && !m_doubleclickReady)
		{
			m_doubleclickReady = true;
		}
		//only do this if mouse pointer is in the text label area
		else if (lastmouse == SDL_BUTTON(SDL_BUTTON_LEFT) && m_framesSinceLastclick > 0 && m_doubleclickReady && mouseY < posY + (80 * textSize / 24) * rowsOfWrappedText)
		{
			m_crewBoxFunction = 1;
			m_framesSinceLastclick = 30;
			m_doubleclickReady = false;
			//cout << "double click set not ready" << endl;
		}
	}
	else
	{
		color white(255,255,255,255);
		rowsOfWrappedText = drawTextWrapped(ren, textSize, white, "     " + m_name, posX , veritcalOffset, sizeX / 2);
	}

	//now draw the qualification icon corresponding (more or less) to the compartment's function
	renderTextureEx(m_compartmentJobIcon, ren, posX, veritcalOffset, (80 * textSize / 24), (80 * textSize / 24), 0);

	int textOffset = (80 * textSize / 24) * rowsOfWrappedText;


	int crewSizeX = 15;
	int crewSizeY = 40;
	//cout << "sizex = " << sizeX << endl;
	
	//start linearly scaling crew icons in the compartments at horizontal screen resolutions above 1024
	if (gscreenx > 1024)
	{
		crewSizeX = crewSizeX * gscreenx / 1024;
		crewSizeY = crewSizeY * gscreenx / 1024;
		//cout << "crewSizeX = " << crewSizeX << endl;
		//cout << "crewSizeY = " << crewSizeY << endl;
	}

	//drawRectFilled(ren, darkBlack, posX, veritcalOffset + (80 * textSize / 24), sizeX, sizeY);
	int i = 0;
	int rowNum = 0;
	int columnsSizeLastReturn = 0;
	int xOffset = 0;
	int yOffset = 0;
	while (i < m_crewSlots)
	{
		if (crewSizeX*(columnsSizeLastReturn+1) > sizeX)
		{
			rowNum++;
			columnsSizeLastReturn = 0;
		}

		xOffset = (columnsSizeLastReturn*crewSizeX);
		yOffset = rowNum * crewSizeY;
		if (columnsSizeLastReturn == 0)
		{
			drawRectFilled(ren, darkBlack, posX, veritcalOffset + textOffset + yOffset, sizeX, crewSizeY);
		}
		if (m_crewSlotArray.at(i) == nullptr)
		{
			renderTextureEx(crewicons_Large.at(17), ren, posX + xOffset, (veritcalOffset + textOffset) + yOffset, crewSizeX, crewSizeY, 0);
		}
		else
		{
			m_crewSlotArray.at(i)->drawIcon(ren, posX + xOffset, (veritcalOffset + textOffset) + yOffset, crewSizeX, crewSizeY, mouseX, mouseY, lastmouse, selected, true);
			//cout << m_crewSlotArray.at(i)->getFirstName() << m_crewSlotArray.at(i)->getLastName() << endl;
			//cout << m_crewSlotArray->at(i)->getFirstName() << endl;
		}

		i++;
		columnsSizeLastReturn++;
	}

	//needed for calculating mouse cursor collisions
	int colXmin = posX;
	int colXmax = posX + sizeX;
	int colYmin = posY;
	int colYmax = veritcalOffset + textOffset + yOffset + crewSizeY;
	//cout << "mouseX = " << mouseX << " mouseY = " << mouseY << endl;
	//cout << " xmin= " << colXmin << " xmax= "<< colXmax << endl;
	//cout << " ymin= " << colYmin << " ymax= "<< colYmax << endl;
	//cout << "yOffset = " << veritcalOffset + (80 * textSize / 24) + yOffset + crewSizeY << endl;
	if (mouseX > colXmin && mouseX < colXmax && mouseY > colYmin && mouseY < colYmax)
	{
		m_boxSelected = true;
		//cout << "selected" << endl;
	}
	else
	{
		m_boxSelected = false;
	}

	//why not just put this bar at the bottom? Much easier programming-wise even though it "doesn't loook the same" as the silent hunter 3 version of this screen
	//I could even give the compartment a "flooding bar" and a "health" bar directly under this and it would look good
	m_compartmentEfficiency.setPos(colXmin, colYmax);
	m_compartmentEfficiency.setSize(sizeX, 10);
	m_compartmentEfficiency.setValue(static_cast<int>(m_currentManpower * 100));
	m_compartmentEfficiency.draw(ren);

	//decrement right click timer counter
	if (m_framesSinceLastclick > 0)
	{
		m_framesSinceLastclick--;
	}

	return colYmax;
}

//use this one instead of drawCrewBox() if the compartment is the onshore crew barracks
void submarineCompartment :: drawCrewBoxBarracks(SDL_Renderer *ren, int posX, int posY, int sizeX, int mouseX, int mouseY, Uint32 lastmouse, crewMember **selected)
{
	m_crewBoxFunction = 0;

	//when operating in crew barracks mode, m_verticalOffset is used as the size variable
	m_verticalOffset = posY;

	//vertical offset = posY
	int veritcalOffset = posY;

	m_screenX = gscreenx;
	m_numCompartments = 1; 		//I forgot if this needs to be zero or 1 if there's only one compartment. I guess I'll find out (if you're reading this after 04/26/21, whatever value that number is is 100% the correct one)
	m_compartmentNumber = 0; 	//index of zero
	int textSize = 6;
	color darkBlack(100,100,100,200);

	//posX, posY and sizeX are provided by the function parameters so no need to specify or recalculate them here
	int sizeY = 200; 		//not actually connected to anything right now
	int rowsOfWrappedText = 0;
	//drawText(ren, textSize, white, m_name, posX , veritcalOffset);

	//if compartment is selected, draw the text in orange. Otherwise, draw it in white
	if (m_isSelected || m_boxSelected)
	{
		color orange(255,150,0,255);
		rowsOfWrappedText = drawTextWrapped(ren, textSize, orange, "     " + m_name, posX , veritcalOffset, sizeX / 2);
		if (lastmouse == SDL_BUTTON(SDL_BUTTON_RIGHT) && m_framesSinceLastclick == 0)
		{
			m_framesSinceLastclick = 40;
			m_crewBoxFunction = 2;
		}
		else if (lastmouse == SDL_BUTTON(SDL_BUTTON_LEFT) && m_framesSinceLastclick == 0 && !m_doubleclickReady)
		{
			//m_doubleclickReady = true;
			m_framesSinceLastclick = 30;
			//cout << "double click set ready" << endl;
		}
		else if (lastmouse != SDL_BUTTON(SDL_BUTTON_LEFT) && m_framesSinceLastclick > 0 && !m_doubleclickReady)
		{
			m_doubleclickReady = true;
		}
		//only do this if mouse pointer is in the text label area
		else if (lastmouse == SDL_BUTTON(SDL_BUTTON_LEFT) && m_framesSinceLastclick > 0 && m_doubleclickReady && mouseY < posY + (80 * textSize / 24) * rowsOfWrappedText)
		{
			m_crewBoxFunction = 1;
			m_framesSinceLastclick = 30;
			m_doubleclickReady = false;
			//cout << "double click set not ready" << endl;
		}
	}
	else
	{
		color white(255,255,255,255);
		rowsOfWrappedText = drawTextWrapped(ren, textSize, white, "     " + m_name, posX , veritcalOffset, sizeX / 2);
	}

	//now draw the qualification icon corresponding (more or less) to the compartment's function
	renderTextureEx(m_compartmentJobIcon, ren, posX, veritcalOffset, (80 * textSize / 24), (80 * textSize / 24), 0);

	int textOffset = (80 * textSize / 24) * rowsOfWrappedText;


	int crewSizeX = 15;
	int crewSizeY = 40;
	//cout << "sizex = " << sizeX << endl;
	
	//start linearly scaling crew icons in the compartments at horizontal screen resolutions above 1024
	if (gscreenx > 1024)
	{
		crewSizeX = crewSizeX * gscreenx / 1024;
		crewSizeY = crewSizeY * gscreenx / 1024;
		//cout << "crewSizeX = " << crewSizeX << endl;
		//cout << "crewSizeY = " << crewSizeY << endl;
	}

	//drawRectFilled(ren, darkBlack, posX, veritcalOffset + (80 * textSize / 24), sizeX, sizeY);
	int i = 0;
	int rowNum = 0;
	int columnsSizeLastReturn = 0;
	int xOffset = 0;
	int yOffset = 0;
	while (i < m_crewSlots)
	{
		if (crewSizeX*(columnsSizeLastReturn+1) > sizeX)
		{
			rowNum++;
			columnsSizeLastReturn = 0;
		}

		xOffset = (columnsSizeLastReturn*crewSizeX);
		yOffset = rowNum * crewSizeY;
		if (columnsSizeLastReturn == 0)
		{
			drawRectFilled(ren, darkBlack, posX, veritcalOffset + textOffset + yOffset, sizeX, crewSizeY);
		}
		if (m_crewSlotArray.at(i) == nullptr)
		{
			renderTextureEx(crewicons_Large.at(17), ren, posX + xOffset, (veritcalOffset + textOffset) + yOffset, crewSizeX, crewSizeY, 0);
		}
		else
		{
			m_crewSlotArray.at(i)->drawIcon(ren, posX + xOffset, (veritcalOffset + textOffset) + yOffset, crewSizeX, crewSizeY, mouseX, mouseY, lastmouse, selected, true);
			//cout << m_crewSlotArray.at(i)->getFirstName() << m_crewSlotArray.at(i)->getLastName() << endl;
			//cout << m_crewSlotArray->at(i)->getFirstName() << endl;
		}

		i++;
		columnsSizeLastReturn++;
	}

	//needed for calculating mouse cursor collisions
	int colXmin = posX;
	int colXmax = posX + sizeX;
	int colYmin = posY;
	int colYmax = veritcalOffset + textOffset + yOffset + crewSizeY;
	if (mouseX > colXmin && mouseX < colXmax && mouseY > colYmin && mouseY < colYmax)
	{
		m_boxSelected = true;
		//cout << "selected" << endl;
	}
	else
	{
		m_boxSelected = false;
	}

	//barracks don't get a efficency bar since no actual or useful work gets "done" by putting crew there
	//m_compartmentEfficiency.setPos(colXmin, colYmax);
	//m_compartmentEfficiency.setSize(sizeX, 10);
	//m_compartmentEfficiency.setValue(static_cast<int>(m_currentManpower * 100));
	//m_compartmentEfficiency.draw(ren);

	//decrement right click timer counter
	if (m_framesSinceLastclick > 0)
	{
		m_framesSinceLastclick--;
	}
}

//returns false if unable to (ex: the compartment is already full). Returns true upon success
bool submarineCompartment :: addCrewToAnySlot(crewMember *person)
{	
	bool foundSpot = false;
	int i = 0;
	//m_crewSlotArray->at(0) = person;
	while (i < m_crewSlots && !foundSpot)
	{
		if (m_crewSlotArray.at(i) == nullptr)
		{
			m_crewSlotArray.at(i) = person;
			foundSpot = true;
		}
		i++;
	}

	if (!foundSpot) 
	{
		return false;
	}
	else
	{ 
		updateManpower();
		return true;
	}
}

//moves a crew member to any slot in the current compartment then passes the value of the slot the said crew member ended up in
//returns true if there was room. returns false if there was no room
//slotNum = -1 if there was no room in the compartment
bool submarineCompartment :: moveCrewToAnySlot(crewMember *person, int *slotNum)
{
	*slotNum = -1;
	bool foundSpot = false;
	int i = 0;
	//m_crewSlotArray->at(0) = person;
	while (i < m_crewSlots && !foundSpot)
	{
		if (m_crewSlotArray.at(i) == nullptr)
		{
			m_crewSlotArray.at(i) = person;
			foundSpot = true;
			*slotNum = i;
		}
		i++;
	}

	if (!foundSpot) 
	{
		return false;
	}
	else
	{ 
		updateManpower();
		return true;
	}
}

//adds crew pointer to slot at screen position inputted by x, y. Returns false if failed, true if success
bool submarineCompartment :: crewToSpecificSlot(crewMember *person, int x, int y, int screenX, int *slotNum, crewMember **crewToPutInPlace)
{
	int posX = 0;
	int posY = 0;
	int crewSizeX = 15;
	int crewSizeY = 40;
	int slotNumber = 0;

	//start linearly scaling crew icons in the compartments at horizontal screen resolutions above 1024
	if (gscreenx > 1024)
	{
		crewSizeX = crewSizeX * gscreenx / 1024;
		crewSizeY = crewSizeY * gscreenx / 1024;
		//cout << "crewSizeX = " << crewSizeX << endl;
		//cout << "crewSizeY = " << crewSizeY << endl;
	}

	coordinatesToSlotNum(x, y, &slotNumber, screenX);

	if (m_crewSlotArray.at(slotNumber) == nullptr)
	{
		*slotNum = slotNumber;
		m_crewSlotArray.at(slotNumber) = person;
		updateManpower();
		*crewToPutInPlace = nullptr;
		return true;
	}
	else
	{
		*slotNum = slotNumber;
		*crewToPutInPlace = m_crewSlotArray.at(slotNumber);
		m_crewSlotArray.at(slotNumber) = person;
		updateManpower();
		return true;
	}
}

//adds crew pointer to slot at position.
//returns 0 if sucess. returns 1 if already occupied. returns 2 if provided slot number invalid
int submarineCompartment :: crewToSlotNumber(crewMember *person, int slotNum)
{	
	if (slotNum < 0 or slotNum > m_crewSlotArray.size()) return 2;

	//if slot unoccupied, put crew pointer in provided slot
	if (m_crewSlotArray.at(slotNum) == nullptr)
	{
		m_crewSlotArray.at(slotNum) = person;
		updateManpower();
		return 0;
	}
	else
	{
		return 1;
	}
}

bool submarineCompartment :: eraseDuplicateCrew(crewMember *person, int excludeSlot)
{
	bool foundMatch = false;
	int i = 0;
	while (!foundMatch && i < m_crewSlotArray.size())
	{
		if (m_crewSlotArray.at(i) == person && i != excludeSlot)
		{
			foundMatch = true;
			m_crewSlotArray.at(i) = nullptr;
			updateManpower();
		}

		i++;
	}

	return foundMatch;
}

bool submarineCompartment :: replaceDuplicateCrew(crewMember *person, int excludeSlot, crewMember* replacement)
{
	bool foundMatch = false;
	int i = 0;
	while (!foundMatch && i < m_crewSlotArray.size())
	{
		if (m_crewSlotArray.at(i) == person && i != excludeSlot)
		{
			foundMatch = true;
			m_crewSlotArray.at(i) = replacement;
			updateManpower();
		}

		i++;
	}

	return foundMatch;
}

void submarineCompartment :: coordinatesToSlotNum(int x, int y, int *slotNum, int screenX)
{
	int textSize = 6;
	int posX = 20 + ((m_numCompartments - m_compartmentNumber - 1) * ((screenX - 20) / m_numCompartments));
	int posY = m_verticalOffset + 10;
	int sizeX = ((screenX - 20) / m_numCompartments) - 20;
	int sizeY = 200;
	int rowsOfWrappedText = getTextRows("     " + m_name, textSize, sizeX / 2);


	int crewSizeX = 15;
	int crewSizeY = 40;
	//start linearly scaling crew icons in the compartments at horizontal screen resolutions above 1024
	if (gscreenx > 1024)
	{
		crewSizeX = crewSizeX * gscreenx / 1024;
		crewSizeY = crewSizeY * gscreenx / 1024;
		//cout << "crewSizeX = " << crewSizeX << endl;
		//cout << "crewSizeY = " << crewSizeY << endl;
	}

	int i = 0;
	int rowNum = 0;
	int columnsSizeLastReturn = 0;
	int xOffset = 0;
	int yOffset = 0;

	bool foundIt = false;

	int textOffset = (80 * textSize / 24) * rowsOfWrappedText;

	while (i < m_crewSlots && !foundIt)
	{
		if (crewSizeX*(columnsSizeLastReturn+1) > sizeX)
		{
			rowNum++;
			columnsSizeLastReturn = 0;
		}

		xOffset = (columnsSizeLastReturn*crewSizeX);
		yOffset = rowNum * crewSizeY;

		if (x > posX + xOffset && x < posX + xOffset + crewSizeX && y > (m_verticalOffset + textOffset) + yOffset && y < (m_verticalOffset + textOffset) + yOffset + crewSizeY)
		{
			cout << "move crew to slot number " << i << endl;
			foundIt = true;
			*slotNum = i;
		}
		//if (columnsSizeLastReturn == 0)
		//{
			//drawRectFilled(ren, darkBlack, posX, veritcalOffset + textOffset + yOffset, sizeX, crewSizeY);
		//}
		//if (m_crewSlotArray.at(i) == nullptr)
		//{
			//renderTextureEx(crewicons_Large.at(17), ren, posX + xOffset, (veritcalOffset + textOffset) + yOffset, crewSizeX, crewSizeY, 0);
		//}
		//else
		//{
			//m_crewSlotArray.at(i)->drawIcon(ren, posX + xOffset, (veritcalOffset + textOffset) + yOffset, crewSizeX, crewSizeY, mouseX, mouseY, lastmouse, selected, true);
			//cout << m_crewSlotArray.at(i)->getFirstName() << m_crewSlotArray.at(i)->getLastName() << endl;
			//cout << m_crewSlotArray->at(i)->getFirstName() << endl;
		//}

		i++;
		columnsSizeLastReturn++;
	}
}

//a standalone way of obtaining the position and size of the crew box for the compartment.
//only works if drawCrewBox() and doDrawing() have already been called on the current instance
void submarineCompartment :: getBoxSize(int *px, int *py, int *sx, int *sy)
{

	int textSize = 6;
	int posX = 20 + ((m_numCompartments - m_compartmentNumber - 1) * ((m_screenX - 20) / m_numCompartments));
	int posY = m_verticalOffset + 10;
	int sizeX = ((m_screenX - 20) / m_numCompartments) - 20;
	int sizeY = 200;
	int rowsOfWrappedText = getTextRows("     " + m_name, textSize, sizeX / 2);


	int crewSizeX = 15;
	int crewSizeY = 40;
	//start linearly scaling crew icons in the compartments at horizontal screen resolutions above 1024
	if (gscreenx > 1024)
	{
		crewSizeX = crewSizeX * gscreenx / 1024;
		crewSizeY = crewSizeY * gscreenx / 1024;
		//cout << "crewSizeX = " << crewSizeX << endl;
		//cout << "crewSizeY = " << crewSizeY << endl;
	}

	int i = 0;
	int rowNum = 0;
	int columnsSizeLastReturn = 0;
	int xOffset = 0;
	int yOffset = 0;


	int textOffset = (80 * textSize / 24) * rowsOfWrappedText;

	while (i < m_crewSlots)
	{
		if (crewSizeX*(columnsSizeLastReturn+1) > sizeX)
		{
			rowNum++;
			columnsSizeLastReturn = 0;
		}

		xOffset = (columnsSizeLastReturn*crewSizeX);
		yOffset = rowNum * crewSizeY;

		/*if (x > posX && x < posX + sizeX && y > posY && y < posY + sizeY)
		{
			foundIt = true;
			*slotNum = i;
		}*/
		//if (columnsSizeLastReturn == 0)
		//{
			//drawRectFilled(ren, darkBlack, posX, veritcalOffset + textOffset + yOffset, sizeX, crewSizeY);
		//}
		//if (m_crewSlotArray.at(i) == nullptr)
		//{
			//renderTextureEx(crewicons_Large.at(17), ren, posX + xOffset, (veritcalOffset + textOffset) + yOffset, crewSizeX, crewSizeY, 0);
		//}
		//else
		//{
			//m_crewSlotArray.at(i)->drawIcon(ren, posX + xOffset, (veritcalOffset + textOffset) + yOffset, crewSizeX, crewSizeY, mouseX, mouseY, lastmouse, selected, true);
			//cout << m_crewSlotArray.at(i)->getFirstName() << m_crewSlotArray.at(i)->getLastName() << endl;
			//cout << m_crewSlotArray->at(i)->getFirstName() << endl;
		//}

		i++;
		columnsSizeLastReturn++;
	}

	int colXmin = posX;
	int colXmax = posX + sizeX;
	int colYmin = posY;
	int colYmax = m_verticalOffset + textOffset + yOffset + crewSizeY;

	*px = colXmin;
	*sx = colXmax;
	*py = colYmin;
	*sy = colYmax;
}

void submarineCompartment :: setQualificationIcon()
{
	//damn I should have made the qualification type ids and the compartment type ids the same. Oh well, live and learn. I'm also not going to go back and fix it.
	int qualificationId = 0;
	switch (m_type)
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

	m_compartmentJobIcon = getQualificationById(qualificationId)->tex();
}

//returns the number of crew in current compartment. nullptr does not count as 1 crew
int submarineCompartment :: numCrew()
{
	int crewSoFar = 0;
	for (int i = 0; i < m_crewSlotArray.size(); i++)
	{
		if (m_crewSlotArray.at(i) != nullptr ) crewSoFar++;
	}

	return crewSoFar;
}

//returns false if all slots of the compartment are occupied. Returns true if not all of the compartment slots are occupied
bool submarineCompartment :: isFull()
{
	if (numCrew() == m_crewSlots) return true;
	else return false;
}

//passes number of sailors, pettyofficers and officers by reference
void submarineCompartment :: numCrewTypes(int *sailors, int *pettyofficers, int *officers)
{
	int sailorsSoFar = 0;
	int posSoFar = 0;
	int officersSoFar = 0;

	for (int i = 0; i < m_crewSlotArray.size(); i++)
	{
		if (m_crewSlotArray.at(i) != nullptr)
		{
			if (m_crewSlotArray.at(i)->getRank() > 0 && m_crewSlotArray.at(i)->getRank() < 6)
			{
				sailorsSoFar++;
			}
			else if (m_crewSlotArray.at(i)->getRank() > 5 && m_crewSlotArray.at(i)->getRank() < 9)
			{
				posSoFar++;
			}
			else if (m_crewSlotArray.at(i)->getRank() > 8)
			{
				officersSoFar++;
			}
		}
	}

	*sailors += sailorsSoFar;
	*pettyofficers += posSoFar;
	*officers += officersSoFar;
}

void submarineCompartment :: updateManpower()
{
	m_currentManpower = 0;

	for (int i = 0; i < m_crewSlotArray.size(); i++)
	{
		if (m_crewSlotArray.at(i) != nullptr)
		{
			m_currentManpower += m_crewSlotArray.at(i)->manpower(m_type);
		}
	}

	cout << m_name << " manpower = " << m_currentManpower << endl;
	cout << "bar value = " << m_compartmentEfficiency.getValue() << " and max = " << m_compartmentEfficiency.getMax() << endl;
}

//returns a random crew member pointer in the compartment
//only returns nullptr if there are no crew in the compartment
crewMember* submarineCompartment :: randomCrew()
{
	crewMember *crewPointer = nullptr;
	if (numCrew() > 0)
	{
		while (crewPointer == nullptr)
		{
			crewPointer = m_crewSlotArray.at(rand() % m_crewSlotArray.size());
		}
		return crewPointer;
	}
	else
	{
		return nullptr;
	}
}

//sorts all the crew in a compartment by job type. Makes things look neat
void submarineCompartment :: sortCrew()
{

	//bruh. There are many different ways to do this but only this specific exact combination worked. wtf

	crewMember *workArray[m_crewSlotArray.size()];

	for (int i = 0; i < m_crewSlotArray.size(); i++)
	{
		workArray[i] = m_crewSlotArray.at(i);
	}

	for (int i = 0; i < m_crewSlotArray.size(); i++)
	{
		int u = 0;
		int highestNum = 0;
		for (int p = 0; p < m_crewSlotArray.size(); p++)
		{
			
			if (workArray[p] != nullptr && workArray[p]->getRank() > highestNum)
			{
				highestNum = workArray[p]->getRank();
				u = p;
			}
		}
		m_crewSlotArray.at(i) = workArray[u];
		workArray[u] = nullptr;
	}

}

void submarineCompartment :: coordinatesToSlotNumInBarracks(int x, int y, int *slotNum, int screenX)
{
	int textSize = 6;
	//int posX = 20 + ((m_numCompartments - m_compartmentNumber - 1) * ((screenX - 20) / m_numCompartments));
	//int posY = m_verticalOffset + 10;
	//int sizeX = ((screenX - 20) / m_numCompartments) - 20;
	//int sizeY = 200;
	int posX = startXR;
	int posY = lowestY + 10;
	int sizeX = screenX;
	int sizeY = 200; 	//instead of calculate a bunch of shit, just consider the top of the box to the bottom of the screen valid drag-drop area
	int rowsOfWrappedText = getTextRows("     " + m_name, textSize, sizeX / 2);


	int crewSizeX = 15;
	int crewSizeY = 40;
	//start linearly scaling crew icons in the compartments at horizontal screen resolutions above 1024
	if (gscreenx > 1024)
	{
		crewSizeX = crewSizeX * gscreenx / 1024;
		crewSizeY = crewSizeY * gscreenx / 1024;
		//cout << "crewSizeX = " << crewSizeX << endl;
		//cout << "crewSizeY = " << crewSizeY << endl;
	}

	int i = 0;
	int rowNum = 0;
	int columnsSizeLastReturn = 0;
	int xOffset = 0;
	int yOffset = 0;

	bool foundIt = false;

	int textOffset = (80 * textSize / 24) * rowsOfWrappedText;

	while (i < m_crewSlots && !foundIt)
	{
		if (crewSizeX*(columnsSizeLastReturn+1) > sizeX)
		{
			rowNum++;
			columnsSizeLastReturn = 0;
		}

		xOffset = (columnsSizeLastReturn*crewSizeX);
		yOffset = rowNum * crewSizeY;

		cout << "is " << x << ", "  << y << " inside " << posX + xOffset << "-" << posX + xOffset + crewSizeX << ", " << (m_verticalOffset + textOffset) + yOffset << "-" << (m_verticalOffset + textOffset) + yOffset + crewSizeY << endl;
		//cout << "m_verticalOffset = " << m_verticalOffset << endl;
		if (x > posX + xOffset && x < posX + xOffset + crewSizeX && y > (m_verticalOffset + textOffset) + yOffset && y < (m_verticalOffset + textOffset) + yOffset + crewSizeY)
		{
			cout << "move crew to slot number " << i << endl;
			foundIt = true;
			*slotNum = i;
		}
		//if (columnsSizeLastReturn == 0)
		//{
			//drawRectFilled(ren, darkBlack, posX, veritcalOffset + textOffset + yOffset, sizeX, crewSizeY);
		//}
		//if (m_crewSlotArray.at(i) == nullptr)
		//{
			//renderTextureEx(crewicons_Large.at(17), ren, posX + xOffset, (veritcalOffset + textOffset) + yOffset, crewSizeX, crewSizeY, 0);
		//}
		//else
		//{
			//m_crewSlotArray.at(i)->drawIcon(ren, posX + xOffset, (veritcalOffset + textOffset) + yOffset, crewSizeX, crewSizeY, mouseX, mouseY, lastmouse, selected, true);
			//cout << m_crewSlotArray.at(i)->getFirstName() << m_crewSlotArray.at(i)->getLastName() << endl;
			//cout << m_crewSlotArray->at(i)->getFirstName() << endl;
		//}

		i++;
		columnsSizeLastReturn++;
	}
}

//adds crew pointer to slot at screen position inputted by x, y. Returns false if failed, true if success
bool submarineCompartment :: crewToSpecificSlotInBarracks(crewMember *person, int x, int y, int screenX, int *slotNum, crewMember **crewToPutInPlace)
{
	int posX = 0;
	int posY = 0;
	int crewSizeX = 15;
	int crewSizeY = 40;
	int slotNumber = 0;

	//start linearly scaling crew icons in the compartments at horizontal screen resolutions above 1024
	if (gscreenx > 1024)
	{
		crewSizeX = crewSizeX * gscreenx / 1024;
		crewSizeY = crewSizeY * gscreenx / 1024;
		//cout << "crewSizeX = " << crewSizeX << endl;
		//cout << "crewSizeY = " << crewSizeY << endl;
	}

	cout << "coordinate to slot function" << endl;
	coordinatesToSlotNumInBarracks(x, y, &slotNumber, screenX);

	if (m_crewSlotArray.at(slotNumber) == nullptr)
	{
		*slotNum = slotNumber;
		m_crewSlotArray.at(slotNumber) = person;
		updateManpower();
		*crewToPutInPlace = nullptr;
		return true;
	}
	else
	{
		*slotNum = slotNumber;
		*crewToPutInPlace = m_crewSlotArray.at(slotNumber);
		m_crewSlotArray.at(slotNumber) = person;
		updateManpower();
		return true;
	}
}

int submarineCompartment :: toSaveXml(XMLElement *dataElement, int index)
{
	XMLElement *compartmentNode = dataElement->InsertNewChildElement("compartment");

	writeElement(compartmentNode, "index", index);
	writeElement(compartmentNode, "compartmentType", m_type);

	for (int i = 0; i < m_crewSlotArray.size(); i++)
	{
		//writeElement(compartmentNode, "slot"+to_string(i), 0);
		if (m_crewSlotArray.at(i) == nullptr) writeElement(compartmentNode, "slot"+to_string(i), 0);
		else writeElement(compartmentNode, "slot"+to_string(i), m_crewSlotArray.at(i)->makeIdHashSalt());
	}

	dataElement->InsertEndChild(compartmentNode);
}

submarineCompartment& submarineCompartment :: operator=(submarineCompartment& other)
{
	m_name = other.displayName();
	m_type = other.type();
	m_crewSlots = other.numSlots();
	m_officerSlots = other.officerSlots();
	m_requiredManpower = other.requiredManpower();
	m_posX = other.posX();
	m_posY = other.posY();
	m_isSelected = false;
	m_boxSelected = false;
	m_sizeMultiplier = 1;
	m_verticalOffset = 0;
	m_numCompartments = 1;
	m_compartmentNumber = other.compartmentNumber();
	m_screenX = 800;
	m_currentManpower = other.currentManpower();
	m_compartmentJobIcon = other.qualIcon();
	m_framesSinceLastclick = 0;
	m_doubleclickReady = false;

	//there's never any legit situation I can think of where you would want to copy a compartment and preserve the click function data
	m_boxFunction = 0;
	m_crewBoxFunction = 0;

	//copy the crew slot data.
	//for some reason, not including this step allows submarine compartments (when in a submarine) to work correctly but not when used as shore barracks
	//why was the data getting deep copied without me saying so? Who tf knows.
	m_crewSlotArray.clear();
	for (int i = 0; i < other.numSlots(); i++)
	{
		m_crewSlotArray.push_back(other.crewInSlot(i));
	}

	m_compartmentEfficiency = other.compartmentBar();

	return *this;
}

ostream& operator<<(ostream& os, submarineCompartment item)
{
	os << "compartment name: " << item.displayName() << endl;
	os << "type: " << item.type() << endl;
	os << "crew slots: " << item.numSlots() << endl;
	os << "officer slots: " << item.officerSlots() << endl;
	os << "required manpower: " << item.requiredManpower() << endl;
	os << "texture location = " << item.posX() << ", " << item.posY() << endl;

	return os;
}