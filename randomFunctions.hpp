void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Query the texture to get its width and height to use
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

//renders a texture with the ability to scale and rotate. Only problem, it's substantially more expensive so use sparingly
void renderTextureEx(SDL_Texture *tex, SDL_Renderer *ren, int posX, int posY, int targetSizeX, int targetSizeY, double angle)
{
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = posX;
	dst.y = posY;
	dst.w = targetSizeX;
	dst.h = targetSizeY;
	//Query the texture to get its width and height to use
	//SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopyEx(ren, tex, NULL, &dst, angle, NULL, SDL_FLIP_NONE);
}

void drawLine(SDL_Renderer *ren, color whatColor, int x1, int y1, int x2, int y2)
{
	SDL_SetRenderDrawColor(ren, whatColor.getRed(), whatColor.getGreen(), whatColor.getBlue(), SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(ren, x1, y1, x2, y2);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

void drawPixel(SDL_Renderer *ren, int x, int y, color whatColor)
{
	SDL_SetRenderDrawColor(ren, whatColor.getRed(), whatColor.getGreen(), whatColor.getBlue(), SDL_ALPHA_OPAQUE);
	SDL_RenderDrawPoint(ren, x, y);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

int screenSizeX(SDL_Window *win)
{
	int w, h;
	//SDL_GetRendererOutputSize(ren, &w, &h);
	SDL_GetWindowSize(win, &w, &h);
	return w;
}

int screenSizeY(SDL_Window *win)
{
	int w, h;
	SDL_GetWindowSize(win, &w, &h);
	return h;
}

void drawText(SDL_Renderer *ren, int fontSize, color TextColor, string textString, int x, int y)
{
	//char stringArray[] = textString;

	//TTF_Font* Sans = TTF_OpenFont("Sans.ttf", fontSize*3);
	int checkedFontSize = fontSize;
	//don't let the font size be more than 48 or there will be a segmentation fault due to the way all the fonts are loaded into ram first
	if (fontSize > 48) fontSize = 48;
	TTF_Font* Sans = fonts.at(fontSize);

	SDL_Color textColor = {TextColor.getRed(), TextColor.getGreen(), TextColor.getBlue()};

	//SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, textString.c_str(), textColor);
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(Sans, textString.c_str(), textColor);

	SDL_Texture* Message = SDL_CreateTextureFromSurface(ren, surfaceMessage);

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = x;  //controls the rect's x coordinate 
	Message_rect.y = y; // controls the rect's y coordinte
	Message_rect.w = (30 * textString.length()) * fontSize / 24; // for every 10 letters at 24pt, make it 300 pixels long
	Message_rect.h = 80 * fontSize / 24; // for every 24pt, make it 80 characters high

	SDL_RenderCopy(ren, Message, NULL, &Message_rect);

	SDL_DestroyTexture(Message);
	SDL_FreeSurface(surfaceMessage);
	//TTF_CloseFont(Sans);

}

void drawText(SDL_Renderer *ren, int fontSize, coloredString textString, int x, int y)
{
	int offsetX = 0;

	for (int i = 0; i < textString.size(); i++)
	{
		string temp = textString.atPos(i).getText();
		color tempColor = textString.atPos(i).getColor();
		drawText(ren, fontSize, tempColor, temp, x + offsetX, y);
		offsetX += getTextXSize(fontSize, temp.size());
	}
}

//that one was a doosey. Seems to be working now though
int drawTextWrapped(SDL_Renderer *ren, int fontSize, color TextColor, string textString, int x, int y, int pixelsBeforeWrap)
{	
	//the formula for calculated size of a string of text
	//(30 * textlength * m_fontsize / 24) = pixels of line
	int maxCharsPerLine = pixelsBeforeWrap / (30 * fontSize / 24);
	int verticalOffset = 80 * fontSize / 24;
	int b = 0;
	int u = 0;
	while (b + (maxCharsPerLine * u) < textString.size())
	{
		int i = 0;
		string line;
		while (i < maxCharsPerLine && i + b + (maxCharsPerLine * u) < textString.size())
		{
			line += textString.at(i + b + (maxCharsPerLine * u));
			i++;
		}
		while (textString[b+i+ (maxCharsPerLine * u)] != ' ' && i + b + (maxCharsPerLine * u) < textString.size())
		{
			line += textString.at(i + b + (maxCharsPerLine * u));
			b++;
		}
		drawText(ren, fontSize, TextColor, line, x, y + (verticalOffset * u));
		u++;
		//cout << "i = " << i << "b = " << b << "u = " << u << endl;
	}

	//u = number of rows it used
	//cout << "u =" << u << endl;
	return u;

}

int getTextRows(string text, int fontSize, int pixelsBeforeWrap)
{
	//the formula for calculated size of a string of text
	//(30 * textlength * m_fontsize / 24) = pixels of line
	int maxCharsPerLine = pixelsBeforeWrap / (30 * fontSize / 24);
	int verticalOffset = 80 * fontSize / 24;
	int b = 0;
	int u = 0;
	while (b + (maxCharsPerLine * u) < text.size())
	{
		int i = 0;
		string line;
		while (i < maxCharsPerLine && i + b + (maxCharsPerLine * u) < text.size())
		{
			line += text.at(i + b + (maxCharsPerLine * u));
			i++;
		}
		while (text[b+i+ (maxCharsPerLine * u)] != ' ' && i + b + (maxCharsPerLine * u) < text.size())
		{
			line += text.at(i + b + (maxCharsPerLine * u));
			b++;
		}
		//drawText(ren, fontSize, TextColor, line, x, y + (verticalOffset * u));
		u++;
		//cout << "i = " << i << "b = " << b << "u = " << u << endl;
	}

	//u = number of rows it used
	//cout << "u =" << u << endl;
	return u;
}

void drawRect(SDL_Renderer *ren, color whatColor, int x, int y, int sizeX, int sizeY)
{
	SDL_Rect thisRect;
	thisRect.x = x;
	thisRect.y = y;
	thisRect.w = sizeX;
	thisRect.h = sizeY;

	SDL_SetRenderDrawColor(ren, whatColor.getRed(), whatColor.getGreen(), whatColor.getBlue(), whatColor.getAlpha());

	SDL_RenderDrawRect(ren, &thisRect);

	SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

void drawRectFilled(SDL_Renderer *ren, color whatColor, int x, int y, int sizeX, int sizeY)
{
	SDL_Rect thisRect;
	thisRect.x = x;
	thisRect.y = y;
	thisRect.w = sizeX;
	thisRect.h = sizeY;

	SDL_SetRenderDrawColor(ren, whatColor.getRed(), whatColor.getGreen(), whatColor.getBlue(), whatColor.getAlpha());

	SDL_RenderFillRect(ren, &thisRect);

	SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

void drawTriangle(SDL_Renderer *ren, color whatColor, int x1, int y1, int x2, int y2, int x3, int y3)
{
	//draws 3 lines to make a triangle
	drawLine(ren, whatColor, x1, y1, x2, y2);
	drawLine(ren, whatColor, x2, y2, x3, y3);
	drawLine(ren, whatColor, x3, y3, x1, y1);
}

//draw an equilateral triangle. Intended to be used for menus. dir 0 = up. 1 = right. 2 = down. 3 = left
void drawEquilateralTriangle(SDL_Renderer *ren, color whatColor, int posX, int posY, int dir, int size, bool filled)
{
	if (dir == 0 ) 
	{
		drawTriangle(ren, whatColor, posX - (size / 2), posY, posX + (size / 2), posY, posX, posY - size);
	}
	else if (dir == 1) 
	{
		drawTriangle(ren, whatColor, posX, posY - (size / 2), posX, posY + (size / 2), posX + size, posY);
	}
	else if (dir == 2) 
	{
		drawTriangle(ren, whatColor, posX - (size / 2), posY, posX + (size / 2), posY, posX, posY + size);
	}
	else if (dir == 3) 
	{
		drawTriangle(ren, whatColor, posX, posY - (size / 2), posX, posY + (size / 2), posX - size, posY);
	}

	//recursive
	if (filled && size > 1)
	{
		drawEquilateralTriangle(ren, whatColor, posX, posY, dir, size - 1, filled);
	}
}

//draw an isosceles triangle. Intended to be used for menus. dir 0 = up. 1 = right. 2 = down. 3 = left
void drawIsoscelesTriangle(SDL_Renderer *ren, color whatColor, int posX, int posY, int dir, int size, int height, bool filled)
{
	if (dir == 0 ) 
	{
		drawTriangle(ren, whatColor, posX - (size / 2), posY, posX + (size / 2), posY, posX, posY - height);
	}
	else if (dir == 1) 
	{
		drawTriangle(ren, whatColor, posX, posY - (size / 2), posX, posY + (size / 2), posX + height, posY);
	}
	else if (dir == 2) 
	{
		drawTriangle(ren, whatColor, posX - (size / 2), posY, posX + (size / 2), posY, posX, posY + height);
	}
	else if (dir == 3) 
	{
		drawTriangle(ren, whatColor, posX, posY - (size / 2), posX, posY + (size / 2), posX - height, posY);
	}

	//recursive
	if (filled && size > 1)
	{
		drawIsoscelesTriangle(ren, whatColor, posX, posY, dir, size - 1, height, filled);
	}
}

void drawCircle(SDL_Renderer *ren, color circleColor, int radius, int xPos, int yPos, bool filled)
{
    SDL_SetRenderDrawColor(ren, circleColor.getRed(), circleColor.getGreen(), circleColor.getBlue(), circleColor.getAlpha());
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if (filled && (dx*dx + dy*dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(ren, xPos + dx, yPos + dy);
            }
    	}
    }

    SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE);
}


void drawEmptyCircle(SDL_Renderer *ren, color circleColor, int radius, int xPos, int yPos)
{
	SDL_SetRenderDrawColor(ren, circleColor.getRed(), circleColor.getGreen(), circleColor.getBlue(), circleColor.getAlpha());

	for (int w = -3; w < radius * 2 + 3; w++)
    {
        for (int h = -3; h < radius * 2 + 3; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx*dx + dy*dy) >= ((radius-1) * (radius-1)) && (dx*dx + dy*dy) <= ((radius+1) * (radius+1)))
            {
                SDL_RenderDrawPoint(ren, xPos + dx, yPos + dy);
            }
   		}	
	}

    SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE);

}

void starInfoTooltip(SDL_Renderer *ren, SDL_Window *win, starSystem system)
{
	color white(255,255,255,255);
	string starNameText = system.getName();
	int nameFontSize = 12;
	if (starNameText.length() > 17)
	{
		nameFontSize = 10;
	}
	if (starNameText.length() > 22)
	{
		nameFontSize = 8;
	}
	drawText(ren, nameFontSize, white, system.getName(), screenSizeX(win) - 300, screenSizeY(win) - 110);
	drawText(ren, 8, white, "Class " + system.getType() + " star", screenSizeX(win) - 300, screenSizeY(win) - 80);
	drawText(ren, 8, white, "Temperature: " + to_string(system.getTemp()) + "K", screenSizeX(win) - 300, screenSizeY(win) - 60);
	string massText = to_string(system.getMass());
	massText.resize(massText.length() - 4);
	drawText(ren, 8, white, "Mass: " + massText + "x 10^30 kg", screenSizeX(win) - 300, screenSizeY(win) - 40);
	drawText(ren, 8, white, "Solar radius: " + to_string(system.getSize()*695700/10) + "km", screenSizeX(win) - 300, screenSizeY(win) - 20);
}

void starInfoTooltip(SDL_Renderer *ren, SDL_Window *win, starSystem system, int x, int y)
{
	color white(255,255,255,255);
	string starNameText = system.getName();
	int nameFontSize = 12;
	if (starNameText.length() > 17)
	{
		nameFontSize = 10;
	}
	if (starNameText.length() > 22)
	{
		nameFontSize = 8;
	}
	drawText(ren, nameFontSize, white, system.getName(), x, y - 110);
	drawText(ren, 8, white, "Class " + system.getType() + " star", x, y - 80);
	drawText(ren, 8, white, "Temperature: " + to_string(system.getTemp()) + "K", x, y - 60);
	string massText = to_string(system.getMass());
	massText.resize(massText.length() - 4);
	drawText(ren, 8, white, "Mass: " + massText + "x 10^30 kg", x, y - 40);
	drawText(ren, 8, white, "Solar radius: " + to_string(system.getSize()*695700/10) + "km", x, y - 20);
}

void planetInfoTooltip(SDL_Renderer *ren, SDL_Window *win, planet whichPlanet, int x, int y)
{
	color white(255,255,255,255);

	drawText(ren, 12, white, whichPlanet.getName(), x, y - 110);
	drawText(ren, 8, white, whichPlanet.getTypeName() + " " + whichPlanet.getSizeName(), x, y - 80);
	//drawText(ren, 8, white, "Temperature: " + to_string(system.getTemp()) + "K", x, y - 60);
	string massText = to_string(whichPlanet.getMass());
	massText.resize(5);
	drawText(ren, 8, white, massText + "x10^23 kg", x, y - 40);
	//drawText(ren, 8, white, "Solar radius: " + to_string(system.getSize()*695700/10) + "km", x, y - 20);
}

uint32_t betterRand(uint32_t seed)
{
	seed += 0xe120fc15;
	uint64_t tmp;
	tmp = (uint64_t)seed * 0x4a39b70d;
	uint32_t m1 = (tmp >> 32) ^ tmp;
	tmp = (uint64_t)m1 * 0x12fad5c9;
	uint32_t m2 = (tmp >> 32) ^ tmp;
	return m2;
}

void initQuickAccessColors()
{
	colorArray[0] = color(255,0,0,255); 	//red
	colorArray[1] = color(255,150,0,255);	//orange
	colorArray[2] = color(255,255,0,255);	//yellow
	colorArray[3] = color(0,100,255,255);		//light blue
	colorArray[4] = color(255,75,0,255);	//orangish red
	colorArray[5] = color(255,255,255,255);	//white
}

color seedToStarColor(uint32_t seed)
{
	//generate a color with the random seed the exact same way the starSystem class does
	return colorArray[betterRand(seed) % 6];
}

int seedToStarSize(uint32_t seed)
{
	color starColor = seedToStarColor(seed);
	int size = 0;

	if (starColor == colorArray[0])	//if star is red
	{
		size = (betterRand(seed + 1028201)%10)+5;
	}else if (starColor == colorArray[1])
	{
		size = (betterRand(seed + 1028201)%6)+3;
	}else if (starColor == colorArray[2])
	{
		size = (betterRand(seed + 1028201)%5)+2;
	}
	else if (starColor == colorArray[3]) //blue giants
	{
		size = (betterRand(seed + 1028201)%10)+5;
	}else if (starColor == colorArray[5])
	{
		size = (betterRand(seed + 1028201)%8)+2;
	}else if (starColor == colorArray[4])
	{
		size = (betterRand(seed + 1028201)%5)+3;
	}

	return size;
}

planetMetaData getPlanetDataFromSeed(uint32_t seed, planetMetaData yeah)
{
	//planetMetaData yeah;
	int typeSize = 0;
	int planetType = static_cast<int>(betterRand(seed)%10);
	seed++;
	if (planetType >= 7)
	{
		typeSize = (betterRand(seed)%2)+1;
		seed++;
		planetType = 7;

	}
	else
	{
		if (betterRand(seed+547265)%1000 > 950)
		{
			typeSize = 3;
		}
		else
		{
			typeSize = betterRand(seed)%3;
		}
	}

	seed++;
	if (typeSize == 0)
	{
		yeah.radius = (betterRand(seed)%537)+100;
		seed++;
	}
	else if (typeSize == 1)
	{
		yeah.radius = (betterRand(seed)%3185)+637;
		seed++;
	}
	else if (typeSize == 2)
	{
		yeah.radius = (betterRand(seed)%21622)+3822;
		seed++;
	}
	else if (typeSize == 3)
	{
		yeah.radius = (betterRand(seed)%252000)+63000;
		seed++;
	}

	if (planetType == 0)
	{
		color theColor((betterRand(seed)%119)+17,136,81);
		yeah.whatColorIsPlanet = theColor;

	}else if (planetType == 1)
	{
		color theColor(212,(betterRand(seed)%65)+115,81);
		yeah.whatColorIsPlanet = theColor;

	}else if (planetType == 2)
	{
		color theColor(193,(betterRand(seed)%34)+212,246);
		yeah.whatColorIsPlanet = theColor;	
	}
	else if (planetType == 3)
	{
		color theColor(150+betterRand(seed)%50,150+betterRand(seed)%50,150+betterRand(seed)%50);
		yeah.whatColorIsPlanet = theColor;
		
	}else if (planetType == 4)
	{
		color theColor(255,(betterRand(seed)%111)+33,33);
		yeah.whatColorIsPlanet = theColor;	
		
	}else if (planetType == 5)
	{
		color theColor(10,(betterRand(seed)%146),146);
		yeah.whatColorIsPlanet = theColor;	

	}else if (planetType == 6)
	{
		color theColor(78,60,betterRand(seed)%60);
		yeah.whatColorIsPlanet = theColor;

	}else if (planetType == 7)
	{
		color theColor((betterRand(seed+1)%150)+100,(betterRand(seed+2)%150)+100,(betterRand(seed)%150)+100);
		yeah.whatColorIsPlanet = theColor;	
	}

	seed++;
	seed++;
	seed++;
	yeah.distance = betterRand(seed)%2000;

	return yeah;
}

void drawGradient(SDL_Renderer *ren, int x1, int y1, int x2, int y2, int numSteps)
{
	color skyBottom(53,214,237);
	color skyTop(210,246,255);
	int rSegmentSize = skyTop.getRed() - skyBottom.getRed();
	int gSegmentSize = skyTop.getGreen() - skyBottom.getGreen();
	int bSegmentSize = skyTop.getBlue() - skyBottom.getBlue();
	int r = skyTop.getRed();
	int g = skyTop.getGreen();
	int b = skyTop.getBlue();
	int yth = y2/numSteps;
	for (int i = 0; i < numSteps; i++)
	{
		color stripColor(r - (i*(rSegmentSize/numSteps)), g - (i*(gSegmentSize/numSteps)), b - (i*(bSegmentSize/numSteps)));
		drawRectFilled(ren, stripColor, x1, yth*i, x2, yth*(i+1));
	}

}

void drawGradient(SDL_Renderer *ren, int x1, int y1, int x2, int y2, color topColor, color bottomColor, int numSteps)
{
	//color skyBottom(53,214,237);
	//color skyTop(210,246,255);
	int rSegmentSize = topColor.getRed() - bottomColor.getRed();
	int gSegmentSize = topColor.getGreen() - bottomColor.getGreen();
	int bSegmentSize = topColor.getBlue() - bottomColor.getBlue();
	int r = topColor.getRed();
	int g = topColor.getGreen();
	int b = topColor.getBlue();
	int yth = y2/numSteps;
	for (int i = 0; i < numSteps; i++)
	{
		color stripColor(r - (i*(rSegmentSize/numSteps)), g - (i*(gSegmentSize/numSteps)), b - (i*(bSegmentSize/numSteps)));
		drawRectFilled(ren, stripColor, x1, yth*i, x2, yth*(i+1));
	}
}
//draw a sidways gradient. It goes sideways unlike drawGradient which goes vertical
void drawSidewaysGradient(SDL_Renderer *ren, int x1, int y1, int x2, int y2, color leftColor, color rightColor, int numSteps)
{
	int rSegmentSize = leftColor.getRed() - rightColor.getRed();
	int gSegmentSize = leftColor.getGreen() - rightColor.getGreen();
	int bSegmentSize = leftColor.getBlue() - rightColor.getBlue();

	//do it left to right
	int r = leftColor.getRed();
	int g = leftColor.getGreen();
	int b = leftColor.getBlue();

	int xth = x2 / numSteps;

	for (int i = 0; i < numSteps + 1; i++)
	{
		color stripColor(r - (i*(rSegmentSize/numSteps)), g - (i*(gSegmentSize/numSteps)), b - (i*(bSegmentSize/numSteps)));
		drawRectFilled(ren, stripColor, x1 + (xth*i), y1, xth, y2);
	}
}

//the gradient that progress bars use. It goes sideways
void drawCuttableSidewaysGradient(SDL_Renderer *ren, int x1, int y1, int x2, int y2, color leftColor, color rightColor, int cuttoff, int numSteps)
{
	int rSegmentSize = leftColor.getRed() - rightColor.getRed();
	int gSegmentSize = leftColor.getGreen() - rightColor.getGreen();
	int bSegmentSize = leftColor.getBlue() - rightColor.getBlue();

	//do it left to right
	int r = leftColor.getRed();
	int g = leftColor.getGreen();
	int b = leftColor.getBlue();

	int xth = x2 / numSteps;
	int i = 0;
	while (i < numSteps && xth*i< cuttoff)
	{
		//cout << "x1 + (xth*i) = " << x1 + (xth*i) << endl;
		color stripColor(r - (i*(rSegmentSize/numSteps)), g - (i*(gSegmentSize/numSteps)), b - (i*(bSegmentSize/numSteps)));
		drawRectFilled(ren, stripColor, x1 + (xth*i), y1, xth, y2);
		i++;
	}

	if (x1 + (xth*i) < x1 + x2 - 1 && i == numSteps)
	{
		color stripColor(r - ((i)*(rSegmentSize/numSteps)), g - ((i)*(gSegmentSize/numSteps)), b - ((i)*(bSegmentSize/numSteps)));
		drawRectFilled(ren, stripColor, x1 + (xth*i), y1, x2 - (xth*i), y2);
	}
}

color colorByteToRGB(short stupidColor)
{
	short stupidColorModulo = stupidColor % 0x0010;
	switch (stupidColorModulo)
	{
		case 0x0000:
			//black
			return color(0,0,0,255);
		case 0x0001:
			//dark blue
			return color(0,0,127,255);
		case 0x0002:
			//dark green
			return color(0,127,0,255);
		case 0x0003:
			//dark cyan
			return color(0,127,127,255);
		case 0x0004:
			//dark red
			return color(127,0,0,255);
		case 0x0005:
			//dark magenta
			return color(127,0,127,255);
		case 0x0006:
			//dark yellow
			return color(127,127,0,255);
		case 0x0007:
			//grey
			return color(192, 192, 192, 255);
		case 0x0008:
			//dark grey
			return color(127,127,127,255);
		case 0x0009:
			//blue
			return color(0, 0, 255, 255);
		case 0x000A:
			//green
			return color(0,255,0,255);
		case 0x000B:
			//cyan
			return color(0,255,255,255);
		case 0x000C:
			//red
			return color(255,0,0,255);
		case 0x000D:
			//magenta
			return color(255,0,255,255);
		case 0x000E:
			//yellow
			return color(255,255,0,255);
		case 0x000F:
			//white
			return color(255,255,255,255);
	/*BG_BLACK = 0x0000,
	BG_DARK_BLUE = 0x0010,
	BG_DARK_GREEN = 0x0020,
	BG_DARK_CYAN = 0x0030,
	BG_DARK_RED = 0x0040,
	BG_DARK_MAGENTA = 0x0050,
	BG_DARK_YELLOW = 0x0060,
	BG_GREY = 0x0070,
	BG_DARK_GREY = 0x0080,
	BG_BLUE = 0x0090,
	BG_GREEN = 0x00A0,
	BG_CYAN = 0x00B0,
	BG_RED = 0x00C0,
	BG_MAGENTA = 0x00D0,
	BG_YELLOW = 0x00E0,
	BG_WHITE = 0x00F0,*/
	}
}

string gramsToReadable(double grams, bool showExact)
{
	double adjustedValue = grams;

	//if tons
	if (grams > 907185)
	{
		adjustedValue /= 907185;
		if (showExact) return to_string(adjustedValue) + "tons";
		return to_string(adjustedValue).substr(0, to_string(adjustedValue).size() - 4) + " tons";
	}

	//if kg quantities
	else if (grams >= 1000)
	{
		adjustedValue /= 1000;
		if (showExact) return to_string(adjustedValue) + " kg";
		else return to_string(adjustedValue).substr(0, to_string(adjustedValue).size() - 4) + " kg";
	}

	//if less than 1 gram
	int numDivisions = 0;
	while (adjustedValue < 1)
	{
		adjustedValue *= 1000;
		numDivisions++;
	}
	if (showExact) to_string(adjustedValue) + " " + metricWeightsSmall[numDivisions];
	else return to_string(adjustedValue).substr(0, to_string(adjustedValue).size() - 4) + " " + metricWeightsSmall[numDivisions];
}

//loads the fonts into ram and keeps so they can be referenced each time the drawText function needs them
int loadFonts()
{
	for (int i = 0; i < 48; i++)
	{
		fonts.push_back(TTF_OpenFont("Sans.ttf", i*3));
		//TTF_CloseFont(Sans);
	}
	//Sans = TTF_OpenFont("Sans.ttf", fontSize*3);
	return 0;
}

//put this at the end of the program to make valgrind shut up
int deleteFonts()
{
	for (int i = 0; i < 48; i++)
	{
		TTF_CloseFont(fonts.at(i));
	}
	fonts.clear();
}

//SDL scancodes go in. ascii codes come out
char SDLcrap_to_char(const Uint8 *sdl_crap)
{
	char correctChar = 'P';
	if (*sdl_crap > 3 && *sdl_crap < 30) return 61 + *sdl_crap;
	else if (*sdl_crap > 29 && *sdl_crap < 38) return 19 + *sdl_crap;
	else if (*sdl_crap == 39) return 48;	//zero is last in sdl scancode table. pretty stupid
	else if (*sdl_crap == 44) return 32;	//space
	else if (*sdl_crap == 42) return 8; 	//backspace
}

string makeLowercase(string input)
{
	string result = input;
	for (int i = 0; i < input.size(); i++)
	{
		if (input.at(i) >= 'A' && input.at(i) <= 'Z')
		{
			result.at(i) = input.at(i) + 32;
		} 
	}

	return result;
}

string makeUppercase(string input)
{

}

void capitalizeFirstLetter(string &input)
{
	if (input.size() > 0 && input.at(0) > 96 && input.at(0) < 123)
	{
		input.at(0) = input.at(0) - 32;
	}
}

//to reduce garbage in the moreDetailedSubmarineInfo() function
coloredString lessOrBigger(int original, int compare)
{
	coloredString stringToReturn;
	if (original > compare)
	{
		color positiveGreen(0,255,0);
		stringToReturn.appendColorString(" (+" + to_string(original - compare) + ")", positiveGreen);
	}
	else if (original != compare)
	{
		color negativeRed(255,0,0);
		stringToReturn.appendColorString(" (" + to_string(original - compare) + ")", negativeRed);
	}

	return stringToReturn;
}

coloredString lessOrBigger(double original, double compare, int decimalPlaces)
{
	coloredString stringToReturn;

	if (original > compare)
	{
		color positiveGreen(0,255,0);
		stringToReturn.appendColorString(" (+" + doubleToString(original - compare, decimalPlaces) + ")", positiveGreen);
	}
	else if(original != compare)
	{
		color negativeRed(255,0,0);
		stringToReturn.appendColorString(" (" + doubleToString(original - compare, decimalPlaces) + ")", negativeRed);
	}

	return stringToReturn;
}

//a 2d collision function. Mainly used for gui mouse collisions but suitable for probably every possible 2d box collision use
bool isColliding2D(int posX, int posY, int sizeX, int sizeY, int mouseX, int mouseY)
{
	if (mouseX > posX && mouseX < posX + sizeX && mouseY > posY && mouseY < posY + sizeY)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//void drawCrewIconLarge(vector<SDL_Texture*> crewLargeTextures, crewMember crewPerson, SDL_Renderer *ren, int x, int y)
//{

//}