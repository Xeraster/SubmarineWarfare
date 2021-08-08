#ifndef THING_H
#define THING_H

extern vector<inventoryItem*> *inventoryItemDatabase;

class thing
{
	public:
		thing();
		thing(uint32_t seed);
		thing(int type, uint32_t seed = 0); //0 = junk. 1 = food. 2 = upgrade part. 3 = sex toy. 4 = drugs. 5 = magic related. 6 = scientific. 7 = skill related (ex: a book). 8 = crafting resource
		thing(string named);
		thing(inventoryItem *itemType);

		inventoryItem *inventoryComponent;

		string getName() { return inventoryComponent->getName(); }
		string getDescription() { return inventoryComponent->getDescription(); }
		string getTooltip() { return inventoryComponent->getOtherDescription(); }
		int getType(){ return inventoryComponent->getType(); }
		int getX() { return xPos; }
		int getY() { return yPos; }
		SDL_Texture *tex;

		thing& operator=(thing& other);
	private:

		void findAndSetTexture();
		int xPos;
		int yPos;

};

ostream& operator<<(ostream& os, thing item);

#include "thing.hpp"

#endif