#ifndef CAMPAIGN_H
#define CAMPAIGN_H

class campaign
{
	public:
		campaign();
		campaign(vector<string> fileContents);

		string getName() { return m_name; }
		string getDesc() { return m_desc; }
		faction* getFaction() { return m_faction; }
		double getFunds() { return m_funds; }
		double payRate() { return m_payRate; }
		int startingRank() { return m_startingRank; }
		submarine* startSub() { return m_startSubmarine; }

		void drawInfoCard(SDL_Renderer *ren, int posX, int posY);

		campaign& operator=(campaign& other);
	private:

		string m_name;
		string m_desc;
		faction *m_faction;
		double m_funds;
		double m_payRate;
		int m_startingRank;
		submarine *m_startSubmarine;

};

void loadCampaignFile(string filePath);

void loadAllCampaigns();

campaign* getCampaignByName(string name);

int getCampaignIndexByName(string name);

vector<campaign> *campaignDatabase = new vector<campaign>;

extern int textSizeHeader;	//12
extern int textSizeMedium; //10
extern int textSizeNormal; //8
extern int textSizeSmall; 	//6

#include "campaign.hpp"

#endif