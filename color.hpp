color :: color()
{

}

color :: color(Uint8 r, Uint8 g, Uint8 b)
{
	red = r;
	green = g;
	blue = b;
	alpha = 255;
}

color :: color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	red = r;
	green = g;
	blue = b;
	alpha = a;
}

Uint8 color :: getRed() const
{
	return red;
}

Uint8 color :: getGreen() const
{
	return green;
}

Uint8 color :: getBlue() const
{
	return blue;
}

Uint8 color :: getAlpha() const
{
	return alpha;
}

color color::operator=(const color& rhs)
{
	red = rhs.getRed();
	green = rhs.getGreen();
	blue = rhs.getBlue();
	alpha = rhs.getAlpha();
	return *this;
}

color color::operator*(const color& rhs)
{
	red = red * static_cast<float>(rhs.getRed()/255.0f);
	green = green * static_cast<float>(rhs.getGreen()/255.0f);
	blue = blue * static_cast<float>(rhs.getBlue()/255.0f);
	//alpha = alpha * static_cast<float>(rhs.getAlpha()/255.0f);
	return *this;
}

bool color::operator==(const color& rhs)
{
	if (rhs.getBlue() == blue && rhs.getGreen() == green && rhs.getRed() == red && rhs.getAlpha() == alpha)
	{
		return true;
	}
	return false;
}

//======================================
//24 bit uint color
//======================================
color24 :: color24()
{

}

color24 :: color24(Uint8 r, Uint8 g, Uint8 b)
{
	red = r;
	green = g;
	blue = b;
}


Uint8 color24 :: getRed() const
{
	return red;
}

Uint8 color24 :: getGreen() const
{
	return green;
}

Uint8 color24 :: getBlue() const
{
	return blue;
}

color24 color24::operator=(const color24& rhs)
{
	red = rhs.getRed();
	green = rhs.getGreen();
	blue = rhs.getBlue();
	return *this;
}

color24 color24::operator*(const color24& rhs)
{
	red = red * static_cast<float>(rhs.getRed()/255.0f);
	green = green * static_cast<float>(rhs.getGreen()/255.0f);
	blue = blue * static_cast<float>(rhs.getBlue()/255.0f);
	return *this;
}

bool color24::operator==(const color24& rhs)
{
	if (rhs.getBlue() == blue && rhs.getGreen() == green && rhs.getRed() == red)
	{
		return true;
	}
	return false;
}