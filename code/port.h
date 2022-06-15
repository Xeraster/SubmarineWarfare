#ifndef PORT_H
#define PORT_H

class port
{
public:
	port();

	//ports are loaded from xml files
	port(XMLElement *portElement);

	//getters and setters
	string getPortName() const { return m_portName; }
	faction* owningFaction() const { return m_owningFaction; } 
	void changeOwningFaction(faction *newOwner);
	double posX() const { return m_posX; }
	double posY() const { return m_posY; }
	bool hasShipyard() const { return m_hasShipyard; }
	bool hasAirport() const { return m_hasAirport; }
	double navalTraffic() const { return m_navalTraffic; }
	double airTraffic() const { return m_airTraffic; }
	double submarineTraffic() const { return m_submarineTraffic; }
	double merchantTraffic() const { return m_merchantTraffic; }
	int getPopulation() const { return m_population; }

	void drawPort(SDL_Renderer *ren, int posX, int posY, double zoom);

	int portFactionSide();

	color getColorBasedOnFaction();

	port& operator=(port& other);

private:
	string m_portName;
	faction *m_owningFaction;
	double m_posX;
	double m_posY;
	bool m_hasShipyard;
	bool m_hasAirport;
	double m_navalTraffic;
	double m_airTraffic;
	double m_submarineTraffic;
	double m_merchantTraffic;
	int m_population;

};

#include "port.hpp"

#endif