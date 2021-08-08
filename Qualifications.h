#ifndef QUALIFICATIONS_H
#define QUALIFICATIONS_H

#include <iostream>
#include <string>
using namespace std;

class qualification
{
public:
	qualification();
	qualification(vector<string> fileData, SDL_Renderer *ren);

	string name() const { return m_name; }
	string desc() const { return m_description; }
	int type() const { return m_type; }
	SDL_Texture* tex() const { return m_icon; }

	void draw(SDL_Renderer *ren, int posX, int posY, int sizeX, int sizeY);

	void drawDraggable(SDL_Renderer *ren, int posX, int posY, int sizeX, int sizeY, int mouseX, int mouseY, Uint32 lastMouse, qualification **selectedQual);

	qualification& operator=(const qualification& other);

protected:
	string m_name;
	string m_description;

	//0 = damagecontrol. 1 = flak gunner. 2 = gunner. 3 = hacking
	//4 = helm. 5 = mechanic. 6 = medic. 7 = nuclear. 8 = radio
	//9 = science. 10 = scorcery. 11 = sex. 12 = torpedo. 13 = watch. 14 = cargo. 15 = clowning
	int m_type;

	bool m_dragging;
	bool m_canClick;

	SDL_Texture *m_icon;

};

//this is where the loaded qualification classes get put into
vector<qualification> *qualificationRegistry = new vector<qualification>;

/*this is where the textures/icons for the qualifications are stored
faq:
q: wouldn't it be easier to just store the texture data itself in the qualification class?
a: No. SDL_Textures, for some stupid reason, cannot be copied. Pointers to SDL_Textures, however, can. In order for stuff like vector resizing and the
copy constructor to work, we have to store the actual texture data elsewhere so that the SDL_Texture pointer can simply be copied.

Additionally, doing it this way is a lot faster and will cut down on time during loading. Probably won't make a noticable difference on most machines but may 
shave several seconds off of loading times on a 486 or one of those modern junk laptops with hdds capable of 300kb/s read speeds that people keep buying for some reason
*/
vector<textureEntry*> *qualificationIcons = new vector<textureEntry*>;

int loadQualificationFile(string filePath, SDL_Renderer *ren);

int loadAllQualifications(SDL_Renderer *ren);

qualification* getQualificationById(int qualId);

#include "Qualifications.hpp"

#endif