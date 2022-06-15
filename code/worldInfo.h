#ifndef WORLDINFO_H
#define WORLDINFO_H

SDL_Texture *unknownSubIcon;
SDL_Texture *friendlySubIcon;
SDL_Texture *neutralSubIcon;
SDL_Texture *enemySubIcon;

SDL_Texture *unknownShipIcon;
SDL_Texture *friendlyShipIcon;
SDL_Texture *neutralShipIcon;
SDL_Texture *enemyShipIcon;

SDL_Texture *waypointButtonTexture;
SDL_Texture *markerButtonTexture;
SDL_Texture *protractorButtonTexture;
SDL_Texture *rulerButtonTexture;
SDL_Texture *eraserButtonTexture;
SDL_Texture *compassButtonTexture;

extern olcEngine3D game3dRenderer;

class worldInfo
{
public:
	worldInfo();
	worldInfo(playerInfo *input, string mapName, SDL_Renderer *ren, SDL_Window *win); 	//set up a world from given playerInfo and improvise from there
	~worldInfo();

	//loads the map data from a corresponding map file in data/maps/. passes heightmap name by reference and then loads ports by reference
	int loadMapData(string mapName, string *heightmapName);

	submarine *m_playerSubmarine;
	playerInfo *m_playerCampaignInfo;

	//date/time functions
	void setTime(double newTime) { m_time = newTime; }
	double getTime() const { return m_time; }
	void setDay(int newDay) { m_day = newDay; }
	int getDay() const { return m_day; }
	void setMonth(int newMonth) { m_month = newMonth; }
	int getMonth() const { return m_month; }
	void setYear(int newYear) { m_year = newYear; }
	int getYear() const { return m_year; }
	bool init() const { return m_initialized; }

	int mapSizeX() const { return m_mapSizeX; }
	int mapSizeY() const { return m_mapSizeY; }

	SDL_Texture* getMapTex() const { return m_mapTex; }

	SDL_Texture *m_mapTex;

	double m_mapScale = 20.0f; 		//how many meters does 1 heightmap pixel represent

	//prepares data to be rendered for frame and sends prepared data to the 3d renderer
	void prepareToRenderFrame(SDL_Renderer *ren, SDL_Window *win, olcEngine3D *engineRender);

	bool drawMap(SDL_Renderer *ren, double zoom, double *posX, double *posY, int mouseX, int mouseY, Uint32 lastMouse);

	void drawShipOnMap(SDL_Renderer *ren, double zoom, double playerX, double playerY, ship *whichShip);

	//made these globally accessible instead
	/*double worldToMapX(double zoom, double mapX, double inX);
	double worldToMapY(double zoom, double mapY, double inY);
	double mapToWorldX(double zoom, double posX, double mapX);
	double mapToWorldY(double zoom, double posY, double mapY);*/

	//stuff spawning commands
	void spawnShip(string shipClass, double posX, double posY, double heading);

	double heightAtCoords(int posX, int posY);

	void generateNearTerrain(double posX, double posY, int distance);

	void generateNearOcean(double posX, double posY, int distance);

	void physicsTick();

	//return 0 = success. 1 = failure
	//dataElement is the pointer to the element containing the player info data
	int worldInfoToSaveXml(XMLElement *dataElement);

	//return 0 = success. 1 = failure
	//dataElement is the pointer to the element containing the player info data
	int worldInfoFromXml(XMLElement *dataElement, SDL_Renderer *ren);

	//would like to be able to use an array for that extra little performance but I've never once got an array to work like this
	//seriously, you will not find a single dynamically allocated array in this entire program. They just. don't. fucking. work like countless internet posts claim they do. All they ever do is make segmentation faults upon creation
	//anything with the format of "var *name;" can't be initialized anywhere other than when it's initially declared in this entire program for some reason. Vectors can be used this way just fine but not arrays
	vector<Uint8> m_heightMap;

	vector<ship> m_ships;				//list of all ships in world
	//vector<aircraft> m_aircraft			//list of all aircraft in world

	vector<torpedo> m_npc_torpedos;
	//vector<projectile> m_allProjectiles;
	//vector<depthCharge> m_depthCharges;

	int numWorldPorts() const { return portsInWorld.size(); }
	port getPort(int index) const { return portsInWorld.at(index); }

	button waypointButton;
	button markerButton;
	button protractorButton;
	button rulerButton;
	button compassButton;
	button eraserButton;
	bool mapDragging = false;
	double mouseBeforeX = 0.0f;
	double mouseBeforeY = 0.0f;
	bool markerMode = false;
	bool rulerMode = false;
	bool protractorMode = false;
	bool compassMode = false;
	bool eraseMode = false;
	vector<markerPoint> points;
	vector<rulerLine> lines;
	vector<protractorAngle> angles;
	vector<compassCircle> circles;
	bool holdingClick = false;
	bool newClick = true;

	bool isInUtilityMode();
	void rulerModeWorker(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastMouse, double zoom, double mapCenterX, double mapCenterY);
	void protractorModeWorker(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastMouse, double zoom, double mapCenterX, double mapCenterY);
	void compassModeWorker(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastMouse, double zoom, double mapCenterX, double mapCenterY);

	float m_metersSinceLastTerrainUpdate;
	double xPosLastUpdate = 0;
	double yPosLastUpdate = 0;


	worldInfo& operator=(const worldInfo& other);
private:

	double m_time;			//time of day from 0 to 86400
	int m_day;				//day of the month
	int m_month; 			//month of the year
	int m_year;				//what year is it

	bool m_initialized = false;

	int m_mapSizeX;
	int m_mapSizeY;

	mesh m_terrain;
	mesh m_ocean;

	vector<port> portsInWorld;
};

void loadMapAssets(SDL_Renderer *ren, SDL_Window *win);
void deleteMapAssets();

#include "worldInfo.hpp"

#endif