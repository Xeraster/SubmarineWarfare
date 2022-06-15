#ifndef SHIP_H
#define SHIP_H

class ship
{
public:

	ship();

	//unlike the submarine class, the ship classes load their data from an xml
	ship(XMLElement *shipElement);
	~ship();


	string className() const { return m_className; }
	string classString() const { return m_classString; }
	string desc() const { return m_description; }
	string textureName() const { return m_textureFolder; }
	string meshName() const { return m_meshName; }

	int getTier() const { return m_tier; }
	double getTopSpeed() const { return m_topSpeed; }
	double getAcceleration() const { return m_acceleration; }
	double getTurnRate() const { return m_turnRate; }
	int getRange() const { return m_range; }
	bool hasHydrophones() const { return m_hydrophones; }
	bool hasSonar() const { return m_sonar; }
	bool hasRadar() const { return m_radar; }

	double getLength() const { return m_length; }
	double getBeam() const { return m_beam; }
	double getDraft() const { return m_draft; }

	int getNumFloodableComps() const { return m_numFloodableCompartments; }
	int pathingPreference() const { return m_pathfinding; }
	double getTonnage() const { return m_tonnage; }
	int getShipType() const { return m_shipType; }

	void setPosX(double x) { worldPosX = x; m_shipMesh.posX = x; }
	void setPosY(double y) { worldPosY = y; m_shipMesh.posY = y; }
	void setPosZ(double z) { worldPosZ = z; m_shipMesh.posZ = z; }
	void setRotX(double hdg) { worldRotX = hdg; m_shipMesh.rotX = hdg; }
	void setRotY(double hdg) { worldRotY = hdg; m_shipMesh.rotY = hdg; }
	void setRotZ(double hdg) { worldRotZ = hdg; m_shipMesh.rotZ = hdg; }

	double getSpeed() const { return m_currentSpeed; }
	void setSpeed(double newSpeed, bool alsoSetTargetSpeed = true) { m_currentSpeed = newSpeed; if (alsoSetTargetSpeed) m_targetSpeed = newSpeed; }
	double getTargetSpeed() const { return m_targetSpeed; }
	void setTargetSpeed(double newTargetSpeed) { m_targetSpeed = newTargetSpeed; }
	double getTargetHeading() const { return m_targetHeading; }
	void setTargetHeading(double target) { m_targetHeading = target; }

	void physicsTick();

	//these more complicated and involved variables are being made fully public because they get used a lot and I'm sick and tired of typing getters and setters over and over in my shitty text editor, forgetting their names and then having to switch back and forth between windows
	//that's like that I spend 90% of my time doing. It sucks
	//pro-tip: use an ide. vscode for example or something with code completion or "intellisense".
	double worldPosX;
	double worldPosY;
	double worldPosZ;

	double worldRotX;
	double worldRotY;
	double worldRotZ;

	mesh m_shipMesh;

	void loadShipMesh(SDL_Renderer *ren, SDL_Window *win);

	ship& operator=(ship& other);
private:

	//stuff that gets loaded from data xml for each ship type
	string m_className; 	//identifier
	string m_classString; 	//in-game name
	string m_description;
	string m_textureFolder;
	string m_meshName;

	int m_tier; 	//0 = junk. 1 = ww2 more or less. 2 = cold war. 3 = modern. 4 = advanced futuristic
	double m_topSpeed;
	double m_acceleration;
	double m_turnRate;
	int m_range; 			//only really matters for missions the ai may chose to send the ship out on. I don't plan to give ai controlled units the ability to run out of gas
	bool m_hydrophones;
	bool m_sonar;
	bool m_radar;
	double m_length;
	double m_beam;
	double m_draft;
	int m_shipType; //0 = merchant. 1 = warship. 2 = natural (e.g. a whale, iceberg, cthulu)

	int m_numFloodableCompartments;
	int m_pathfinding; 		//here does the ship prefer to pathfind? 0 = coastal. 1 = deep ocean. 2 = no preference
	double m_tonnage;

	//in-game/pysics related stuff
	double m_currentSpeed;
	double m_targetSpeed;
	double m_targetHeading;


};

//this is where the loaded ship classes get put into
vector<ship> *shipRegistry = new vector<ship>;

int loadShipFile(string filePath, SDL_Renderer *ren, SDL_Window *win);

int loadAllShips(SDL_Renderer *ren, SDL_Window *win);

ship* getShipByName(string name);

#include "ship.hpp"

#endif