button :: button()
{
	color orange(255,128,0);
	m_highlightColor = orange;
	color yellow(255,255,0);
	m_clickColor = yellow;
	m_framesTillUnclick = 0;
	m_showBorder = false;
	m_drawArrow = false;
	m_hightlightRadius = 50;
	m_buttonIsCircle = false;
	m_tooltip = "";
	m_drawArrow = -1;
}

button :: button(string label, color textColor, int posX, int posY, int fontSize)
{
	m_label = label;
	m_textColor = textColor;
	color noColor(0,0,0,0);
	color orange(255,128,0);
	m_highlightColor = orange;
	color yellow(255,255,0);
	m_clickColor = yellow;
	m_backgroundColor = noColor;
	m_posX = posX;
	m_posY = posY;
	m_fontsize = fontSize;
	m_sizeX = (30 * label.length()) * fontSize / 24;
	m_sizeY = 80 * fontSize / 24;
	m_framesTillUnclick = 0;
	m_showBorder = false;
	m_drawArrow = -1;
	m_hightlightRadius = 50;
	m_buttonIsCircle = false;
	m_tooltip = "";
}

button :: button(const button& other)
{
	m_label = other.getLabel();
	m_textColor = other.textColor();
	m_backgroundColor = other.backgroundColor();
	m_highlightColor = other.highlightColor();
	m_clickColor = other.clickColor();
	m_posX = other.posX();
	m_posY = other.posY();
	m_sizeX = other.sizeX();
	m_sizeY = other.sizeY();
	m_fontsize = other.fontsize();
	m_framesTillUnclick = other.framesUnclick();
	m_showBorder = other.showBorder();
	m_drawArrow = other.arrow();
	m_hightlightRadius = other.highlightRadius();
	m_buttonIsCircle = other.buttonIsCircle();
	m_tooltip = other.tooltip();
}

button& button :: operator=(const button& other)
{
	m_label = other.getLabel();
	m_textColor = other.textColor();
	m_backgroundColor = other.backgroundColor();
	m_highlightColor = other.highlightColor();
	m_clickColor = other.clickColor();
	m_posX = other.posX();
	m_posY = other.posY();
	m_sizeX = other.sizeX();
	m_sizeY = other.sizeY();
	m_fontsize = other.fontsize();
	m_framesTillUnclick = other.framesUnclick();
	m_showBorder = other.showBorder();
	m_drawArrow = other.arrow();
	m_hightlightRadius = other.highlightRadius();
	m_buttonIsCircle = other.buttonIsCircle();
	m_tooltip = other.tooltip();

	return *this;
}

void button :: setFontSize(int size)
{
	m_fontsize = size;
	m_sizeX = (30 * m_label.length()) * m_fontsize / 24;
	m_sizeY = 80 * m_fontsize / 24;
}

void button :: setLabel(string newLabel)
{
	m_label = newLabel;
	m_sizeX = (30 * newLabel.length()) * m_fontsize / 24;
	m_sizeY = 80 * m_fontsize / 24;
}

void button :: setPos(int posX, int posY)
{
	m_posX = posX;
	m_posY = posY;
}

bool button :: isMouseTouching(int mouseX, int mouseY)
{
	if (mouseX > m_posX && mouseX < m_posX + m_sizeX && mouseY > m_posY && mouseY < m_posY + m_sizeY)
	{
		return true;
	}
	else if (m_drawArrow == 3 && mouseX > m_posX - ((80 * m_fontsize / 24)/2) - 5 && mouseX < m_posX + m_sizeX && mouseY > m_posY && mouseY < m_posY + m_sizeY) 
	{
		return true;
	}
	else if (m_drawArrow == 1 && mouseX > m_posX && mouseX < m_posX + m_sizeX + 5 + ((80 * m_fontsize / 24)/2) && mouseY > m_posY && mouseY < m_posY + m_sizeY)
	{
		return true;
	}
	else if (m_drawArrow == 0 && mouseX > m_posX - ((80 * m_fontsize / 24)/2)&& mouseX < m_posX + ((80 * m_fontsize / 24)/2) && mouseY > m_posY  - ((80 * m_fontsize / 24)/2) - 5 && mouseY < m_posY)
	{
		return true;
	}
	else if (m_drawArrow == 2 && mouseX > m_posX - ((80 * m_fontsize / 24)/2)&& mouseX < m_posX + ((80 * m_fontsize / 24)/2) && mouseY < m_posY + m_sizeY + 5 + ((80 * m_fontsize / 24)/2) && mouseY > m_posY + m_sizeY + 5)
	{
		return true;
	}
	else return false;
}

bool button :: draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse)
{	
	if (lastmouse == SDL_BUTTON(SDL_BUTTON_LEFT) && m_framesTillUnclick == 0 && isMouseTouching(mouseX, mouseY)) m_framesTillUnclick = 10;

	doDraw(ren, mouseX, mouseY, lastmouse);
	//strobe true when in a 60fps loop (it's true for 1 frame)
	if (m_framesTillUnclick == 9) return true;
	else return false;

}

void button:: draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse, bool &boolToToggle)
{
	
	if (lastmouse == SDL_BUTTON(SDL_BUTTON_LEFT) && m_framesTillUnclick == 0 && isMouseTouching(mouseX, mouseY)) m_framesTillUnclick = 10;

	doDraw(ren, mouseX, mouseY, lastmouse);
	//strobe true when in a 60fps loop (it's true for 1 frame)
	if (m_framesTillUnclick == 9) 
	{
		boolToToggle = !boolToToggle;
	}
}

void button :: doDraw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse)
{
	if (m_backgroundColor.getAlpha() != 0) drawRectFilled(ren, m_backgroundColor, m_posX, m_posY, m_sizeX, m_sizeY);
	if (m_framesTillUnclick > 0)
	{
		if (m_showBorder) drawRect(ren, m_clickColor, m_posX, m_posY, m_sizeX, m_sizeY);
		drawText(ren, m_fontsize, m_clickColor, m_label, m_posX, m_posY);
		if (m_drawArrow > -1) drawArrow(ren, m_clickColor);
		m_framesTillUnclick--;
	}
	//if mouse is hovering over button, draw it in the highlight color instead of the text color
	else if (isMouseTouching(mouseX, mouseY))
	{
		if (!m_buttonIsCircle)
		{
			drawText(ren, m_fontsize, m_highlightColor, m_label, m_posX, m_posY);
			if (m_showBorder) drawRect(ren, m_highlightColor, m_posX, m_posY, m_sizeX, m_sizeY);
			if (m_drawArrow > -1) drawArrow(ren, m_highlightColor);
		}
		else
		{
			drawCircle(ren, m_highlightColor, m_hightlightRadius, m_posX + (m_sizeX/2), m_posY + (m_sizeY/2), true);
			drawText(ren, m_fontsize, m_textColor, m_tooltip, m_posX, m_posY + (m_sizeY/2));
		}
	}
	else 
	{
		if (m_showBorder) drawRect(ren, m_textColor, m_posX, m_posY, m_sizeX, m_sizeY);
		drawText(ren, m_fontsize, m_textColor, m_label, m_posX, m_posY);
		if (m_drawArrow > -1) drawArrow(ren ,m_textColor);
	}
}

void button :: drawArrow(SDL_Renderer *ren, color arrowColor)
{
	//left arrow
	if (m_drawArrow == 3)
	{
		drawIsoscelesTriangle(ren, arrowColor, m_posX - 5, m_posY + ((80 * m_fontsize / 24)/2), m_drawArrow, (80 * m_fontsize / 24), (80 * m_fontsize / 24)/2, true);
	}
	//right arrow
	else if (m_drawArrow == 1)
	{
		drawIsoscelesTriangle(ren, arrowColor, m_posX + m_sizeX + 5, m_posY + ((80 * m_fontsize / 24)/2), m_drawArrow, (80 * m_fontsize / 24), (80 * m_fontsize / 24)/2, true);
	}
	//up arrow
	else if (m_drawArrow == 0)
	{
		drawIsoscelesTriangle(ren, arrowColor, m_posX, m_posY - 5, m_drawArrow, (80 * m_fontsize / 24), (80 * m_fontsize / 24)/2, true);
	}
	//down arrow
	else if (m_drawArrow == 2)
	{
		drawIsoscelesTriangle(ren, arrowColor, m_posX, m_posY + m_sizeY + 5, m_drawArrow, (80 * m_fontsize / 24), (80 * m_fontsize / 24)/2, true);
	}

}

//=============================================================
//textbox
//=============================
textbox :: textbox()
{
	m_text = "this is a textbox";
	color white(255,255,255,255);
	color clearBlack(0,0,0,100);
	m_textColor = white;
	m_backgroundColor = clearBlack;
	m_posX = 0;
	m_posY = 0;
	m_fontsize = 12;
	m_maxChars = 30;
	m_sizeX = (30 * m_maxChars * m_fontsize / 24);
	m_sizeY = 80 * m_fontsize / 24;
	m_isSelected = false;
	m_framesTillCursorBlink = 30;
	m_cursorVisible = false;
	m_timeTillNextKey = 0;
	m_frameWait = 0;
}

textbox :: textbox(string label, color textColor, int posX, int posY, int fontSize, int maxChars)
{
	m_text = label;
	m_textColor = textColor;
	color clearBlack(0,0,0,100);
	m_backgroundColor = clearBlack;
	m_posX = posX;
	m_posY = posY;
	m_fontsize = fontSize;
	m_maxChars = maxChars;
	m_sizeX = (30 * m_maxChars * m_fontsize / 24);
	m_sizeY = 80 * m_fontsize / 24;
	m_isSelected = false;
	m_framesTillCursorBlink = 30;
	m_cursorVisible = false;
	m_timeTillNextKey = 0;
	m_frameWait = 0;
}

bool textbox :: isMouseTouching(int mouseX, int mouseY)
{
	if (mouseX > m_posX && mouseX < m_posX + m_sizeX && mouseY > m_posY && mouseY < m_posY + m_sizeY) return true;
	else return false;
}

textbox& textbox :: operator=(textbox& other)
{
	m_text = other.text();
	m_textColor = other.textColor();
	m_backgroundColor = other.backgroundColor();
	m_posX = other.posX();
	m_posY = other.posY();
	m_sizeX = other.sizeX();
	m_sizeY = other.sizeY();
	m_fontsize = other.fontsize();
	m_maxChars = other.maxChars();
}

string textbox :: draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse)
{	
	//clicking anywhere in the textbox selects it
	if (lastmouse == SDL_BUTTON(SDL_BUTTON_LEFT) && isMouseTouching(mouseX, mouseY)) select();
	//clicking anywhere outside the textbox deselects it
	else if (lastmouse == SDL_BUTTON(SDL_BUTTON_LEFT) && !isMouseTouching(mouseX, mouseY)) deselect();

	doDraw(ren, mouseX, mouseY, lastmouse);
	return m_text;
}

void textbox :: doDraw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse)
{
	//draw background first
	drawRectFilled(ren, m_backgroundColor, m_posX, m_posY, m_sizeX, m_sizeY);
	drawText(ren, m_fontsize, m_textColor, m_text, m_posX, m_posY);
	if (m_isSelected) 
	{

		//SDL_PollEvent( &keyboardEvent );
		/*while (SDL_PollEvent(&keyboardEvent) == 1)
		{
	

       	 	if (keyboardEvent.type == SDL_TEXTINPUT)
       	 	{
       	 		m_text += keyboardEvent.text.text;
       	 	}

        	if (keyboardEvent.window.event == SDL_WINDOWEVENT_CLOSE)
			{
				exitGame = true;
			}

    	}*/

    	//backspace isnt handled by the SDL_TEXTINPUT event
    	/*const Uint8 *lastKey = SDL_GetKeyboardState(NULL);
    	if (m_timeTillNextKey <= 0)
    	{
    		if (lastKey[SDL_SCANCODE_BACKSPACE]) 
    		{
    			m_text = m_text.substr(0, m_text.size() - 1);
    			m_timeTillNextKey = 10;
    		}
    	}*/
    	if (backspaceAsserted && m_timeTillNextKey <= 0)
    	{
    		m_text = m_text.substr(0, m_text.size() - 1);
    		m_timeTillNextKey = 10;
    	}
    	else if (m_timeTillNextKey > 0) m_timeTillNextKey--;
    	else if (backspaceAsserted) m_timeTillNextKey = 0;

        //since i'm overriding the event by polling it, I have to do a close game check
        //to be honest, this system kinda sucks balls. You can't even argue that "yeah well its better this way cuz there's interrupts" because you have to poll it anyway.

        //cout << to_string(keyboardEvent.key.type) << endl;
        if (m_text.size() < m_maxChars) m_text += lastCharTyped;
		drawCursor(ren);
	}
}

void textbox :: drawCursor(SDL_Renderer *ren)
{
	int cursorTop = m_posY + (m_sizeY*0.15);
	int cursorBottom = m_posY + m_sizeY - (m_sizeY*0.15);
	if (m_cursorVisible) drawLine(ren, m_textColor, m_posX + ((30 * m_text.length()) * m_fontsize / 24), cursorTop, m_posX + ((30 * m_text.length()) * m_fontsize / 24), cursorBottom);
	m_framesTillCursorBlink--;

	if (m_framesTillCursorBlink <= 0)
	{
		m_framesTillCursorBlink = 30;
		m_cursorVisible = !m_cursorVisible;
	}
}

void textbox :: appendText(string keyboardInput)
{
	if (keyboardInput == "Backspace" && m_text.size() > 0) m_text = m_text.substr(0, m_text.size() - 1);
	else if (keyboardInput == "CapsLock") capsLock = !capsLock;
	else if (keyboardInput == "Space") m_text += " ";
	//cout << "keyboardInput = " << keyboardInput << endl;
	else if (keyboardInput.size() == 1)
	{
		if (capsLock) m_text += keyboardInput;
		else m_text += makeLowercase(keyboardInput);
	}
	//m_text.substr(0, m_text.size() - 1);
}

//=========================================
//progress bar
//========================================

progressBar :: progressBar()
{

}

progressBar :: progressBar(int x, int y, int sizeX, int sizeY, color barColor, int max, bool gradient)
{
	color black(0,0,0,255);
	m_mainColor = barColor;
	m_leftColor = barColor;
	/*if (m_leftColor.getRed() > 100) m_leftColor.setRed(m_leftColor.getRed() - 100);
	if (m_leftColor.getGreen() > 100) m_leftColor.setGreen(m_leftColor.getGreen() - 100);
	if (m_leftColor.getBlue() > 100) m_leftColor.setBlue(m_leftColor.getBlue() - 100);*/

	m_leftColor.setRed(m_leftColor.getRed() * 0.2);
	m_leftColor.setGreen(m_leftColor.getGreen() * 0.2);
	m_leftColor.setBlue(m_leftColor.getBlue() * 0.2);
	m_boarderColor = black;
	m_posX = x;
	m_posY = y;
	m_sizeX = sizeX;
	m_sizeY = sizeY;
	m_gradient = gradient;
	m_max = max;
	m_value = 0;
}

void progressBar :: draw(SDL_Renderer *ren)
{
	if (m_gradient)
	{
		//cout << "number equals " << (static_cast<double>(m_value) / static_cast<double>(m_max)) << endl;
		int cutoffSize = (static_cast<double>(m_value) / static_cast<double>(m_max)) * m_sizeX;
		//cout << "cutoff size = " << cutoffSize << endl;
		drawCuttableSidewaysGradient(ren, m_posX, m_posY, m_sizeX, m_sizeY, m_leftColor, m_mainColor, cutoffSize, 20);
	}
	else
	{
		drawRectFilled(ren, m_mainColor, m_posX, m_posY, m_sizeX, m_sizeY);
	}
	drawRect(ren, m_boarderColor, m_posX, m_posY, m_sizeX, m_sizeY);
}

progressBar& progressBar :: operator=(const progressBar& other)
{
	m_mainColor = other.mainColor();
	m_leftColor = other.secondaryColor();
	m_boarderColor = other.boarderColor();
	m_posX = other.posX();
	m_posY = other.posY();
	m_sizeX = other.sizeX();
	m_sizeY = other.sizeY();
	m_gradient = other.hasGradient();
	m_max = other.getMax();
	m_value = other.getValue();
}