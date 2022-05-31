#ifndef COLOR_H
#define COLOR_H

class color
{
public:
	color();

	color(int r, int g, int b);

	color(int r, int g, int b, int a);

	int getRed() const;
	int getGreen() const;
	int getBlue() const;
	int getAlpha() const;

	void setRed(int value) { red = value; }
	void setGreen(int value) { green = value; }
	void setBlue(int value) { blue = value; }
	void setAlpha(int value) { alpha = value; }

	color operator=(const color& rhs);

	color operator*(const color& rhs); //multiplication operator for 3d shading purposes

	bool operator==(const color& rhs);

protected:
	int red;
	int green;
	int blue;
	int alpha;

};

#include "color.hpp"

#endif