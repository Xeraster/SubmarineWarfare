//the save system in this game is mostly based off of how Rimworld manages saving. The only real difference is that the save and load functions are 2 different functions whereas in Rimworld, exposedata handles both

//return 0 = success. 1 = failure
int saveToXml(string saveName, playerInfo *player)
{
	//xml testing shit
	XMLDocument doc;
	XMLElement *relement = doc.NewElement("savefile");
	XMLElement *onpatrolnode = relement->InsertNewChildElement("onPatrol");
	onpatrolnode->SetText("false");
	relement->InsertEndChild(onpatrolnode);

	XMLElement *playerInfoNode = relement->InsertNewChildElement("playerInfo");
	//now, let the playerinfo class inject its data
	player->playerInfoToSaveXml(playerInfoNode);
	relement->InsertEndChild(playerInfoNode);

	doc.InsertEndChild(relement);
	string savepath = "Saves/" + saveName + ".xml";
	doc.SaveFile(savepath.c_str());

	return 0;
}

//return 0 = success. 1 = failed
int loadFromXml(string saveName, playerInfo *player, SDL_Renderer *ren)
{

	//cout << "before loading test.xml" << endl;
	//xml testing shit
	XMLDocument doc;
	doc.LoadFile(saveName.c_str());

	if (doc.RootElement() == nullptr)
	{
		cout << "warning: a save file with no root element was loaded" << endl;
		return 1;
	}

	XMLElement *rootElement = doc.RootElement();
	cout << rootElement->FirstChildElement("onPatrol")->GetText() << endl;
	if (stringToBool(rootElement->FirstChildElement("onPatrol")->GetText()))
	{
		cout << "save file is on patrol but this feature isn't implemented yet" << endl;
		return 1;
	}

	//set up a pointer to the playerInfo element

	XMLElement *playerinfoElement = rootElement->FirstChildElement("playerInfo");
	string newCampaignName = playerinfoElement->FirstChildElement("startingCampaign")->GetText();
	string playerName = playerinfoElement->FirstChildElement("playerName")->GetText();

	//you have to initialize the playerInfo object to at least the bare minimum levels of initialization before it can be used and the rest of the data can be loaded
	playerCampaignInfo = new playerInfo(&campaignDatabase->at(getCampaignIndexByName(newCampaignName)), playerName, "temp", ren);
	playerCampaignInfo->playerInfoFromXml(playerinfoElement, ren);

	//cout << "after loading test.xml (the stuff line above should be the contents of the file" << endl;
	//rootElement->SetText("true");
	//doc.SaveFile("test.xml");

	return 0;
}