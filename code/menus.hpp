void loadMenuTextures(SDL_Renderer *ren, int menuQuality)
{
	//Enable text input
    SDL_StartTextInput();
    SDL_Rect thisRect;
	thisRect.x = 0;
	thisRect.y = 0;
	thisRect.w = 800;
	thisRect.h = 600;
	SDL_SetTextInputRect(&thisRect);

	double aspectRatio = static_cast<double>(gscreenx) / static_cast<double>(gscreeny);

	string mainBackgroundPath = "Textures/Menus/Backgrounds/Main_small.png";
	string newCampaignBackgroundPath = "Textures/Menus/Backgrounds/newcampaign_small.png";
	string CampaignBaseBackgroundPath = "Textures/Menus/Backgrounds/Campain_base.png";
	string RecruitmentBackgroundPath = "Textures/Menus/Backgrounds/recruitment_lowres.png";
	string stuffPurchaseBackgroundPath = "Textures/Menus/Backgrounds/jbaymazon_43.png";

	//settings background is just going to be the same for all screen sizes
	string SettingsBackgroundPath = "Textures/Menus/Backgrounds/crt_monitor_front_close.png";

	string titlepicBackgroundPath = "Textures/Menus/Misc/titlepic.png";

	//determine what graphics setting the menu is in. IMG_Load is slower than SDL_LoadBMP but it can load files other than uncompressed bitmap
	if (menuQuality == 0) 
	{
		mainBackgroundPath = "Textures/Menus/Backgrounds/Main_small.png";
		newCampaignBackgroundPath = "Textures/Menus/Backgrounds/newcampaign_small.png";
		CampaignBaseBackgroundPath = "Textures/Menus/Backgrounds/Campain_base_lowres.png";
		RecruitmentBackgroundPath = "Textures/Menus/Backgrounds/recruitment_lowres.png";
	}
	else if (menuQuality == 1) 
	{
		mainBackgroundPath = "Textures/Menus/Backgrounds/Main_medium.png";
		newCampaignBackgroundPath = "Textures/Menus/Backgrounds/newcampaign_full.png";
		CampaignBaseBackgroundPath = "Textures/Menus/Backgrounds/Campain_base.png";
		RecruitmentBackgroundPath = "Textures/Menus/Backgrounds/recruitment_full.png";
	}

	//fuck your menu quality slider. If you're running at a high resolution, you get the high res textures
	//if aspect ratio is a little wider than 4:3 (1.33333) and user is running at a horizontal resolution of equal to or greater than 1024 (for example 1024x600 would be included in this)
	if (aspectRatio > 1.4 && gscreenx >= 1024)
	{
		mainBackgroundPath = "Textures/Menus/Backgrounds/Main_widescreen.png";
		newCampaignBackgroundPath = "Textures/Menus/Backgrounds/newcampaign_full.png";
		CampaignBaseBackgroundPath = "Textures/Menus/Backgrounds/Campain_base.png";
		RecruitmentBackgroundPath = "Textures/Menus/Backgrounds/recruitment_full.png";
	}

	//if aspect ratio is greater than 4:3 regardless of what the actual resolution magnitude is
	else if (aspectRatio > 1.4)
	{
		stuffPurchaseBackgroundPath = "Textures/Menus/Backgrounds/jbaymazon_wide.png";
	}

	cout << "background path = " << mainBackgroundPath << endl;
	//load the texture into ram
	//SDL_Surface *bmp = SDL_LoadBMP(mainBackgroundPath.c_str());
	SDL_Surface *bmp = IMG_Load(mainBackgroundPath.c_str());

	background = SDL_CreateTextureFromSurface(ren, bmp);
	SDL_FreeSurface(bmp);

	//load the background for starting a new campaign
	SDL_Surface *bmp2 = IMG_Load(newCampaignBackgroundPath.c_str());
	newCampaignBackground = SDL_CreateTextureFromSurface(ren, bmp2);
	SDL_FreeSurface(bmp2);

	bmp2 = IMG_Load(CampaignBaseBackgroundPath.c_str());
	campaignInPortMain = SDL_CreateTextureFromSurface(ren, bmp2);
	SDL_FreeSurface(bmp2);

	bmp2 = IMG_Load(RecruitmentBackgroundPath.c_str());
	recruitmentBackground = SDL_CreateTextureFromSurface(ren, bmp2);
	SDL_FreeSurface(bmp2);

	//load settings background png
	bmp2 = IMG_Load(SettingsBackgroundPath.c_str());
	settingsBackground = SDL_CreateTextureFromSurface(ren, bmp2);
	SDL_FreeSurface(bmp2);

	//load purchase screen background
	bmp2 = IMG_Load(stuffPurchaseBackgroundPath.c_str());
	purchaseScreenBackground = SDL_CreateTextureFromSurface(ren, bmp2);
	SDL_FreeSurface(bmp2);

	//load title logo (titlepic.png)
	bmp2 = IMG_Load(titlepicBackgroundPath.c_str());
	titlepic = SDL_CreateTextureFromSurface(ren, bmp2);
	SDL_FreeSurface(bmp2);
	//calculate size of position of titlepic now during asset loading instead of doing it on every frame later
	int texSizeX;
	int texSizeY;
	SDL_QueryTexture(titlepic, NULL, NULL, &texSizeX, &texSizeY);
	titlepicSizeX = gscreenx / 2.5;
	titlepicSizeY = texSizeY * (static_cast<double>(titlepicSizeX) / static_cast<double>(texSizeX));
	titlepicPosX = (gscreenx - titlepicSizeX) / 2;
	titlepicPosY = 10 * gscreeny / 600;

	textSizeHeader = 12 * (static_cast<double>(gscreenx) / static_cast<double>(800));
	textSizeMedium = 10 * (static_cast<double>(gscreenx) / static_cast<double>(800));
	textSizeNormal = 8 * (static_cast<double>(gscreenx) / static_cast<double>(800));
	textSizeSeven = 7 * (static_cast<double>(gscreenx) / static_cast<double>(800));
	textSizeSmall = 6 * (static_cast<double>(gscreenx) / static_cast<double>(800));

	color white(255,255,255,255);
	button tempButton("new game", white, 30, 200, 16);
	newGameButton = tempButton;
	tempButton.setLabel("load game");
	tempButton.setPos(30, 255);
	loadGameButton = tempButton;

	singleMission = tempButton;
	singleMission.setLabel("single Mission");
	singleMission.setPos(30, 310);

	multiplayer = tempButton;
	multiplayer.setLabel("multiplayer");
	multiplayer.setPos(30, 365);

	missionEditor = tempButton;
	missionEditor.setLabel("mission editor");
	missionEditor.setPos(30, 420);

	settings = tempButton;
	settings.setLabel("settings");
	settings.setPos(30, 475);

	quitGame = tempButton;
	quitGame.setLabel("quit");
	quitGame.setPos(30, 530);

	enable3D = false;

	button newTempButtom("back", white, 30, 0, 16);
	newTempButtom.setPos(30, gscreeny - newTempButtom.sizeY() - 50);
	color darkBlack(0,0,0,150);
	newCampaignBackButton = newTempButtom;
	newCampaignBackButton.setBackgroundColor(darkBlack);
	newCampaignBackButton.setArrow(3);
	newCampaignBackButton.setBorder(true);

	textbox tempbox("New Player", white, gscreenx * 0.333, 80, textSizeMedium, 30);
	newPlayerNameTextbox = tempbox;
	startNewCampaign = newTempButtom;
	startNewCampaign.setLabel("Start");
	startNewCampaign.setBackgroundColor(darkBlack);
	startNewCampaign.setArrow(1);
	startNewCampaign.setBorder(true);
	startNewCampaign.setPos(gscreenx - startNewCampaign.sizeX() - 50, gscreeny - startNewCampaign.sizeY() - 50);

	//position of randomize player name button is directly to under and a little to the right of player name textbox
	button randomize("randomize player name", white, 200, 120, textSizeNormal);
	randomize.setPos((gscreenx * 0.333) + newPlayerNameTextbox.derivedSizeX() - randomize.derivedSizeX(), 80 + newPlayerNameTextbox.derivedSizeY());
	randomizePlayerName = randomize;


	returnToMainMenu = newTempButtom;
	returnToMainMenu.setLabel("Back");
	returnToMainMenu.setArrow(3);
	returnToMainMenu.setBorder(true);
	returnToMainMenu.setBackgroundColor(darkBlack);
	returnToMainMenu.setPos(30, gscreeny - returnToMainMenu.sizeY() - 50);

	//the input boxes start 1.3rd of the way across the screen in the x direction
	shipNameTextbox = tempbox;
	shipNameTextbox.setPos(gscreenx * 0.333, newPlayerNameTextbox.posY() + (randomizePlayerName.sizeY()*2) + newPlayerNameTextbox.sizeY());
	shipNameTextbox.replaceText(crewNameGeneratorObject->randomShipName());
	purchaseScreenNewName = shipNameTextbox;
	randomizeShipNameButton = randomize;
	randomizeShipNameButton.setPos(shipNameTextbox.posX() + shipNameTextbox.derivedSizeX() - randomizeShipNameButton.derivedSizeX(), shipNameTextbox.posY() + shipNameTextbox.derivedSizeY());

	//campaignSelectionX
	campaignSelectionX = gscreenx * 0.25;
	campaignSelectionY = randomizeShipNameButton.posY() + (randomizeShipNameButton.sizeY() * 2);

	//most games don't go this far in the way of automatic scaling
	//I'm too lazy to program it to display more info on larger screen sizes that could handle it so I'll just keep making everything automatically scale
	//some developers are too lazy to even add gui scaling capability at all
	button genericArrow("", white, campaignSelectionX, campaignSelectionY, 10 * gscreeny / 600);
	campaignRightArrow = genericArrow;
	campaignLeftArrow = genericArrow;
	campaignLeftArrow.setArrow(3);
	campaignRightArrow.setArrow(1);
	campaignRightArrow.setPos(campaignSelectionX + (320 * gscreenx / 800), campaignSelectionY);

	scrollLeftArrow = campaignLeftArrow;
	scrollRightArrow = campaignRightArrow;

	//the circle button for clicking on the crew recruitment file cabinet
	color invisible(0,0,0,0);
	color transparentYellow(255,255,0,50);
	button circleButton("    ", white, 25 * gscreenx / 800, 50 * gscreeny / 600, 24);
	circleButton.setCircle(true);
	circleButton.setHighlightRadious(80);
	circleButton.setHighlightColor(transparentYellow);
	circleButton.setTooltip("recruitment");
	purchaseScreen = circleButton;
	purchaseScreen.setPos(425 * gscreenx / 800, 392 * gscreeny / 600);
	purchaseScreen.setTooltip("store");

	startMission = circleButton;
	startMission.setTooltip("begin mission");
	startMission.setPos(403 * gscreenx / 1024, 115 * gscreeny / 768);
	if (aspectRatio > 1.4 && gscreenx >= 1024)
	{
		purchaseScreen.setPos(587 * gscreenx / 1366, 498 * gscreeny / 768);
		startMission.setPos(591 * gscreenx / 1920, 146 * gscreeny / 1080);
	}

	//recruitment screen stuff
	recruitUpScroll = genericArrow;
	recruitDownScroll = genericArrow;
	recruitUpScroll.setArrow(0);
	recruitDownScroll.setArrow(2);


	crewHiring = circleButton;

	int vertTextSeven = 7 * (static_cast<double>(gscreeny) / static_cast<double>(600));
	button temp3("recruitment", white, 10, (400 * gscreeny / 600) + (getTextYSize(vertTextSeven)*0), vertTextSeven);
	temp3.setBorder(true);
	temp3.setBackgroundColor(darkBlack);
	hiringTab = temp3;
	temp3.setPos(10, (400 * gscreeny / 600) + (getTextYSize(vertTextSeven)*2));
	temp3.setLabel("awards");
	awardsTab = temp3;
	barracksTab = temp3;
	barracksTab.setLabel("barracks");
	barracksTab.setPos(10, (400 * gscreeny / 600) + (getTextYSize(vertTextSeven)*1));

	//settings screen stuff

	//I will buy anyone who figures out a less annoying way to set up new button, textbox and progress bar objects an entire keg of beer of their choice
	color linuxGreen(24,240,24);
	color linuxGreenButDarker(14, 64, 14);
	textbox settingsTempBox("gui init error", linuxGreen, 0, 0, textSizeNormal, 4);
	settingsTempBox.setBackgroundColor(linuxGreenButDarker);

	sizeXEntry = settingsTempBox;
	sizeYEntry = settingsTempBox;

	sizeXEntry.setPos(gscreenx*static_cast<double>(0.15), (gscreeny * static_cast<double>(0.10)) + (getTextYSize(textSizeHeader)*2) + (getTextYSize(textSizeNormal)*1));
	sizeYEntry.setPos(gscreenx*static_cast<double>(0.15), (gscreeny * static_cast<double>(0.10)) + (getTextYSize(textSizeHeader)*2) + (getTextYSize(textSizeNormal)*2));
	sizeXEntry.replaceText(to_string(gscreenx));
	sizeYEntry.replaceText(to_string(gscreeny));

	//startXR = returnToMainMenu.posX() + returnToMainMenu.sizeX() + 20;
	startXR = 160 * gscreeny / 600;
	awardsTextSize *= (static_cast<double>(gscreeny) / static_cast<double>(600));

	//set up the buttons and gui shit for the jbaymazon purchase screen
	button shittySideStoreButton("submarines", white, 10, (160 * gscreeny / 1080), textSizeNormal);

	submarineCategory = shittySideStoreButton;
	torpedoCategory = shittySideStoreButton;
	torpedoCategory.setPos(10, (160 * gscreeny / 1080) + getTextYSize(textSizeNormal));
	torpedoCategory.setLabel("torpedos");
	upgradesCategory = shittySideStoreButton;
	upgradesCategory.setLabel("upgrades");
	upgradesCategory.setPos(10, (160 * gscreeny / 1080) + (2*getTextYSize(textSizeNormal)));
	junkCategory = shittySideStoreButton;
	junkCategory.setLabel("stuff / misc junk");
	junkCategory.setPos(10, (160 * gscreeny / 1080) + (3*getTextYSize(textSizeNormal)));

	button tempPurchaseWhatever("confirm", white, 0, 0, textSizeSeven);
	tempPurchaseWhatever.setBorder(true);
	tempPurchaseWhatever.setBackgroundColor(darkBlack);
	//randomizeName;
	confirm = tempPurchaseWhatever;
	cancel = tempPurchaseWhatever;
	cancel.setLabel("cancel");
	//textbox purchaseScreenNewName;

	//purchase screen randomize ship name button
	randomizeName = cancel;
	randomizeName.setLabel("randomize");

	int partTabStartX = (gscreenx * 0.226613);
	int partTabStartY = (gscreeny * 0.14319);
	//upgrade part purchase screen tab shit
	//button uptabtemp(string label, color textColor, int posX, int posY, int fontSize)
	batteryTab = button("battery", color(255,255,255), 0, 0, textSizeNormal);
	upgradeTabs.push_back(&batteryTab);
	dieselTab = button("diesel", color(255,255,255), 0, 0, textSizeNormal);
	upgradeTabs.push_back(&dieselTab);
	electricTab = button("electric", color(255,255,255), 0, 0, textSizeNormal);
	upgradeTabs.push_back(&electricTab);
	nuclearTab = button("nuclear", color(255,255,255), 0, 0, textSizeNormal);
	upgradeTabs.push_back(&nuclearTab);
	fuelTab = button("fuel", color(255,255,255), 0, 0, textSizeNormal);
	upgradeTabs.push_back(&fuelTab);
	oxygenTab = button("oxygen generator", color(255,255,255), 0, 0, textSizeNormal);
	upgradeTabs.push_back(&oxygenTab);
	radarTab = button("radar", color(255,255,255), 0, 0, textSizeNormal);
	upgradeTabs.push_back(&radarTab);
	lidarTab = button("lidar", color(255,255,255), 0, 0, textSizeNormal);
	upgradeTabs.push_back(&lidarTab);
	sonarTab = button("sonar", color(255,255,255), 0, 0, textSizeNormal);
	upgradeTabs.push_back(&sonarTab);
	hydrophoneTab = button("hydrophone", color(255,255,255), 0, 0, textSizeNormal);
	upgradeTabs.push_back(&hydrophoneTab);
	deckgunTab = button("guns", color(255,255,255), 0, 0, textSizeNormal);
	upgradeTabs.push_back(&deckgunTab);
	hullTab = button("hull", color(255,255,255), 0, 0, textSizeNormal);
	upgradeTabs.push_back(&hullTab);
	stealthTab = button("stealth", color(255,255,255), 0, 0, textSizeNormal);
	upgradeTabs.push_back(&stealthTab);
	miscTab = button("misc", color(255,255,255), 0, 0, textSizeNormal);
	upgradeTabs.push_back(&miscTab);

	int v = 0;
	int y = 0;
	for (int i = 0; i < upgradeTabs.size(); i++)
	{
		if (i == 0)
		{
			upgradeTabs.at(i)->setPos(partTabStartX, partTabStartY);
		}
		else
		{
			if (upgradeTabs.at(i-1)->sizeX() + upgradeTabs.at(i-1)->posX() > gscreenx * 0.8)
			{
				y++;
				v = 0;
				upgradeTabs.at(i)->setPos(partTabStartX, partTabStartY + (y * getTextYSize(textSizeNormal)));
			}
			else
			{
				upgradeTabs.at(i)->setPos(upgradeTabs.at(i-1)->sizeX() + upgradeTabs.at(i-1)->posX() + 20, partTabStartY + (y * getTextYSize(textSizeNormal)));
			}
		}
		v++;
	}

	//all the in game menu ui stuff here
	

	loadIngameSpecificTextures(ren);


	//load misc stuff like button icons
	loadGuiGizmos(ren);

}

void drawMainMenu(SDL_Renderer *ren, int screenSizeX, int screenSizeY, SDL_Window *win)
{	
	color menuBackgroundColor(0,0,0,100);
	color white(255,255,255,255);
	color black(0,0,0,255);
	int mouseX, mouseY;
	Uint32 lastMouse = SDL_GetMouseState(&mouseX, &mouseY);
	if (newCampaignScreen)
	{
		//this screen is shown when the player is about to start a new campaign
		showMainMenu = false;
		renderTextureEx(newCampaignBackground, ren, 0, 0, gscreenx, gscreeny, 0);
		drawText(ren, textSizeNormal, black, "Name:", newPlayerNameTextbox.posX(), newPlayerNameTextbox.posY() - newPlayerNameTextbox.derivedSizeY());
		//drawRectFilled(ren, menuBackgroundColor, 200, 120, 300, 24);

		//let player input a name for themselves or whatever
		playerName = newPlayerNameTextbox.draw(ren, mouseX, mouseY, lastMouse);
		showMainMenu = newCampaignBackButton.draw(ren, mouseX, mouseY, lastMouse);

		//let player input the ship's name
		drawText(ren, textSizeNormal, black, "Ship name:", shipNameTextbox.posX(), shipNameTextbox.posY() - shipNameTextbox.derivedSizeY());
		shipName = shipNameTextbox.draw(ren, mouseX, mouseY, lastMouse);

		if (startNewCampaign.draw(ren, mouseX, mouseY, lastMouse))
		{
			showMainMenu = false;
			newCampaignScreen = false;
			campaignBaseScreen = true;
			startCampaign(ren);
		}
		bool putRandomName = randomizePlayerName.draw(ren, mouseX, mouseY, lastMouse);
		if (putRandomName) newPlayerNameTextbox.replaceText((crewNameGeneratorObject->randomName(1)) + " " + (crewNameGeneratorObject->randomLastName()));

		bool putRandomShipName = randomizeShipNameButton.draw(ren, mouseX, mouseY, lastMouse);
		if (putRandomShipName) shipNameTextbox.replaceText(crewNameGeneratorObject->randomShipName());

		//campaign selection box
		drawText(ren, textSizeNormal, black, "campaign selection", campaignSelectionX + 10, campaignSelectionY - getTextYSize(textSizeNormal));
		bool campaignRight = campaignRightArrow.draw(ren, mouseX, mouseY, lastMouse);
		bool campaignLeft = campaignLeftArrow.draw(ren, mouseX, mouseY, lastMouse);
		drawRectFilled(ren, menuBackgroundColor, campaignSelectionX + 10, campaignSelectionY, 300 * gscreenx / 800, getTextYSize(textSizeNormal));
		drawText(ren, textSizeNormal, white, campaignDatabase->at(campaignSelectionIndex).getName(), campaignSelectionX + 10, campaignSelectionY);
		if (campaignRight && clickButtonCooldown == 0)
		{
			campaignSelectionGoRight();
		}
		if (campaignLeft && clickButtonCooldown == 0)
		{
			campaignSelectionGoLeft();
		}
		//draw more information about the selected campaign scenario
		campaignDatabase->at(campaignSelectionIndex).drawInfoCard(ren, 150 * gscreenx / 800, campaignSelectionY + getTextYSize(textSizeNormal) + (20*gscreenx/800));
	}
	else if (showSettings)
	{
		//showMainMenu = returnToMainMenu.draw(ren, mouseX, mouseY, lastMouse);
		drawSettingsScreen(ren, screenSizeX, screenSizeY, mouseX, mouseY, lastMouse);
	}
	//multiplayer screen
	else if (multiplayerMenu)
	{
		showMainMenu = false;

		//recycle the new campaign back button to go back to main menu. It's the same anyway.
		showMainMenu = newCampaignBackButton.draw(ren, mouseX, mouseY, lastMouse);
		multiplayerMenu = !showMainMenu;

	}
	//the screen you get when clicking the "load game" button on the main menu
	else if (loadGameScreen)
	{
		showMainMenu = false;
		showMainMenu = newCampaignBackButton.draw(ren, mouseX, mouseY, lastMouse);
		drawLoadGameStuff(ren, mouseX, mouseY, lastMouse);
	}

	else if (campaignBaseScreen)
	{
		if (!recruitmentScreen && !showPurchaseScreen && !preliminaryMissionStartScreen)
		{
			//this is the screen that displays when the user is in campaign mode and is at port (and not in a mission)
			renderTextureEx(campaignInPortMain, ren, 0, 0, gscreenx, gscreeny, 0);
			if (returnToMainMenu.draw(ren, mouseX, mouseY, lastMouse))
			{
				delete playerCampaignInfo;
				campaignBaseScreen = false;
				newCampaignScreen = false;
				showMainMenu = true;
			}

			//button that toggles the recruitment screen
			recruitmentScreen = crewHiring.draw(ren,mouseX,mouseY,lastMouse);
			if (recruitmentScreen)
			{
				prepareRecruitmentScreen(ren);
			}

			if (purchaseScreen.draw(ren, mouseX, mouseY, lastMouse))
			{
				selectedPurchasableSubmarine = nullptr;
				showPurchaseScreen = true;
			}

			if (startMission.draw(ren, mouseX, mouseY, lastMouse))
			{
				preliminaryMissionStartScreen = true;
			}
		}
		else if (showPurchaseScreen)
		{
			drawPurchaseScreen(ren, mouseX, mouseY, lastMouse);
		}
		else if (recruitmentScreen)
		{
			drawRecruitmentScreen(ren, gscreenx, gscreeny, mouseX, mouseY, lastMouse);
			//you can reuse the same buttons for different functions
			if (returnToMainMenu.draw(ren, mouseX, mouseY, lastMouse))
			{
				recruitmentScreen = false;
			}
		}
		else if (preliminaryMissionStartScreen)
		{
			if (returnToMainMenu.draw(ren, mouseX, mouseY, lastMouse))
			{
				preliminaryMissionStartScreen = false;
				enable3D = false;
				campaignBaseScreen = true;
			}

			//im recycling the start new campaign start button because it's already the correct size and in the correct screen scaled position
			if (startNewCampaign.draw(ren, mouseX, mouseY, lastMouse))
			{
				theWorld = worldInfo(playerCampaignInfo, "heightmap4096", ren, win);
				//preliminaryMissionStartScreen = false;
				enable3D = true;
				ingameMenus = true;
				campaignBaseScreen = false;

				theWorld.generateNearTerrain(0, 0, 20);
				theWorld.generateNearOcean(0, 0, 1);

				//spawn a ship jhust for kix
				theWorld.spawnShip("AFS1", 50, 10, 90);
			}

			drawPeliminaryMissionStartScreen(ren, mouseX, mouseY, lastMouse);
		}
	}

	else if (ingameMenus)
	{
		beIngame(ren, mouseX, mouseY, lastMouse);
	}

	if (showMainMenu)
	{
		//this screen is shown when the player has initially started the game and the loading screen finishes
		newCampaignScreen = false;
		showSettings = false;
		loadGameScreen = false;
		loadedSaves = false;
		//renderTextureEx doesn't cause THAT bad of a performance hit..
		renderTextureEx(background, ren, 0, 0, gscreenx, gscreeny, 0);

		//draw title logo
		renderTextureEx(titlepic, ren, titlepicPosX, titlepicPosY, titlepicSizeX, titlepicSizeY, 0);
		//cout << "titleposX= " << titlepicPosX << ", titleposy= " << titlepicPosY << ", titlesizex= " << titlepicSizeX << ", titlesizey= " << titlepicSizeY << endl;
		//renderTextureEx(titlepic, ren, 0, 0, 500, 300, 0);

		drawRectFilled(ren, menuBackgroundColor, 20, 200, 300, 375);
		newGameButton.draw(ren, mouseX, mouseY, lastMouse, newCampaignScreen);
		loadGameButton.draw(ren, mouseX, mouseY, lastMouse, loadGameScreen);
		singleMission.draw(ren, mouseX, mouseY, lastMouse);
		multiplayer.draw(ren, mouseX, mouseY, lastMouse, multiplayerMenu);
		missionEditor.draw(ren, mouseX, mouseY, lastMouse);
		showSettings = settings.draw(ren, mouseX, mouseY, lastMouse);
		quitGame.draw(ren, mouseX, mouseY, lastMouse);

	}

}

void campaignSelectionGoRight()
{
	if (campaignDatabase->size() > campaignSelectionIndex + 1)
	{
		campaignSelectionIndex++;
	}
	else
	{
		campaignSelectionIndex = 0;
	}
}

void campaignSelectionGoLeft()
{
	if (campaignSelectionIndex > 0)
	{
		campaignSelectionIndex--;
	}
	else
	{
		campaignSelectionIndex = campaignDatabase->size() - 1;
	}
}

void drawRecruitmentScreen(SDL_Renderer *ren, int screenSizeX, int screenSizeY, int mouseX, int mouseY, Uint32 lastMouse)
{
	menuDecrementQualification = false;
	int numCrewToShow = 3;
	//crewMember *selectedCrew = nullptr;
	crewMember *selectedCrew = playerCampaignInfo->getInfoCardCrewPointer();
	bool buttonClicked = false;
	lowestY = 0;
	renderTextureEx(recruitmentBackground, ren, 0, 0, gscreenx, gscreeny, 0);
	playerCampaignInfo->playerEquippedSubmarine()->drawInfoScreen(ren, screenSizeX, screenSizeY, mouseX, mouseY, lastMouse, &lowestY, &selectedCrew);

	//the part for the barracks crew box
	if (hiringTabMode == 2)
	{
		playerCampaignInfo->drawPlayerBarrack(ren, startXR, lowestY + 20, (screenSizeX/2) - startXR, mouseX, mouseY, lastMouse, &selectedCrew);
	}

	if (selectedCrew != nullptr) 
	{
		//cout << playerCampaignInfo->getInfoCardCrewPointer()->getFirstName() << endl;
		playerCampaignInfo->setInfoCardCrewPointer(selectedCrew);
		//the code that handles the mouse dragging around the icon of a selected crew member
		if (playerCampaignInfo->getInfoCardCrewPointer()->isSelected())
		{
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
			playerCampaignInfo->getInfoCardCrewPointer()->drawIcon(ren, mouseX, mouseY, crewSizeX, crewSizeY, mouseX, mouseY, lastMouse, nullptr, true);
			stillSelected = true;
			//cout << "is selected" << endl;
		}
		//if player was dragging crew icon in previous frame but isn't anymore
		if (stillSelected && playerCampaignInfo->getInfoCardCrewPointer()->isSelected() == false)
		{
			//set the bool to false so this will only execute this tick
			stillSelected = false;
			if (!playerCampaignInfo->isInsideBarracksBox(mouseX, mouseY) || hiringTabMode != 2)
			{
				crewMember *pointerToPass = nullptr;
				int barrackSlotNum = 0;
				playerCampaignInfo->playerEquippedSubmarine()->putCrewInCompartment(playerCampaignInfo->getInfoCardCrewPointer(), mouseX, mouseY, screenSizeX, &pointerToPass, &barrackSlotNum);
				
				//I have to use this ugly ass abomination since c++ doesn't have the class forward declaration capabilities of c#
				//(it can forward declare classes but not use their member functions until after declaration WHICH IS WHAT I NEED TO MAKE THIS SECTION OF CODE NOT SUCK)
				//I feel sorry for anyone who ever attempts to look at the crew management gui code for this (sorry bro I did the best I could.)

				//anyway this is the part that deals with erasing duplicate crew points in barracks after being copied from barracks to submarine
				//I just mindlessly changed this 04/30/21 14:40 and it fixed a bug, so maybe check this first next time a new bug comes up
				if (pointerToPass == nullptr)
				{
					//playerCampaignInfo->findAndEraseDuplicateCrew(playerCampaignInfo->getInfoCardCrewPointer(), barrackSlotNum);
					playerCampaignInfo->findAndEraseDuplicateCrew(playerCampaignInfo->getInfoCardCrewPointer(), -1);
				}
				else
				{
					//playerCampaignInfo->findAndReplaceDuplicateCrew(playerCampaignInfo->getInfoCardCrewPointer(), barrackSlotNum, pointerToPass);
					playerCampaignInfo->findAndReplaceDuplicateCrew(playerCampaignInfo->getInfoCardCrewPointer(), -1, pointerToPass);
				}

			} 
			else
			{
				playerCampaignInfo->putCrewInBarrack(playerCampaignInfo->getInfoCardCrewPointer(), mouseX, mouseY, (screenSizeX/2) - startXR);
			}
		}
		//cout << "still selected = " << stillSelected << endl;
	}

	//draw the crew infocard
	if (playerCampaignInfo->getInfoCardCrewPointer() != nullptr)
	{
		//cout << playerCampaignInfo->getInfoCardCrewPointer()->getLastName() << endl;
		playerCampaignInfo->getInfoCardCrewPointer()->drawInfoCard(ren, (screenSizeX / 2) + 50, lowestY + 10, (screenSizeX / 2) - 80, screenSizeY - lowestY - 30, mouseX, mouseY, lastMouse);
	}
	//playerCampaignInfo->getEmployableCrew(crewIndex + 1).drawRecruitmentInfoCard(ren, 150, lowestY + 70, 250, 50, mouseX, mouseY, lastMouse, &buttonClicked);
	//playerCampaignInfo->getEmployableCrew(crewIndex + 2).drawRecruitmentInfoCard(ren, 150, lowestY + 140, 250, 50, mouseX, mouseY, lastMouse, &buttonClicked);

	//decrement the player's qualification allowance if one got used in the last frame
	if (menuDecrementQualification)
	{
		menuDecrementQualification = false;
		playerCampaignInfo->decrementQualifications();
		//be sure to recalculate the manpower in the entire submarine since it can't be updated from within the crew class
		playerCampaignInfo->playerEquippedSubmarine()->recalculateManpower();
	}

	if (menuDecrementAward)
	{
		menuDecrementAward = false;
		playerCampaignInfo->decrementAward(selectedAward);
	}

	//the tab buttons that let you choose between the hiring crew view and the handing out awards view
	if (hiringTab.draw(ren, mouseX, mouseY, lastMouse))
	{
		hiringTabMode = 0;
	}
	
	if (awardsTab.draw(ren, mouseX, mouseY, lastMouse))
	{
		hiringTabMode = 1;
	}

	if (barracksTab.draw(ren, mouseX, mouseY, lastMouse))
	{
		hiringTabMode = 2;
	}

	if (hiringTabMode == 0)
	{
		//the part that deals with hiring new crew
		for (int i = 0; i < numCrewToShow; i++)
		{
			selectedCrew = playerCampaignInfo->getEmployableCrew(crewIndex + i).drawRecruitmentInfoCard(ren, 150 * gscreenx / 800, lowestY + 10 + (60 * i), 250, 50, mouseX, mouseY, lastMouse, &buttonClicked);
			if (buttonClicked && ticksSinceLastHire < 1)
			{
				playerCampaignInfo->hireCrew(crewIndex + i);
				ticksSinceLastHire = 10;
				//playerCampaignInfo->getSubmarine(0).crewToRandomCompartment(selectedCrew);
			}
			//if something other than nullptr, that means a crew member was selected. Load that into the pointer
			if (selectedCrew != nullptr)
			{
				//selectedCrew = pointer;
				playerCampaignInfo->setInfoCardCrewPointer(selectedCrew);
			}
		}

		recruitDownScroll.setPos(130 * gscreenx / 800, lowestY + (30 * gscreeny / 600));
		recruitUpScroll.setPos(130 * gscreenx / 800, lowestY + (30 * gscreeny / 600));

		if (recruitDownScroll.draw(ren, mouseX, mouseY, lastMouse) && crewIndex > 0)
		{
			crewIndex--;
		}
		else if (recruitUpScroll.draw(ren, mouseX, mouseY, lastMouse) && crewIndex < playerCampaignInfo->numEmployableCrew() - numCrewToShow)
		{
			crewIndex++;
		}
	}
	else if (hiringTabMode == 1)
	{
		//int xMultFuck = gscreeny / 600;
		//int awardIconsPadding = gscreeny / 600 * 30;
		int iconScaledSize = 20 * gscreeny / 600;
		int numQualifs = qualificationRegistry->size();
		int qualifSize = 20;
		//int twentyScaled = 20 * gscreeny / 600;
		
		//first off, draw a box
		color whatever(25,25,25,200);
		color white(255,255,255,255);
		drawRectFilled(ren, whatever, startXR, lowestY + 20, /*(295 * gscreenx / 800)*/(screenSizeX/2) - startXR, screenSizeY - lowestY - 40);
		drawText(ren, awardsTextSize, white, "qualifications (" + to_string(playerCampaignInfo->getQualificationCount()) + ")", startXR, lowestY + 20);
		selectedQual = nullptr;

		//draw the qualification section
		if (playerCampaignInfo->getQualificationCount() > 0)
			for (int i = 0; i < qualificationRegistry->size(); i++)
			{
				//qualificationRegistry->at(i).draw(ren, 150 + (20*(i%8)), (lowestY + 40) + (static_cast<int>(i/8)*20), 20, 20);
				qualificationRegistry->at(i).drawDraggable(ren, (startXR) + (20*(i%8)), (lowestY + 20 + getTextYSize(awardsTextSize)) + (static_cast<int>(i/8)*20), 20, 20, mouseX, mouseY, lastMouse, &selectedQual);
			}
		else
		{
			drawText(ren, awardsTextSize, white, "none available", startXR, lowestY + 20 + getTextYSize(awardsTextSize));
		}
		selectedAward = nullptr;
		//the award section
		if (3==3)
		{
			for (int i = 0; i < playerCampaignInfo->numLoadedAwards(); i++)
			{
				//only display user-assignable awards (awards of type 9)
				int numThisAward = playerCampaignInfo->getAwardCount(i);
				drawText(ren, awardsTextSize, white, to_string(numThisAward), startXR + iconScaledSize*2*(i%7) + iconScaledSize, lowestY + 20 + (static_cast<int>(numQualifs/7)*qualifSize) + getTextYSize(awardsTextSize));
				//drawText(ren, textSizeNormal, white, to_string(numThisAward), (170 * xMultFuck) + (iconScaledSize*(i%7)), (lowestY) + (static_cast<int>(i/7)*iconScaledSize) + getTextYSize(textSizeSeven)*2 + awardIconsPadding);
				//if (numThisAward > 0) playerCampaignInfo->getAwardData(i)->listedAward->drawDraggable(ren, (150 * xMultFuck) + (iconScaledSize*(i%7)), (lowestY + twentyScaled) + (static_cast<int>(i/7)*iconScaledSize) + getTextYSize(textSizeSeven) + awardIconsPadding, iconScaledSize/2, iconScaledSize/2, mouseX, mouseY, lastMouse, &selectedAward);
				//else playerCampaignInfo->getAwardData(i)->listedAward->draw(ren, (150 * xMultFuck) + (iconScaledSize*(i%7)), (lowestY + twentyScaled) + (static_cast<int>(i/7)*iconScaledSize) + getTextYSize(textSizeSeven) + awardIconsPadding, iconScaledSize/2, iconScaledSize/2);
				if (numThisAward > 0) playerCampaignInfo->getAwardData(i)->listedAward->drawDraggable(ren, startXR + iconScaledSize*2*(i%7), lowestY + 20 + (static_cast<int>(numQualifs/7)*qualifSize) + getTextYSize(awardsTextSize), iconScaledSize, iconScaledSize, mouseX, mouseY, lastMouse, &selectedAward);
				else playerCampaignInfo->getAwardData(i)->listedAward->draw(ren, startXR + iconScaledSize*2*(i%7), lowestY + 20 + (static_cast<int>(numQualifs/7)*qualifSize) + getTextYSize(awardsTextSize), iconScaledSize, iconScaledSize);
			}
		}
	}
	else if (hiringTabMode == 2)
	{
		//the below line of code is being added to the same area as the rest of the crew box dragging/dropping code in order to make it easier to not have problems
		//playerCampaignInfo->drawPlayerBarrack(ren, startXR, lowestY + 20, (screenSizeX/2) - startXR, 0, mouseX, mouseY, lastMouse);
	}

	if (ticksSinceLastHire > 0) ticksSinceLastHire--;

}

void startCampaign(SDL_Renderer *ren)
{
	playerCampaignInfo = new playerInfo(&campaignDatabase->at(campaignSelectionIndex), playerName, shipName, ren);
	cout << "campaign = " << campaignDatabase->at(campaignSelectionIndex).getName() << endl;
	cout << "player ship = " << playerCampaignInfo->getSubmarine(0).name() << endl;
}

void prepareRecruitmentScreen(SDL_Renderer *ren)
{
	playerCampaignInfo->generateEmployableCrew(100);
}

void drawSettingsScreen(SDL_Renderer *ren, int screenSizeX, int screenSizeY, int mouseX, int mouseY, Uint32 lastMouse)
{
	//text size will be based on horizontal screen size
	int textSizeHeader = 12 * (static_cast<double>(screenSizeX) / static_cast<double>(800));
	int textSizeNormal = 8 * (static_cast<double>(screenSizeX) / static_cast<double>(800));

	color linuxGreen(24,240,24,255);
	//sizeXEntry.setPos(screenSizeX*static_cast<double>(0.15), screenSizeY * static_cast<double>(0.10) + (getTextYSize(textSizeNormal)*3));
	//sizeYEntry.setPos(screenSizeX*static_cast<double>(0.15), screenSizeY * static_cast<double>(0.10) + (getTextYSize(textSizeNormal)*4));

	//text gets drawn under the monitor to give it a realistic glassy look
	drawText(ren, textSizeHeader, linuxGreen, "Game settings", screenSizeX*static_cast<double>(0.15), screenSizeY * static_cast<double>(0.10));
	drawText(ren, textSizeHeader, linuxGreen, "Screen Resolution", screenSizeX*static_cast<double>(0.15), screenSizeY * static_cast<double>(0.10) + (getTextYSize(textSizeNormal)*2));
	sizeXEntry.draw(ren, mouseX, mouseY, lastMouse);
	sizeYEntry.draw(ren, mouseX, mouseY, lastMouse);

	renderTextureEx(settingsBackground, ren, 0, 0, gscreenx, gscreeny, 0);
	showMainMenu = returnToMainMenu.draw(ren, mouseX, mouseY, lastMouse);
}

//the screen used for buying stuff such as submarines, upgrades, inventory crap and other stuff
void drawPurchaseScreen(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastMouse)
{	
	color white(255,255,255,255);
	//draw background
	renderTextureEx(purchaseScreenBackground, ren, 0, 0, gscreenx, gscreeny, 0);

	//draw back button
	if (returnToMainMenu.draw(ren, mouseX, mouseY, lastMouse))
	{
		showPurchaseScreen = false;
	}

	//note: the partition line on the online store background is exactly 22.6613% of the way from the left of the screen
	//the horizontal y partition line is at 14.3519% from the top of the screen
	//draw the text showing the player's account balance
	drawText(ren, textSizeNormal, white, "Account balance: $" + to_string(playerCampaignInfo->money()), gscreenx*static_cast<double>(0.226613), gscreeny - (textSizeNormal*3));
	if (submarineCategory.draw(ren, mouseX, mouseY, lastMouse))
	{
		purchaseTab = 0;
	}
	if (torpedoCategory.draw(ren, mouseX, mouseY, lastMouse))
	{
		purchaseTab = 1;
	}
	if (upgradesCategory.draw(ren, mouseX, mouseY, lastMouse))
	{
		purchaseTab = 2;
	}
	if (junkCategory.draw(ren, mouseX, mouseY, lastMouse))
	{
		purchaseTab = 3;
	}

	if (purchaseTab == 0)
	{	
		//draw the left and right scroll arrows for the list of submarines
		if (scrollLeftArrow.draw(ren, mouseX, mouseY, lastMouse) && submarineScrollCounter > 0)
		{
			submarineScrollCounter--;
		} 
		//there can be 4 on the screen at the same time
		else if (scrollRightArrow.draw(ren, mouseX, mouseY, lastMouse) && submarineScrollCounter + 4 < submarineRegistry->size())
		{
			submarineScrollCounter++;
		}

		//draw each submarine's purchase info card
		int cardSizeX = 150 * gscreenx / 800;
		int cardSizeY = 100 * gscreeny / 600;
		int submarinePurchaseCardOffset = 10 * gscreenx / 1366;
		int i = 0;
		submarine *subPurchasePointer = nullptr;
		while (i < submarineRegistry->size() && i + submarineScrollCounter < submarineScrollCounter + 4)
		{
			subPurchasePointer = submarineRegistry->at(submarineScrollCounter + i).drawPurchaseInfoCard(ren, (gscreenx * 0.226613) + ((cardSizeX+submarinePurchaseCardOffset)*i), gscreeny * 0.143519, cardSizeX, cardSizeY, mouseX, mouseY, lastMouse);
			
			//if user clicked on one of the submarine purchase infocards, set that submarine to be the selected submarine
			if (subPurchasePointer != nullptr)
			{
				selectedPurchasableSubmarine = subPurchasePointer;
				selectedPurchasableSubmarine->setupDetailsStrings(playerCampaignInfo->playerEquippedSubmarine());
				purchaseInProgress = false;
			}
			i++;
		}

		if (selectedPurchasableSubmarine != nullptr)
		{
			//show the selected submarine's details until the user purchases it. If that happens, set the "selected submarine" pointer to nullptr
			if (purchaseInProgress)
			{
				purchaseScreenNewName.setPos(gscreenx * 0.226613, gscreeny / 1.5);
				confirm.setPos(purchaseScreenNewName.posX(), purchaseScreenNewName.posY() + purchaseScreenNewName.sizeY());
				cancel.setPos(confirm.posX() + confirm.sizeX(), confirm.posY());
				randomizeName.setPos(purchaseScreenNewName.posX() + purchaseScreenNewName.sizeX() - randomizeName.sizeX(), purchaseScreenNewName.posY() + purchaseScreenNewName.sizeY());
				newShipName = purchaseScreenNewName.draw(ren, mouseX, mouseY, lastMouse);
				color white(255,255,255);
				drawText(ren, textSizeSeven, white, "Name your new ship", purchaseScreenNewName.posX(), purchaseScreenNewName.posY() - purchaseScreenNewName.sizeY());
				int texSizeX;
				int texSizeY;
				SDL_QueryTexture(selectedPurchasableSubmarine->getSmallIcon(), NULL, NULL, &texSizeX, &texSizeY);
				double icon_multiplier = static_cast<double>(texSizeY) / static_cast<double>(getTextYSize(textSizeSeven));
				//cout << "multiplier is " << icon_multiplier << endl;
				//cout << "texSizeX * mult = " << to_string(texSizeX * icon_multiplier) << " texSizeY * mult = " << to_string(texSizeY * icon_multiplier) << endl;
				renderTextureEx(selectedPurchasableSubmarine->getSmallIcon(), ren, purchaseScreenNewName.posX(), purchaseScreenNewName.posY() - (purchaseScreenNewName.sizeY()*2), texSizeX / icon_multiplier, texSizeY / icon_multiplier, 0);
				drawText(ren, textSizeSeven, white, selectedPurchasableSubmarine->name(), purchaseScreenNewName.posX() + (texSizeX / icon_multiplier), purchaseScreenNewName.posY() - (purchaseScreenNewName.sizeY()*2));
				if (confirm.draw(ren, mouseX, mouseY, lastMouse))
				{
					//transfer all crew in current submarine into barracks
					playerCampaignInfo->playerEquippedSubmarine()->moveEveryoneToBarracks(playerCampaignInfo->barracks());

					playerCampaignInfo->buySubmarine(ren, selectedPurchasableSubmarine, newShipName);

					//now transfer any needed crew from barracks into the new submarine
					//any uneeded crew will stay in barracks until the next time you need them
					playerCampaignInfo->barracksToSubmarine();

					purchaseInProgress = false;
				}
				if (cancel.draw(ren, mouseX, mouseY, lastMouse))
				{
					purchaseInProgress = false;
				}
				if (randomizeName.draw(ren, mouseX, mouseY, lastMouse))
				{
					purchaseScreenNewName.replaceText(crewNameGeneratorObject->randomShipName());
				}
			}
			else if(selectedPurchasableSubmarine->moreDetailedSubmarineInfo(ren, (gscreenx * 0.226613), gscreeny / 2, gscreenx - (gscreenx * 0.226613), gscreeny / 2, mouseX, mouseY, lastMouse, playerCampaignInfo->playerEquippedSubmarine(), true))
			{
				if (playerCampaignInfo->canBuySubmarine(selectedPurchasableSubmarine))
				{
					purchaseInProgress = true;

					//generate a new random name every time the player clicks the purchase button
					purchaseScreenNewName.replaceText(crewNameGeneratorObject->randomShipName());
					//selectedPurchasableSubmarine = nullptr;
				}
			}
		}
	}

	//man, are guis in most games also this much of a clusterfuck or am I just smoking crack?
	if (purchaseTab == 1)
	{
		if (scrollLeftArrow.draw(ren, mouseX, mouseY, lastMouse) && torpedoScrollCounter > 0)
		{
			torpedoScrollCounter--;
		} 
		//there can be 4 on the screen at the same time
		else if (scrollRightArrow.draw(ren, mouseX, mouseY, lastMouse) && torpedoScrollCounter + 4 < torpedoRegistry->size())
		{
			torpedoScrollCounter++;
		}

		int cardSizeX = 150 * gscreenx / 800;
		int cardSizeY = 100 * gscreeny / 600;
		int torpedoPurchaseCardOffset = 10 * gscreenx / 1366;
		int i = 0;
		torpedo *torpedoPurchasePointer = nullptr;
		while (i < torpedoRegistry->size() && i + torpedoScrollCounter < torpedoScrollCounter + 4)
		{
			torpedoPurchasePointer = torpedoRegistry->at(torpedoScrollCounter + i).drawPurchaseInfoCard(ren, (gscreenx * 0.226613) + ((cardSizeX+torpedoPurchaseCardOffset)*i), gscreeny * 0.143519, cardSizeX, cardSizeY, mouseX, mouseY, lastMouse);
			
			//if user clicked on one of the submarine purchase infocards, set that submarine to be the selected submarine
			if (torpedoPurchasePointer != nullptr)
			{
				selectedPurchasableTorpedo = torpedoPurchasePointer;
				//selectedPurchasableSubmarine->setupDetailsStrings(playerCampaignInfo->playerEquippedSubmarine());
				//purchaseInProgress = false;
			}
			i++;
		}
		torpedo *torpedoToSell = nullptr;
		playerCampaignInfo->playerEquippedSubmarine()->drawTorpedoArming(ren, (gscreenx * 0.226613), gscreeny / 2, gscreenx - (gscreenx * 0.226613), gscreeny / 2, mouseX, mouseY, lastMouse, &torpedoToSell);

		if (selectedPurchasableTorpedo != nullptr)
		{
			//if click on the torpedo purchase button
			if (selectedPurchasableTorpedo->drawPurchaseButton(ren, (gscreenx * 0.296613), (gscreeny / 2) - (getTextYSize(textSizeNormal)*2), mouseX, mouseY, lastMouse))
			{
				cout << "click buy button " <<endl;
				playerCampaignInfo->buyTorpedo(selectedPurchasableTorpedo);
			}
		}

		if (torpedoToSell != nullptr)
		{
			playerCampaignInfo->sellTorpedo(torpedoToSell);
		}
		//torpedoRegistry->at(0).drawPurchaseInfoCard(ren, gscreenx * 0.226613, gscreeny * 0.143519, cardSizeX, cardSizeY, mouseX, mouseY, lastMouse);
	}

	if (purchaseTab == 2)
	{
		for (int i = 0; i < upgradeTabs.size(); i++)
		{
			if (upgradeTabs.at(i)->draw(ren, mouseX, mouseY, lastMouse))
			{
				upgradePartTabIndex = i;
			}
		}
		int cardSizeX = 150 * gscreenx / 800;
		int cardSizeY = 50 * gscreenx / 800;
		int counter = 0; 		//count how many actual upgrade parts there are
		for (int i = 0; i < inventoryItemDatabase->size(); i++)
		{
			//only show upgrade parts
			if (inventoryItemDatabase->at(i)->getItemType() == 2)
			{
				bool isPartCompatible = static_cast<upgradePart*>(inventoryItemDatabase->at(i))->getUpgradeType() == upgradePartTabIndex && static_cast<upgradePart*>(inventoryItemDatabase->at(i))->getSubSize() == playerCampaignInfo->playerEquippedSubmarine()->getSize();
				bool isPartCompatibleWithEverything = static_cast<upgradePart*>(inventoryItemDatabase->at(i))->getUpgradeType() == upgradePartTabIndex && static_cast<upgradePart*>(inventoryItemDatabase->at(i))->getSubSize() == -1;
				if (isPartCompatible || isPartCompatibleWithEverything)
				{
					bool willPartFit = playerCampaignInfo->playerEquippedSubmarine()->canHavePart(static_cast<upgradePart*>(inventoryItemDatabase->at(i)));
					bool alreadyHasPart = playerCampaignInfo->playerEquippedSubmarine()->alreadyHasPart(static_cast<upgradePart*>(inventoryItemDatabase->at(i)));
					//cout << "does ship already have " << inventoryItemDatabase->at(i)->getName() << alreadyHasPart << endl;
					//cout << "is ship compatible with " << inventoryItemDatabase->at(i)->getName() << willPartFit << endl;
					//renderTextureEx(inventoryItemDatabase->at(i)->getTexture(), ren, (gscreenx * 0.226613), miscTab.posY() + miscTab.sizeY() + (counter*(cardSizeY+10)), cardSizeY, cardSizeY, 0);
					if (static_cast<upgradePart*>(inventoryItemDatabase->at(i))->drawPurchaseIcon(ren, (gscreenx * 0.226613), miscTab.posY() + miscTab.sizeY() + (counter*(cardSizeY+10)), cardSizeX + cardSizeY, cardSizeY, mouseX, mouseY, lastMouse, alreadyHasPart, willPartFit))
					{
						playerCampaignInfo->applyUpgradeToSubmarine(static_cast<upgradePart*>(inventoryItemDatabase->at(i)));
					}
					//drawText(ren, 6, color(255,255,255), inventoryItemDatabase->at(i)->getName(), 500, 200 + (i*20));
					counter++;
				}
			}
		}

		//draw the submarine's info and shit at a glance in the bottom right quadrant of the screen
		int statusScreenX = (gscreenx * 0.226613) + cardSizeX + cardSizeY*2;
		int statusScreenY = ((gscreeny - (miscTab.posY() + miscTab.sizeY()))/2); 		//half way from the start y of the upgrade icons to the bottom of the screen
		int statusScreenSX = gscreenx - statusScreenX;
		int statusScreenSY = gscreeny - statusScreenY;
		playerCampaignInfo->playerEquippedSubmarine()->moreDetailedSubmarineInfo(ren, statusScreenX, statusScreenY, statusScreenSX, statusScreenSY, mouseX, mouseY, lastMouse, nullptr, false);
	}

}

void loadGuiGizmos(SDL_Renderer *ren)
{
	//load torpedo slot. use multi format loader and use a png
	string torpedoSlotPath = "Textures/Menus/Misc/torpedo_slot.png";
	string torpedoSlotOrangePath = "Textures/Menus/Misc/torpedo_slot_recycle.png";
	
	SDL_Surface *bmp2 = IMG_Load(torpedoSlotPath.c_str());
	torpedoSlot = SDL_CreateTextureFromSurface(ren, bmp2);
	SDL_FreeSurface(bmp2);

	bmp2 = IMG_Load(torpedoSlotOrangePath.c_str());
	torpedoSlotOrange = SDL_CreateTextureFromSurface(ren, bmp2);
	SDL_FreeSurface(bmp2);
}

void drawLoadGameStuff(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastMouse)
{
	//gameLoadingScrollview
	if (!loadedSaves)
	{	
		loadGameFileButton = newCampaignBackButton;
		loadGameFileButton.setArrow(1);
		loadGameFileButton.setLabel("Load");
		loadGameFileButton.setPos(gscreenx - loadGameButton.sizeX() - (20 * gscreenx / 800), newCampaignBackButton.posY());
		//clear any previously loaded elements that may have been present
		gameLoadingScrollview.removeAllElements();

		//make a list of all present savegame paths
		string saveGamePath = "Saves";
		vector<string> filePaths;

		for (const auto & entry : std::filesystem::directory_iterator(saveGamePath))
		{
    	    std::cout << entry.path() << std::endl;
    	    filePaths.push_back(entry.path());
		}

		for (int i = 0; i < filePaths.size(); i++)
		{
			gameLoadingScrollview.addElement(filePaths.at(i));
		}
		loadedSaves = true;

	}

	//set up correct positioning for the scrollview
	gameLoadingScrollview.setPos(newCampaignBackButton.posX() + 20, 100 * gscreeny / 600);
	//gameLoadingScrollview.setSize(gscreenx / 2, gscreeny - newCampaignBackButton.posY() - gscreeny - gameLoadingScrollview.posY());
	gameLoadingScrollview.setSize(gscreenx / 2, 300);
	string selected = gameLoadingScrollview.draw(ren, mouseX, mouseY, lastMouse);
	//cout << "selected item = " << selected << "." << endl;
	if (selected != "-1")
	{
		drawText(ren, textSizeNormal, color(255,255,255), "selected save file:", gameLoadingScrollview.posX() + gameLoadingScrollview.sizeX() + 50, gameLoadingScrollview.posY());
		drawText(ren, textSizeNormal, color(255,255,255), selected, gameLoadingScrollview.posX() + gameLoadingScrollview.sizeX() + 50, gameLoadingScrollview.posY() + (getTextYSize(textSizeNormal) * 1));
		drawText(ren, textSizeNormal, color(255,255,255), "on patrol: xxx", gameLoadingScrollview.posX() + gameLoadingScrollview.sizeX() + 50, gameLoadingScrollview.posY() + (getTextYSize(textSizeNormal) * 2));
		drawText(ren, textSizeNormal, color(255,255,255), "date: xxx", gameLoadingScrollview.posX() + gameLoadingScrollview.sizeX() + 50, gameLoadingScrollview.posY() + (getTextYSize(textSizeNormal) * 3));

		if (loadGameFileButton.draw(ren, mouseX, mouseY, lastMouse))
		{
			if (loadFromXml(selected, playerCampaignInfo, ren) == 0)
			{
				cout << "load xml savefile reported success" << endl;
				gameLoadingScrollview.deselect();
				showMainMenu = false;
				newCampaignScreen = false;
				campaignBaseScreen = true;
				loadGameScreen = false;
			}
			else
			{
				gameLoadingScrollview.deselect();
				cout << "load xml savefile failed" << endl;
			}
		}
	}

	return void();
}

void drawPeliminaryMissionStartScreen(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastMouse)
{
	drawText(ren, textSizeNormal, color(255,255,255), "some map or something idk yet", 200, 200);
}

void loadIngameSpecificTextures(SDL_Renderer *ren)
{
	generic_dial_needle = loadTextureToRam("Textures/Menus/Controls/generic_dial_needle.png", ren);

	string depthMeterSmallPath = "Textures/Menus/Controls/Depth 50.png";
	string compassTexturePath = "Textures/Menus/Controls/compass.png";
	string throttleTexturePath = "Textures/Menus/Controls/Throttle.png";
	
	string periscopeButtonTexturePath = "Textures/Menus/Shortcuts/Periscope.png";
	string mapViewTexturePath = "Textures/Menus/Shortcuts/NavMap.png";
	string torpedoManagementTexturePath = "Textures/Menus/Shortcuts/TorpedoManagement.png";
	string crewManagementTexturePath = "Textures/Menus/Shortcuts/Crew.png";
	string freeCameraTexturePath = "Textures/Menus/Shortcuts/FreeCamera.png";

	SDL_Surface *bmp2 = IMG_Load(depthMeterSmallPath.c_str());
	depthMeterSmall = SDL_CreateTextureFromSurface(ren, bmp2);
	SDL_FreeSurface(bmp2);

	bmp2 = IMG_Load(compassTexturePath.c_str());
	compassTexture = SDL_CreateTextureFromSurface(ren, bmp2);
	SDL_FreeSurface(bmp2);

	//min 30. max 329
	depthMeterDial = dial(50*gscreenx/800, 700*gscreenx/800, 500*gscreeny/600, 65, depthMeterSmall, 30, 329);
	//dial(depthMeterSmall, ren, 700*gscreenx/800, 500*gscreeny/600, 100*gscreenx/800, 100*gscreenx/800, 0);

	//bmp2 = IMG_Load(throttleTexturePath.c_str());
	//throttleTexture = SDL_CreateTextureFromSurface(ren, bmp2);
	//SDL_FreeSurface(bmp2);
	throttleTexture = loadTextureToRam(throttleTexturePath ,ren);

	periscopeButtonTexture = loadTextureToRam(periscopeButtonTexturePath ,ren);
	mapViewTexture = loadTextureToRam(mapViewTexturePath ,ren);
	torpedoManagementTexture = loadTextureToRam(torpedoManagementTexturePath ,ren);
	crewManagementTexture = loadTextureToRam(crewManagementTexturePath ,ren);
	freeCameraTexture = loadTextureToRam(freeCameraTexturePath ,ren);
	periscope_viewport = loadTextureToRam("Textures/Menus/Controls/Periscope.png", ren);

	//set up the buttons
	periscopeButton = button("xxx", color(255,255,255),0,300,textSizeNormal);
	periscopeButton.setBackgroundColor(color(0,0,0,200));
	periscopeButton.setBorder(true);

	mapviewButton = button("xxx", color(255,255,255),0,periscopeButton.posY() + periscopeButton.sizeY(),textSizeNormal);
	mapviewButton.setBackgroundColor(color(0,0,0,200));
	mapviewButton.setBorder(true);

	torpedoManagementButton = button("xxx", color(255,255,255),0,mapviewButton.posY() + mapviewButton.sizeY(),textSizeNormal);
	torpedoManagementButton.setBackgroundColor(color(0,0,0,200));
	torpedoManagementButton.setBorder(true);

	crewManagementButton = button("xxx", color(255,255,255),0,torpedoManagementButton.posY() + torpedoManagementButton.sizeY(),textSizeNormal);
	crewManagementButton.setBackgroundColor(color(0,0,0,200));
	crewManagementButton.setBorder(true);

	freeCameraButton = button("xxx", color(255,255,255),0,crewManagementButton.posY() + crewManagementButton.sizeY(),textSizeNormal);
	freeCameraButton.setBackgroundColor(color(0,0,0,200));
	freeCameraButton.setBorder(true);

	//periscope screen stuff
	periscopeHeight.setSize(gscreeny*20/600, gscreeny*200/600);
	periscopeHeight.setPos(((gscreenx - gscreeny)/2)+gscreeny - periscopeHeight.sizeX(), gscreeny*200/600);

	return void();
}

void beIngame(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastMouse)
{
	if (test3dButtonF1.draw(ren, mouseX, mouseY, lastMouse))
	{
		reverseMeshPushbackOrder = !reverseMeshPushbackOrder;
		game3dRenderer.Start();
	}

	if (periscopeView)
	{
		periscopeScreen(ren, mouseX, mouseY, lastMouse);
	}
	else if (mapView)
	{
		mapScreen(ren, mouseX, mouseY, lastMouse);
	}
	else if (inGameTorpedoManagement)
	{

	}
	else if (inGameCrewManagement)
	{

	}
	else
	{
		//free camera
	}
	
	if (periscopeButton.draw(ren, mouseX, mouseY, lastMouse, periscopeButtonTexture))
	{
		periscopeView = true;
		mapView = false;
		inGameTorpedoManagement = false;
		inGameCrewManagement = false;
		freeCameraView = false;

		//3d is enabled in periscope mode because the periscope is used to view stuff in the 3d world
		enable3D = true;
	}

	if (mapviewButton.draw(ren, mouseX, mouseY, lastMouse, mapViewTexture))
	{
		periscopeView = false;
		mapView = true;
		inGameTorpedoManagement = false;
		inGameCrewManagement = false;
		freeCameraView = false;

		//map mode is where the player probably will spend most of their time. 3d is not enabled for this
		enable3D = false;
	}

	if (torpedoManagementButton.draw(ren, mouseX, mouseY, lastMouse, torpedoManagementTexture))
	{
		periscopeView = false;
		mapView = false;
		inGameTorpedoManagement = true;
		inGameCrewManagement = false;
		freeCameraView = false;

		//nothing having to do with 3d happens on the torpedo management screen
		enable3D = false;
	}

	if (crewManagementButton.draw(ren, mouseX, mouseY, lastMouse, crewManagementTexture))
	{
		periscopeView = false;
		mapView = false;
		inGameTorpedoManagement = false;
		inGameCrewManagement = true;
		freeCameraView = false;

		//nothing having to do with 3d happens on the crew management screen
		enable3D = false;
	}

	if (freeCameraButton.draw(ren, mouseX, mouseY, lastMouse, freeCameraTexture))
	{
		periscopeView = false;
		mapView = false;
		inGameTorpedoManagement = false;
		inGameCrewManagement = false;
		freeCameraView = true;

		//3d is drawn in free camera mode
		enable3D = true;
	}

	if (test3dButtonF2.draw(ren, mouseX, mouseY, lastMouse))
	{
		offset1++;
		if (offset1 == 2) 
		{
			offset1 = -1; 
			offset2++;
		}
		if (offset2 == 2)
		{
			offset2 = -1;
		}

		game3dRenderer.Start();
	}

	drawText(ren, textSizeNormal, color(255,255,255), "in game. Now what, you asshat?", 200, 200);

	double testDialVar = depthMeterDial.draw(ren, mouseX, mouseY, lastMouse);
	drawText(ren, textSizeSeven, color(255,255,255), "depth = " + to_string(testDialVar), 400, 400);
	drawText(ren, textSizeSeven, color(255,255,255), "degrees = " + to_string(depthMeterDial.degrees()), 400, 450);
	//renderTextureEx(depthMeterSmall, ren, 700*gscreenx/800, 500*gscreeny/600, 100*gscreenx/800, 100*gscreenx/800, 0);
	renderTextureEx(throttleTexture, ren, 600*gscreenx/800, 500*gscreeny/600, 100*gscreenx/800, 100*gscreenx/800, 0);
	renderTextureEx(compassTexture, ren, 500*gscreenx/800, 500*gscreeny/600, 100*gscreenx/800, 100*gscreenx/800, 0);

	drawText(ren, textSizeSeven, color(255,255,255), to_string(offset2) + " " + to_string(offset1), 820, 150);

	drawText(ren, textSizeSeven, color(255,255,255), to_string(shiftSlot3d), 820, 200);
	if (test3dButtonF3.draw(ren, mouseX, mouseY, lastMouse))
	{
		shiftSlot3d++;
		if (shiftSlot3d > 10) shiftSlot3d = 0;
		game3dRenderer.Start();
	}
}

void periscopeScreen(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastMouse)
{
	//draw periscope heading lines
	//do this behind the periscop player for reasons
	int middle = ((gscreenx - gscreeny)/2)+(gscreeny/2); //get where the "middle" of the heading indicator should be
	double curPeriRot = playerCampaignInfo->playerEquippedSubmarine()->m_periscopeRotation;

	//convert periscope rotation into a +/- 180 degree format for easier calculating
	if (curPeriRot > 180) curPeriRot = (curPeriRot - 360);

	//we don't have to this for for the full 360 in each direction but we do have to do it for a little more than 180 in each direction for it to look right
	for (int i = -210; i < 210; i++)
	{

		//tick marks are higher if heading tickmark is a multiple of 10
		int heightMult = 55;
		if (i % 10 == 0)
		{
			heightMult = 70;

			//convert the value of i to be suitable to be used as a marking for the 10s place on the periscope heading ticker
			string convHdgValue;
			if (i < 0) convHdgValue = to_string(i*-1);
			else convHdgValue = to_string(360-i);
			if (convHdgValue == "360") convHdgValue = "0";

			//draw the heading text
			drawText(ren, 8, color(0,0,0), convHdgValue, (middle - ((curPeriRot*5) + i*5))-(getTextXSize(8, convHdgValue.size())/2), 80);
		}

		//draw the heading tick mark line itself
		drawLine(ren, color(0,0,0,255), middle - ((curPeriRot*5) + i*5), 50 * gscreeny / 600, middle - ((curPeriRot*5) + i*5), heightMult * gscreeny / 600);
	}

	//draw periscope lense and pad sides with black
	renderTextureEx(periscope_viewport, ren, (gscreenx - gscreeny)/2, 0, gscreeny, gscreeny, 0);
	drawRectFilled(ren, color(0,0,0), 0, 0, (gscreenx - gscreeny)/2, gscreeny);
	drawRectFilled(ren, color(0,0,0), ((gscreenx - gscreeny)/2)+gscreeny, 0, (gscreenx - gscreeny)/2, gscreeny);

	//draw periscope height indicator
	periscopeHeight.setValue(static_cast<int>(playerCampaignInfo->playerEquippedSubmarine()->m_periscopeHeight));
	periscopeHeight.draw(ren);

	if (lastKey[SDL_SCANCODE_PAGEDOWN])
	{
		cout << "pagedown asserted" << endl;
		playerCampaignInfo->playerEquippedSubmarine()->periscopeRaise(-0.1f);
		cout << "periscope height = " << playerCampaignInfo->playerEquippedSubmarine()->m_periscopeHeight << endl;
		game3dRenderer.setCamPosY(playerCampaignInfo->playerEquippedSubmarine()->m_periscopeHeight);
	}

	if (lastKey[SDL_SCANCODE_PAGEUP])
	{
		cout << "pageup asserted" << endl;
		playerCampaignInfo->playerEquippedSubmarine()->periscopeRaise(0.1f);
		cout << "periscope height = " << playerCampaignInfo->playerEquippedSubmarine()->m_periscopeHeight << endl;
		game3dRenderer.setCamPosY(playerCampaignInfo->playerEquippedSubmarine()->m_periscopeHeight);
	}

	if (lastKey[SDL_SCANCODE_A] || lastKey[SDL_SCANCODE_LEFT])
	{
		playerCampaignInfo->playerEquippedSubmarine()->periscopeRotate(-1.0f);
		cout << "periscope rot = " << playerCampaignInfo->playerEquippedSubmarine()->m_periscopeRotation << endl;
		game3dRenderer.setCamRot(playerCampaignInfo->playerEquippedSubmarine()->m_periscopeRotation);
	}

	if (lastKey[SDL_SCANCODE_D] || lastKey[SDL_SCANCODE_RIGHT])
	{
		playerCampaignInfo->playerEquippedSubmarine()->periscopeRotate(1.0f);
		cout << "periscope rot = " << playerCampaignInfo->playerEquippedSubmarine()->m_periscopeRotation << endl;
		game3dRenderer.setCamRot(playerCampaignInfo->playerEquippedSubmarine()->m_periscopeRotation);
	}
}

void mapScreen(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastMouse)
{
	if (wheelUp)
	{
		mapZoom += 0.1*mapZoom;
		cout << "map zoom =" << mapZoom << endl;
	}
	else if (wheelDown)
	{
		mapZoom -= 0.1*mapZoom;
		cout << "map zoom =" << mapZoom << endl;
	}

	if (mapDragging)
	{
		mapViewX += (mouseX - mouseBeforeX)/mapZoom;
		mapViewY += (mouseY - mouseBeforeY)/mapZoom;
		cout << "now map pos = " << mapViewX << "," << mapViewY << endl;
	}

	if (lastMouse == SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		mapDragging = true;
		mouseBeforeX = mouseX;
		mouseBeforeY = mouseY;
	}
	else
	{
		mapDragging = false;
	}

	theWorld.drawMap(ren, mapZoom, mapViewX, mapViewY);
}