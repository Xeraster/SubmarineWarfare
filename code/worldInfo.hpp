worldInfo :: worldInfo()
{

}

//set up a world from given playerInfo and improvise from there
worldInfo :: worldInfo(playerInfo *input, string heightmapName, SDL_Renderer *ren, SDL_Window *win)
{
	SDL_DestroyTexture(m_mapTex);
	//temporarily load the texture as an SDL texture. This isn't fast enough, however
	m_mapTex = loadTextureToRam_TA("Textures/Heightmaps/"+heightmapName+".bmp", ren, win);
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
}

bool worldInfo :: drawMap(SDL_Renderer *ren, double zoom, double posX, double posY)
{
	if (!m_initialized)
	{
		cout << "error: tried to draw world map but a valid world isn't loaded" << endl;
		return false;
	}

	renderTextureEx(m_mapTex, ren, (gscreenx/2)-(m_mapSizeX/2*zoom)+posX*zoom, ((gscreeny/2)-m_mapSizeY/2*zoom)+posY*zoom, (m_mapSizeX)*zoom, (m_mapSizeY)*zoom, 0);

	//draw the world to map space location of the player's submarine
	double playerX = m_playerSubmarine->worldPosX;
	double playerY = m_playerSubmarine->worldPosY;
	renderTextureEx(unknownSubIcon, ren, worldToMapX(zoom, posX, playerX)-8, worldToMapY(zoom, posY, playerY)-8, 16, 16, 0);

	for (int s = 0; s < m_ships.size(); s++)
	{
		drawShipOnMap(ren, zoom, posX, posY, &m_ships.at(s));
	}

	for (int x = -200; x < 200; x++)
	{
		for (int y = -200; y < 200; y++)
		{
			int v = heightAtCoords(x, y);
			drawPixel(ren, x + 200, y + 200, color(v,v,v));
		}
	}

	return true;
}

void worldInfo :: drawShipOnMap(SDL_Renderer *ren, double zoom, double playerX, double playerY, ship *whichShip)
{
	renderTextureEx(unknownShipIcon, ren, worldToMapX(zoom, playerX, whichShip->worldPosX)-8, worldToMapY(zoom, playerY, whichShip->worldPosZ)-8, 16, 16, 0);

	return void();
}

double worldInfo :: worldToMapX(double zoom, double mapX, double inX)
{
	double centerX = (gscreenx/2)+(m_mapSizeX/2)*zoom+mapX*zoom;

	//return ((inX+m_mapSizeX/2)*zoom) + centerX;
	return centerX - (((inX/m_mapScale)+m_mapSizeX/2))*zoom;
}

double worldInfo :: worldToMapY(double zoom, double mapY, double inY)
{
	double centerY = ((gscreeny/2)+m_mapSizeY/2*zoom)+mapY*zoom;

	//return ((inY + m_mapSizeY/2)*zoom) + centerY;
	return centerY - (((inY/m_mapScale) + m_mapSizeY/2)*zoom);
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
				cout << "processing vertex for heightmap pos " << x << ", " << y << endl;
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