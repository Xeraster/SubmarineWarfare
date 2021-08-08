devConsole :: devConsole()
{
	//color consoleColor(0,255,0);
	//coloredString welcome("Welcome to the console", consoleColor);
	coloredString welcome("Welcome", color(255,127,0));
	welcome += coloredString(" to the ", color(120,150,255));
	welcome += coloredString("console", color(0,255,0));
	m_consoleOutput.push_front(welcome);
	//m_consoleOutput.push_front("Welcome to the console");

	color bkg(25,25,25,200);
	color txt(24,240,24,255);
	m_backgroundColor = bkg;
	m_textColor = txt;
	m_enterDeAssertedYet = true;
	m_showConsole = false;

	textbox temp("", m_textColor, 0, 0, 8, 255);
	m_inputLine = temp;
}

void devConsole :: draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse, int screenSizeX, int screenSizeY)
{
	//I added this to prevent the console from inserting the tilde key every time the user closes it with tildo
	if (lastCharTyped == "`" && m_showConsole)
	{
		m_inputLine.deselect();
	}

	if (m_showConsole)
	{
		drawRectFilled(ren, m_backgroundColor, 0, 0, m_screenX, m_screenY / 2);

		//draw each of the lines of text in the list
		list<coloredString> copied(m_consoleOutput);
		for (int i = 0; i < m_consoleOutput.size(); i++)
		{
			//drawText(ren, m_textSize, m_textColor, copied.front(), 10, (m_screenY / 2) - ((i+2)*(80 * m_textSize / 24)));
			drawText(ren, m_textSize, copied.front(), 10, (m_screenY / 2) - ((i+2)*(80 * m_textSize / 24)));
			copied.pop_front();
		}

		string currentText = m_inputLine.draw(ren, mouseX, mouseY, lastmouse);
		if (enterAsserted && m_enterDeAssertedYet)
		{
			if (parseInput(currentText)) m_inputLine.replaceText("");
			m_enterDeAssertedYet = false;
		}

		if (!enterAsserted && ! m_enterDeAssertedYet)
		{
			m_enterDeAssertedYet = true;
		}
	}

	if (lastCharTyped == "`")
	{
		m_showConsole = !m_showConsole;
		if (m_showConsole) m_inputLine.select();
		else if (!m_showConsole) m_inputLine.deselect();
	}
}

void devConsole :: setScreenSize(int x, int y) 
{ 
	m_screenX = x;
	m_screenY = y;

	//use 800x600 to establish the base ratio
	m_textSize = 8 * (m_screenY / 600);

	int textHeight = (80 * m_textSize / 24);
	int consoleY = m_screenY / 2;
	m_numLines = consoleY / textHeight;

	textbox temp("", m_textColor, 0, 0, m_textSize, 255);
	m_inputLine = temp;
	m_inputLine.setPos(0, consoleY - textHeight);

	cout << "number of console lines based on screen size and provided text size is " << m_numLines << endl;
}

void devConsole :: printString(string stringToPrint)
{
	appendTextToConsole(stringToPrint);
}

void devConsole :: giveQualifications(string parameters)
{
	if (parameters.size() == 0)
	{
		throwError("no parameters");
		return void();
	}
	int qualId = stoi(parameters.substr(0, 2));

	//find pointer ONCE and save it for later
	qualification *qual = getQualificationById(qualId);

	if (qual == nullptr)
	{
		throwError("qualification id not found");
		return void();
	}
	int count = 0;

	if (playerCampaignInfo != nullptr && playerCampaignInfo)
	{
		if (playerCampaignInfo->numEmployedCrew() == 0)
		{
			throwError("no crew hired");
		}
		else
		{
			for (int i = 0; i < playerCampaignInfo->numEmployedCrew(); i++)
			{
				if (playerCampaignInfo->getEmployedCrew(i).isInitialized())
				{
					if (playerCampaignInfo->getEmployedCrew(i).giveQualification(qual)) 
					{
						count++;
						cout << "gave qualification to " << playerCampaignInfo->getEmployedCrew(i).getFirstName() << playerCampaignInfo->getEmployedCrew(i).getLastName() << endl;
					}
				}
			}

			appendTextToConsole("Awarded " + qual->name() + " to " + to_string(count) + " crew members");
		}
	}
	else
	{
		throwError("not ingame");
	}
}

void devConsole :: addQualifications(string parameters)
{
	if (parameters.size() == 0)
	{
		throwError("no parameters");
		return void();
	}
	int qualsToAdd = 0;
	
	if (parameters.size() < 6)
	{
		qualsToAdd = stoi(parameters.substr(0, parameters.size()));
	}
	else
	{
		qualsToAdd = 1;
	}

	if (playerCampaignInfo != nullptr)
	{
		int oldNum = playerCampaignInfo->getQualificationCount();
		playerCampaignInfo->setQualificationCount(oldNum + qualsToAdd);
		appendTextToConsole("changed qualifications from " + to_string(oldNum) + " to " + to_string(playerCampaignInfo->getQualificationCount()));
	}
	else
	{
		throwError("not ingame");
	}
}

void devConsole :: addAwards(string parameters)
{
	if (!isIngame())
	{
		throwError("not ingame");
		return void();
	}
	else
	{
		for (int i = 0; i < playerCampaignInfo->numLoadedAwards(); i++)
		{
			playerCampaignInfo->setAwards(i, 10);
		}
		appendTextToConsole("set all awards to 10");
	}


}

void devConsole :: addMoney(string parameters)
{
	if (parameters.size() == 0)
	{
		throwError("no parameters");
		return void();
	}
	else if (!isIngame())
	{
		throwError("not ingame");
		return void();
	}
	else
	{
		int moneyToAdd = 0;

		if (parameters.size() < 7)
		{
			moneyToAdd = stoi(parameters.substr(0, parameters.size()));
		}
		else
		{
			moneyToAdd = 2147483646;
		}
		playerCampaignInfo->setMoney(playerCampaignInfo->money() + moneyToAdd);
		coloredString textResult("Added ");
		textResult += coloredString("$", color(255,255,50));
		textResult += coloredString(to_string(moneyToAdd), color(100,255,100));
		textResult += coloredString(" to player's account");
		appendTextToConsole(textResult);

	}
}

void devConsole :: crewToBarracks()
{
	if (!isIngame())
	{
		throwError("not in game");
		return void();
	}
	else
	{
		bool success = playerCampaignInfo->playerEquippedSubmarine()->moveEveryoneToBarracks(playerCampaignInfo->barracks());
		if (success)
		{
			coloredString msg("All crew moved to ");
			msg += coloredString("barracks", color(255,255,0));
			appendTextToConsole(msg);
		}
		else
		{
			coloredString msg("Not all ", color (255,100,100));
			msg += coloredString("crew moved to ");
			msg += coloredString("barracks", color(255,255,0));
			appendTextToConsole(msg);
		}
	}
}

void devConsole :: barracksToSubmarine()
{
	if (!isIngame())
	{
		throwError("not in game");
		return void();
	}
	else
	{
		playerCampaignInfo->barracksToSubmarine();
		appendTextToConsole("done");
	}
}

void devConsole :: changeSubmarine(string parameters)
{
	if (parameters.size() == 0)
	{
		throwError("no parameters");
		return void();
	}
	if (!isIngame())
	{
		throwError("not in game");
		return void();
	}
	int subIndex = stoi(parameters);
	if (playerCampaignInfo->ownedSubmarines() < subIndex)
	{
		throwError("invalid submarine index");
		return void();
	}
	else
	{
		//before changing submarine, transfer all crew to barracks
		playerCampaignInfo->playerEquippedSubmarine()->moveEveryoneToBarracks(playerCampaignInfo->barracks());

		//set the submarine index as the player's "equipped" submarine
		playerCampaignInfo->getInSubmarine(subIndex);

		//transfer neccesary crew from barracks to new submarine
		playerCampaignInfo->barracksToSubmarine();

		coloredString msg("changed to ");
		msg += coloredString(playerCampaignInfo->playerEquippedSubmarine()->shipName(), color(200,150,255));
		msg += coloredString(", a ");
		msg += coloredString(playerCampaignInfo->playerEquippedSubmarine()->name(), color(100,255,100));
		msg += coloredString(" class submarine", color(255,255,100));
		appendTextToConsole(msg);
	}
}

void devConsole :: randomTorpedoCommand()
{
	if (!isIngame())
	{
		throwError("not in game");
		return void();
	}
	else
	{
		torpedo *torpedoPointer = randomTorpedo();
		bool result = playerCampaignInfo->addTorpedoToSubmarine(torpedoPointer);
		if (result)
		{	
			coloredString msg("added a ");
			msg += coloredString(torpedoPointer->name(), color(100,255,100));
			msg += coloredString(" to the player's current submarine");
			appendTextToConsole(msg);
		}
		else
		{
			throwError("the selected submarine is already full of torpedos");
		}
	}
}

void devConsole :: fillTorpedosCommand()
{
	if (!isIngame())
	{
		throwError("not in game");
		return void();
	}
	else
	{
		int numTorpedos = 0;
		while (playerCampaignInfo->addTorpedoToSubmarine(randomTorpedo()))
		{
			numTorpedos++;
		}
		coloredString msg = "Fill selected submarine with ";
		msg += coloredString(to_string(numTorpedos), color(255,255,100));
		msg += coloredString(" torpedos");
		appendTextToConsole(msg);
	}
}

bool devConsole :: parseInput(string input)
{
	if (input.substr(0, 6) == "print ")
	{
		printString(input.substr(6, input.size()));
		return true;
	}
	else if(input.substr(0, 18) == "givequalification ")
	{
		giveQualifications(input.substr(18, input.size()));
		return true;
	}
	else if (input.substr(0, 18) == "addqualifications ")
	{
		addQualifications(input.substr(18, input.size()));
		return true;
	}
	else if (input.substr(0, 3) == "420")
	{
		appendTextToConsole("420? lol nice");
		return true;
	}
	else if (input.substr(0, 2) == "69")
	{
		appendTextToConsole("69? lol nice");
		return true;
	}
	else if (input.substr(0,9) == "addawards")
	{
		addAwards(input.substr(9, input.size()));
		return true;
	}
	else if (input.substr(0,9) == "addmoney ")
	{
		addMoney(input.substr(9, input.size()));
		return true;
	}
	else if (input.substr(0,14) == "crewtobarracks")
	{
		crewToBarracks();
		return true;
	}
	else if (input.substr(0,19) == "barrackstosubmarine")
	{
		barracksToSubmarine();
		return true;
	}
	else if (input.substr(0,15) == "changesubmarine")
	{
		changeSubmarine(input.substr(15, input.size()));
		return true;
	}
	else if (input.substr(0,13) == "randomtorpedo")
	{
		randomTorpedoCommand();
		return true;
	}
	else if (input.substr(0,12) == "filltorpedos")
	{
		fillTorpedosCommand();
		return true;
	}
	//appendTextToConsole(input);
	return false;
}

/*void devConsole :: appendTextToConsole(string text)
{
	coloredString convertedString = text;
	m_consoleOutput.push_front(convertedString);
	if (m_consoleOutput.size() > m_numLines)
	{
		m_consoleOutput.pop_back();
	}
}*/

void devConsole :: appendTextToConsole(coloredString text)
{
	//coloredString convertedString = text;
	m_consoleOutput.push_front(text);
	if (m_consoleOutput.size() > m_numLines)
	{
		m_consoleOutput.pop_back();
	}
}

void devConsole :: throwError(string reason)
{
	coloredString errormsg("Error: ", color(255,20,20));
	errormsg += coloredString(reason, color(255,255,100));
	appendTextToConsole(errormsg);
}