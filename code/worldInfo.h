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

extern olcEngine3D game3dRenderer;

class worldInfo
{
public:
	worldInfo();
	worldInfo(playerInfo *input, string heightmapName, SDL_Renderer *ren, SDL_Window *win); 	//set up a world from given playerInfo and improvise from there
	~worldInfo();

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

	bool drawMap(SDL_Renderer *ren, double zoom, double posX, double posY);

	void drawShipOnMap(SDL_Renderer *ren, double zoom, double playerX, double playerY, ship *whichShip);

	double worldToMapX(double zoom, double mapX, double inX);
	double worldToMapY(double zoom, double mapY, double inY);

	//stuff spawning commands
	void spawnShip(string shipClass, double posX, double posY, double heading);

	double heightAtCoords(int posX, int posY);

	void generateNearTerrain(double posX, double posY, int distance);

	void generateNearOcean(double posX, double posY, int distance);

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
};

void loadMapAssets(SDL_Renderer *ren, SDL_Window *win);
void deleteMapAssets();

#include "worldInfo.hpp"

#endif