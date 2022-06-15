port :: port()
{

}

port :: port(XMLElement *portElement)
{
    m_portName = portElement->FirstChildElement("name")->GetText();
    if (getFactionByName(portElement->FirstChildElement("owning_faction")->GetText()) == nullptr) cout << "faction = nullptr. fuck" << endl;
    m_owningFaction = getFactionByName(portElement->FirstChildElement("owning_faction")->GetText());
    m_posX = atof(portElement->FirstChildElement("posx")->GetText());
    m_posY = atof(portElement->FirstChildElement("posy")->GetText());
    m_navalTraffic = atof(portElement->FirstChildElement("naval_traffic")->GetText());
    m_airTraffic = atof(portElement->FirstChildElement("air_traffic")->GetText());
    m_submarineTraffic = atof(portElement->FirstChildElement("submarine_traffic")->GetText());
    m_merchantTraffic = atof(portElement->FirstChildElement("merchant_traffic")->GetText());
    //boolean data values
    m_hasShipyard = stringToBool(portElement->FirstChildElement("has_shipyard")->GetText());
    m_hasAirport = stringToBool(portElement->FirstChildElement("has_airport")->GetText());
	m_population = atoi(portElement->FirstChildElement("population")->GetText());
}

void port :: changeOwningFaction(faction *newOwner)
{
    m_owningFaction = newOwner;
    return void();
}

void port :: drawPort(SDL_Renderer *ren, int posX, int posY, double zoom)
{
    int circleSize = 6;
    int textSize = 7 * gscreenx/800; 
    if (zoom < 1.0f && zoom > 0.17f)
    {
        textSize = 6 * gscreenx/800; 
    }
    else if (zoom <= 0.8f && zoom > 0.17f)
    {
        textSize = 5 * gscreenx/800;
    }
    else if (zoom <= 0.17f && zoom > 0.10f)
    {
        textSize = 4 * gscreenx/800;
    }
    else if (zoom <= 0.10f)
    {
        textSize = 1 * gscreenx/800;
    }


    drawCircle(ren, getColorBasedOnFaction(), 3, posX, posY, true);
    drawText(ren, textSize, getColorBasedOnFaction(), m_portName, posX + 10, posY);
    return void();
}

int port :: portFactionSide()
{
    return m_owningFaction->team();
}

color port :: getColorBasedOnFaction()
{
    //friendly is blue
    if (portFactionSide() == 0 || portFactionSide() == 1) return color(0,0,255);

    //enemy is red
    if (portFactionSide() == 3 || portFactionSide() == 4) return color(255,0,0);

    //neutral is green
    else return color(0,255,0);
}

port& port :: operator=(port& other)
{
    m_portName = other.getPortName();
    m_owningFaction = other.owningFaction();
    m_posX = other.posX();
    m_posY = other.posY();
    m_hasShipyard = other.hasShipyard();
    m_hasAirport = other.hasAirport();
    m_navalTraffic = other.navalTraffic();
    m_airTraffic = other.airTraffic();
    m_merchantTraffic = other.merchantTraffic();
    m_submarineTraffic = other.submarineTraffic();
    m_population = other.getPopulation();

    return *this;
}