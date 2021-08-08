#ifndef CREWMEMBER_H
#define CREWMEMBER_H

#include <iostream>
#include "nameGenerator.h"
#include "randomFunctions.h"
#include <string>
#include <vector>
using namespace std;
//random number generator
uint32_t betterRand(uint32_t seed);

string *skillStringArray = new string;

vector<string> *sexualities;
vector<string> *fetishes;

class crewMember
{
public:
	crewMember();

	crewMember(crewNameGenerator *randomNameObject);

	crewMember(crewNameGenerator *randomNameObject, uint32_t seed);


	string getRankString();

	string getFirstName() const { return firstname; }
	string getLastName() const { return lastname; }
	string genderToString() { if (gender == 0) return "Female"; else return "Male"; }
	int getGender() const { return gender; }
	int getRank() const { return rank; }
	double getWage() const { return wage; }
	int getAge() const { return age; }
	int getSexiness() { return sexiness; }
	bool hasPenis() { if (gender == 1) return true; }
	string getBreastSize() const { return breastSize; }
	double getPenisLength() const { return penisLength; }
	int getStripperVariant() const { return stripperVariant; }
	string printVaginaSize();
	int getSkill() const { return skill; }
	int getWitchcraftSkill() const { return wizardingSkill; }
	int getIntelligenceSkill() const { return intelligence; }
	int getSexSkill() const { return sexiness; }
	string skillAsString(int skillLevel, bool isSexRelated = false);
	string getAnusType() const { return anusType; }
	string getPubicHair() const { return pubicHair; }
	string getFetishString();
	string getSexualityString();
	int getSexualityIndex() const { return sexualityIndex; }
	bool employedByPlayer() const { return m_employedByPlayer; }
	void setEmployedByPlayer(bool status) { m_employedByPlayer = status; }
	bool isSelected() { return m_isSelected; }
	bool selectable() { return m_selectable; }
	int getSlotNumber() const { return m_slotNumber; }

	//if mouseX = -1 or mouseY = -1, icon is not selectable via mouse pointer collision
	void drawIcon(SDL_Renderer *ren, int posX, int posY, int sizeX, int sizeY, int mouseX, int mouseY, Uint32 lastMouse, crewMember **selected, bool draggableIcon = false);

	//return = nullptr if nothing selected. Pointer pointing to location in memory of specified crew if selected
	//mouseClicked = whether or not the "hire" button was pressed, if applicable
	crewMember* drawRecruitmentInfoCard(SDL_Renderer *ren, int posX, int posY, int sizeX, int sizeY, int mouseX, int mouseY, Uint32 lastMouse, bool *mouseClicked);

	//return true if "close infocard" button clicked
	bool drawInfoCard(SDL_Renderer *ren, int posX, int posY, int sizeX, int sizeY, int mouseX, int mouseY, Uint32 lastMouse);



	bool isWizard() const { return wizard; }
	bool isScientist() const { return scientist; }
	void setWizard(bool option) { wizard = option; }
	void setScientist(bool option) { scientist = option; }
	bool isCapableOfWitchcraft() { if (wizardingSkill == 0) return false; else return true; }

	int promote();
	int demote();

	button getDefaultButton(){ return defaultTab; }
	button getSkillsButton() { return skillsTab; }
	button getSexButton() { return sexTab; }

	int getSexIndex() const { return sexualityIndex; }
	int getFetishIndex() const { return fetishIndex; }

	//returns the amount of "manpower" that a crew member is able to output
	double manpower(int compartmentType);

	//prostitutes/strippers are only allowed to be given a sex qualification
	//clowns/assistant clowns are only allowed to be given a clowning qualification
	//sailors are not allowed to be given a qualification (but if they were a clown or prostitute and got promoted to sailor, they keep their qualification)
	//pettyofficers are allowed 1 of any qualification as well as, in addition, either a sex or clowning qualification
	//officers are allowed 3 of any qualification. Clowning and sex qualifications count against this limit of 3 the same way any other qualification does
	//returns false if was unable to give qualification based on the above rules
	//returns true if was able to give qualification and was still within the above rules
	bool giveQualification(qualification *qual);

	bool hasQualification(int typeId);

	bool giveAward(award *awardPointer);

	bool hasAward(award *awardPointer);

	//housekeeping variables
	int m_slotNumber;

	bool isInitialized() { return m_init; }

	crewMember& operator=(const crewMember& other);


	//theres no point in having this stuff since it doesn't make vector<crewMember>.erase work and it was only implemented because I thought it might do that
	//edit: apparently my problem was that operator= needed to have its argument const. vector<crewMember>.erase works now

	// Copy Constructor
    //crewMember(const crewMember& source);
 
    // Move Constructor
    //crewMember(crewMember&& source);

	bool isEqualTo(crewMember other);

	//dammit the vector memory allocation bug is really fucking this up
	//luckily, declaring it as a new vector in the init constructor and the copy constructor fixes it. For now
	//qualifications and awards
	vector<qualification*> *crewQualifications;
	vector<award*> *crewAwards;

protected:
	//whether or not it has been properly initialized
	bool m_init;

	//0 = female, 1 = male
	int gender;
	string firstname;
	string lastname;

	//skill ranges from 0 - 20
	int skill;
	int wizardingSkill;
	int intelligence;
	int sexiness;

	//index number for the sexuality and fetish arrays
	int sexualityIndex;
	int fetishIndex;

	int age;
	string breastSize;
	double penisLength; 		//negative values denote the presence of a vagina
	string anusType;
	string pubicHair;
	int stripperVariant;
	//0 = prisoner. 1 = entertainer lvl 1. 2 = entertainer lvl 2. 3 = recruit. 4 = apprentice. 5 = seaman
	//6 = pettyofficer 3rd class. 7 = pettyofficer 2nd class. 8 = pettyofficer 1st class. 9 = chief pettyofficer. 10 = senior chief pettyofficer. 11 = master chief pettyofficer
	//12 = command master chief pettyofficer. 13 = fleet master chief pettyofficer. 14 = master chief pettyofficer of the navy
	int rank;
	double wage;

	//whether or not crew member holds one of these special job classes
	bool wizard;
	bool scientist;
	bool m_employedByPlayer;
	//whether or not the player is dragging them around with the mouse
	bool m_isSelected;
	bool m_selectable;

	void initialSetupStep(crewNameGenerator *randomNameObject, uint32_t seed);
	void generateSexProperties(uint32_t seed);
	int randomRank(uint32_t seed);
	double randomWage(uint32_t seed);
	int randomAge(uint32_t seed, int minAge = 15, int maxAge = 42);
	string generateBreastSize(uint32_t seed);
	double generatePenisLength(uint32_t seed);
	string returnAnusType(uint32_t seed);
	string returnHairType(uint32_t seed);
	int generateSkillset(uint32_t seed);
	void configureSpecialJobType(uint32_t seed);

	//infocard / display variables
	button defaultTab;
	button skillsTab;
	button sexTab;
	button hiringButton;
	button personnelButton;
	bool m_infoCardCanDrop;

	void setupButtons()
	{
		color white(255,255,255,255);
		color darkBlack(0,0,0,150);
		button templateButton("default", white, 0, 0, 4);
		defaultTab = templateButton;
		skillsTab = templateButton;
		sexTab = templateButton;
		skillsTab.setLabel("skills");
		sexTab.setLabel("sex");
		hiringButton = templateButton;
		hiringButton.setLabel("Hire");
		hiringButton.setBorder(true);
		hiringButton.setFontSize(8);
		hiringButton.setBackgroundColor(darkBlack);
		personnelButton = templateButton;
		personnelButton.setLabel("Personal");
		personnelButton.setBackgroundColor(darkBlack);

	}

};

//global variable that tells what qualification the player is dragging
extern qualification *selectedQual;
extern award *selectedAward;
extern bool menuDecrementQualification;
extern bool menuDecrementAward;

ostream& operator<<(ostream& os, crewMember operandYeah);

extern vector<SDL_Texture*> crewicons_Large;

void drawCrewIconLarge(vector<SDL_Texture*> crewLargeTextures, crewMember crewPerson, SDL_Renderer *ren, int x, int y);

int loadSkillStringsIntoRam();

int loadMiscSexStuffIntoRam();

int m_infoType = 0; 	//0 = default. 1 = skills. 2 = sex related. 3 = personnel file


//#include "randomFunctions.h"
#include "crewMember.hpp"

#endif