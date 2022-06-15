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
bool multiplayerMenu = false;
bool loadGameScreen = false;
bool loadedSaves = false;
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

/*=============================
in-game menus
============================
1. the general purpose overlay that's over everything regardless of what in-game view mode you're in
2. periscope
3. map view
4. torpedo management
5. crew management
6. free camera view
*/
bool ingameMenus = false;
bool periscopeView = false;
bool mapView = false;
bool inGameTorpedoManagement = false;
bool inGameCrewManagement = false;
bool freeCameraView = false;

//in game menu textures
SDL_Texture *depthMeterSmall;
SDL_Texture *throttleTexture;
SDL_Texture *compassTexture;
SDL_Texture *displayCompassTexture;
SDL_Texture *periscope_viewport;
dial depthMeterDial;
dial throttleDial;
dial headingDial;
dial headingDisplayDial;

SDL_Texture *periscopeButtonTexture;
SDL_Texture *mapViewTexture;
SDL_Texture *torpedoManagementTexture;
SDL_Texture *crewManagementTexture;
SDL_Texture *freeCameraTexture;

button periscopeButton;
button mapviewButton;
button torpedoManagementButton;
button crewManagementButton;
button freeCameraButton;

button test3dButtonF1 = button("reverse dir", color(255,0,255), 600, 100, 12);
button test3dButtonF2 = button("change offsets", color(255,0,255), 600, 150, 12);
button test3dButtonF3 = button("shift matrices", color(255,0,255), 600, 200, 12);
extern olcEngine3D game3dRenderer;
extern worldInfo theWorld;
double mapZoom = 1.0;
double mapViewX = 0;
double mapViewY = 0;
double mouseBeforeX = 0;
double mouseBeforeY = 0;
bool mapDragging = false;

progressBar periscopeHeight(0, 0, 50, 50, color(255,150,0), 15, true);

//the load game screen objects
verticalScrollView gameLoadingScrollview(800, 600, 250, 100, 15);
button loadGameFileButton;

void campaignSelectionGoRight();
void campaignSelectionGoLeft();

void startCampaign(SDL_Renderer *ren);

void prepareRecruitmentScreen(SDL_Renderer *ren);

void drawRecruitmentScreen(SDL_Renderer *ren, int screenSizeX, int screenSizeY, int mouseX, int mouseY, Uint32 lastMouse);

void drawSettingsScreen(SDL_Renderer *ren, int screenSizeX, int screenSizeY, int mouseX, int mouseY, Uint32 lastMouse);

//the screen used for buying stuff such as submarines, upgrades, inventory crap and other stuff
void drawPurchaseScreen(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastMouse);

void drawLoadGameStuff(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastMouse);

void drawPeliminaryMissionStartScreen(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastMouse);

void loadIngameSpecificTextures(SDL_Renderer *ren);

//in-game 2d menu draing functions
void beIngame(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastMouse);

void periscopeScreen(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastMouse);

void mapScreen(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastMouse);

#include "menus.hpp"

#endif 
