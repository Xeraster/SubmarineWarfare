#ifndef BUTTON_H
#define BUTTON_H

class button
{
public:
	button();
	button(string label, color textColor, int posX, int posY, int fontSize);

	button(const button& other);

	string getLabel() const { return m_label; }
	color textColor() const  { return m_textColor; }
	color backgroundColor() const  { return m_backgroundColor; }
	color highlightColor() const  { return m_highlightColor; }
	color clickColor() const { return m_clickColor; }
	int posX() const { return m_posX; }
	int posY() const { return m_posY; }
	int sizeX() const { return m_sizeX; }
	int sizeY() const { return m_sizeY; }
	int fontsize() const { return m_fontsize; }
	int framesUnclick() const { return m_framesTillUnclick; }
	bool showBorder() const { return m_showBorder; }
	int arrow() const { return m_drawArrow; }
	int highlightRadius() const { return m_hightlightRadius; }
	bool buttonIsCircle() const { return m_buttonIsCircle; }
	string tooltip() const { return m_tooltip; }

	void setTooltip(string tooltip) { m_tooltip = tooltip; }
	void setCircle(bool circle) { m_buttonIsCircle = circle; }
	void setHighlightRadious(int radius) { m_hightlightRadius = radius; }

	void setFontSize(int size);
	void setLabel(string newLabel);
	void setPos(int posX, int posY);
	void setArrow(int arrow) { m_drawArrow = arrow; }
	void setBorder(bool borderStatus) { m_showBorder = borderStatus; }

	void setTextColor(color text) { m_textColor = text; }
	void setBackgroundColor(color background) { m_backgroundColor = background; }
	void setHighlightColor(color highlight) { m_highlightColor = highlight; }

	bool isMouseTouching(int mouseX, int mouseY);

	int derivedSizeY() { return (80 * m_fontsize / 24); }
	int derivedSizeX() { return (30 * m_label.size() * m_fontsize / 24); }

	bool draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse);

	void draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse, bool &boolToToggle);

	button& operator=(const button& other);
private:
	string m_label;
	color m_textColor;
	color m_backgroundColor;
	color m_highlightColor;
	color m_clickColor;
	int m_posX;
	int m_posY;
	int m_sizeX;
	int m_sizeY;
	int m_fontsize;
	int m_framesTillUnclick;
	bool m_showBorder;
	string m_tooltip;
	int m_drawArrow; 		//-1 = no. 0 = up, 1 = right. 2 = down. 3 = left
	void doDraw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse);
	void drawArrow(SDL_Renderer *ren, color arrowColor);

	int m_hightlightRadius;
	bool m_buttonIsCircle;

};

class textbox
{

public:
	textbox();
	textbox(string label, color textColor, int posX, int posY, int fontSize, int maxChars);

	string text() { return m_text; }
	color textColor() { return m_textColor; }
	color backgroundColor() { return m_backgroundColor; }
	void setTextColor(color tcolor) { m_textColor = tcolor; }
	void setBackgroundColor(color bcolor) { m_backgroundColor = bcolor; }

	int posX() { return m_posX; }
	int posY() { return m_posY; }
	int sizeX() { return m_sizeX; }
	int sizeY() { return m_sizeY; }
	int fontsize() { return m_fontsize; }
	int maxChars() { return m_maxChars; }
	void replaceText(string text) { m_text = text;}

	bool isMouseTouching(int mouseX, int mouseY);
	void setDefaultText(string newText) { m_text = newText; }
	void setPos(int posX, int posY)
	{
		m_posX = posX;
		m_posY = posY;
	}

	int derivedSizeY() { return (80 * m_fontsize / 24); }
	int derivedSizeX() { return (30 * m_maxChars * m_fontsize / 24); }

	//call this one to draw the textbox
	string draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse);

	void select() { m_isSelected = true; }
	void deselect() { m_isSelected = false; }

	textbox& operator=(textbox& other);
private:
	void doDraw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse);
	void drawCursor(SDL_Renderer *ren);
	void appendText(string keyboardInput);
	string m_text;

	color m_textColor;
	color m_backgroundColor;

	int m_posX;
	int m_posY;
	int m_sizeX;
	int m_sizeY;
	int m_fontsize;
	int m_maxChars;
	int m_timeTillNextKey;

	bool m_isSelected;
	int m_framesTillCursorBlink;
	bool m_cursorVisible;
	int m_frameWait;

};

class progressBar
{
public:
	progressBar();
	progressBar(int x, int y, int sizeX, int sizeY, color barColor, int max, bool gradient = false);

	void setMainColor(color whatColor) { m_mainColor = whatColor; }
	color mainColor() const { return m_mainColor; }
	void setSecondaryColor(color whatColor) { m_leftColor = whatColor; }
	color secondaryColor() const { return m_leftColor; }
	void setboarderColor(color whatColor) { m_boarderColor = whatColor; }
	color boarderColor() const { return m_boarderColor; }

	void setPos(int px, int py) { m_posX = px; m_posY = py; }
	int posX() const { return m_posX; }
	int posY() const { return m_posY; }

	void setSize(int sx, int sy) { m_sizeX = sx; m_sizeY = sy; }
	int sizeX() const { return m_sizeX; }
	int sizeY() const { return m_sizeY; }

	bool hasGradient() const { return m_gradient; }
	void setGradient(bool grad) { m_gradient = grad; }

	void setValue(int number) { m_value = number; }
	int getValue() const { return m_value; }

	void setMax(int number) { m_max = number; }
	int getMax() const { return m_max; }

	//progress bars are non-interactive gui elements
	void draw(SDL_Renderer *ren);

	progressBar& operator=(const progressBar& other);
private:
	color m_mainColor;
	color m_leftColor;
	color m_boarderColor;
	int m_posX;
	int m_posY;
	int m_sizeX;
	int m_sizeY;
	bool m_gradient;

	int m_value;
	int m_max;
};

extern SDL_Event testEvent;
extern bool exitGame;
SDL_Event keyboardEvent;

#include "button.hpp"

#endif 
