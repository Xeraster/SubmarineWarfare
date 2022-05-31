#ifndef AWARDS_H
#define AWARDS_H

class award
{
public:
	award();
	award(vector<string> fileData, SDL_Renderer *ren);

	string name() const { return m_name; }
	string desc() const { return m_description; }
	int type() const { return m_type; }
	int amount() const { return m_amount; }
	bool playerIssued() const { return m_playerIssued; }
	SDL_Texture* tex() const { return m_icon; }

	void draw(SDL_Renderer *ren, int posX, int posY, int sizeX, int sizeY);

	void drawDraggable(SDL_Renderer *ren, int posX, int posY, int sizeX, int sizeY, int mouseX, int mouseY, Uint32 lastMouse, award **selectedAward);

	award& operator=(const award& other);

protected:
	string m_name;
	string m_description;

	/*
	m_type is the condition id. There are many of them and probably more to come.
	0. = number of patrols completed. 1 = amount of tonnage sunk. 2 = purple heart. 3 = number of ships sunk while doing anything other than chilling out in the crew quarters
	//4 = number of miles sailed. 5 = number of days spent on patrol (continuous). 6 = number of days spent on patrol (total). 7 = experience points earned.
	8 = max depth dived to. 9 = player issued only (and the amount is the level). 10 = medal of honor. 11. number of nuclear weapons deployed while working in relevant compartment
	*/
	int m_type;
	int m_amount;

	bool m_playerIssued;

	bool m_dragging;
	bool m_canClick;

	SDL_Texture *m_icon;

};

//this is where the loaded submarine classes get put into
vector<award> *awardRegistry = new vector<award>;

vector<textureEntry*> *awardIcons = new vector<textureEntry*>;

int loadAwardFile(string filePath, SDL_Renderer *ren);

int loadAllAwards(SDL_Renderer *ren);

void getAwardsOfType(int type, vector<award*> *awardArray);

award* getAwardByName(string name);

#include "awards.hpp"

#endif