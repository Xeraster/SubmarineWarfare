#ifndef SUBMARINECOMPARTMENT_H
#define SUBMARINECOMPARTMENT_H

//forward class declaration. Find alternative if it causes segfaults
class submarine;

class submarineCompartment
{
public:
	submarineCompartment();
	submarineCompartment(string displayName, int type, int crewSlots, int officerSlots, double requiredManpower, int posX, int posY);

	string displayName() { return m_name; }
	int type() { return m_type; }
	int numSlots() { return m_crewSlots; }
	int officerSlots() { return m_officerSlots; }
	double requiredManpower() { return m_requiredManpower; }
	double currentManpower() { return m_currentManpower; }

	//the janky wanky variables. m_compartmentNumber is not valid until both of the draw functions have been executed at once
	int compartmentNumber() { return m_compartmentNumber; }

	SDL_Texture* qualIcon() { return m_compartmentJobIcon; }
	
	int posX() { return m_posX; }
	int posY() { return m_posY; }
	int sizeX();
	int sizeY();

	//function = what command to do. 0 = nothing. 1 = transfer crew to compartment. 2 = get crew out of compartment
	int boxFunction() { return m_boxFunction; }
	int crewBoxFunction() { return m_crewBoxFunction; }

	//used for collisions
	//only works after doDrawing has been called at least once for the current screen settings in this instance (changes do not survive a deep copy)
	bool isInside(int x, int y)
	{
		int xMin = 0;
		int xMax = 0;
		int yMin = 0;
		int yMax = 0;

		getBoxSize(&xMin, &yMin, &xMax, &yMax);

		cout << "is " << x << ", " << y << " inside of " << xMin << "-" << xMax << ", " << yMin << "-" << yMax << "?" << endl;

		if (x > xMin && x < xMax && y > yMin && y < yMax)
		{
			cout << "yes" << endl;
			return true;
		}
		else
		{
			cout << "no" << endl;
			return false;
		}
	}
	//void setParent(submarine *parentSubmarine) { m_parentSubmarine = parentSubmarine; }
	//submarine* getParent() { return m_parentSubmarine; }
	void loadTextures(SDL_Renderer *ren, string textureName);
	void clearTextures();	//sets texture pointers to nullptr to avoid segfaults when they get deleted later

	void doDrawing(SDL_Renderer *ren, double sizeMultiplier, int horizontalOffset, int veritcalOffset, int mouseX, int mouseY, Uint32 lastmouse);

	//returns y coordinate of bottom of box
	//the function that draws crew icons for each crew member in compartment
	int drawCrewBox(SDL_Renderer *ren, int screenX, int screenY, int veritcalOffset, int compartmentNumber, int numCompartments, int mouseX, int mouseY, Uint32 lastmouse, crewMember **selected);

	//use this one instead of drawCrewBox() if the compartment is the onshore crew barracks
	void drawCrewBoxBarracks(SDL_Renderer *ren, int posX, int posY, int sizeX, int mouseX, int mouseY, Uint32 lastmouse, crewMember **selected);

	//returns false if unable to (ex: the compartment is already full). Returns true upon success
	bool addCrewToAnySlot(crewMember *person);

	//moves a crew member to any slot in the current compartment then passes the value of the slot the said crew member ended up in
	//returns true if there was room. returns false if there was no room
	//slotNum = -1 if there was no room in the compartment
	bool moveCrewToAnySlot(crewMember *person, int *slotNum);

	//adds crew pointer to slot at screen position inputted by x, y. Returns false if failed, true if success
	bool crewToSpecificSlot(crewMember *person, int x, int y, int screenX, int *slotNum, crewMember **crewToPutInPlace);

	//adds crew pointer to slot at position.
	//returns 0 if sucess. returns 1 if already occupied. returns 2 if given slot number invalid
	int crewToSlotNumber(crewMember *person, int slotNum);

	bool eraseDuplicateCrew(crewMember *person, int excludeSlot);

	bool replaceDuplicateCrew(crewMember *person, int excludeSlot, crewMember* replacement);

	//a standalone way of obtaining the coordinates for a crew box icon space thingy (or whatever its called)
	void coordinatesToSlotNum(int x, int y, int *slotNum, int screenX);

	//a standalone way of obtaining the position and size of the crew box for the compartment.
	//only works if drawCrewBox() and doDrawing() have already been called on the current instance
	void getBoxSize(int *px, int *py, int *sx, int *sy);

	//returns the number of crew in current compartment. nullptr does not count as 1 crew
	int numCrew();

	//returns false if all slots of the compartment are occupied. Returns true if not all of the compartment slots are occupied
	bool isFull();

	//passes number of sailors, pettyofficers and officers by reference
	void numCrewTypes(int *sailors, int *pettyofficers, int *officers);

	//called each time something changes or happens that might change the compartment's manpower
	void updateManpower();

	int getFunctionType()
	{
		if (m_boxFunction != 0 ) return m_boxFunction;
		else if (m_crewBoxFunction != 0) return m_crewBoxFunction;
		else return 0;
	}

	crewMember* crewInSlot(int index)
	{
		if (index < m_crewSlotArray.size())
		{
			return m_crewSlotArray.at(index);
		}
		else return nullptr;
	}

	progressBar compartmentBar() { return m_compartmentEfficiency; }

	//returns a random crew member pointer in the compartment
	//only returns nullptr if there are no crew in the compartment
	crewMember* randomCrew();

	//sorts all the crew in a compartment by job type. Makes things look neat
	void sortCrew();

	void coordinatesToSlotNumInBarracks(int x, int y, int *slotNum, int screenX);
	//adds crew pointer to slot at screen position inputted by x, y. Returns false if failed, true if success
	bool crewToSpecificSlotInBarracks(crewMember *person, int x, int y, int screenX, int *slotNum, crewMember **crewToPutInPlace);

	int toSaveXml(XMLElement *dataElement, int index);

	submarineCompartment& operator=(submarineCompartment& other);


private:
	string getTextureName();
	//0=bow torpedo. 1=stern torpedo. 2=diesel engines. 3=electric engines. 4=bow crew quarters. 5=command room. 6=radio room. 7=cargo. 8=stripper pole. 9=science lab. 10=nuclear reactor.
	//11 = hacking center. 12 = clowning center. 13 = witchcraft stuff. 14 = stern crew quarters
	int m_type;
	string m_name;
	int m_crewSlots;
	int m_officerSlots;
	double m_requiredManpower;
	double m_currentManpower;

	//whatever the multiplier passed by the last draw call was. Defaults to 1 if doDrawing() has not yet been called in current instance. 
	//Does not persist after a deep-copy (it changes back to 1)
	double m_sizeMultiplier;
	//this works the same way as m_sizeMUltiplier. Defaults to 0
	int m_verticalOffset;
	//works the same way as the above 2 variables. Defaults to 1
	int m_numCompartments;
	int m_compartmentNumber;
	int m_screenX;
	
	//upper-right position of compartment (as far as cursor collision is concerned) when the submarine MainIcon_inside texture is unstretched and unscaled
	//size data is fetched from SDL_QueryTexture later on
	int m_posX;
	int m_posY;

	//pointer to parent submarine
	//submarine *m_parentSubmarine;

	//pointer to the mouse selection texture
	SDL_Texture *selectTexture;

	//pointer to the "qualification" icon of the given compartment
	SDL_Texture *m_compartmentJobIcon;

	//man, FUCK arrays
	//crewMember** m_crewSlotArray;
	vector<crewMember*> m_crewSlotArray;

	//gui variables
	bool m_isSelected;
	bool m_boxSelected;
	int m_framesSinceLastclick;
	bool m_doubleclickReady;
	//function = what command to do. 0 = nothing. 1 = transfer crew to compartment. 2 = get crew out of compartment
	int m_boxFunction;
	int m_crewBoxFunction;

	progressBar m_compartmentEfficiency;

	//set qualification icon texture pointer.
	//the qualification icon that corresponds to the type of compartment
	void setQualificationIcon();

};

extern int lowestY;
extern int startXR;

extern vector<SDL_Texture*> crewicons_Large;
extern vector<textureEntry*> *extraSubmarineSprites;

extern vector<crewMember> fuckfuckfuck;

ostream& operator<<(ostream& os, submarineCompartment item);

#include "submarineCompartment.hpp"

#endif