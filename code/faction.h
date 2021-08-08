#ifndef FACTION_H
#define FACTION_H

class faction
{
public:
	faction();
	faction(vector<string> fileContents, SDL_Renderer *ren);
	~faction();

	string name() { return m_name; }
	string description() { return m_description; }
	int team() { return m_team; }
	bool hasSubmarines() { return m_submarines; }
	int tier() { return m_tier; }
	string textureName() { return m_textureName; }

	void loadTexture(SDL_Renderer *ren);

	void drawFlag(SDL_Renderer *ren, int posX, int posY);
	void drawFlag(SDL_Renderer *ren, int posX, int posY, int sizeX, int sizeY);


	faction& operator=(faction& other);

	SDL_Texture *m_factionflag;

private:
	string m_name;
	string m_description;
	string m_textureName;
	int m_team;
	bool m_submarines;
	int m_tier;

};

void loadAllFactions(SDL_Renderer *ren);

void loadFactionFile(string filePath, SDL_Renderer *ren);

faction* getFactionByName(string name);

vector<faction> *factionDatabase = new vector<faction>;
vector<textureEntry*> *factionFlags = new vector<textureEntry*>;

#include "faction.hpp"

#endif