#include "code/xml/tinyxml2.h" 				//tinyxml2 for xml support
#include "code/xml/tinyxml2.cpp" 				//tinyxml2 for xml support

#include "SDL2/SDL.h" 						//SDL for graphics, font and image scaling
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"


#include <iostream>
#include <thread>
#include <cstdlib>
#include <time.h>
#include <string>
using namespace std;
using namespace tinyxml2;

#include <tgmath.h>
#include <fstream>
#include <filesystem>
#include <vector>
#include <list>

bool reverseMeshPushbackOrder = false;
int offset1 = 1;
int offset2 = 1;
int shiftSlot3d = 0;

#include <type_traits>

#include "color.h"
#include "code/coloredString.h"
#include "randomFunctions.h"
#include "code/settings.h"
#include "code/button.h"
#include "code/textureEntry.h"
#include "code/faction.h"
#include "code/3dRenderer.h"
#include "LTimer.h"
#include "code/inventoryItem.h"
#include "code/thing.h"
#include "code/torpedo.h"
#include "nameGenerator.h"
#include "planet.h"
#include "simpleStarSystem.h"
#include "starSystem.h"
#include "crewNameGenerator.h"
#include "Qualifications.h"
#include "code/awards.h"
#include "crewMember.h"
#include "code/submarineCompartment.h"
#include "code/submarine.h"
#include "code/campaign.h"
#include "code/playerInfo.h"
#include "code/worldInfo.h"
#include "code/garbageCollection.h"
#include "code/saveutils.h"
#include "code/devConsole.h"
SDL_Event testEvent;
#include "code/menus.h"

//a question people will probably ask or wonder a lot is "why do you have to pass the renderer in so many functions?"
//the answer is because any SDL draw or render call cannot work when used under threading. However there is nothing preventing non-drawing or rendering functions from being run in a thread
//having to pass ren is basically a reminder that the function requiring the sdl renderer parameter can't be put in a new thread

LTimer fpsTimer;
LTimer capTimer;

string timeText;


const int SCREEN_FPS = 60;
const double SCREEN_TICKS_PER_SECOND = 300;
const int SCREEN_TICKS_PER_FRAME = SCREEN_TICKS_PER_SECOND / SCREEN_FPS;

bool exitGame = false;

color white(255,255,255);
color green(0,255,0);
color transGray(150,150,150,150);

int largeZoomX = 0;
int largeZoomY = 0;

bool zoomedOut = true;
bool galaxyView = true;
bool solarSystemView = false;

starSystem selectedSystem;
bool aStarIsSelected = false;
int zoomLevel = 0;

bool aPlanetIsSelected = false;
planet selectedPlanet;
int solarPosX = 0;

bool canClickMouse = true;

int countedFrames = 0;
char s[256];

//player setup variables
string playerName;
string shipName;
playerInfo *playerCampaignInfo;

textureEntry testTexture;

//moved the inventory item database global variable to just above the "thing" class. I need functions in that class to be able to use it
vector<inventoryItem*> *inventoryItemDatabase = new vector<inventoryItem*>;
//vector<food> *foodDatabase = new vector<food>;

//tbh I'm not sure why this works but whatever
crewNameGenerator *crewNameGeneratorObject = new crewNameGenerator;

vector<crewMember> fuckfuckfuck;
//thread testThread;

void update(SDL_Renderer *ren, SDL_Window *win);

void crewIconsLargeIntoMemory(SDL_Renderer *ren, vector<SDL_Texture*> &textureVector);

SDL_Texture *tex;
vector<SDL_Texture*> crewicons_Large;

SDL_Texture *poopy; //test texture access texture


//SDL_Event testEvent;

olcEngine3D game3dRenderer;
bool enable3D = true;
thing testThing;

//initialize the dev console
devConsole console;

//int threadedSimpleStar(void* yeah);

void helloWorld();

int main()
{	
	//coloredString test333;
	//coloredString test555;
	//test555 = "blah blah blah";
	//test333 = "blah blah blah";
	//load settings file to obtain screen resolution and other settings
	loadSettingsFile("settings.cfg");

	cout << "loadSkillStringsIntoRam() returned " << loadSkillStringsIntoRam() << endl;
	cout << "loadMiscSexStuffIntoRam()" << loadMiscSexStuffIntoRam() << endl;
	cout << "sexualites size =" << sexualities->size() << endl;

	/* initialize random seed: */
	int testSeed = 69420;
  	srand (time(NULL));
	

	/*crewMember testPerson(crewNameGeneratorObject);
	crewMember testPerson1(crewNameGeneratorObject);
	crewMember testPerson2(crewNameGeneratorObject);
	crewMember testPerson3(crewNameGeneratorObject);
	crewMember testPerson4(crewNameGeneratorObject);
	crewMember testPerson5(crewNameGeneratorObject);
	crewMember testPerson6(crewNameGeneratorObject);
	crewMember testPerson7(crewNameGeneratorObject);
	cout << testPerson << endl;
	cout << testPerson1 << endl;
	cout << testPerson2 << endl;
	cout << testPerson3 << endl;
	cout << testPerson4 << endl;
	cout << testPerson5 << endl;
	cout << testPerson6 << endl;
	cout << testPerson7 << endl;
	fuckfuckfuck.push_back(testPerson);
	fuckfuckfuck.push_back(testPerson1);
	fuckfuckfuck.push_back(testPerson2);
	fuckfuckfuck.push_back(testPerson3);
	fuckfuckfuck.push_back(testPerson4);
	fuckfuckfuck.push_back(testPerson5);
	fuckfuckfuck.push_back(testPerson6);
	fuckfuckfuck.push_back(testPerson7);*/

	//inventoryItem poop("poop", "poop 1", "poop 2", 1, 0, "poop.bmp");
	//food banana("banana", "banana 1", "banana 2", 5, 2, "banana.bmp", 1, 1.0, false);
	//upgradePart battery("battery", "battery 1", "battery 2", 1000, 3, "battery.bmp", 0, -1, 9000);
	//sexItem dildo("dildo", "dildo 1", "dildo 2", 15, 2, "dildo.bmp", 0);
	//food lettuce("lettuce", "green", "tastes like lettuce", 5, 2, "lettuce.bmp", 0, 1.0, false);
	//inventoryItem bowlingBall("bowling ball", "bowling ball 1", "bowling ball 2", 1, 0, "bowlingBall.bmp");
	//inventoryItem testThing = poop;

	//inventoryItemDatabase->push_back(&poop);
	//inventoryItemDatabase->push_back(&testThing);
	/*
	inventoryItemDatabase->push_back(&banana);
	inventoryItemDatabase->push_back(&battery);
	inventoryItemDatabase->push_back(&dildo);
	inventoryItemDatabase->push_back(&lettuce);
	inventoryItemDatabase->push_back(&bowlingBall);*/

	//jeez what a pain in the ass.. at least it works
	//cout << *inventoryItemDatabase->at(0) << endl;
	//cout << *inventoryItemDatabase->at(0) << endl;
	//cout << *static_cast<food*>(inventoryItemDatabase->at(1)) << endl;
	//cout << *static_cast<upgradePart*>(inventoryItemDatabase->at(2)) << endl;
	//cout << *static_cast<sexItem*>(inventoryItemDatabase->at(3)) << endl;


	//initialize this global variable for better zoom 1 performance
	//initQuickAccessColors();
  	cout << "poop" << endl;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	TTF_Init();
	SDL_Window *win = SDL_CreateWindow("Submarine Warfare", 100, 100, gscreenx, gscreeny, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	//SDL_SetWindowResizable(win, SDL_TRUE);
	if (win == nullptr)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr)
	{
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	//load the fonts into ram
	loadFonts();
	cout << "poop" << endl;

	//enable blending. May be useful to add option to disable blending for better performance
	SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);


	std::string imagePath = "Textures/Qualifications/flak_gunner.bmp";
	SDL_Surface *bmp = SDL_LoadBMP(imagePath.c_str());
	if (bmp == nullptr)
	{
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	//SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
	tex = SDL_CreateTextureFromSurface(ren, bmp);
	SDL_FreeSurface(bmp);
	if (tex == nullptr)
	{
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	//tell the dev console what the screen size is
	console.setScreenSize(screenSizeX(win), screenSizeY(win));

	//load menu resources
	loadMenuTextures(ren, 0);

	//time to load all the qualifications
	loadAllQualifications(ren);

	//load all the awards
	loadAllAwards(ren);
	for (int i = 0; i < awardRegistry->size(); i++)
	{
		cout << awardRegistry->at(i).name() << endl;
		cout << awardRegistry->at(i).desc() << endl;
	}

	//configure the error texture
	SDL_Surface *errorSmall = SDL_LoadBMP("Textures/error_handling/errorsmall.bmp");
	errorTexture = SDL_CreateTextureFromSurface(ren, errorSmall);
	SDL_FreeSurface(errorSmall);

	crewIconsLargeIntoMemory(ren, crewicons_Large);
	textureDirectoryIntoDatabase("Textures/Items/", ren);
	loadInventoryItems(inventoryItemDatabase);
	loadAllTorpedos(ren);
	//printAllItemsInDatabaseDetailed(inventoryItemDatabase);
	//cout << "desc = " << getRandomInventoryItem(inventoryItemDatabase)->getDescription() << endl;
	//thing poop(rand() % 8);
	//testThing = poop;
	//cout << testThing << endl;
	
	loadAllSubmarines(ren);
	//loadSubmarineFile("Data/submarines/Foxtrot.sub");
	//cout << "parent submarine= " << submarineRegistry->at(0).compartmentList.at(0).getParent()->name() << endl;
	int texQX = 0;
	int texQY = 0;
	SDL_QueryTexture(submarineRegistry->at(0).getLargeIcon(), NULL, NULL, &texQX, &texQY);
	//SDL_QueryTexture(submarineRegistry->at(0).getLargeIcon(), SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, texQX, texQY);
	//cout << "size of MainIcon = " << texQX << " ," << texQY << endl;
	loadAllFactions(ren);
	loadAllCampaigns();
	//after the campaigns have all been loaded, run this function to designate the default one
	campaignSelectionIndex = getCampaignIndexByName("Rags to Riches");

	//all this does is print information about each loaded faction. Commenting out now as there is TOO MUCH FUCKING SPAM outputting to the console every time this starts up
	/*for (int i = 0; i < factionDatabase->size(); i++)
	{
		cout << factionDatabase->at(i).name() << endl;
		cout << factionDatabase->at(i).description() << endl;
		cout << factionDatabase->at(i).textureName() << endl;
	}*/

	//you can actually set this to a number lower than the windowsize (for example 400x300) and it will render the 3d in a lower resolution than the 2d layer
	//great for running on super old crappy computers
	if (game3dRenderer.ConstructConsole(gscreenx, gscreeny, 1, 1, win, ren))
	{
		game3dRenderer.Start();
		cout << "3d renderer started sucessfully" << endl;
	}
	else
	{
		cout << "3d renderer could not start for some reason";
	}

	cout << "before loading test.xml" << endl;
	//xml testing shit
	XMLDocument doc;
	doc.LoadFile("test.xml");
	XMLElement *rootElement = doc.RootElement()->FirstChildElement("onPatrol");
	cout << rootElement->GetText() << endl;
	cout << "after loading test.xml (the stuff line above should be the contents of the file" << endl;
	rootElement->SetText("true");
	doc.SaveFile("test.xml");

	poopy = loadTextureToRam_TA("stripes.bmp", ren, win);
	//cout << "loaded texture" << endl;
	//color poopyColor = pixelAtPos(poopy, ren, win, 0, 0);
	//color poopyColor2 = pixelAtPos(poopy, ren, win, 2, 4);
	//color poopyColor3 = pixelAtPos(poopy, ren, win, 6, 3);
	//cout << "got color information of texture at given position" << endl;
	//cout << "r=" << poopyColor.getRed() << ", g=" << poopyColor.getGreen() << ", b=" << poopyColor.getBlue() << endl;
	//cout << "r=" << poopyColor2.getRed() << ", g=" << poopyColor2.getGreen() << ", b=" << poopyColor2.getBlue() << endl;
	//cout << "r=" << poopyColor3.getRed() << ", g=" << poopyColor3.getGreen() << ", b=" << poopyColor3.getBlue() << endl;
	//cout << "printed color information" << endl;

	fpsTimer.start();
	while (exitGame == false)
	{
		capTimer.start();
		update(ren, win);


		//Calculate and correct fps
        double avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.0f/*SCREEN_TICKS_PER_SECOND*/ );
        if( avgFPS > 2000000 )
        {
        	avgFPS = 0;
        }
        timeText = "FPS: " + to_string(avgFPS);

        // Update Title & Present Screen Buffer
		//snprintf(s, 256, "OneLoneCoder.com - Console Game Engine (SDL) - %s - FPS: %3.2f", bufAppName, 1.0f / fElapsedTime);
		snprintf(s, 256, "Submarine Warfare - FPS: %3.2f", avgFPS);
		SDL_SetWindowTitle(win, s);

		//handle all the events at the end of update even it there are many
		//SDL_Event testEvent;

		//there can only be 1 event handler per frame or else they will fight each other
		//this results in typing text being a pain in the ass and not working well since some keypressed don't seem to "register"
		//what is really happening is that there's no guarentee the keypress will register on the event handler you want
		//the more event handlers per frame, the worse the problem gets
		lastCharTyped = "";
		backspaceAsserted = false;
		enterAsserted = false;
		while (SDL_PollEvent(&testEvent) == 1)
		{
			if (testEvent.type == SDL_TEXTINPUT)
       	 	{
       	 		lastCharTyped = testEvent.text.text;
       	 	}

			if (testEvent.window.event == SDL_WINDOWEVENT_CLOSE)
			{
				exitGame = true;
			}

		}

		const Uint8 *lastKey = SDL_GetKeyboardState(NULL);
    	//if (m_timeTillNextKey <= 0)
    	//{
    		if (lastKey[SDL_SCANCODE_BACKSPACE]) 
    		{
    			backspaceAsserted = true;
    		}
    		else if(lastKey[SDL_SCANCODE_RETURN] || lastKey[SDL_SCANCODE_KP_ENTER])
    		{
    			enterAsserted = true;
    		}
    	//}

		if (fpsTimer.getTicks() > SCREEN_TICKS_PER_SECOND * 3)
		{
			fpsTimer.stop();
			fpsTimer.start();
			countedFrames = 0;
		}

	}

	//delete [] nameRandomizerObject;
	//delete [] crewNameGeneratorObject;
	deleteFonts();
	delete [] skillStringArray;
	//delete [] game3dRenderer.meshesToRender;
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_DestroyTexture(tex);
	//delete game3dRenderer;
	//delete [] bmp;
	return 0;
} 


void update(SDL_Renderer *ren, SDL_Window *win)
{
		thread test(deletePlayerTorpedos);
		//for drawing the selection box around the mouse
		int mouseBoxX = 80 * (screenSizeX(win)/800);
		int mouseBoxY = 60 * (screenSizeY(win)/600);

		string lastKeyPressed = "shut up";
		int mouseX, mouseY;
		Uint32 lastMouse = SDL_GetMouseState(&mouseX, &mouseY);

		/*if (lastMouse == SDL_BUTTON(SDL_BUTTON_LEFT) && canClickMouse && zoomedOut && galaxyView && !aStarIsSelected)
		{
			lastKeyPressed = "left mouse is being pressed";
			canClickMouse = false;
			zoomedOut = false;
			largeZoomX = (mouseX - (mouseBoxX/2))+largeZoomX;
			largeZoomY = (mouseY - (mouseBoxY/2))+largeZoomY;
		}
		else if(lastMouse == SDL_BUTTON(SDL_BUTTON_LEFT) && canClickMouse && galaxyView && aStarIsSelected)
		{
			canClickMouse = false;
			solarSystemView = true;
			galaxyView = false;
		}

		if (lastMouse == SDL_BUTTON(SDL_BUTTON_RIGHT) && canClickMouse && !zoomedOut && galaxyView)
		{
			lastKeyPressed = "right mouse is being pressed";
			canClickMouse = false;
			zoomedOut = true;
			largeZoomX = largeZoomX-(screenSizeX(win)/2)+(mouseBoxX/2)-(mouseX - (screenSizeX(win)/2));
			largeZoomY = largeZoomY-(screenSizeY(win)/2)+(mouseBoxY/2)-(mouseY - (screenSizeY(win)/2));
		}
		else if (lastMouse == SDL_BUTTON(SDL_BUTTON_RIGHT) && canClickMouse && solarSystemView)
		{
			canClickMouse = false;
			galaxyView = true;
			solarSystemView = true;
			zoomedOut = false;
		}*/

		//if (!canClickMouse)
		//{
			//ticksSinceLastMouse++;
		//}

		if (!canClickMouse && lastMouse != SDL_BUTTON(SDL_BUTTON_LEFT) && lastMouse != SDL_BUTTON(SDL_BUTTON_RIGHT))
		{
			//ticksSinceLastMouse=0;
			canClickMouse = true;
		}

		//const Uint8 *lastKey = SDL_GetKeyboardState(NULL);

		//cout << "windowsize = " << screenSizeX(win) << "x" << screenSizeY(win) << endl;
		uint32_t bluh = 42069;

		//First clear the renderer
		SDL_RenderClear(ren);
		//color red(255,0,0);
		//drawRectFilled(ren, red, 0, 0, 800, 600);
		//drawLine(ren, red, 0, 0, 400, 500);
		if (enable3D) game3dRenderer.GameThread();
		if (mainMenu) drawMainMenu(ren, screenSizeX(win), screenSizeY(win));

		//manage the console
		console.draw(ren, mouseX, mouseY, lastMouse, screenSizeX(win), screenSizeY(win));

		//color theColorBlack(0,0,0);
		//color theColorWhite(255,255,255);
		//drawGradient(ren, 0, 0, screenSizeX(win), screenSizeY(win), theColorBlack, theColorWhite, 100);

		/*renderTexture(testThing.tex, ren, 400, 400);
		for (int i = 0; i < 8; i++)
		{
			drawCrewIconLarge(crewicons_Large, fuckfuckfuck.at(i), ren, i*40, 400);
		}*/

		/*submarineRegistry->at(0).drawIconSmall(ren, 200, 200);
		submarineRegistry->at(1).drawIconSmall(ren, 200, 250);
		submarineRegistry->at(2).drawIconSmall(ren, 200, 300);
		submarineRegistry->at(3).drawIconSmall(ren, 200, 350);*/
		/*for (int i = 0; i < factionDatabase->size(); i++)
		{
			factionDatabase->at(i).drawFlag(ren, 600, 50 + (i*96), 96, 64);
		}*/
		//color red(255,0,0);
		//drawRectFilled(ren, red, 0, 0, 800, 600);
		//renderTexture(textureDatabase.at(0)->tex, ren, 400, 400);
		drawText(ren, 8, white, timeText, 2, 2);
		drawText(ren, 8, white, "mouse=" + to_string(mouseX) + "x" + to_string(mouseY), 2, 50);

		//the loop that tests the pixelAtPos function
		//for (int xxx = 0; xxx < 8; xxx++)
		//{
		//	for (int yyy=0; yyy<8; yyy++)
		//	{
		//		drawPixel(ren, xxx, yyy, pixelAtPos(poopy, ren, win, xxx, yyy));
		//	}
		//}

		//Update the screen
		SDL_RenderPresent(ren);
		test.join();
		//deletePlayerTorpedos();
		//Take a quick break after all that hard work
	int frameticks = capTimer.getTicks();
	if (frameticks < SCREEN_TICKS_PER_FRAME)
	{
		capTimer.stop();
		SDL_Delay(SCREEN_TICKS_PER_FRAME - frameticks);
	}
	countedFrames++;
	//delete lastKey;

	//SDL_Delay(1000);
}

void helloWorld()
{
	cout << "hello, world!" << endl;
}

//getting this to work ws probably the single biggest fuck of my life
void crewIconsLargeIntoMemory(SDL_Renderer *ren, vector<SDL_Texture*> &textureVector)
{
	string imagePath = "Textures/Crew/";
	string *iconsToLoad = new string[18];
	iconsToLoad[0] = "Prisoner_Female.bmp";
	iconsToLoad[1] = "Prisoner_Male.bmp";
	iconsToLoad[2] = "Entertainer_Female_1.bmp";
	iconsToLoad[3] = "Entertainer_Female_2.bmp";
	iconsToLoad[4] = "Entertainer_Female_3.bmp";
	iconsToLoad[5] = "Entertainer_Female_4.bmp";
	iconsToLoad[6] = "Entertainer_Male.bmp";
	iconsToLoad[7] = "Sailor_Female.bmp";
	iconsToLoad[8] = "Sailor_Male.bmp";
	iconsToLoad[9] = "PettyOfficer_Female.bmp";
	iconsToLoad[10] = "PettyOfficer_Male.bmp";
	iconsToLoad[11] = "Officer_Female.bmp";
	iconsToLoad[12] = "Officer_Male.bmp";
	iconsToLoad[13] = "Sorcerer_Female.bmp";
	iconsToLoad[14] = "Sorcerer_Male.bmp";
	iconsToLoad[15] = "Scientist_Female.bmp";
	iconsToLoad[16] = "Scientist_Male.bmp";
	iconsToLoad[17] = "blank.bmp";

	//sizeof(iconsToLoad) doesn't work correctly for some reason. It keeps returning 8 and fucking everything up
	for (int i = 0; i < 18; i++)
	{
		string pathString = imagePath+iconsToLoad[i];
		SDL_Surface *bmp = SDL_LoadBMP(pathString.c_str());

		//SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);

		textureVector.push_back(SDL_CreateTextureFromSurface(ren, bmp));
		SDL_FreeSurface(bmp);
	}
	
	//SDL_Surface *bmp = SDL_LoadBMP(imagePath.c_str());
	

	/*if (bmp == nullptr)
	{
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}*/

	//SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
	

	//tex = SDL_CreateTextureFromSurface(ren, bmp);
	//SDL_FreeSurface(bmp);
	

	/*if (tex == nullptr)
	{
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}*/
	delete [] iconsToLoad;
}