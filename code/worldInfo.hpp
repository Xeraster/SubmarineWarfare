worldInfo :: worldInfo()
{

}

//set up a world from given playerInfo and improvise from there
worldInfo :: worldInfo(playerInfo *input, string mapName, SDL_Renderer *ren, SDL_Window *win)
{
	portsInWorld.clear();
	string heightmapName = "error";
	loadMapData("Data/maps/" + mapName, &heightmapName);
	cout << "loaded " << portsInWorld.size() << " ports into the world" << endl;
	//if (m_mapTex != nullptr) SDL_DestroyTexture(m_mapTex); //this started causing crashes for no goddamn reason after I added port loading. Makes no fucking goddamn sense. Guess that's yet another impossible to avoid memory leak that nothing can be done about. Fucking bullshit
	//temporarily load the texture as an SDL texture. This isn't fast enough, however
	m_mapTex = loadTextureToRam_TA("Textures/Heightmaps/"+heightmapName, ren, win);
	if (m_mapTex == nullptr)
	{
		cout << "could not find heightmap named " << heightmapName << ". Loading a bigass flat empty ocean map instead." << endl;
	}


	//get size of texture because this is important
	SDL_QueryTexture(m_mapTex, NULL, NULL, &m_mapSizeX, &m_mapSizeY);
	int numPixels = (m_mapSizeX * m_mapSizeY);
	cout << "heightmap has " << numPixels << " pixels in it and is " << m_mapSizeX << "x" << m_mapSizeY << " pixels in size" << endl;

	//obtain the raw data of the texture and put it into a bytefield
	//might as well do more calculations now during loading so that less calculations can be done per frame later on
	byte * bytes = nullptr;
	int pitch = 0;
	SDL_LockTexture(m_mapTex, nullptr, reinterpret_cast<void **>(&bytes), &pitch);

	//now, add each byte of the texture into the byte vector
	m_heightMap.clear();
	for (int px = 0; px < numPixels; px++)
	{
		int byteNum = px * 4;
		//color newPixel;
		//newPixel.setRed((int)bytes[byteNum+2]);
		//newPixel.setGreen((int)bytes[byteNum+1]);
		//newPixel.setBlue((int)bytes[byteNum]);
		//newPixel.setAlpha((int)bytes[byteNum+3]);
		//rawTexture.push_back(newPixel);
		m_heightMap.push_back((Uint8)bytes[byteNum]);
		if (bytes[byteNum] < (byte)150)
		{
			bytes[byteNum+1]=(byte)(150*(int)bytes[byteNum]/255);
			if ((int)bytes[byteNum] < 50) bytes[byteNum] = (byte)50;
			bytes[byteNum] = (byte)((int)bytes[byteNum] + 100);
			bytes[byteNum+2]=(byte)10;
			bytes[byteNum+3]=(byte)0;
		}
		else
		{
			bytes[byteNum]=(byte)0;
			bytes[byteNum+2]=(byte)0;
			bytes[byteNum+3]=(byte)0;
		}
	}
	cout << "done loading world heightmap" << endl;

	SDL_UnlockTexture(m_mapTex);


	m_playerCampaignInfo = input;
	m_playerSubmarine = input->playerEquippedSubmarine();
	m_initialized = true;

	//initialize the gui buttons
	waypointButton = button("xxx", color(255,255,255),0,250,textSizeNormal);
	waypointButton.setBackgroundColor(color(0,0,0,200));
	waypointButton.setBorder(true);

	markerButton = button("xxx", color(255,255,255),0,waypointButton.posY() - waypointButton.sizeY(),textSizeNormal);
	markerButton.setBackgroundColor(color(0,0,0,200));
	markerButton.setBorder(true);

	protractorButton = button("xxx", color(255,255,255),0,markerButton.posY() - markerButton.sizeY(),textSizeNormal);
	protractorButton.setBackgroundColor(color(0,0,0,200));
	protractorButton.setBorder(true);

	rulerButton = button("xxx", color(255,255,255),0,protractorButton.posY() - protractorButton.sizeY(),textSizeNormal);
	rulerButton.setBackgroundColor(color(0,0,0,200));
	rulerButton.setBorder(true);

	compassButton = button("xxx", color(255,255,255),0,rulerButton.posY() - rulerButton.sizeY(),textSizeNormal);
	compassButton.setBackgroundColor(color(0,0,0,200));
	compassButton.setBorder(true);

	eraserButton = button("xxx", color(255,255,255),0,compassButton.posY() - compassButton.sizeY(),textSizeNormal);
	eraserButton.setBackgroundColor(color(0,0,0,200));
	eraserButton.setBorder(true);
}

//loads the map data from a corresponding map file in data/maps/. passes heightmap name by reference and then loads ports by reference
int worldInfo :: loadMapData(string mapName, string *heightmapName)
{
	//initialize the XML document
	//this is an important step that doesn't happen very often due to the modular fashion of the saving and loading structure. Make a mental note of this declaration's location in case you need an example later as this is one of the few instances in the code where this happens
	XMLDocument doc;
	doc.LoadFile(mapName.c_str());

	if (doc.RootElement() == nullptr)
	{
		cout << "warning: a map xml file with no root element was loaded" << endl;
		return 1;
	}

	XMLElement *rootElement = doc.RootElement();

	string temp = rootElement->FirstChildElement("recommended_heightmap")->GetText();
	cout << "heightmap = " << temp << endl;
	*heightmapName = temp; 	//that's kind of stupid that it won't work without making a temp value. Glad this isn't happening in the 3d renderer.  This type of thing in just the wrong rasterizing routine would costs lots of fps

	XMLElement *portListElement = rootElement->FirstChildElement("ports")->FirstChildElement("port");
		while (portListElement != nullptr)
		{
			//create port from node
			port tempPort(portListElement);
			cout << tempPort.getPortName() << endl;
			portsInWorld.push_back(tempPort);
			//set pointer to next element in preparation for next iteration
			portListElement = portListElement->NextSiblingElement("port");
		}

		return 0;

}

bool worldInfo :: drawMap(SDL_Renderer *ren, double zoom, double *posX, double *posY, int mouseX, int mouseY, Uint32 lastMouse)
{
	if (!isInUtilityMode())
	{
		if (mapDragging)
		{
			*posX += (mouseX - mouseBeforeX)/zoom;
			*posY += (mouseY - mouseBeforeY)/zoom;
			cout << "now map pos = " << *posX << "," << *posY << endl;
		}

		if (lastMouse == SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			mapDragging = true;
			mouseBeforeX = mouseX;
			mouseBeforeY = mouseY;
		}
		else
		{
			mapDragging = false;
		}	
	}
	//the stuff above this line used to be in the menus but I moved it to the world object because that offers greater versatility
	if (!m_initialized)
	{
		cout << "error: tried to draw world map but a valid world isn't loaded" << endl;
		return false;
	}

	renderTextureEx(m_mapTex, ren, (gscreenx/2)-(m_mapSizeX/2*zoom)+*posX*zoom, ((gscreeny/2)-m_mapSizeY/2*zoom)+*posY*zoom, (m_mapSizeX)*zoom, (m_mapSizeY)*zoom, 0);

	waypointButton.draw(ren, mouseX, mouseY, lastMouse, waypointButtonTexture);

	if (markerButton.draw(ren, mouseX, mouseY, lastMouse, markerButtonTexture) && newClick)
	{
		markerMode = true;
		mapDragging = false;
		newClick = false;
		cout << "marker mode = true";
	}
	if (isInUtilityMode() && lastMouse == SDL_BUTTON(SDL_BUTTON_RIGHT))
	{
		newClick = false;
		markerMode = false;
		rulerMode = false;
		protractorMode = false;
		compassMode = false;
		eraseMode = false;
		cout << "marker mode disengaged" << endl;
	}
	if (markerMode && lastMouse == SDL_BUTTON(SDL_BUTTON_LEFT) && newClick)
	{
		newClick = false;
		//place marker on map at specified location
		markerPoint tempPoint(mapToWorldX(zoom, *posX, mouseX), mapToWorldY(zoom, *posY, mouseY), points.size());
		//cout << "placing point at " << mapToWorldX(zoom, *posX, mouseX) << ", " <<  mapToWorldY(zoom, *posY, mouseY) << endl;
		//cout << "draw x" << worldToMapX(zoom, *posX, tempPoint.posX()*m_mapScale) << endl;
		points.push_back(tempPoint);
		//cout << "map to world = " << mapToWorldX(zoom, *posX, mouseX) << ", " << mapToWorldY(zoom, *posY, mouseY) << endl;
		//cout << "map to world X = " << mapToWorldX(zoom, *posX, mouseX) << endl;
	}

	if(rulerButton.draw(ren, mouseX, mouseY, lastMouse, rulerButtonTexture) && newClick)
	{
		rulerMode = true;
		mapDragging = false;
		newClick = false;
		cout << "in ruler mode" << endl;
	}

	if (rulerMode)
	{
		rulerModeWorker(ren, mouseX, mouseY, lastMouse, zoom, *posX, *posY);
	}

	if (protractorButton.draw(ren, mouseX, mouseY, lastMouse, protractorButtonTexture) && newClick)
	{
		protractorMode = true;
		mapDragging = false;
		newClick = false;
		cout << "in protractor mode" << endl;
	}

	if (protractorMode)
	{
		protractorModeWorker(ren, mouseX, mouseY, lastMouse, zoom, *posX, *posY);
	}

	if (compassButton.draw(ren, mouseX, mouseY, lastMouse, compassButtonTexture))
	{
		compassMode = true;
		mapDragging = false;
		newClick = false;
		cout << "in circle compass mode" << endl;
	}

	if (compassMode)
	{
		compassModeWorker(ren, mouseX, mouseY, lastMouse, zoom, *posX, *posY);
	}

	if (eraserButton.draw(ren, mouseX, mouseY, lastMouse, eraserButtonTexture))
	{
		eraseMode = true;
		mapDragging = false;
		newClick = false;
		cout << "in erase mode" << endl;
	}
	//erase mode doesn't have an erase worker since it works differently from the other tools

	/*if (eraseMode && lastMouse == SDL_BUTTON(SDL_BUTTON_RIGHT))
	{
		newClick = false;
	}*/

	//draw eack of the placed markers on map
	for (int m = 0; m < points.size(); m++)
	{
		int drawX = worldToMapX(zoom, *posX, points.at(m).posX()*m_mapScale, m_mapSizeX, m_mapScale);
		int drawY = worldToMapY(zoom, *posY, points.at(m).posY()*m_mapScale, m_mapSizeY, m_mapScale);
		//cout << "draw x" << drawX << endl;
		if (points.at(m).draw(ren, mouseX, mouseY, lastMouse, drawX, drawY, eraseMode))
		{
			//if mosue cursor is over object and erase mode is enabled, do an erase if the proper clicking conditions are met
			if (lastMouse == SDL_BUTTON(SDL_BUTTON_LEFT) && newClick)
			{
				newClick = true;
				points.erase(points.cbegin() + m);
			}
		}
	}

	//draw eack of the placed ruler lines on map
	for (int m = 0; m < lines.size(); m++)
	{
		//int drawX = worldToMapX(zoom, *posX, points.at(m).posX()*m_mapScale, m_mapSizeX, m_mapScale);
		//int drawY = worldToMapY(zoom, *posY, points.at(m).posY()*m_mapScale, m_mapSizeY, m_mapScale);
		//cout << "draw x" << drawX << endl;
		if (lines.at(m).draw(ren, mouseX, mouseY, lastMouse, zoom, *posX, *posY, m_mapScale, m_mapSizeX, m_mapSizeY, false, eraseMode))
		{
			//if mosue cursor is over object and erase mode is enabled, do an erase if the proper clicking conditions are met
			if (lastMouse == SDL_BUTTON(SDL_BUTTON_LEFT) && newClick)
			{
				newClick = true;
				lines.erase(lines.cbegin() + m);
			}
		}
		//cout << "drawing a line" << endl;
	}

	//draw each of the placed protractor angles on the map
	for (int p = 0; p < angles.size(); p++)
	{
		if (angles.at(p).draw(ren, mouseX, mouseY, lastMouse, zoom, *posX, *posY, m_mapScale, m_mapSizeX, m_mapSizeY, eraseMode))
		{
			if (lastMouse == SDL_BUTTON(SDL_BUTTON_LEFT) && newClick)
			{
				newClick = true;
				angles.erase(angles.cbegin() + p);
			}
		}
	}

	//draw each of the placed compass circles on the map
	for (int c = 0; c < circles.size(); c++)
	{
		if (circles.at(c).draw(ren, mouseX, mouseY, lastMouse, zoom, *posX, *posY, m_mapScale, m_mapSizeX, m_mapSizeY, eraseMode))
		{
			if (lastMouse == SDL_BUTTON(SDL_BUTTON_LEFT) && newClick)
			{
				newClick = true;
				circles.erase(circles.cbegin() + c);
			}
		}
	}

	//draw the world to map space location of the player's submarine
	double playerX = m_playerSubmarine->worldPosX;
	double playerY = m_playerSubmarine->worldPosZ;
	renderTextureEx(unknownSubIcon, ren, worldToMapX(zoom, *posX, playerX, m_mapSizeX, m_mapScale)-8, worldToMapY(zoom, *posY, playerY, m_mapSizeY, m_mapScale)-8, 16, 16, 0);

	for (int s = 0; s < m_ships.size(); s++)
	{
		drawShipOnMap(ren, zoom, *posX, *posY, &m_ships.at(s));
	}

	//draw ports on map
	for (int p = 0; p < portsInWorld.size(); p++)
	{
		int drawX = worldToMapX(zoom, *posX, portsInWorld.at(p).posX()*m_mapScale, m_mapSizeX, m_mapScale);
		int drawY = worldToMapY(zoom, *posY, portsInWorld.at(p).posY()*m_mapScale, m_mapSizeY, m_mapScale);
		//if (drawX < gscreenx && drawX > 0 && drawY < gscreeny && drawY > 0)
		//{
			//cout << "drawx = " << drawX << "drawy = " << drawY << endl; 
			portsInWorld.at(p).drawPort(ren, drawX, drawY, zoom);
		//}
	}

	if ((lastMouse == SDL_BUTTON(SDL_BUTTON_RIGHT) || lastMouse == SDL_BUTTON(SDL_BUTTON_LEFT)) && !holdingClick)
	{
		holdingClick = true;
	}
	else if (lastMouse != SDL_BUTTON(SDL_BUTTON_RIGHT) && lastMouse != SDL_BUTTON(SDL_BUTTON_LEFT) && holdingClick)
	{
		holdingClick = false;
		newClick = true;
	}

	return true;
}

void worldInfo :: drawShipOnMap(SDL_Renderer *ren, double zoom, double playerX, double playerY, ship *whichShip)
{
	//this draws the icon on the map
	double x1 = worldToMapX(zoom, playerX, whichShip->worldPosX, m_mapSizeX, m_mapScale);
	double y1 = worldToMapY(zoom, playerY, whichShip->worldPosZ, m_mapSizeY, m_mapScale);
	renderTextureEx(unknownShipIcon, ren, x1-8, y1-8, 16, 16, 0);
	//now, the draw the indicator line as to which direction it's going
	double x2 = sin(whichShip->worldRotY * (3.141592/180)) * (whichShip->getSpeed());
	double y2 = cos(whichShip->worldRotY * (3.141592/180)) * (whichShip->getSpeed()) * -1;
	drawLine(ren, color(200,200,200), x1, y1, x1-x2, y1-y2);

	return void();
}

/*double worldInfo :: worldToMapX(double zoom, double mapX, double inX)
{
	double centerX = (gscreenx/2)+(m_mapSizeX/2)*zoom+mapX*zoom;

	return centerX - (((inX/m_mapScale)+m_mapSizeX/2))*zoom;
}

double worldInfo :: worldToMapY(double zoom, double mapY, double inY)
{
	double centerY = ((gscreeny/2)+m_mapSizeY/2*zoom)+mapY*zoom;

	return centerY - (((inY/m_mapScale) + m_mapSizeY/2)*zoom);
}

double worldInfo :: mapToWorldX(double zoom, double posX, double mapX)
{
	return (posX)+((gscreenx/2)-mapX)*(1/zoom);
}

double worldInfo :: mapToWorldY(double zoom, double posY, double mapY)
{
	return (posY)+((gscreeny/2)-mapY)*(1/zoom);
}*/

bool worldInfo :: isInUtilityMode()
{
	if (markerMode || rulerMode || protractorMode || compassMode || eraseMode)
	{
		return true;
	}
	else
	{
		return false;
	}

}

void worldInfo :: rulerModeWorker(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastMouse, double zoom, double mapCenterX, double mapCenterY)
{
	if (lastMouse == SDL_BUTTON(SDL_BUTTON_LEFT) && newClick)
	{
		newClick = false;
		//if there are 0 lines, or the most recent line is complete, place a new line
		if (lines.size() == 0 || lines.back().secondPointPlaced())
		{
			rulerLine tempLine(mapToWorldX(zoom, mapCenterX, mouseX), mapToWorldY(zoom, mapCenterY, mouseY));
			lines.push_back(tempLine);
			cout << "created new ruler line " << endl;
		}

		//if the most recent line does not have a second point, complete that line instead of making a new one
		else if (!lines.back().secondPointPlaced())
		{
			lines.back().setSecondPoint(mapToWorldX(zoom, mapCenterX, mouseX), mapToWorldY(zoom, mapCenterY, mouseY));
			cout << "finished the most recently created ruler line " << endl;
		}
	}

	return void();
}

void worldInfo :: protractorModeWorker(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastMouse, double zoom, double mapCenterX, double mapCenterY)
{
	if (lastMouse == SDL_BUTTON(SDL_BUTTON_LEFT) && newClick)
	{
		newClick = false;

		//if there are 0 angles drawn OR the most recently placed angles is complete, create a whole new one
		if (angles.size() == 0 || angles.back().secondLinePlaced())
		{
			protractorAngle tempAngle(mapToWorldX(zoom, mapCenterX, mouseX), mapToWorldY(zoom, mapCenterY, mouseY));
			angles.push_back(tempAngle);
			cout << "created new angle" << endl;
		}

		//if the first line has had both of its points placed but the second line has not
		else if (angles.back().getFirstLine().secondPointPlaced() && !angles.back().getSecondLine().secondPointPlaced())
		{
			angles.back().setSecondLineSecondPoint(mapToWorldX(zoom, mapCenterX, mouseX), mapToWorldY(zoom, mapCenterY, mouseY));
			cout << "placed final point of second line " << endl;
		}

		//if the first line has not had all of its points placed (which also means the second line has none of its points placed)
		else if (!angles.back().getFirstLine().secondPointPlaced())
		{
			angles.back().setFirstLineSecondPoint(mapToWorldX(zoom, mapCenterX, mouseX), mapToWorldY(zoom, mapCenterY, mouseY));
			cout << "placed final point of first line " << endl;
		}
	}

	return void();
}

void worldInfo :: compassModeWorker(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastMouse, double zoom, double mapCenterX, double mapCenterY)
{
	//basically just the same as the ruler mode worker except with the circle
	if (lastMouse == SDL_BUTTON(SDL_BUTTON_LEFT) && newClick)
	{
		newClick = false;

		//if there are 0 compass circles, or the most recent line is complete, place a new line
		if (circles.size() == 0 || circles.back().m_theLine.secondPointPlaced())
		{
			compassCircle tempCircle(mapToWorldX(zoom, mapCenterX, mouseX), mapToWorldY(zoom, mapCenterY, mouseY));
			circles.push_back(tempCircle);
			cout << "created new compass circle " << endl;
		}

		//if the most recent line does not have a second point, complete that line instead of making a new one
		else if (!circles.back().getLine().secondPointPlaced())
		{
			circles.back().m_theLine.setSecondPoint(mapToWorldX(zoom, mapCenterX, mouseX), mapToWorldY(zoom, mapCenterY, mouseY));
			cout << "finished the most recently created compass circle " << endl;
		}
	}

	return void();
}

worldInfo& worldInfo :: operator=(const worldInfo& other)
{
	m_time = other.getTime();
	m_day = other.getDay();
	m_month = other.getMonth();
	m_year = other.getYear();
	m_initialized = other.init();
	m_mapSizeX = other.mapSizeX();
	m_mapSizeY = other.mapSizeY();

	m_playerSubmarine = other.m_playerSubmarine;
	m_playerCampaignInfo = other.m_playerCampaignInfo;

	m_mapTex = other.getMapTex();

	m_heightMap.clear();

	for (int i = 0; i < other.m_heightMap.size(); i++)
	{
		m_heightMap.push_back(other.m_heightMap.at(i));
	}

	portsInWorld.clear();
	for (int p = 0; p < other.numWorldPorts(); p++)
	{
		portsInWorld.push_back(other.getPort(p));
	}

	//copy the points to the new map object
	points.clear();
	for (int i = 0; i < points.size(); i++)
	{
		points.push_back(other.points.at(i));
	}

	//copy the ruler lines to the new map object
	lines.clear();
	for (int i = 0; i < lines.size(); i++)
	{
		lines.push_back(other.lines.at(i));
	}

	//copy the protractor angles to the new map object
	angles.clear();
	for (int i = 0; i < angles.size(); i++)
	{
		angles.push_back(other.angles.at(i));
	}

	//copy the circle compass objects to the new map object
	circles.clear();
	for (int c = 0; c < circles.size(); c++)
	{
		circles.push_back(other.circles.at(c));
	}

	waypointButton = other.waypointButton;
	markerButton = other.markerButton;
	protractorButton = other.protractorButton;
	rulerButton = other.rulerButton;
	compassButton = other.compassButton;
	eraserButton = other.eraserButton;

	return *this;
}

worldInfo :: ~worldInfo()
{

}

//prepares data to be rendered for frame and sends prepared data to the 3d renderer
void worldInfo :: prepareToRenderFrame(SDL_Renderer *ren, SDL_Window *win, olcEngine3D *engineRender)
{
	//on every frame, erase the mesh pointer buffer and refill it with whatever stuff needs to be drawn
	game3dRenderer.meshesToRender.clear();

	game3dRenderer.meshesToRender.push_back(&m_ocean);
	game3dRenderer.meshesToRender.push_back(&m_terrain);

	//copy each ship into render buffer
	for (int i = 0; i < m_ships.size(); i++)
	{
		game3dRenderer.meshesToRender.push_back(&m_ships.at(i).m_shipMesh);
	}
}

void worldInfo :: spawnShip(string shipClass, double posX, double posY, double heading)
{
	ship newShip = *getShipByName(shipClass);
	newShip.setPosX(posX);
	newShip.setPosZ(posY);
	//newShip.setPosX(5);
	//newShip.setPosY(0);
	newShip.setRotY(heading); //in a 3d space, Y axis is up/down
	m_ships.push_back(newShip);
}

double worldInfo :: heightAtCoords(int posX, int posY)
{
	int num = (posX+(m_mapSizeX/2)) + ((posY+(m_mapSizeX/2))*m_mapSizeX);
	//int num = (texSizeX - x) + (y*texSizeX);
	if (num > m_heightMap.size()-1) 
	{
		cout << "error: position was off bounds of heightmap array at array position " << num << " at pos " << posX << ", " << posY << endl;
		num = num % m_heightMap.size(); //no crashing. I don't care if this condition isn't supposed to ever happen. Fuck crashes.
	}
	//return rawTexture.at(rawTexture.size() - num - 1); 	//for some reason it renders the textures "flipped vertically" unless you do this (instead of the line under it)
	//return m_heightMap.at(m_heightMap.size() - num - 1);
	return m_heightMap.at(num);
}

void worldInfo :: generateNearTerrain(double posX, double posY, int distance)
{
		m_terrain.tris.clear();
		m_terrain.rawTexture.clear();
		m_terrain.posX = posX;
		m_terrain.posZ = posY;
		m_terrain.rotY = 180;
		m_terrain.posY = -150.0f;
		int mult = 20;
		for (int x = posX - distance; x < posX + distance; x++)
		{
			for (int y = posY - distance; y < posY + distance; y++)
			{
				triangle newTriangle;
				newTriangle.p[0].x = (x)*mult;
				newTriangle.p[0].z = (y+1)*mult;
				newTriangle.p[0].y = heightAtCoords(x,y+1);
				//newTriangle.p[0].y = 0;
				newTriangle.p[1].x = (x+1)*mult;
				newTriangle.p[1].z = (y)*mult;
				newTriangle.p[1].y = heightAtCoords(x+1,y);
				//newTriangle.p[1].y = 0;
				newTriangle.p[2].x = (x)*mult;
				newTriangle.p[2].z = (y)*mult;
				newTriangle.p[2].y = heightAtCoords(x,y);
				//newTriangle.p[2].y = 0;

				newTriangle.t[0].u = 0;
				newTriangle.t[0].v = 0;
				newTriangle.t[1].u = 0;
				newTriangle.t[1].v = 0;
				newTriangle.t[2].u = 0;
				newTriangle.t[2].v = 0;
				m_terrain.tris.push_back(newTriangle);

				triangle newTriangle2;
				newTriangle2.p[0].x = (x+1)*mult;
				newTriangle2.p[0].z = (y+1)*mult;
				newTriangle2.p[0].y = heightAtCoords(x+1,y+1);
				//newTriangle2.p[0].y = 0;

				newTriangle2.p[1].x = (x+1)*mult;
				newTriangle2.p[1].z = (y)*mult;
				newTriangle2.p[1].y = heightAtCoords(x+1,y);
				//newTriangle2.p[1].y = 0;
				newTriangle2.p[2].x = (x)*mult;
				newTriangle2.p[2].z = (y+1)*mult;
				newTriangle2.p[2].y = heightAtCoords(x,y+1);
				//newTriangle2.p[2].y = 0;

				newTriangle2.t[0].u = 0;
				newTriangle2.t[0].v = 0;
				newTriangle2.t[1].u = 0;
				newTriangle2.t[1].v = 0;
				newTriangle2.t[2].u = 0;
				newTriangle2.t[2].v = 0;

				m_terrain.tris.push_back(newTriangle2);

			}
		}

		m_terrain.texSizeX = 1;
		m_terrain.texSizeY = 0;
		m_terrain.rawTexture.push_back(color(10,100,0));
}

void worldInfo :: generateNearOcean(double posX, double posY, int distance)
{
	m_ocean.tris.clear();
	m_ocean.rawTexture.clear();
	m_ocean.posX = 0.0f;
	m_ocean.posZ = 0.0f;
	m_ocean.posY = 0.0f;
	int mult = 100;
	for (int x = distance * -1; x < distance; x++)
	{
		for (int y = distance * -1; y < distance; y++)
		{
			triangle newTriangle;
			newTriangle.p[0].x = (x)*mult;
			newTriangle.p[0].z = (y+1)*mult;
			newTriangle.p[0].y = 0;
			newTriangle.p[1].x = (x+1)*mult;
			newTriangle.p[1].z = (y)*mult;
			newTriangle.p[1].y = 0;
			newTriangle.p[2].x = (x)*mult;
			newTriangle.p[2].z = (y)*mult;
			newTriangle.p[2].y = 0;

			newTriangle.t[0].u = 0;
			newTriangle.t[0].v = 0;
			newTriangle.t[1].u = 0;
			newTriangle.t[1].v = 0;
			newTriangle.t[2].u = 0;
			newTriangle.t[2].v = 0;
			m_ocean.tris.push_back(newTriangle);

			triangle newTriangle2;
			newTriangle2.p[0].x = (x+1)*mult;
			newTriangle2.p[0].z = (y+1)*mult;
			newTriangle2.p[0].y = 0;
			newTriangle2.p[1].x = (x+1)*mult;
			newTriangle2.p[1].z = (y)*mult;
			newTriangle2.p[1].y = 0;
			newTriangle2.p[2].x = (x)*mult;
			newTriangle2.p[2].z = (y+1)*mult;
			newTriangle2.p[2].y = 0;

			newTriangle2.t[0].u = 0;
			newTriangle2.t[0].v = 0;
			newTriangle2.t[1].u = 0;
			newTriangle2.t[1].v = 0;
			newTriangle2.t[2].u = 0;
			newTriangle2.t[2].v = 0;

			m_ocean.tris.push_back(newTriangle2);

			m_ocean.texSizeX = 0;
			m_ocean.texSizeY = 0;
		}
	}
	m_ocean.rawTexture.push_back(color(0,255,255));
}

void worldInfo :: physicsTick()
{
	//set the position of the camera
	//game3dRenderer.setCamRot(m_playerCampaignInfo->playerEquippedSubmarine()->worldRotY);
	m_playerCampaignInfo->playerEquippedSubmarine()->physicsTick();
	game3dRenderer.setCamRot(m_playerCampaignInfo->playerEquippedSubmarine()->m_periscopeRotation + m_playerCampaignInfo->playerEquippedSubmarine()->worldRotY);
	game3dRenderer.setCamPosX(m_playerCampaignInfo->playerEquippedSubmarine()->worldPosX);
	//game3dRenderer.setCamPosY(m_playerCampaignInfo->playerEquippedSubmarine()->worldPosY);
	game3dRenderer.setCamPosZ(m_playerCampaignInfo->playerEquippedSubmarine()->worldPosZ);
	game3dRenderer.setCamPosY(m_playerCampaignInfo->playerEquippedSubmarine()->m_periscopeHeight - m_playerCampaignInfo->playerEquippedSubmarine()->worldPosY);

	//check if the player's submarine moved far enough to trigger a terrain update
	if (abs(m_playerCampaignInfo->playerEquippedSubmarine()->worldPosX) > abs(xPosLastUpdate) + 50 || abs(m_playerCampaignInfo->playerEquippedSubmarine()->worldPosZ) > abs(yPosLastUpdate) + 50)
	{
		xPosLastUpdate = m_playerCampaignInfo->playerEquippedSubmarine()->worldPosX;
		yPosLastUpdate = m_playerCampaignInfo->playerEquippedSubmarine()->worldPosZ;
		cout << "regenerating map within view distance" << endl;
		generateNearTerrain(m_playerCampaignInfo->playerEquippedSubmarine()->worldPosX/m_mapScale*-1, m_playerCampaignInfo->playerEquippedSubmarine()->worldPosZ/m_mapScale*-1, 20);
		generateNearOcean(m_playerCampaignInfo->playerEquippedSubmarine()->worldPosX/m_mapScale*-1, m_playerCampaignInfo->playerEquippedSubmarine()->worldPosZ/m_mapScale*-1, 10);
		cout << "done regenerating map within view distance" << endl;

	}
	//m_playerCampaignInfo->playerEquippedSubmarine()->wo

	//do the ship class physic tick stuff
	for (int s = 0; s < m_ships.size(); s++)
	{
		m_ships.at(s).physicsTick();
	}
}

//return 0 = success. 1 = failure
//dataElement is the pointer to the element containing the player info data
int worldInfo :: worldInfoToSaveXml(XMLElement *dataElement)
{

}

//return 0 = success. 1 = failure
//dataElement is the pointer to the element containing the player info data
int worldInfo :: worldInfoFromXml(XMLElement *dataElement, SDL_Renderer *ren)
{

}

void loadMapAssets(SDL_Renderer *ren, SDL_Window *win)
{
	unknownSubIcon = loadTextureToRam("Textures/Menus/Map/unknownsubmarine.png", ren);
	friendlySubIcon = loadTextureToRam("Textures/Menus/Map/friendlysubmarine.png", ren);
	neutralSubIcon = loadTextureToRam("Textures/Menus/Map/neutralsubmarine.png", ren);
	enemySubIcon = loadTextureToRam("Textures/Menus/Map/enemysubmarine.png", ren);

	unknownShipIcon = loadTextureToRam("Textures/Menus/Map/unknownship.png", ren);
	friendlyShipIcon = loadTextureToRam("Textures/Menus/Map/friendlyship.png", ren);
	neutralShipIcon = loadTextureToRam("Textures/Menus/Map/neutralship.png", ren);
	enemyShipIcon = loadTextureToRam("Textures/Menus/Map/enemyship.png", ren);

	waypointButtonTexture = loadTextureToRam("Textures/Menus/Shortcuts/Waypoint2.png", ren);
	markerButtonTexture = loadTextureToRam("Textures/Menus/Shortcuts/Marker.png", ren);
	protractorButtonTexture = loadTextureToRam("Textures/Menus/Shortcuts/Protractor.png", ren);
	rulerButtonTexture = loadTextureToRam("Textures/Menus/Shortcuts/Ruler.png", ren);
	compassButtonTexture = loadTextureToRam("Textures/Menus/Shortcuts/Compass.png", ren);
	eraserButtonTexture = loadTextureToRam("Textures/Menus/Shortcuts/Eraser.png", ren);

}

void deleteMapAssets()
{
	SDL_DestroyTexture(unknownSubIcon);
	SDL_DestroyTexture(friendlySubIcon);
	SDL_DestroyTexture(neutralSubIcon);
	SDL_DestroyTexture(enemySubIcon);

	SDL_DestroyTexture(unknownShipIcon);
	SDL_DestroyTexture(friendlyShipIcon);
	SDL_DestroyTexture(neutralShipIcon);
	SDL_DestroyTexture(enemyShipIcon);

	return void();
}