inventoryItem :: inventoryItem()
{

}

inventoryItem :: inventoryItem(string newName, string desc, string desc2, double cost, int rare, string textureName)
{
	name = newName;
	description = desc;
	m_additionalInfo = desc2;
	type = 0;
	relevantStat = 0;
	m_cost = cost;
	rarity = rare;
	m_textureName = textureName;

	findAndSetTexture();
}

//this needs to very specifically be only the vector<string> generated from the file loader or else it will fail catastrophically
inventoryItem :: inventoryItem(vector<string> *fileContents)
{
	//for junk items only
	if (fileContents->at(0) != "junk")
	{
		cout << "error. Possibly corrupt file" << endl;
	}
	else
	{
		loadDefaults(fileContents, 0);

	}
}

void inventoryItem :: loadDefaults(vector<string> *fileStreamLines, int itemType)
{
	//description = fileStreamLines->at(2);
	//m_additionalInfo = fileStreamLines->at(3);
	//name = fileStreamLines->at(1);
	//relevantStat = stod(fileStreamLines->at(4));	//string to double
	//type = itemType;
	//m_cost = stod(fileStreamLines->at(5));	//string to double
	//m_stackSize = stoi(fileStreamLines->at(6));	//string to int
	//m_packageWeight = stod(fileStreamLines->at(7));	//string to double
	//rarity = stoi(fileStreamLines->at(8));	//string to int
	//m_textureName = fileStreamLines->at(9);
	//changing it to the common sensical file format instead of the shitty fuckpoop I had before
	
	type = itemType;
	int i = 0;
	while (i < fileStreamLines->size())
	{
		if (fileStreamLines->at(i).substr(0,5) == "name=") 
		{
			//cout << "name is" << fileData.at(i).substr(5, fileData.at(i).size()) << endl;
			name = fileStreamLines->at(i).substr(5, fileStreamLines->at(i).size());
		}

		if (fileStreamLines->at(i).substr(0,5) == "desc=") 
		{
			//cout << "name is" << fileData.at(i).substr(5, fileData.at(i).size()) << endl;
			description = fileStreamLines->at(i).substr(5, fileStreamLines->at(i).size());
		}

		if (fileStreamLines->at(i).substr(0,6) == "desc2=") 
		{
			//cout << "name is" << fileData.at(i).substr(5, fileData.at(i).size()) << endl;
			m_additionalInfo = fileStreamLines->at(i).substr(6, fileStreamLines->at(i).size());
		}

		if (fileStreamLines->at(i).substr(0,13) == "relevantstat=") 
		{
			//cout << "name is" << fileData.at(i).substr(5, fileData.at(i).size()) << endl;
			relevantStat = stod(fileStreamLines->at(i).substr(13, fileStreamLines->at(i).size()));
		}

		if (fileStreamLines->at(i).substr(0,5) == "cost=") 
		{
			//cout << "name is" << fileData.at(i).substr(5, fileData.at(i).size()) << endl;
			m_cost = stod(fileStreamLines->at(i).substr(5, fileStreamLines->at(i).size()));
		}

		if (fileStreamLines->at(i).substr(0,10) == "stacksize=") 
		{
			//cout << "name is" << fileData.at(i).substr(5, fileData.at(i).size()) << endl;
			m_stackSize = stoi(fileStreamLines->at(i).substr(10, fileStreamLines->at(i).size()));
		}

		if (fileStreamLines->at(i).substr(0,7) == "weight=") 
		{
			//cout << "name is" << fileData.at(i).substr(5, fileData.at(i).size()) << endl;
			m_packageWeight = stod(fileStreamLines->at(i).substr(7, fileStreamLines->at(i).size()));
		}

		if (fileStreamLines->at(i).substr(0,7) == "rarity=") 
		{
			//cout << "name is" << fileData.at(i).substr(5, fileData.at(i).size()) << endl;
			rarity = stoi(fileStreamLines->at(i).substr(7, fileStreamLines->at(i).size()));
		}

		if (fileStreamLines->at(i).substr(0,8) == "texture=") 
		{
			//cout << "name is" << fileData.at(i).substr(5, fileData.at(i).size()) << endl;
			m_textureName = fileStreamLines->at(i).substr(8, fileStreamLines->at(i).size());
		}


		i++;
	}

	findAndSetTexture();
}

inventoryItem :: ~inventoryItem()
{

}

string inventoryItem :: printItemType()
{
	switch (type)
	{
		case 0:
			return "junk";
		case 1:
			return "food";
		case 2:
			return "upgrade part";
		case 3:
			return "sex toy";
		case 4:
			return "drugs";
		case 5:
			return "magic";
		case 6:
			return "scientific";
		case 7:
			return "skill";
		case 8:
			return "crafting resource";
		default:
			return "error";
	}
}

string inventoryItem :: printRarity()
{
	switch (rarity)
	{
		case 0:
			return "abundant";
		case 1:
			return "common";
		case 2:
			return "uncommon";
		case 3:
			return "rare";
		case 4:
			return "legendary";
		case 5:
			return "one of a kind";
		case 6:
			return "cheat item";
		case 7:
			return "not even supposed to exist (you hacker :p)";
		case 8:
			return "Doesn't exist (lol how did you pull that off)";
		default:
			return "error";
	}
}

void inventoryItem :: findAndSetTexture()
{
	//vector<textureEntry*> *textureDatabase
	int i = 0;
	bool foundTexture = false;
	//cout << "creating a new " << getName() << endl;
	while (!foundTexture && i < textureDatabase->size())
	{
		//cout << "compare " << textureDatabase->at(i)->getName() << " to " << getName() << endl;
		if (textureDatabase->at(i)->getName() == m_textureName)
		{	
			//cout << "match found" << endl;
			foundTexture = true;
			tex = textureDatabase->at(i)->tex;
		}
		i++;
	}

	if (!foundTexture) tex = errorTexture;
}

//-2 = absolutely disgusting. 1 = rather gross. 0 = bland. 1 = quite tasty. 2 lavishly delicious
string food :: printPreferability()
{
	switch (m_preferability)
	{
		case -2:
			return "absolutely disgusting";
		case -1:
			return "rather gross";
		case 0:
			return "bland";
		case 1:
			return "quite tasty";
		case 2:
			return "lavishly delicious";
		default:
			return "non-edible";
	}
}

//0 = battery. 1 = diesel engine. 2 = electric engine. 3 = nuclear. 4 = fuel tank. 5 = oxygen generator.
//6 = radar. 7 = lidar. 8 = sonar. 9 = hydrophone. 10 = deck gun. 11 = hull strength. 12 = detection related. 13 = fun
string upgradePart :: printUpgradeType()
{
	switch (upgradeType)
	{
		case 0:
			return "battery";
		case 1:
			return "diesel engine";
		case 2:
			return "electric engine";
		case 3:
			return "nuclear";
		case 4:
			return "fuel tank";
		case 5:
			return "oxygen generator";
		case 6:
			return "radar";
		case 7:
			return "lidar";
		case 8:
			return "sonar";
		case 9:
			return "hydrophone";
		case 10:
			return "deck gun";
		case 11:
			return "hull";
		case 12:
			return "stealth";
		case 13:
			return "fun";
		default:
			return "error";
	}
}

string upgradePart :: printModifiedStat()
{
	switch (upgradeType)
	{
		case 0:
			return "battery capacity: ";
		case 1:
			return "surface speed: ";
		case 2:
			return "submerged speed: ";
		case 3:
			return "power output: ";
		case 4:
			return "fuel capacity: ";
		case 5:
			return "oxygen: ";
		case 6:
			return "radar range: ";
		case 7:
			return "detection bands: ";
		case 8:
			return "active sonar: ";
		case 9:
			return "hydrophone range: ";
		case 10:
			return "deck gun";
		case 11:
			return "max crush depth: ";
		case 12:
			return "stealth";
		case 13:
			return "fun";
		default:
			return "error";
	}
}

//0 = dildo. 1 = buttplug. 2 = cock ring. 3 = cuckhold. 4 = whip. 5 = lingere.
//6 = latex suit. 7 = leather cuit. 8 = vibrator. 9 = porn vhs. 10 = erotic novel. 11 = playboy. 12 = strap-on.
string sexItem :: printSexItemType()
{
	switch (m_sexItemType)
	{
		case 0:
			return "dildo";
		case 1:
			return "buttplug";
		case 2:
			return "cock ring";
		case 3:
			return "cuckhold";
		case 4:
			return "whip";
		case 5:
			return "lingere";
		case 6:
			return "latex suit";
		case 7:
			return "leather suit";
		case 8:
			return "vibrator";
		case 9:
			return "porn vhs";
		case 10:
			return "erotic novel";
		case 11:
			return "playboy magazine";
		case 12:
			return "strap-on";
		default:
			return "error";
	}
}

string drug :: printUseType()
{
	switch (m_useType)
	{
		case 0:
			return "medical";
		case 1:
			return "recreational";
		case 2:
			return "both";
		case 3:
			return "poison";
		default:
			return "error";
	}
}

string skillItem :: printSkillImproved()
{
	switch (m_skillImproved)
	{
		case 0:
			return "seafaring";
		case 1:
			return "witchcraft";
		case 2:
			return "intelligence";
		case 3:
			return "sex";
		default:
			return "shitting";
	}
}

//item's state of matter at room temp and 1 atm
//0 = solid. 1 = liquid. 2 = gas. 3 = other (ex: fire, magic energy orb). 4 = bullshit abtract
string craftingResource :: returnStateOfMatter()
{
	switch (m_stateOfMatter)
	{
		case 0:
			return "solid";
		case 1:
			return "liquid";
		case 2:
			return "gas";
		case 3:
			return "other";
		case 4:
			return "abstract";
	}
}

food :: food()
{

}

food :: food(string newName, string desc, string desc2, double cost, int rare, string textureName, int preferability, double nutrition, bool humanMeat)
{
	name = newName;
	description = desc;
	m_additionalInfo = desc2;
	type = 1;
	relevantStat = 0;
	m_cost = cost;
	rarity = rare;
	m_textureName = textureName;

	m_preferability = preferability;
	m_nutrition = nutrition;
	m_humanMeat = humanMeat;
}

//this needs to very specifically be only the vector<string> generated from the file loader or else it will fail catastrophically
food :: food(vector<string> *fileContents)
{
	//for junk items only
	if (fileContents->at(0) != "food")
	{
		cout << "error. Possibly corrupt file" << endl;
	}
	else
	{
		loadDefaults(fileContents, 1);

		//m_preferability = stoi(fileContents->at(10)); //string to int
		//m_nutrition = stod(fileContents->at(11));	//string to double
		//m_humanMeat = stringToBool(fileContents->at(12));
		int i = 0;
		while (i < fileContents->size())
		{
			//cout << fileContents->at(i) << endl;
			if (fileContents->at(i).substr(0,14) == "preferability=") 
			{
				//cout << "name is" << fileData.at(i).substr(5, fileData.at(i).size()) << endl;
				m_preferability = stoi(fileContents->at(i).substr(14, fileContents->at(i).size()));
			}

			if (fileContents->at(i).substr(0,10) == "nutrition=") 
			{
				//cout << "name is" << fileData.at(i).substr(5, fileData.at(i).size()) << endl;
				m_nutrition = stod(fileContents->at(i).substr(10, fileContents->at(i).size()));
			}

			if (fileContents->at(i).substr(0,10) == "humanmeat=") 
			{
				//cout << "name is" << fileData.at(i).substr(5, fileData.at(i).size()) << endl;
				m_humanMeat = stringToBool(fileContents->at(i).substr(10, fileContents->at(i).size()));
			}

			i++;
		}
	}
}

upgradePart :: upgradePart()
{

}

upgradePart :: upgradePart(string newName, string desc, string desc2, double cost, int rare, string textureName, int upgradeThingType, int submarineCompatibility, double modifier)
{
	name = newName;
	description = desc;
	m_additionalInfo = desc2;
	type = 2;
	relevantStat = 0;
	m_cost = cost;
	rarity = rare;
	m_textureName = textureName;
	m_secondStat = 0;
	m_thirdStat = 0;

	relevantStat = modifier;
	upgradeType = upgradeThingType;
	compatibleSubmarineSize = submarineCompatibility;

	int fsize = 7 * gscreenx / 600;
	m_purchaseButton = button("buy", color(255,255,255), 0, 0, fsize);
	m_purchaseButton.setBorder(true);
	m_purchaseButton.setBackgroundColor(color(20,20,20,100));
}

//this needs to very specifically be only the vector<string> generated from the file loader or else it will fail catastrophically
upgradePart :: upgradePart(vector<string> *fileContents)
{
	m_secondStat = 0;
	m_thirdStat = 0;
	//for junk items only
	if (fileContents->at(0) != "upgrade_part")
	{
		cout << "error. Possibly corrupt file" << endl;
	}
	else
	{
		loadDefaults(fileContents, 2);

		//upgradeType = stoi(fileContents->at(10));
		//compatibleSubmarineSize = stoi(fileContents->at(11));

		int i = 0;
		while (i < fileContents->size())
		{
			if (fileContents->at(i).substr(0,12) == "upgradetype=") 
			{
				upgradeType = stoi(fileContents->at(i).substr(12, fileContents->at(i).size()));
			}

			if (fileContents->at(i).substr(0,14) == "compatiblesub=") 
			{
				compatibleSubmarineSize = stoi(fileContents->at(i).substr(14, fileContents->at(i).size()));
			}

			if (fileContents->at(i).substr(0,11) == "secondstat=") 
			{
				m_secondStat = stod(fileContents->at(i).substr(11, fileContents->at(i).size()));
			}

			if (fileContents->at(i).substr(0,10) == "thirdstat=") 
			{
				m_thirdStat = stod(fileContents->at(i).substr(10, fileContents->at(i).size()));
			}

			i++;
		}
	}

	int fsize = 7 * gscreenx / 600;
	m_purchaseButton = button("buy", color(255,255,255), 0, 0, fsize);
	m_purchaseButton.setBorder(true);
	m_purchaseButton.setBackgroundColor(color(20,20,20,100));
}

//returns pointer to this if buy button pressed
upgradePart* upgradePart :: drawPurchaseIcon(SDL_Renderer *ren, int posX, int posY, int sizeX, int sizeY, int mouseX, int mouseY, Uint32 lastMouse, bool alreadyHasPart, bool isCompatible)
{
	int font_size = 5 * sizeY / 50;
	drawRectFilled(ren, color(20,20,20,100), posX, posY, sizeX, sizeY);
	drawTextWrapped(ren, font_size, color(255,255,255), name + "  " + doubleToMoney(m_cost), posX + sizeY, posY, 2 * (sizeX - sizeY) / 3 );
	drawText(ren, font_size, statString(), posX + sizeY, posY + (getTextYSize(font_size)*2));
	renderTextureEx(tex, ren, posX, posY, sizeY, sizeY, 0);

	if (alreadyHasPart)
	{
		drawRectFilled(ren, color(20,20,20,100), posX, posY, sizeX, sizeY);
		drawText(ren, font_size * 2, color(150,127,255) ,"already equipped", posX, posY + getTextYSize(font_size));
	}
	else if (!isCompatible)
	{
		drawRectFilled(ren, color(20,20,20,100), posX, posY, sizeX, sizeY);
		drawText(ren, font_size * 2, color(255,127,0) ,"incompatible", posX, posY + getTextYSize(font_size));
	}

	if (isColliding2D(posX, posY, sizeX, sizeY, mouseX, mouseY))
	{
		drawRect(ren, color(255,255,0), posX, posY, sizeX, sizeY);
	}

	//set the position for the purchase button and then draw poll it
	m_purchaseButton.setPos(posX + sizeX ,posY);
	m_purchaseButton.draw(ren, mouseX, mouseY, lastMouse);
}

coloredString upgradePart :: statString()
{
	coloredString msg = printModifiedStat();

	if ((upgradeType < 5 && upgradeType != 3) || upgradeType == 11)
	{
		if (relevantStat > 1)
		{
			msg += coloredString("+", color(0,255,0));
			msg += coloredString(doubleToString((relevantStat-1)*100), color(0,255,0));
			msg += coloredString("%", color(0,255,0));
		}
		else
		{
			msg += coloredString("-", color(255,0,0));
			msg += coloredString(doubleToString((relevantStat-1)*100), color(255,0,0));
			msg += coloredString("%", color(255,0,0));
		}
	}

	else if (upgradeType == 5)
	{
		msg += coloredString(to_string(static_cast<int>(relevantStat)), color(255,255,100));
		msg += coloredString(" crew", color(255,255,255));
	}

	else if (upgradeType == 3)
	{
		msg += coloredString(to_string(static_cast<int>(relevantStat)), color(255,255,100));
		msg += coloredString("kw", color(255,255,100));
	}

	else if (upgradeType == 6)
	{
		msg += coloredString(to_string(static_cast<int>(relevantStat)), color(255,255,100));
		msg += coloredString("km", color(255,255,100));
	}

	else if (upgradeType == 7)
	{
		if (relevantStat == 1)
		{
			msg += coloredString("S, X band", color(255,255,100));
		}
		else
		{
			msg += coloredString("S band", color(255,255,100));
		}
	}

	else if (upgradeType == 8)
	{
		//active sonar is given a score of 1, 2, 3, 4 or 5. 1 is lowest, 5 is best
		if (relevantStat == 1)
		{
			msg = coloredString("better than nothing", color(255,20,20));
		}
		else if (relevantStat == 2)
		{
			msg = coloredString("fair", color(255,100,20));
		}
		else if (relevantStat == 3)
		{
			msg = coloredString("mediocre", color(255,255,100));
		}
		else if (relevantStat == 4)
		{
			msg = coloredString("good", color(20,255,20));
		}
		else if (relevantStat == 5)
		{
			msg = coloredString("excellent", color(0,255,100));
		}
	}

	else if (upgradeType == 9)
	{
		msg += coloredString(to_string(static_cast<int>(relevantStat)), color(255,255,100));
		msg += coloredString("km", color(255,255,100));
	}

	else if (upgradeType == 12)
	{
		if (relevantStat > m_secondStat)
		{
			msg = coloredString("Radar detection: ", color(255,255,255));

			if (relevantStat > 1)
			{
				msg += coloredString("-", color(0,255,0));
				msg += coloredString(doubleToString((relevantStat-1)*100), color(0,255,0));
				msg += coloredString("%", color(0,255,0));
			}
			else
			{
				msg += coloredString("+", color(255,0,0));
				msg += coloredString(doubleToString((relevantStat-1)*100), color(255,0,0));
				msg += coloredString("%", color(255,0,0));
			}
		}
		else
		{
			msg = coloredString("Sonar detection: ", color(255,255,255));
			if (m_secondStat > 1)
			{
				msg += coloredString("-", color(0,255,0));
				msg += coloredString(doubleToString((m_secondStat-1)*100), color(0,255,0));
				msg += coloredString("%", color(0,255,0));
			}
			else
			{
				msg += coloredString("+", color(255,0,0));
				msg += coloredString(doubleToString((m_secondStat-1)*100), color(255,0,0));
				msg += coloredString("%", color(255,0,0));
			}
		}
	}

	return msg;
}

sexItem :: sexItem()
{

}

sexItem :: sexItem(string newName, string desc, string desc2, double cost, int rare, string textureName, int sexItemType)
{
	name = newName;
	description = desc;
	m_additionalInfo = desc2;
	type = 3;
	relevantStat = 0;
	m_cost = cost;
	rarity = rare;
	m_textureName = textureName;

	m_sexItemType = sexItemType;

	m_poop = 0;
	m_cum = 0;
	m_piss = 0;
	m_vaginalSlime = 0;
}

//this needs to very specifically be only the vector<string> generated from the file loader or else it will fail catastrophically
sexItem :: sexItem(vector<string> *fileContents)
{
	//for junk items only
	if (fileContents->at(0) != "sex")
	{
		cout << "error. Possibly corrupt file" << endl;
	}
	else
	{
		loadDefaults(fileContents, 3);

		int i = 0;
		while (i < fileContents->size())
		{
			if (fileContents->at(i).substr(0,12) == "sexitemtype=") 
			{
				m_sexItemType = stoi(fileContents->at(i).substr(12, fileContents->at(i).size()));
			}

			i++;
		}

		//m_sexItemType = stoi(fileContents->at(10)); //string to int
	}
}

drug :: drug()
{

}

drug :: drug(string newName, string desc, string desc2, double cost, int rare, string textureName, int useType, double quantity)
{
	name = newName;
	description = desc;
	m_additionalInfo = desc2;
	type = 4;
	relevantStat = 0;
	m_cost = cost;
	rarity = rare;
	m_textureName = textureName;

	m_useType = useType;
	m_quantity = quantity;
}

//this needs to very specifically be only the vector<string> generated from the file loader or else it will fail catastrophically
drug :: drug(vector<string> *fileContents)
{
	//for junk items only
	if (fileContents->at(0) != "drug")
	{
		cout << "error. Possibly corrupt file" << endl;
	}
	else
	{
		loadDefaults(fileContents, 4);

		//m_useType = stoi(fileContents->at(10)); //string to int
		//m_quantity = stod(fileContents->at(11)); 	//string to double

		int i = 0;
		while (i < fileContents->size())
		{
			if (fileContents->at(i).substr(0,8) == "usetype=") 
			{
				m_useType = stoi(fileContents->at(i).substr(8, fileContents->at(i).size()));
			}

			if (fileContents->at(i).substr(0,13) == "activeamount=") 
			{
				m_quantity = stod(fileContents->at(i).substr(13, fileContents->at(i).size()));
			}

			i++;
		}
	}
}

magicItem :: magicItem()
{

}

magicItem :: magicItem(string newName, string desc, string desc2, double cost, int rare, string textureName, double power)
{
	name = newName;
	description = desc;
	m_additionalInfo = desc2;
	type = 5;
	relevantStat = 0;
	m_cost = cost;
	rarity = rare;
	m_textureName = textureName;

	m_power= power;
}

//this needs to very specifically be only the vector<string> generated from the file loader or else it will fail catastrophically
magicItem :: magicItem(vector<string> *fileContents)
{
	//for junk items only
	if (fileContents->at(0) != "magic")
	{
		cout << "error. Possibly corrupt file" << endl;
	}
	else
	{
		loadDefaults(fileContents, 5);

		//m_power = stod(fileContents->at(10)); //string to double

		int i = 0;
		while (i < fileContents->size())
		{
			if (fileContents->at(i).substr(0,11) == "magicpower=") 
			{
				m_power = stod(fileContents->at(i).substr(11, fileContents->at(i).size()));
			}

			i++;
		}
	}
}

scienceItem :: scienceItem()
{

}

scienceItem :: scienceItem(string newName, string desc, string desc2, double cost, int rare, string textureName, bool bong)
{
	name = newName;
	description = desc;
	m_additionalInfo = desc2;
	type = 6;
	relevantStat = 0;
	m_cost = cost;
	rarity = rare;
	m_textureName = textureName;

	m_canBeUsedAsBong = bong;
}

//this needs to very specifically be only the vector<string> generated from the file loader or else it will fail catastrophically
scienceItem :: scienceItem(vector<string> *fileContents)
{
	//for junk items only
	if (fileContents->at(0) != "science")
	{
		cout << "error. Possibly corrupt file" << endl;
	}
	else
	{
		loadDefaults(fileContents, 6);

		//m_canBeUsedAsBong = stringToBool(fileContents->at(10)); //string to bool

		int i = 0;
		while (i < fileContents->size())
		{
			if (fileContents->at(i).substr(0,7) == "isbong=") 
			{
				m_canBeUsedAsBong = stringToBool(fileContents->at(i).substr(7, fileContents->at(i).size()));
			}

			i++;
		}
	}
}

skillItem :: skillItem()
{

}

//this needs to very specifically be only the vector<string> generated from the file loader or else it will fail catastrophically
skillItem :: skillItem(vector<string> *fileContents)
{
	//for junk items only
	if (fileContents->at(0) != "skill")
	{
		cout << "error. Possibly corrupt file" << endl;
	}
	else
	{
		loadDefaults(fileContents, 7);

		//m_skillImproved = stoi(fileContents->at(10)); //string int
		//m_minLevel = stoi(fileContents->at(11)); //string to int
		//m_maxLevel = stoi(fileContents->at(12)); //string to int

		int i = 0;
		while (i < fileContents->size())
		{
			if (fileContents->at(i).substr(0,14) == "skillimproved=") 
			{
				m_skillImproved = stoi(fileContents->at(i).substr(14, fileContents->at(i).size()));
			}

			if (fileContents->at(i).substr(0,9) == "minskill=") 
			{
				m_minLevel = stoi(fileContents->at(i).substr(9, fileContents->at(i).size()));
			}

			if (fileContents->at(i).substr(0,9) == "maxskill=") 
			{
				m_maxLevel = stoi(fileContents->at(i).substr(9, fileContents->at(i).size()));
			}

			i++;
		}
	}
}

craftingResource :: craftingResource()
{

}

//this needs to very specifically be only the vector<string> generated from the file loader or else it will fail catastrophically
craftingResource :: craftingResource(vector<string> *fileContents)
{
	//for junk items only
	if (fileContents->at(0) != "crafting")
	{
		cout << "error. Possibly corrupt file" << endl;
	}
	else
	{
		loadDefaults(fileContents, 8);

		//m_isMetal = stringToBool(fileContents->at(10));
		//m_isSemiconductor = stringToBool(fileContents->at(11));
		//m_isMagic = stringToBool(fileContents->at(12));
		//m_isRadioactive = stringToBool(fileContents->at(13));
		//m_stateOfMatter = stoi(fileContents->at(14));
		//m_metallicStrength = stod(fileContents->at(15));

		int i = 0;
		while (i < fileContents->size())
		{
			if (fileContents->at(i).substr(0,9) == "is_metal=") 
			{
				m_isMetal = stringToBool(fileContents->at(i).substr(9, fileContents->at(i).size()));
			}

			if (fileContents->at(i).substr(0,17) == "is_semiconductor=") 
			{
				m_isSemiconductor = stringToBool(fileContents->at(i).substr(17, fileContents->at(i).size()));
			}

			if (fileContents->at(i).substr(0,9) == "is_magic=") 
			{
				m_isMagic = stringToBool(fileContents->at(i).substr(9, fileContents->at(i).size()));
			}

			if (fileContents->at(i).substr(0,15) == "is_radioactive=") 
			{
				m_isRadioactive = stringToBool(fileContents->at(i).substr(15, fileContents->at(i).size()));
			}

			if (fileContents->at(i).substr(0,14) == "stateofmatter=") 
			{
				m_stateOfMatter = stoi(fileContents->at(i).substr(14, fileContents->at(i).size()));
			}

			if (fileContents->at(i).substr(0,17) == "metallicstrength=") 
			{
				m_metallicStrength = stod(fileContents->at(i).substr(17, fileContents->at(i).size()));
			}

			i++;
		}
	}
}

string sexDirtyToString(int dirtiness)
{
	switch (dirtiness)
	{
		case 0:
			return "none";
		case 1:
			return "little";
		case 2:
			return "lots";
		default:
			return "i don't know, man";
	}
}

ostream& operator<<(ostream& os, inventoryItem item)
{
	os << "Item name: " << item.getName() << endl;
	os << "Description: " << item.getDescription() << endl;
	os << "Other description: " << item.getOtherDescription() << endl;
	os << "item type: " << item.printItemType() << " (" << item.getItemType() << ")" << endl;
	os << "rarity: " << item.printRarity() << " (" << item.getRarity() << ")" << endl;
	os << "cost: " << item.getCost() << endl;
	os << "max stack size: " << item.maxStackSize() << endl;
	os << "weight: " << gramsToReadable(item.weight()) << endl;
	os << "texture name: " << item.getTextureName() << endl;

	return os;
}

ostream& operator<<(ostream& os, food item)
{
	os << "Item name: " << item.getName() << endl;
	os << "Description: " << item.getDescription() << endl;
	os << "Other description: " << item.getOtherDescription() << endl;
	os << "item type: " << item.printItemType() << " (" << item.getItemType() << ")" << endl;
	os << "rarity: " << item.printRarity() << " (" << item.getRarity() << ")" << endl;
	os << "cost: " << item.getCost() << endl;
	os << "max stack size: " << item.maxStackSize() << endl;
	os << "weight: " << gramsToReadable(item.weight()) << endl;
	os << "texture name: " << item.getTextureName() << endl;
	os << "preferability: " << item.getPreferability() << endl;
	os << "nutrition: " << item.getNutrition() << endl;
	os << "isHumanMeat: " << item.isHumanMeat() << endl;

	return os;
}

ostream& operator<<(ostream& os, upgradePart item)
{
	os << "Item name: " << item.getName() << endl;
	os << "Description: " << item.getDescription() << endl;
	os << "Other description: " << item.getOtherDescription() << endl;
	os << "item type: " << item.printItemType() << " (" << item.getItemType() << ")" << endl;
	os << "rarity: " << item.printRarity() << " (" << item.getRarity() << ")" << endl;
	os << "cost: " << item.getCost() << endl;
	os << "max stack size: " << item.maxStackSize() << endl;
	os << "weight: " << gramsToReadable(item.weight()) << endl;
	os << "texture name: " << item.getTextureName() << endl;
	os << "upgrade type: " << item.printUpgradeType() << " (" << item.getUpgradeType() << ")" << endl;
	os << "modifier value: " << item.getModifierAmount() << endl;
	os << "compatible submarine size" << item.getSubSize() << endl;

	return os;
}

ostream& operator<<(ostream& os, sexItem item)
{
	os << "Item name: " << item.getName() << endl;
	os << "Description: " << item.getDescription() << endl;
	os << "Other description: " << item.getOtherDescription() << endl;
	os << "item type: " << item.printItemType() << " (" << item.getItemType() << ")" << endl;
	os << "rarity: " << item.printRarity() << " (" << item.getRarity() << ")" << endl;
	os << "cost: " << item.getCost() << endl;
	os << "max stack size: " << item.maxStackSize() << endl;
	os << "weight: " << gramsToReadable(item.weight()) << endl;
	os << "texture name: " << item.getTextureName() << endl;
	os << "type of sextoy: " << item.printSexItemType() << " (" << item.sexItemType() << ")" << endl;
	os << "amount of poop: " << sexDirtyToString(item.getPoop()) << endl;
	os << "amount of cum: " << sexDirtyToString(item.getCum()) << endl;
	os << "amount of piss: " << sexDirtyToString(item.getPiss()) << endl;
	os << "amount of slime: " << sexDirtyToString(item.getSlime()) << endl;

	return os;
}

ostream& operator<<(ostream& os, drug item)
{
	os << "Item name: " << item.getName() << endl;
	os << "Description: " << item.getDescription() << endl;
	os << "Other description: " << item.getOtherDescription() << endl;
	os << "item type: " << item.printItemType() << " (" << item.getItemType() << ")" << endl;
	os << "rarity: " << item.printRarity() << " (" << item.getRarity() << ")" << endl;
	os << "cost: " << item.getCost() << endl;
	os << "max stack size: " << item.maxStackSize() << endl;
	os << "weight: " << gramsToReadable(item.weight()) << endl;
	os << "texture name: " << item.getTextureName() << endl;
	os << "drug type: " << item.printUseType() << endl;
	os << "amount per dose: " << gramsToReadable(item.getQuantity()) << " (" << item.getQuantity() << ")" << endl;

	return os;
}

ostream& operator<<(ostream& os, magicItem item)
{
	os << "Item name: " << item.getName() << endl;
	os << "Description: " << item.getDescription() << endl;
	os << "Other description: " << item.getOtherDescription() << endl;
	os << "item type: " << item.printItemType() << " (" << item.getItemType() << ")" << endl;
	os << "rarity: " << item.printRarity() << " (" << item.getRarity() << ")" << endl;
	os << "cost: " << item.getCost() << endl;
	os << "max stack size: " << item.maxStackSize() << endl;
	os << "weight: " << gramsToReadable(item.weight()) << endl;
	os << "texture name: " << item.getTextureName() << endl;
	os << "magical power:" << item.getPower() << endl;

	return os;
}

ostream& operator<<(ostream& os, scienceItem item)
{
	os << "Item name: " << item.getName() << endl;
	os << "Description: " << item.getDescription() << endl;
	os << "Other description: " << item.getOtherDescription() << endl;
	os << "item type: " << item.printItemType() << " (" << item.getItemType() << ")" << endl;
	os << "rarity: " << item.printRarity() << " (" << item.getRarity() << ")" << endl;
	os << "cost: " << item.getCost() << endl;
	os << "max stack size: " << item.maxStackSize() << endl;
	os << "weight: " << gramsToReadable(item.weight()) << endl;
	os << "texture name: " << item.getTextureName() << endl;
	os << "isbong = " << item.canBeUsedAsBong() << endl;

	return os;
}

ostream& operator<<(ostream& os, skillItem item)
{
	os << "Item name: " << item.getName() << endl;
	os << "Description: " << item.getDescription() << endl;
	os << "Other description: " << item.getOtherDescription() << endl;
	os << "item type: " << item.printItemType() << " (" << item.getItemType() << ")" << endl;
	os << "rarity: " << item.printRarity() << " (" << item.getRarity() << ")" << endl;
	os << "cost: " << item.getCost() << endl;
	os << "max stack size: " << item.maxStackSize() << endl;
	os << "weight: " << gramsToReadable(item.weight()) << endl;
	os << "texture name: " << item.getTextureName() << endl;
	os << "skill improved: " << item.printSkillImproved() << " (" << item.skillImproved() << ") " << endl;
	os << "min skill: " << item.minLevel() << endl;
	os << "max skill: " << item.maxLevel() << endl;

	return os;
}

ostream& operator<<(ostream& os, craftingResource item)
{
	os << "Item name: " << item.getName() << endl;
	os << "Description: " << item.getDescription() << endl;
	os << "Other description: " << item.getOtherDescription() << endl;
	os << "item type: " << item.printItemType() << " (" << item.getItemType() << ")" << endl;
	os << "rarity: " << item.printRarity() << " (" << item.getRarity() << ")" << endl;
	os << "cost: " << item.getCost() << endl;
	os << "max stack size: " << item.maxStackSize() << endl;
	os << "weight: " << gramsToReadable(item.weight()) << endl;
	os << "texture name: " << item.getTextureName() << endl;
	os << "state of matter: " << item.returnStateOfMatter() << " (" << item.stateOfMatter() << ") " << endl;
	os << "is metallic: " << item.isMetal() << endl;
	os << "is semiconductor: " << item.isSemiconductor() << endl;
	os << "is magic: " << item.isMagic() << endl;
	os << "is radioactive: " << item.isRadioactive() << endl;

	return os;
}

//= operator overloads
inventoryItem& inventoryItem :: operator=(inventoryItem& other)
{
	name = other.getName();
	description = other.getDescription();
	m_additionalInfo = other.getOtherDescription();
	type = other.getType();
	relevantStat = other.getRelevantStat();
	m_cost = other.getCost();
	rarity = other.getRarity();
	m_textureName = other.getTextureName();
	m_stackSize = other.maxStackSize();
	m_packageWeight = other.weight();
	tex = other.getTexture();
	return *this;
}

food& food :: operator=(food& other)
{
	name = other.getName();
	description = other.getDescription();
	m_additionalInfo = other.getOtherDescription();
	type = other.getType();
	relevantStat = other.getRelevantStat();
	m_cost = other.getCost();
	rarity = other.getRarity();
	m_textureName = other.getTextureName();
	m_stackSize = other.maxStackSize();
	m_packageWeight = other.weight();

	m_preferability = other.getPreferability();
	m_nutrition = other.getNutrition();
	m_humanMeat = other.isHumanMeat();

	tex = other.getTexture();

	return *this;
}

upgradePart& upgradePart :: operator=(upgradePart& other)
{
	name = other.getName();
	description = other.getDescription();
	m_additionalInfo = other.getOtherDescription();
	type = other.getType();
	relevantStat = other.getRelevantStat();
	m_cost = other.getCost();
	rarity = other.getRarity();
	m_textureName = other.getTextureName();
	m_stackSize = other.maxStackSize();
	m_packageWeight = other.weight();

	upgradeType = other.getUpgradeType();
	compatibleSubmarineSize = other.getSubSize();

	m_secondStat = other.getSecondStat();
	m_thirdStat = other.getThirdStat();

	tex = other.getTexture();

	//int fsize = 7 * gscreenx / 600;
	//m_purchaseButton = button("buy", color(255,255,255), 0, 0, fsize);
	m_purchaseButton = other.getPurchaseButton();

	return *this;
}

sexItem& sexItem :: operator=(sexItem& other)
{
	name = other.getName();
	description = other.getDescription();
	m_additionalInfo = other.getOtherDescription();
	type = other.getType();
	relevantStat = other.getRelevantStat();
	m_cost = other.getCost();
	rarity = other.getRarity();
	m_textureName = other.getTextureName();
	m_stackSize = other.maxStackSize();
	m_packageWeight = other.weight();

	m_sexItemType = other.sexItemType();
	m_poop = other.getPoop();
	m_cum = other.getCum();
	m_piss = other.getPiss();
	m_vaginalSlime = other.getSlime();

	tex = other.getTexture();

	return *this;
}

drug& drug :: operator=(drug& other)
{
	name = other.getName();
	description = other.getDescription();
	m_additionalInfo = other.getOtherDescription();
	type = other.getType();
	relevantStat = other.getRelevantStat();
	m_cost = other.getCost();
	rarity = other.getRarity();
	m_textureName = other.getTextureName();
	m_stackSize = other.maxStackSize();
	m_packageWeight = other.weight();

	m_useType = other.useType();
	m_quantity = other.getQuantity();

	tex = other.getTexture();

	return *this;
}

magicItem& magicItem :: operator=(magicItem& other)
{
	name = other.getName();
	description = other.getDescription();
	m_additionalInfo = other.getOtherDescription();
	type = other.getType();
	relevantStat = other.getRelevantStat();
	m_cost = other.getCost();
	rarity = other.getRarity();
	m_textureName = other.getTextureName();
	m_stackSize = other.maxStackSize();
	m_packageWeight = other.weight();

	m_power = other.getPower();

	tex = other.getTexture();

	return *this;
}

scienceItem& scienceItem :: operator=(scienceItem& other)
{
	name = other.getName();
	description = other.getDescription();
	m_additionalInfo = other.getOtherDescription();
	type = other.getType();
	relevantStat = other.getRelevantStat();
	m_cost = other.getCost();
	rarity = other.getRarity();
	m_textureName = other.getTextureName();
	m_stackSize = other.maxStackSize();
	m_packageWeight = other.weight();

	m_canBeUsedAsBong = other.canBeUsedAsBong();

	tex = other.getTexture();

	return *this;
}

skillItem& skillItem :: operator=(skillItem& other)
{
	name = other.getName();
	description = other.getDescription();
	m_additionalInfo = other.getOtherDescription();
	type = other.getType();
	relevantStat = other.getRelevantStat();
	m_cost = other.getCost();
	rarity = other.getRarity();
	m_textureName = other.getTextureName();
	m_stackSize = other.maxStackSize();
	m_packageWeight = other.weight();

	m_skillImproved= other.skillImproved();
	m_minLevel = other.minLevel();
	m_maxLevel = other.maxLevel();

	tex = other.getTexture();

	return *this;
}

craftingResource& craftingResource :: operator=(craftingResource& other)
{
	name = other.getName();
	description = other.getDescription();
	m_additionalInfo = other.getOtherDescription();
	type = other.getType();
	relevantStat = other.getRelevantStat();
	m_cost = other.getCost();
	rarity = other.getRarity();
	m_textureName = other.getTextureName();
	m_stackSize = other.maxStackSize();
	m_packageWeight = other.weight();

	m_isMetal = other.isMetal();
	m_metallicStrength = other.metallicStrength();
	m_isSemiconductor = other.isSemiconductor();
	m_isMagic = other.isMagic();
	m_isRadioactive = other.isRadioactive();
	m_stateOfMatter = other.stateOfMatter();

	tex = other.getTexture();

	return *this;
}

inventoryItem* getRandomInventoryItem(vector<inventoryItem*> *itemDatabase, uint32_t seed)
{
	int thingIndex = 0;

	if (seed == 0)
	{
		thingIndex = rand() % itemDatabase->size();
	}
	else
	{
		thingIndex = betterRand(seed + 9912) % itemDatabase->size();
	}

	return itemDatabase->at(thingIndex);
}

inventoryItem* getRandomJunk(vector<inventoryItem*> *itemDatabase, uint32_t seed)
{
	int thingIndex = 0;
	int i = 0;
	bool loop = true;

	while (loop)
	{
		if (seed == 0)
		{
			thingIndex = rand() % itemDatabase->size();
		}
		else
		{
			thingIndex = betterRand(seed + 9912 + i) % itemDatabase->size();
		}

		if (itemDatabase->at(thingIndex)->getItemType() == 0) loop = false;
		i++; 
	}


	return itemDatabase->at(thingIndex);
}

food* getRandomFood(vector<inventoryItem*> *itemDatabase, uint32_t seed)
{
	int thingIndex = 0;
	int i = 0;
	bool loop = true;

	while (loop)
	{
		if (seed == 0)
		{
			thingIndex = rand() % itemDatabase->size();
		}
		else
		{
			thingIndex = betterRand(seed + 9912 + i) % itemDatabase->size();
		}

		if (itemDatabase->at(thingIndex)->getItemType() == 1) loop = false;
		i++; 
	}


	return static_cast<food*>(itemDatabase->at(thingIndex));
}

upgradePart* getRandomUpgradePart(vector<inventoryItem*> *itemDatabase, uint32_t seed)
{
	int thingIndex = 0;
	int i = 0;
	bool loop = true;

	while (loop)
	{
		if (seed == 0)
		{
			thingIndex = rand() % itemDatabase->size();
		}
		else
		{
			thingIndex = betterRand(seed + 9912 + i) % itemDatabase->size();
		}

		if (itemDatabase->at(thingIndex)->getItemType() == 2) loop = false;
		i++; 
	}


	return static_cast<upgradePart*>(itemDatabase->at(thingIndex));
}

sexItem* getRandomSexItem(vector<inventoryItem*> *itemDatabase, uint32_t seed)
{
	int thingIndex = 0;
	int i = 0;
	bool loop = true;

	while (loop)
	{
		if (seed == 0)
		{
			thingIndex = rand() % itemDatabase->size();
		}
		else
		{
			thingIndex = betterRand(seed + 9912 + i) % itemDatabase->size();
		}

		if (itemDatabase->at(thingIndex)->getItemType() == 3) loop = false;
		i++; 
	}


	return static_cast<sexItem*>(itemDatabase->at(thingIndex));
}

drug* getRandomDrug(vector<inventoryItem*> *itemDatabase, uint32_t seed)
{
	int thingIndex = 0;
	int i = 0;
	bool loop = true;

	while (loop)
	{
		if (seed == 0)
		{
			thingIndex = rand() % itemDatabase->size();
		}
		else
		{
			thingIndex = betterRand(seed + 9912 + i) % itemDatabase->size();
		}

		if (itemDatabase->at(thingIndex)->getItemType() == 4) loop = false;
		i++; 
	}


	return static_cast<drug*>(itemDatabase->at(thingIndex));
}

magicItem* getRandomMagicItem(vector<inventoryItem*> *itemDatabase, uint32_t seed)
{
	int thingIndex = 0;
	int i = 0;
	bool loop = true;

	while (loop)
	{
		if (seed == 0)
		{
			thingIndex = rand() % itemDatabase->size();
		}
		else
		{
			thingIndex = betterRand(seed + 9912 + i) % itemDatabase->size();
		}

		if (itemDatabase->at(thingIndex)->getItemType() == 5) loop = false;
		i++; 
	}


	return static_cast<magicItem*>(itemDatabase->at(thingIndex));
}

scienceItem* getRandomScienceItem(vector<inventoryItem*> *itemDatabase, uint32_t seed)
{
	int thingIndex = 0;
	int i = 0;
	bool loop = true;

	while (loop)
	{
		if (seed == 0)
		{
			thingIndex = rand() % itemDatabase->size();
		}
		else
		{
			thingIndex = betterRand(seed + 9912 + i) % itemDatabase->size();
		}

		if (itemDatabase->at(thingIndex)->getItemType() == 6) loop = false;
		i++; 
	}


	return static_cast<scienceItem*>(itemDatabase->at(thingIndex));
}

skillItem* getRandomSkillItem(vector<inventoryItem*> *itemDatabase, uint32_t seed)
{
	int thingIndex = 0;
	int i = 0;
	bool loop = true;

	while (loop)
	{
		if (seed == 0)
		{
			thingIndex = rand() % itemDatabase->size();
		}
		else
		{
			thingIndex = betterRand(seed + 9912 + i) % itemDatabase->size();
		}

		if (itemDatabase->at(thingIndex)->getItemType() == 7) loop = false;
		i++; 
	}


	return static_cast<skillItem*>(itemDatabase->at(thingIndex));
}

craftingResource* getRandomCraftingResource(vector<inventoryItem*> *itemDatabase, uint32_t seed)
{
	int thingIndex = 0;
	int i = 0;
	bool loop = true;

	while (loop)
	{
		if (seed == 0)
		{
			thingIndex = rand() % itemDatabase->size();
		}
		else
		{
			thingIndex = betterRand(seed + 9912 + i) % itemDatabase->size();
		}

		if (itemDatabase->at(thingIndex)->getItemType() == 8) loop = false;
		i++; 
	}


	return static_cast<craftingResource*>(itemDatabase->at(thingIndex));
}

upgradePart* findUpgradePartByName(vector<inventoryItem*> *itemDatabase, string thingyname)
{
	int thingIndex = 0;
	int i = 0;
	bool loop = true;

	while (loop && i < itemDatabase->size())
	{
		if (itemDatabase->at(i)->getItemType() == 2 && itemDatabase->at(i)->getName() == thingyname) 
		{
			cout << itemDatabase->at(i)->getName() << "==" << thingyname << endl; 
			loop = false;
			thingIndex = i;
		}
		//cout << "is " << itemDatabase->at(i)->getName() << " equal to " << thingyname << " ?" << endl;
		i++; 
	}

	if (loop)
	{
		//if it didn't find a match
		cout << "upgrade part of name " << thingyname << " not found" << endl;
		return nullptr;
	}
	else
	{
		cout << "returning " << itemDatabase->at(thingIndex)->getName() << ". queried name was " << thingyname << endl;
		return static_cast<upgradePart*>(itemDatabase->at(thingIndex));
	}
}

void printAllItemsInDatabase(vector<inventoryItem*> *itemDatabase)
{
	for (int i = 0; i < itemDatabase->size(); i++)
	{
		cout << itemDatabase->at(i)->getName() << endl;
	}
}

void printAllItemsInDatabaseDetailed(vector<inventoryItem*> *itemDatabase)
{
	for (int i = 0; i < itemDatabase->size(); i++)
	{
		int thingType = itemDatabase->at(i)->getType();
		cout << "type = " << thingType << endl;
		switch (itemDatabase->at(i)->getType())
		{
			case 0:
				cout << *itemDatabase->at(i) << endl;
				break;
			case 1:
				cout << *static_cast<food*>(itemDatabase->at(i)) << endl;
				break;
			case 2:
				cout << *static_cast<upgradePart*>(itemDatabase->at(i)) << endl;
				break;
			case 3:
				cout << *static_cast<sexItem*>(itemDatabase->at(i)) << endl;
				break;
			case 4:
				cout << *static_cast<drug*>(itemDatabase->at(i)) << endl;
				break;
			case 5:
				cout << *static_cast<magicItem*>(itemDatabase->at(i)) << endl;
				break;
			case 6:
				cout << *static_cast<scienceItem*>(itemDatabase->at(i)) << endl;
				break;
			case 7:
				cout << *static_cast<skillItem*>(itemDatabase->at(i)) << endl;
				break;
			case 8:
				cout << *static_cast<craftingResource*>(itemDatabase->at(i)) << endl;
				break;
		}
	}
}

int loadInventoryItems(vector<inventoryItem*> *itemDatabase)
{
	string itemsPath = "Data/items/";
	string partsPath = "Data/parts/";
	vector<string> filePaths;

	for (const auto & entry : std::filesystem::directory_iterator(itemsPath))
	{
        //std::cout << entry.path() << std::endl;
        filePaths.push_back(entry.path());
	}

	for (const auto & entry : std::filesystem::directory_iterator(partsPath))
	{
        //std::cout << entry.path() << std::endl;
        filePaths.push_back(entry.path());
	}

	int numFiles = filePaths.size();
	for (int i = 0; i < numFiles; i++)
	{
		ifstream itemFile(filePaths.at(i));
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


		if (linesOfFile.at(0) == "junk") 
		{
			inventoryItem newItem(&linesOfFile);
			itemDatabase->push_back(new inventoryItem);
			*itemDatabase->back() = newItem;
		}
		else if (linesOfFile.at(0) == "food")
		{
			food newItem(&linesOfFile);
			itemDatabase->push_back(new food);
			*static_cast<food*>(itemDatabase->back()) = newItem;
		}
		else if (linesOfFile.at(0) == "sex")
		{
			sexItem newItem(&linesOfFile);
			itemDatabase->push_back(new sexItem);
			*static_cast<sexItem*>(itemDatabase->back()) = newItem;
		}
		else if (linesOfFile.at(0) == "drug")
		{
			drug newItem(&linesOfFile);
			itemDatabase->push_back(new drug);
			*static_cast<drug*>(itemDatabase->back()) = newItem;
		}
		else if (linesOfFile.at(0) == "magic")
		{
			magicItem newItem(&linesOfFile);
			itemDatabase->push_back(new magicItem);
			*static_cast<magicItem*>(itemDatabase->back()) = newItem;
		}
		else if (linesOfFile.at(0) == "science")
		{
			scienceItem newItem(&linesOfFile);
			itemDatabase->push_back(new scienceItem);
			*static_cast<scienceItem*>(itemDatabase->back()) = newItem;
		}
		else if (linesOfFile.at(0) == "skill")
		{
			skillItem newItem(&linesOfFile);
			itemDatabase->push_back(new skillItem);
			*static_cast<skillItem*>(itemDatabase->back()) = newItem;
		}
		else if (linesOfFile.at(0) == "crafting")
		{
			craftingResource newItem(&linesOfFile);
			itemDatabase->push_back(new craftingResource);
			*static_cast<craftingResource*>(itemDatabase->back()) = newItem;
		}
		else if (linesOfFile.at(0) == "upgrade_part")
		{
			upgradePart newItem(&linesOfFile);
			itemDatabase->push_back(new upgradePart);
			*static_cast<upgradePart*>(itemDatabase->back()) = newItem;
		}
		itemFile.close();

	}
	return 0;
}