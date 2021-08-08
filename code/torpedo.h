#ifndef TORPEDO_H
#define TORPEDO_H 

class torpedo
{
public:
	torpedo();

	torpedo(vector<string> fileData);

	//torpedo(const torpedo &other);

	string name() const { return m_name; }
	string description() const { return m_description; }
	string textureFolder() const { return m_textureFolder; }
	string mesh_low() const { return m_mesh_low; }
	string mesh_high() const { return m_mesh_high; }
	int speed(int index) const
	{
		if (index == 0) return m_speed1;
		else if (index == 1) return m_speed2;
		else return m_speed3;
	}
	int range(int index) const
	{
		if (index == 0) return m_range1;
		else if (index == 1) return m_range2;
		else return m_range3;
	}

	int armingRange() const { return m_armingRange; }
	int type() const { return m_type; }
	bool hasWire() const { return m_hasWire; }

	double warhead() const { return m_warheadpower; }
	int guidance() const { return m_guidance; }
	int controlSurfaces() const { return m_controlSurfaces; }
	int crushDepth() const { return m_crushdepth; }
	double turnSpeed() const { return m_turnspeed; }
	double cost() const { return m_cost; }
	bool magnetic() const { return m_magnetic; }
	bool rangeExplode() const { return m_rangeExplode; }
	double maxGyroangle() const { return m_maxGyroangle; }
	double loudness() const { return m_loudness; }
	bool serverAlert() const { return m_serverAlert; } 

	int largestSpeed();
	int largestRange();

	bool markedForDeletion() const { return m_markedForDeletion; }
	void markForDeletion() { m_markedForDeletion = true; }

	SDL_Texture* getTex() const { return m_icon; }

	//loads the torpedo's textures
	int loadTorpedoTextures(SDL_Renderer *ren);

	torpedo* drawPurchaseInfoCard(SDL_Renderer *ren, int posX, int posY, int sizeX, int sizeY, int mouseX, int mouseY, Uint32 lastMouse);

	bool drawPurchaseButton(SDL_Renderer *ren, int posX, int posY, int mouseX, int mouseY, Uint32 lastMouse);

	bool drawTorpedoIcon(SDL_Renderer *ren, int posX, int posY, int sizeX, int sizeY, int mouseX, int mouseY, Uint32 lastMouse, bool rear = false);

	torpedo& operator=(const torpedo& other);

private:
	string m_name;
	string m_description;
	string m_textureFolder;
	string m_mesh_low;
	string m_mesh_high;

	//-1 means disabled
	int m_speed1;
	int m_speed2;
	int m_speed3;
	int m_range1;
	int m_range2;
	int m_range3;

	//the distance the torpedo has to travel before the warhead and homing capabilites become active
	int m_armingRange;

	//0 = torpedo. 1 = it flies in the air
	int m_type;

	//does it have the capability to be wire guided
	bool m_hasWire;

	double m_warheadpower;	//in tons of TNT
	
	//0 = guided heading (straight line). 1 = passive acoustic homing. 3 = active sonar. 4 = heat-seeking. 5 = magic.
	int m_guidance;

	//0 = it only goes left and right. 1 = it can go left, right, up and down. Irrelevant for non-homing torpedos
	int m_controlSurfaces;

	int m_crushdepth; //in meters

	double m_turnspeed;

	double m_cost;

	bool m_magnetic; 		//does it have the option to use a magnetic pistol
	bool m_rangeExplode;

	double m_maxGyroangle; 	//gyroangle the torpedo is capable of going to immediately after leaving the torpedo tube. 180 means any.

	double m_loudness;		//how many decibels the torpedo is at its fastest speed. Louder ones are easier to hear on hydrophones

	//should the admin or something get a notification if a player fires this. (for example you'd want to be informed on every instance of a magic nuke torpedo being fired know who's hacking)
	bool m_serverAlert;

	SDL_Texture *m_icon;

	//gui related variables
	bool m_selected;
	bool m_mouseOver;
	button purchaseButton;

	//garbage collection
	bool m_markedForDeletion;
};

vector<torpedo> *torpedoRegistry = new vector<torpedo>;

vector<textureEntry*> *torpedoSprites = new vector<textureEntry*>;

int loadTorpedoFile(string filePath, SDL_Renderer *ren);

int loadAllTorpedos(SDL_Renderer *ren);

torpedo* getTorpedoByName(string name);

torpedo* randomTorpedo();

#include "torpedo.hpp"
#endif