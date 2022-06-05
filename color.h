#ifndef COLOR_H
#define COLOR_H

class color
{
public:
	color();

	color(Uint8 r, Uint8 g, Uint8 b);

	color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	Uint8 getRed() const;
	Uint8 getGreen() const;
	Uint8 getBlue() const;
	Uint8 getAlpha() const;

	void setRed(Uint8 value) { red = value; }
	void setGreen(Uint8 value) { green = value; }
	void setBlue(Uint8 value) { blue = value; }
	void setAlpha(Uint8 value) { alpha = value; }

	color operator=(const color& rhs);

	color operator*(const color& rhs); //multiplication operator for 3d shading purposes

	bool operator==(const color& rhs);

protected:
	Uint8 red;
	Uint8 green;
	Uint8 blue;
	Uint8 alpha;

};

//a faster, more stripped down color for best possible 3d performance
class color24
{
public:
	color24();

	color24(Uint8 r, Uint8 g, Uint8 b);

	Uint8 getRed() const;
	Uint8 getGreen() const;
	Uint8 getBlue() const;

	void setRed(Uint8 value) { red = value; }
	void setGreen(Uint8 value) { green = value; }
	void setBlue(Uint8 value) { blue = value; }

	color24 operator=(const color24& rhs);

	color24 operator*(const color24& rhs); //multiplication operator for 3d shading purposes

	bool operator==(const color24& rhs);

protected:
	int red;
	int green;
	int blue;
	int alpha;

};

#include "color.hpp"

#endif