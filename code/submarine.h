#ifndef SUBMARINE_H
#define SUBMARINE_H

class submarine
{
public:
	submarine();
	submarine(vector<string> fileData);

	~submarine();

	string name() { return m_name; }
	string description() { return m_description; }

	//ex: USS Nautilus, Queen Ann's Revenge, HMS boob
	string shipName() { return m_shipName; }
	void setShipName(string newName) { m_shipName = newName; }


	string textureName() { return m_textureName; }
	string mesh_low() { return m_mesh_low; }
	string mesh_high() { return m_mesh_high; }

	double topspeed_surface() { return m_topspeed_surface; }
	double topspeed_submerged() { return m_topspeed_submerged; }
	double acceleration() { return m_acceleration; }
	double diesels_mult_water() { return m_diesels_mult_water; }

	//tier 0 = potato. 1 = ww2 capability. 2 = early cold war. 3 = late cold war and modern. 4 = advanced futuristic
	int tier() { return m_tier; }

	double length() { return m_length; }
	double beam() { return m_beam; }
	double draught() { return m_draught; }
	double displacement() { return m_displacement; }

	double mpg() { return m_mpg; }
	int powerType() { return m_powerType; } 		//0 = diesel electric. 1 = diesel electric except the electric engines are always used and diesel only generates power. 2 = nuclear
	double fuelCapacity() { return m_fuelCapacity; }
	double ampHours() { return m_ampHours; }
	int range() { return m_range; }
	int batRange() { return m_batrange; }

	int getSize() { return m_submarine_size; }

	//crew information
	int sailors() {return m_sailors; }
	int pettyOfficers() { return m_pettyOfficers; }
	int officers() { return m_officers; }

	//torpedo information
	int bowTorpedoTubes() { return m_bowTorpedoTubes; }
	int sternTorpedoTubes() { return m_sternTorpedoTubes; }
	int bowReserve() { return m_bowReserve; }
	int sternReserve() { return m_sternReserve; }

	double nukeOutput() { return m_nukeOutput; }	//in MW
	double nukeEfficiency() { return m_nukeEfficiency; }	//number of years it takes a fuel rod to run down
	
	//upgrade and parts information
	bool canGoNuclear() { return m_canGoNuclear; }
	int canHaveOxygenGen() { return m_oxygenGen; }
	int canHavePassiveSonar() { return m_passiveSonar; }
	int canHaveActiveSonar() { return m_activeSonar; }
	int canHaveRader() { return m_rader; }
	int canHaveLidar() { return m_lidar; }
	int canHaveSnorkel() { return m_snorkel; }
	bool canHaveDeckGun() { return m_canHaveDeckgun; }
	int deckGunX() { return m_deckGunPosX; }
	int deckGUnY() { return m_deckGunPosY; }

	double cost() { return m_cost; }
	int crushDepth() { return m_crushDepth; }
	int safeDepth() { return m_safeDepth; }

	double air() { return m_air; }
	int numCargoSlots() { return m_cargoSlots; }

	//compartment getters
	//0 = battery. 1 = diesel engine. 2 = electric engine. 3 = nuclear. 4 = fuel tank. 5 = oxygen generator.
	//6 = radar. 7 = radar detector. 8 = sonar. 9 = hydrophone. 10 = deck gun. 11 = hull strength. 12 = detection related. 13 = fun
	upgradePart* getUpgradeConst(int index) const;

	upgradePart* getUpgrade(int index);

	vector<submarineCompartment> compartmentList;

	/*fixed size vector of pointers. Torpedos themselves are stored in playerInfo
	slot numbering convention goes m_bowTorpedoTubes, m_bowReserve, m_sternTorpedoTubes, m_sternReserve
	
	FOR EXAMPLE: a submarine with 4 bow tubes, 10 bow reserve, 2 stern tubes and 2 stern reserve will have a torpedoStorage size of 18
	position 0-3 will be bow torpedo tubes 1, 2, 3 and 4.
	position 4-13 will be bow reserve slots 1-10
	position 14 and 15 will be stern tubes 1 and 2
	position 16 and 17 will be stern reserve slot 1 and 2
	*/
	vector<torpedo*> *torpedoStorage = new vector<torpedo*>;

	//the drawing related functions
	SDL_Texture* getSmallIcon() { return smallIcon; }
	SDL_Texture* getLargeIcon() { return largeIcon; }
	SDL_Texture* interiorTexture() { return m_interiorTexture; }
	void drawIconSmall(SDL_Renderer *ren, int posX, int posY);
	void drawIconLarge(SDL_Renderer *ren, int posX, int posY);

	progressBar getCrewBar() const { return m_crewOccupancy; }
	progressBar getpoBar() const { return m_poOccupancy; }
	progressBar getOfficerBar() const { return m_officerOccupancy; }

	//size x = screen size X, size y = screen size Y
	//returns selected crew
	void drawInfoScreen(SDL_Renderer *ren, int sizeX, int sizeY, int mouseX, int mouseY, Uint32 lastMouse, int *yBottom, crewMember **selected);

	//loads the standard 3-set of submarine icons. Loaded upon game start
	int loadSubmarineIcons(SDL_Renderer *ren, bool useCompressed = false);

	//loads each of the submarine's compartment textures. Only done when the player "selects" a submarine.
	//This way, having a modlist of 200+ modded submarines won't lag the game out from the stupid search algorithms and/or a massive ram hit
	int loadExtraSubmarineIcons(SDL_Renderer *ren);

	//recursively removes each texture pointer in the submarine's compartment list. Then, deletes all textures in extraSubmarineSprites
	int clearExtraSubmarineIcons(SDL_Renderer *ren);

	bool crewToRandomCompartment(crewMember *person);

	//put crew in compartment at position indicatedby posX, posY
	bool putCrewInCompartment(crewMember* person, int posX, int posY, int screenX, crewMember **replacement, int *slotNumb);

	void findAndEraseDuplicateCrew(crewMember* person, int excludeCompartment, int excludeSlot);

	void findAndReplaceDuplicateCrew(crewMember* person, int excludeCompartment, int excludeSlot, crewMember* replacement);

	/*
	sends all crew from the source compartment (compartment) to crew quarters.
	if there isn't room in crew quarters for everyone, it just moves some of them.
	if the source compartment is a crew quarters compartment, it evenly distributes them to different parts of the submarine
	*/
	void sendCompartmentToRest(submarineCompartment compartment);

	/*
	populates the provided compartment to the inputted percentage using crew from crew quarters
	if there is not enough available crew to achieve the inputted compartment manpower percentage, it will do as many crew as it can
	if there is no available crew in any of the crew quarters compartments, it does nothing
	if the provided compartment is crew quarters, takes any tired or unneeded crew from other compartments and transfers them into the provided compartment
	*/
	void autoPopulateCompartment(submarineCompartment *compartment, double targetPercentage = 0.65);

	//moves all crew in the submarine to the provided barracks compartment pointer
	//true = finished
	//false = not enough room in barracks for everyone
	bool moveEveryoneToBarracks(submarineCompartment *barracks);

	//currently only updates the "progress" bars that show crew count. Will do more in the future
	void updateCrewCounts();

	void getCrewCounts(int *sailors, int *pos, int *officers);

	int totalCrewSlots();

	int totalCrewInSub();

	//recalculates manpower values for every compartment in the submarine
	void recalculateManpower();

	submarine* drawPurchaseInfoCard(SDL_Renderer *ren, int posX, int posY, int sizeX, int sizeY, int mouseX, int mouseY, Uint32 lastMouse);

	//displays some of the basic, user-upgradable information 
	void basicSubmarineInfo(SDL_Renderer *ren, int posX, int posY, int sizeX, int sizeY);
	
	//displays more info than the purchase infocard alone does.
	//returns true if user pressed the purchase button
	bool moreDetailedSubmarineInfo(SDL_Renderer *ren, int posX, int posY, int sizeX, int sizeY, int mouseX, int mouseY, Uint32 lastMouse, submarine *compareSub = nullptr, bool showBuyButton = true);

	void drawTorpedoArming(SDL_Renderer *ren, int posX, int posY, int sizeX, int sizeY, int mouseX, int mouseY, Uint32 lastMouse, torpedo **torpedoToSell = nullptr);

	double getBatteryMultiplier();
	double getDieselMultiplier();
	double getElectricNultiplier();
	double getFuelMultiplier();
	double getHullMultiplier();

	void setupDetailsStrings(submarine *compareSub);

	//checks if the submarine is compatible with a certain part
	bool canHavePart(upgradePart *part);

	//checks if the submarine already has a certain part
	bool alreadyHasPart(upgradePart *part);

	void putPartInSubmarine(upgradePart *part);

	//returns a mostly unique id used for saving and loading based on the submarines's info
	//it's not impossible for 2 submarines to have the same id, just highly unlikely. In the future, the way this function works may change
	string makeIdHashSalt();

	//takes a submarine and saves it to xml in the game-saving function
	int toSaveXml(XMLElement *dataElement, int subIndex);

	void loadRestOfStuffFromXml(XMLElement *dataElement);

	void progressUpgradeSaving(XMLElement *dataElement, string keyName, upgradePart *part);

	submarine& operator=(submarine& other);

protected:
	void upgradePointersNull();

	//if the submarine class "comes with" certain upgrade parts by default, find out what they are, find them in the database and then apply their pointers
	void applyCorrectParts();

	string m_name;
	string m_description;

	//ex: USS Nautilus, Queen Ann's Revenge, HMS boob
	string m_shipName;

	string m_textureName;
	string m_mesh_low;		//low quality 3d model
	string m_mesh_high;		//higher quality 3d model

	//texture pointers (to avoid using a search algorithm later which is slow)
	SDL_Texture *smallIcon;
	SDL_Texture *largeIcon;

	//for the player's ship management screen. Just load it now because it will be easier to keep track of and avoid segfaults
	SDL_Texture *m_interiorTexture;

	double m_topspeed_surface;
	double m_topspeed_submerged;
	double m_acceleration;
	double m_diesels_mult_water;
	//tier 0 = potato. 1 = ww2 capability. 2 = early cold war. 3 = late cold war and modern. 4 = advanced futuristic
	int m_tier;

	//dimensions
	double m_length;
	double m_beam;
	double m_draught;
	double m_displacement;

	//submarine size (for upgrade part compatibility checks. options are 0 = small. 1 = medium. 2 = large)
	int m_submarine_size;

	//nautical miles per gallon of fuel at half surface top speed
	double m_mpg;
	int m_powerType;	//0 = diesel electric. 1 = diesel electric except the electric engines are always used and diesel only generates power. 2 = nuclear

	double m_fuelCapacity; //in gallons
	double m_ampHours;	//
	int m_range;
	int m_batrange; //in nautical miles, the distance the submarine can travel at 1/4th the submerged top speed.

	//crew information
	int m_sailors;
	int m_pettyOfficers;
	int m_officers;

	//torpedo information
	int m_bowTorpedoTubes;
	int m_sternTorpedoTubes;
	int m_bowReserve;
	int m_sternReserve;

	double m_nukeOutput;	//in MW
	double m_nukeEfficiency;	//number of years it takes a fuel rod to run down
	
	//upgrade and parts information
	//0 = can't have. 1 = can have. 2 = yes, by default
	bool m_canGoNuclear;
	int m_oxygenGen;
	int m_passiveSonar;//70-=BBBBBB <- those damn cats
	int m_activeSonar;
	int m_rader;
	int m_lidar; 		//this is actually radar detector
	int m_snorkel;
	bool m_canHaveDeckgun;
	int m_deckGunPosX;
	int m_deckGunPosY;

	double m_cost;
	int m_crushDepth;
	int m_safeDepth;

	double m_air;
	int m_cargoSlots;

	progressBar m_crewOccupancy;
	progressBar m_poOccupancy;
	progressBar m_officerOccupancy;
	button purchaseButton;
	//torpedo gui variables
	int m_sourceSlotNum;
	int m_destSlotNum;


	//upgrade slots
	upgradePart *m_batteryUpgrade;
	upgradePart *m_engineUpgrade;
	upgradePart *m_electricEngineUpgrade;
	upgradePart *m_nuclearReactor;			//nuclear submarines have this slot already populated
	upgradePart *m_fuelTank;
	upgradePart *m_oxygenGenerator;			//submarines that come with an oxygen generator have this slot populated by default
	
	//ww2 or before comes with Fumo 30.
	//early cold war or later comes with Loran mast radar
	upgradePart *m_radarUpgrade;				//submarines that come with radar have this slot already populated by default
	
	//submarines that come with a radar detector have this slot already populated by default
	//ww2 or before comes with Metox
	//early cold war or later comes with XCF-80
	upgradePart *m_radarDetector;

	//if a submarine comes with an active sonar system, this will be populated by default. What type of default sonar depends on the sub's tech level
	//ww2 = asdic-based sonar
	//early cold war = GHBa
	//modern day and futuristic = BQQ5
	upgradePart *m_activeSonarUpgrade;

	//if a submarine has hydrophones by default, early cold war and before gets GHB. Modern day and later gets BQQ5
	upgradePart *m_hydrophones;

	upgradePart *m_hullUpgrade;

	upgradePart *m_stealthMisc;

};

//this is where the loaded submarine classes get put into
vector<submarine> *submarineRegistry = new vector<submarine>;

vector<textureEntry*> *submarineSprites = new vector<textureEntry*>;

vector<textureEntry*> *extraSubmarineSprites = new vector<textureEntry*>;

int loadSubmarineFile(string filePath, SDL_Renderer *ren);

int loadAllSubmarines(SDL_Renderer *ren);

submarine* getSubmarineByName(string name);

//coloredString global variables below this line
//I made them global variables so I could easily calculate them once instead of on every frame because that adds too much overhead
coloredString depthString;
coloredString bowTorpedoString;
coloredString bowTorpedoReserve;
coloredString aftTorpedoString;
coloredString aftTorpedoReserve;
coloredString maxSpeedString;
coloredString maxSpeedSubmergedString;
coloredString surfaceRange;
coloredString underwaterRange;
coloredString daysOFair;
coloredString cargoSlotsString;
coloredString devices; 			//sonar, radar, radar detector, hydrophones all on one stupidass line

//double batteryMultiplier = 1;
//double dieselMultiplier = 1;
//double electricMultiplier = 1;
//double hullMultiplier = 1;
//double fuelMultiplier = 1;

extern SDL_Texture *torpedoSlot;
extern SDL_Texture *torpedoSlotOrange;

#include "submarine.hpp"

#endif