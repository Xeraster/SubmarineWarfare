#ifndef BUTTON_H
#define BUTTON_H

SDL_Texture *generic_dial_needle;

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

	bool draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse, SDL_Texture *optionalTexture = nullptr);

	void draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse, bool &boolToToggle, SDL_Texture *optionalTexture = nullptr);

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
	void doDraw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse, SDL_Texture *optionalTexture = nullptr);
	void drawTextOrTexture(SDL_Renderer *ren, color textColor, SDL_Texture *optionalTexture = nullptr);	//to make the doDraw function easier to read and less complicated
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

//a vertical scroll view. You know, the kind of thing that looks like:
/*

----------------------------------
|   blah blah blah             |--
|   blah blah blah             |^^
|   blorf blorf blorf          |!!
|   example example            |!!
|   foo foo foo                |\/
|   bar                        |--
|---------------------------------
*/

//note that the vertical scroll view class is pretty new and there might still be bugs
class verticalScrollView
{
public:
	verticalScrollView();

	//make a constructor with nearly every parameter
	verticalScrollView(int x, int y, int sizeX, int sizeY, int barWidth, color backgroundColor, color barColor, color highlightColor, color textColor);

	//make a more minified one
	verticalScrollView(int x, int y, int sizeX, int sizeY, int barWidth);

	verticalScrollView(const verticalScrollView& other);

	void setBackgroundColor(color whatColor) { m_backgroundColor = whatColor; }
	color backgroundColor() const { return m_backgroundColor; }
	void setBarColor(color whatColor) { m_barColor = whatColor; }
	color barColor() const { return m_barColor; }
	void setHighlightColor(color whatColor) { m_hightlightColor = whatColor; }
	color highlightColor() const { return m_hightlightColor; }
	void setTextColor(color whatColor) { m_textColor = whatColor; }
	color textColor() const { return m_textColor; }


	//calculates the text size automatically.
	void setTextSize(int size) { m_textSize = size; }
	int textSize() const { return m_textSize; }

	void setPos(int px, int py);
	int posX() const { return m_posX; }
	int posY() const { return m_posY; }

	void setSize(int sx, int sy) { m_sizeX = sx; m_sizeY = sy; }
	int sizeX() const { return m_sizeX; }
	int sizeY() const { return m_sizeY; }

	void setBarWidth(int newWidth) { m_barWidth = newWidth; }
	int barWidth() const { return m_barWidth; }

	void setBarPos(int pos) { m_barPos = pos; }
	int barPos() const { return m_barPos; }

	//returns string of selected thing
	string draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse);

	verticalScrollView& operator=(const verticalScrollView& other);

	void addElement(string elementText);

	//removes all elements from the scroll view
	void removeAllElements();

	//deselects whatever is currently selected
	void deselect();


private:
	color m_backgroundColor;
	color m_barColor;
	color m_hightlightColor;
	color m_textColor;
	int m_posX;
	int m_posY;
	int m_sizeX;
	int m_sizeY;
	int m_barWidth;

	//the text size is calculated automatically
	void calculateTextSize();
	int m_textSize;

	//housekeeping variables used internally based on stuff. Not meant to be accessed from the outside
	int m_barHeight;
	int m_barPos;
	int m_mouseVerticalOffset;
	bool m_holdingClick;
	int m_selectedIndex;

	//i'm going to try to work smart not hard by making the vertical scroll view contain a vector of buttons. That way part of the code is already managed by button objects
	vector<button> m_elements;

	//separate the scroll bar and the non scroll bar drawing code to make everything easier for the programmer to figure out wtf is going on
	void drawScrollBar(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse);
	void setStupidBool(bool value) { m_holdingClick = value; }

	//figure out how many different scroll positions there are
	int getNumPositions();

};

//==========================================================
//dial ui element
//========================================================
class dial
{

public:

	dial();
	dial(int size, int posX, int posY, int maxVal, SDL_Texture *texture, double minAngle = 0, double maxAngle = 360);
	dial(const dial& other);


	dial& operator=(const dial& other);

	int posX() const { return m_posX; }
	int posY() const { return m_posY; }
	void setPos(int px, int py) { m_posX = px; m_posY = py; }

	int sizeX() const { return m_sizeX; }
	int sizeY() const { return m_sizeY; }

	color getDialColor() const { return m_dialColor; }
	void setDialColor(color newColor) { m_dialColor = newColor; }

	double maxVal() const { return m_maxVal; }
	void setMaxVal(double newMax) { m_maxVal = newMax; }

	void setMinDegrees(double newVal) { m_minDegrees = newVal; }
	void setMaxDegrees(double newVal) { m_maxDegrees = newVal; }
	double minDegrees() const { return m_minDegrees; }
	double maxDegrees() const { return m_maxDegrees; }

	SDL_Texture* getTexture() const { return m_elementTexture; }
	void setTexture(SDL_Texture *newTexture) { m_elementTexture = newTexture; }

	int getRadius() const { return m_radius; }
	void setRadius(int newValue) { m_radius = newValue; m_sizeY = m_radius*2; m_sizeX = m_radius*2; }

	void getCenter(int &x, int &y) { y = m_posY + m_radius; x = m_posX + m_radius; }

	double value() const { return m_currentValue; }
	double degrees() const { return m_degreesOfLastClick; }

	double draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse);

private:
	int m_posX;
	int m_posY;
	int m_sizeX;
	int m_sizeY;

	double m_maxVal;

	double m_minDegrees;
	double m_maxDegrees;

	int m_radius;
	color m_dialColor;
	SDL_Texture *m_elementTexture;

	double m_currentValue;
	double m_degreesOfLastClick;
};

extern SDL_Event testEvent;
extern bool exitGame;
SDL_Event keyboardEvent;

#include "button.hpp"

#endif 
