#ifndef WORLDINFO_H
#define WORLDINFO_H

class worldInfo
{
public:
	worldInfo();
	~worldInfo();

	//date/time functions
	void setTime(double newTime) { m_time = newTime; }
	double getTime() { return m_time; }
	void setDay(int newDay) { m_day = newDay; }
	int getDay() { return m_day; }
	void setMonth(int newMonth) { m_month = newMonth; }
	int getMonth() { return m_month; }
	void setYear(int newYear) { m_year = newYear; }
	int getYear() { return m_year; }

	//return 0 = success. 1 = failure
	//dataElement is the pointer to the element containing the player info data
	int worldInfoToSaveXml(XMLElement *dataElement);

	//return 0 = success. 1 = failure
	//dataElement is the pointer to the element containing the player info data
	int worldInfoFromXml(XMLElement *dataElement, SDL_Renderer *ren);
private:
	vector<submarine*> m_npc_submarines;   //list of all submarines except the player's current one
	submarine *m_playerSubmarine;
	playerInfo *playerCampaignInfo;

	double m_time;			//time of day from 0 to 86400
	int m_day;				//day of the month
	int m_month; 			//month of the year
	int m_year;				//what year is it

	//vector<ship> m_ships;				//list of all ships in world
	//vector<aircraft> m_aircraft			//list of all aircraft in world

	vector<torpedo> m_npc_torpedos;
	//vector<projectile> m_allProjectiles;
	//vector<depthCharge> m_depthCharges;
};

#include "worldInfo.hpp"

#endif