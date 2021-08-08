#ifndef PLAYERINFO_H
#define PLAYERINFO_H

struct awardData
{
	award *listedAward;
	int amount;
};

class playerInfo
{
	public:
		playerInfo();
		playerInfo(campaign *newCampaign, string captainName, string shipName, SDL_Renderer *ren);
		~playerInfo();

		string playerName() { return m_playerName; }
		int rank() { return m_rank; }
		double money() { return m_budget; }
		void setMoney(double amount) { m_budget = amount; }

		double payRate() { return m_payRate; }
		double tonnageSunk() { return m_tonnageSunk; }
		faction* getFaction() { return m_faction; }
		campaign* getCampaign() { return m_startingCampaign; }
		submarine& getSubmarine(int index) { return m_submarines.at(index); }
		submarine* playerEquippedSubmarine() { return m_selectedSubmarine; }
		int ownedSubmarines() { return m_submarines.size(); }
		bool getInSubmarine(int index);

		submarineCompartment* barracks() { return &m_barracks; }

		void generateEmployableCrew(int quantity);
		crewMember& getEmployableCrew(int index) { return m_recruitableEmployees.at(index); }
		crewMember& getEmployedCrew(int index) { return m_playerEmployees.at(index); }
		int numEmployableCrew() { return m_recruitableEmployees.size(); }
		int numEmployedCrew();

		void setInfoCardCrewPointer(crewMember *crew) { m_infoCardCrew = crew; }
		crewMember* getInfoCardCrewPointer() { return m_infoCardCrew; }
		void hireCrew(int indexNum);

		//return the amount of qualifications that the player has been given to hand out
		//Am I doing a shit job of describing what these are? Either play Silent Hunter 3 or watch a SH3 let's play (I recommend wolfpack345) to see what I'm talking about
		int getQualificationCount() { return m_qualsToHandout; }
		void setQualificationCount(int num) { m_qualsToHandout = num; }
		void decrementQualifications() { m_qualsToHandout--; }

		awardData* getAwardData(int index);

		int numLoadedAwards() { return assignableAwardInfo.size(); }

		void setAwards(int index, int number)
		{
			if (index > assignableAwardInfo.size()) return void();
			else assignableAwardInfo.at(index).amount = number;
		}

		int getAwardCount(int index) 
		{ 
			if (index > assignableAwardInfo.size()) return 0;
			else return assignableAwardInfo.at(index).amount; 
		}

		void decrementAward(award *award);

		//draw the player's barrack box
		//this is basically a place to temporarily put crew if player wants to switch to a smaller submarine for a few missions or something
		void drawPlayerBarrack(SDL_Renderer *ren, int posX, int posY, int sizeX, int mouseX, int mouseY, Uint32 lastMouse, crewMember **selected);

		//I promise, after I get the crew barracks feature fully working, no more shitty hack fuck ass shits
		bool putCrewInBarrack(crewMember* person, int posX, int posY, int screenX);

		bool isInsideBarracksBox(int x, int y);

		void findAndEraseDuplicateCrew(crewMember* person, int excludeSlot);

		void findAndReplaceDuplicateCrew(crewMember* person, int excludeSlot, crewMember* replacement);

		bool buySubmarine(SDL_Renderer *ren, submarine *subPointer, string shipName);

		bool canBuySubmarine(submarine *subPointer);

		//moves crew from barracks to the current submarine
		bool barracksToSubmarine();

		//void getBarracksBoxSize(int *px, int *py, int *sx, int *sy)

		/*
		adds a torpedo to the given submarine
		takes the pointer to the torpedo type, makes a new torpedo, sets it equal in every way to the class pointed to by the pointer
		then adds it to the player's vector of owned torpedos. It then adds the pointer of the torpedo to a random slot on the submarine
		*/
		bool addTorpedoToSubmarine(torpedo *torpedoType);

		bool buyTorpedo(torpedo *torpedoType);

		void sellTorpedo(torpedo *pointer);

		//return 0 = success. 1 = not enough money. 2 = submarine already contains the exact same part. 3 = submarine not compatible with part. 4 = provided part was null
		int applyUpgradeToSubmarine(upgradePart *upgrade);

		//needs to be public variable for garbage collection routines
		//where all torpedos the player owns are stored
		//vector<torpedo> *m_playerTorpedos = new vector<torpedo>;
		list<torpedo> *m_playerTorpedos = new list<torpedo>;


	private:

		string m_playerName;

		//only for stats purposes. Game data will not be taken from the campaign pointer alone since stuff changes
		campaign *m_startingCampaign;

		//each vector needs to be a copy and not a pointer since the player will be able to modify their ship
		//it's also a vector since the player should be able to own "a garage" of submarines
		vector<submarine> m_submarines;

		//any crew members the player has recruited/hired/is in player's payroll
		vector<crewMember> m_playerEmployees;

		//any crew members the player can recruit
		vector<crewMember> m_recruitableEmployees;

		crewMember *m_infoCardCrew;

		//0 = prisoner. 1 = entertainer lvl 1. 2 = entertainer lvl 2. 3 = recruit. 4 = apprentice. 5 = seaman
		//6 = pettyofficer 3rd class. 7 = pettyofficer 2nd class. 8 = pettyofficer 1st class. 9 = chief pettyofficer. 10 = senior chief pettyofficer. 11 = master chief pettyofficer
		//12 = command master chief pettyofficer. 13 = fleet master chief pettyofficer. 14 = master chief pettyofficer of the navy
		//typically, the rank a player starts with shouldn't be lower than 9
		int m_rank;

		//how much money the player has
		double m_budget;

		//how much money the admiralty pays the player per ton of sunk shipping
		double m_payRate;

		//the player's faction
		faction *m_faction;

		double m_tonnageSunk;

		int m_selectedSubmarineIndex;

		//number of qualifications the player has been given to hand out
		int m_qualsToHandout;

		//vector that keeps track of how many awards of each type the player is able to give out
		vector<awardData> assignableAwardInfo;

		//the place where the player can store crew who won't be participating on the next mission
		submarineCompartment m_barracks;
		int m_barracksPx;
		int m_barracksPy;
		int m_barracksSx;
		int m_barracksSy;

		submarine *m_selectedSubmarine;
};


extern bool deleteTorpedosNotify;

extern crewNameGenerator *crewNameGeneratorObject;

#include "playerInfo.hpp"

#endif