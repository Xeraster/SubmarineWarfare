#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H

#include <iostream>
#include <string>
using namespace std;

class inventoryItem
{
public:
	inventoryItem();
	inventoryItem(string newName, string desc, string desc2, double cost, int rare, string textureName);
	inventoryItem(vector<string> *fileContents); //this needs to very specifically be only the vector<string> generated from the file loader or else it will fail catastrophically
	~inventoryItem();

	int getItemType() { return type; }
	string printItemType();

	int getRarity() { return rarity; }
	string printRarity();

	string getName() { return name; }
	string getDescription() { return description; }
	string getOtherDescription() { return m_additionalInfo; }
	double getCost() { return m_cost; }
	string getTextureName() { return m_textureName; }
	int getType() { return type; }
	double getRelevantStat() { return relevantStat; }
	SDL_Texture* getTexture() { return tex; }

	inventoryItem& operator=(inventoryItem& other);

	void setDescription(string desc){ description = desc; }
	void setOtherDescription(string desc){ m_additionalInfo = desc; }

	int maxStackSize() { return m_stackSize; }
	double weight() { return m_packageWeight; }

	//makes more sense to put this here instead of the thing class
	void findAndSetTexture();

	button getPurchaseButton() const { return m_purchaseButton; }


protected:
	string name;
	string description;
	string m_additionalInfo;

	//0 = junk. 1 = food. 2 = upgrade part. 3 = sex toy. 4 = drugs. 5 = magic related. 6 = scientific. 7 = skill related (ex: a book). 8 = crafting resource
	int type;

	double relevantStat;
	double m_cost;

	//0 = abundant. 1 = common. 2 = uncommon. 3 = rare. 4 = legendary. 5 = one of a kind. 6 = dev or godmode only. 7 = not supposed to exit. 8 = doesn't exist
	int rarity;

	//"null", "shut_up", and "stfu" as well as anything without a file extension will use the default sprite for its item class
	string m_textureName;

	int m_stackSize;
	double m_packageWeight;

	void loadDefaults(vector<string> *fileStreamLines, int itemType);

	bool m_researchRequired;
	string m_research;

	//pointer to the correct texture. It is important that this works as a pointer and does so correctly in order to avoid stupidly massive amounts of overhead
	SDL_Texture *tex;

	button m_purchaseButton;

};

class food: public inventoryItem
{
public:
	food();
	food(string newName, string desc, string desc2, double cost, int rare, string textureName, int preferability, double nutrition, bool humanMeat);
	food(vector<string> *fileContents); //this needs to very specifically be only the vector<string> generated from the file loader or else it will fail catastrophically

	int getPreferability() { return m_preferability; }
	double getNutrition() { return m_nutrition; }

	bool isHumanMeat() { return m_humanMeat; }

	string printPreferability();

	food& operator=(food& other);

protected:
	//-2 = absolutely disgusting. 1 = rather gross. 0 = bland. 1 = quite tasty. 2 lavishly delicious
	int m_preferability;

	double m_nutrition;

	bool m_humanMeat;

};

class upgradePart: public inventoryItem
{
public:
	upgradePart();
	upgradePart(string newName, string desc, string desc2, double cost, int rare, string textureName, int upgradeThingType, int submarineCompatibility, double modifier);
	upgradePart(vector<string> *fileContents); //this needs to very specifically be only the vector<string> generated from the file loader or else it will fail catastrophically

	int getUpgradeType() { return upgradeType; }
	int getSubSize() { return compatibleSubmarineSize; }

	double getModifierAmount() { return relevantStat; }
	double getSecondStat() const { return m_secondStat; }
	double getThirdStat() const { return m_thirdStat; }
	string printUpgradeType();
	string printModifiedStat();

	//returns pointer to this if buy button pressed
	upgradePart* drawPurchaseIcon(SDL_Renderer *ren, int posX, int posY, int sizeX, int sizeY, int mouseX, int mouseY, Uint32 lastMouse, bool alreadyHasPart = false, bool isCompatible = true);
	coloredString statString();

	upgradePart& operator=(upgradePart& other);

protected:
	//0 = battery. 1 = diesel engine. 2 = electric engine. 3 = nuclear. 4 = fuel tank. 5 = oxygen generator.
	//6 = radar. 7 = radar detector. 8 = sonar. 9 = hydrophone. 10 = deck gun. 11 = hull strength. 12 = detection related. 13 = fun
	int upgradeType;

	double m_secondStat;
	double m_thirdStat;

	//0 = small, 1 = medium, 2 = large, -1 = irrelevant
	int compatibleSubmarineSize;

};

class sexItem: public inventoryItem
{
public:
	sexItem();
	sexItem(string newName, string desc, string desc2, double cost, int rare, string textureName, int sexItemType);
	sexItem(vector<string> *fileContents); //this needs to very specifically be only the vector<string> generated from the file loader or else it will fail catastrophically

	int sexItemType() { return m_sexItemType; }
	string printSexItemType();

	int getPoop() { return m_poop; }
	int getCum() { return m_cum; }
	int getPiss() { return m_piss; }
	int getSlime() { return m_vaginalSlime; }

	void washItem()
	{
		m_poop = 0;
		m_cum = 0;
		m_piss = 0;
		m_vaginalSlime = 0;
	}

	sexItem& operator=(sexItem& other);

protected:
	//0 = dildo. 1 = buttplug. 2 = cock ring. 3 = cuckhold. 4 = whip. 5 = lingere.
	//6 = latex suit. 7 = leather cuit. 8 = vibrator. 9 = porn vhs. 10 = erotic novel. 11 = playboy. 12 = strap-on.
	int m_sexItemType;

	//0 = none. 1 = a little. 2 = lots.
	int m_poop;
	int m_cum;
	int m_piss;
	int m_vaginalSlime;

};

class drug: public inventoryItem
{
public:
	drug();
	drug(string newName, string desc, string desc2, double cost, int rare, string textureName, int useType, double quantity);
	drug(vector<string> *fileContents); //this needs to very specifically be only the vector<string> generated from the file loader or else it will fail catastrophically

	int useType() { return m_useType; }
	string printUseType();

	double getQuantity() { return m_quantity; }

	drug& operator=(drug& other);

protected:
	//0 = medical. 1 = recreational. 2 = both.
	int m_useType;

	//quantity per drug dose (in grams)
	double m_quantity;

};

class magicItem: public inventoryItem
{
public:
	magicItem();
	magicItem(string newName, string desc, string desc2, double cost, int rare, string textureName, double power);
	magicItem(vector<string> *fileContents); //this needs to very specifically be only the vector<string> generated from the file loader or else it will fail catastrophically

	double getPower() { return m_power; }

	magicItem& operator=(magicItem& other);

protected:
	//0 = medical. 1 = recreational. 2 = both.
	double m_power;

};

class scienceItem: public inventoryItem
{
public:
	scienceItem();
	scienceItem(string newName, string desc, string desc2, double cost, int rare, string textureName, bool bong);
	scienceItem(vector<string> *fileContents); //this needs to very specifically be only the vector<string> generated from the file loader or else it will fail catastrophically

	bool canBeUsedAsBong() { return m_canBeUsedAsBong; }

	scienceItem& operator=(scienceItem& other);

protected:
	bool m_canBeUsedAsBong;

};

class skillItem: public inventoryItem
{
public:
	skillItem();
	skillItem(vector<string> *fileContents); //this needs to very specifically be only the vector<string> generated from the file loader or else it will fail catastrophically
	//~skillItem();

	string printSkillImproved();
	int skillImproved() { return m_skillImproved; }
	int minLevel() { return m_minLevel; }
	int maxLevel() { return m_maxLevel; }

	skillItem& operator=(skillItem& other);

protected:
	//0 = seafaring. 1 = witchcraft. 2 = intelligence. 3 = sex. 4 = all
	int m_skillImproved;

	//minimum level in the relevant skill required to use this item
	int m_minLevel;

	//max level in the relevant skill required to use this item
	int m_maxLevel;

};

class craftingResource: public inventoryItem
{
public:
	craftingResource();
	craftingResource(vector<string> *fileContents); //this needs to very specifically be only the vector<string> generated from the file loader or else it will fail catastrophically
	//~craftingResource();

	bool isMetal() { return m_isMetal; }
	bool isSemiconductor() { return m_isSemiconductor; }
	bool isMagic() { return m_isMagic; }
	bool isRadioactive() { return m_isRadioactive; }
	double metallicStrength() { return m_metallicStrength; }

	int stateOfMatter() { return m_stateOfMatter; }
	string returnStateOfMatter();

	craftingResource& operator=(craftingResource& other);

protected:
	bool m_isMetal;
	double m_metallicStrength;
	bool m_isSemiconductor;
	bool m_isMagic;
	bool m_isRadioactive;

	//item's state of matter at room temp and 1 atm
	//0 = solid. 1 = liquid. 2 = gas. 3 = other (ex: fire, magic energy orb). 4 = bullshit abtract
	int m_stateOfMatter;

};

string sexDirtyToString(int dirtiness);

//<< operator overloads

ostream& operator<<(ostream& os, inventoryItem item);
ostream& operator<<(ostream& os, food item);
ostream& operator<<(ostream& os, upgradePart item);
ostream& operator<<(ostream& os, sexItem item);
ostream& operator<<(ostream& os, drug item);
ostream& operator<<(ostream& os, magicItem item);
ostream& operator<<(ostream& os, scienceItem item);
ostream& operator<<(ostream& os, skillItem item);
ostream& operator<<(ostream& os, craftingResource item);

//the random finders

inventoryItem* getRandomInventoryItem(vector<inventoryItem*> *itemDatabase, uint32_t seed = 0);

inventoryItem* getRandomJunk(vector<inventoryItem*> *itemDatabase, uint32_t seed = 0);
food* getRandomFood(vector<inventoryItem*> *itemDatabase, uint32_t seed = 0);
upgradePart* getRandomUpgradePart(vector<inventoryItem*> *itemDatabase, uint32_t seed = 0);
sexItem* getRandomSexItem(vector<inventoryItem*> *itemDatabase, uint32_t seed = 0);
drug* getRandomDrug(vector<inventoryItem*> *itemDatabase, uint32_t seed = 0);
magicItem* getRandomMagicItem(vector<inventoryItem*> *itemDatabase, uint32_t seed = 0);
scienceItem* getRandomScienceItem(vector<inventoryItem*> *itemDatabase, uint32_t seed = 0);
skillItem* getRandomSkillItem(vector<inventoryItem*> *itemDatabase, uint32_t seed = 0);
craftingResource* getRandomCraftingResource(vector<inventoryItem*> *itemDatabase, uint32_t seed = 0);

upgradePart* findUpgradePartByName(vector<inventoryItem*> *itemDatabase, string thingyname);

void printAllItemsInDatabase(vector<inventoryItem*> *itemDatabase);
void printAllItemsInDatabaseDetailed(vector<inventoryItem*> *itemDatabase);

//and finally, the loader
int loadInventoryItems(vector<inventoryItem*> *itemDatabase);

#include "inventoryItem.hpp"

#endif