#ifndef MENUS_H
#define MENUS_H

//0 = 800x600 w/ no scaling or other expensive subroutines. 1 = some larger 4:3 size. 2 = some 16:9 size
void loadMenuTextures(SDL_Renderer *ren, int menuQuality);

void loadGuiGizmos(SDL_Renderer *ren);

void drawMainMenu(SDL_Renderer *ren, int screenSizeX, int screenSizeY);

SDL_Texture *background;
SDL_Texture *newCampaignBackground;
SDL_Texture *campaignInPortMain;
SDL_Texture *recruitmentBackground;
SDL_Texture *settingsBackground;
SDL_Texture *purchaseScreenBackground;

SDL_Texture *titlepic; 		//"submarine warfare" logo
int titlepicPosX = 0;
int titlepicPosY = 0;
int titlepicSizeX = 0;
int titlepicSizeY = 0;

//guis icons and gizmos
SDL_Texture *torpedoSlot;
SDL_Texture *torpedoSlotOrange;

//main menu buttons
button newGameButton;
button loadGameButton;
button newCampaignBackButton;
textbox newPlayerNameTextbox;
button startNewCampaign;
button randomizePlayerName;
button returnToMainMenu;

//more main menu buttons
button campaignRightArrow;
button campaignLeftArrow;
button singleMission;
button multiplayer;
button missionEditor;
button settings;
button quitGame;

textbox shipNameTextbox;
button randomizeShipNameButton;
int campaignSelectionX = 150;
int campaignSelectionY = 240;
int campaignSelectionIndex = 0;
int clickButtonCooldown = 0;

//global text sizing
int textSizeHeader;	//12
int textSizeMedium; //10
int textSizeNormal; //8
int textSizeSeven; //7
int textSizeSmall; 	//6

//recruitment screen buttons
button recruitUpScroll;
button recruitDownScroll;
int crewIndex = 0;	//crew selection index for recruitment scrollbar

//awards panel variables. what a piece of shit the gui code for this is turning out to be
int startXR;
int awardsTextSize = 8;

button hiringTab;
button awardsTab;
button barracksTab;
int hiringTabMode = 0; 	//0= hiring tab. 1 = awards tab. 2 = barracks tab
qualification *selectedQual;
award *selectedAward;
bool menuDecrementQualification = false;
bool menuDecrementAward = false;

//the all important lowestY variable
int lowestY = 0;

//purchase screen stuff
int purchaseTab = 0; 		//0 = submarines. 1 = torpedos. 2 = upgrades. 3 = stuff/junk
button submarineCategory;
button torpedoCategory;
button upgradesCategory;
button junkCategory;
button scrollLeftArrow;
button scrollRightArrow;
int submarineScrollCounter = 0;
int torpedoScrollCounter = 0;
submarine *selectedPurchasableSubmarine = nullptr; 	//pointer to whatever the selected submarine in the purchase screen is. Nullptr for no selection
torpedo *selectedPurchasableTorpedo = nullptr;
bool purchaseInProgress = false;
button randomizeName;
button confirm;
button cancel;
textbox purchaseScreenNewName;
string newShipName;

//upgrade tabs
//0 = battery. 1 = diesel engine. 2 = electric engine. 3 = nuclear. 4 = fuel tank. 5 = oxygen generator.
//6 = radar. 7 = lidar. 8 = sonar. 9 = hydrophone. 10 = deck gun. 11 = hull strength. 12 = detection related. 13 = fun
int upgradePartTabIndex = 0;
button batteryTab;
button dieselTab;
button electricTab;
button nuclearTab;
button fuelTab;
button oxygenTab;
button radarTab;
button lidarTab;
button sonarTab;
button hydrophoneTab;
button deckgunTab;
button hullTab;
button stealthTab;
button miscTab;

//contains a vector of pointers to all 14 of the above buttons for ease of whatevering them
vector<button*> upgradeTabs;

//settings screen stuff
textbox sizeXEntry;
textbox sizeYEntry;

//variables regarding what the game is actually doing at the current moment
bool mainMenu = true;
bool showMainMenu = true;
bool showSettings = false;
bool newCampaignScreen = false;
bool campaignBaseScreen = false;
bool recruitmentScreen = false;
bool showPurchaseScreen = false;
bool preliminaryMissionStartScreen = false;
extern bool enable3D;

bool newPlayerGenerated = false;

//campaign in port buttons
button crewHiring;
button purchaseScreen;
button startMission; 		//the thing that lets you click on the map to get to the screen you see before the mission starts and the 3d renderer becomes enabled
bool stillSelected = false;
int ticksSinceLastHire = 10; 	//put at least a 10 frame delay in between crew hiring to make it not a sporadic clusterfuck

extern playerInfo *playerCampaignInfo;
extern crewNameGenerator *crewNameGeneratorObject;
extern string playerName;
extern string shipName;

void campaignSelectionGoRight();
void campaignSelectionGoLeft();

void startCampaign(SDL_Renderer *ren);

void prepareRecruitmentScreen(SDL_Renderer *ren);

void drawRecruitmentScreen(SDL_Renderer *ren, int screenSizeX, int screenSizeY, int mouseX, int mouseY, Uint32 lastMouse);

void drawSettingsScreen(SDL_Renderer *ren, int screenSizeX, int screenSizeY, int mouseX, int mouseY, Uint32 lastMouse);

//the screen used for buying stuff such as submarines, upgrades, inventory crap and other stuff
void drawPurchaseScreen(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastMouse);

#include "menus.hpp"

#endif 
