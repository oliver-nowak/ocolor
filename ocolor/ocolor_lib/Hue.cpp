#include "Hue.h"

const Hue Hue::RED = Hue::Hue("red", 0, true);
const Hue Hue::ORANGE = Hue::Hue("orange", 30 / 360.0f, true);
const Hue Hue::YELLOW = Hue::Hue("yellow", 60 / 360.0f, true);
const Hue Hue::LIME = Hue::Hue("lime", 90 / 360.0f);
const Hue Hue::GREEN = Hue::Hue("green", 120 / 360.0f, true);
const Hue Hue::TEAL = Hue::Hue("teal", 150 / 360.0f);
const Hue Hue::CYAN = Hue::Hue("cyan", 180 / 360.0f);
const Hue Hue::AZURE = Hue::Hue("azure", 210 / 360.0f);
const Hue Hue::BLUE = Hue::Hue("blue", 240 / 360.0f, true);
const Hue Hue::INDIGO = Hue::Hue("indigo", 270 / 360.0f);
const Hue Hue::PURPLE = Hue::Hue("purple", 300 / 360.0f, true);
const Hue Hue::PINK = Hue::Hue("pink", 330 / 360.0f, true);
const float Hue::PRIMARY_VARIANCE = 0.01;

vector<Hue> Hue::primaryColors(10);
tr1::unordered_map<const char*, Hue> Hue::namedColors(10);

/**
 * Default constructor.
 * 
 */
Hue::Hue()
{
	this->name = "";
	this->hue = 0.0;
	this->isPrimary = false;
}

/**
 * Constructor.
 * Create a hue with a name and initialize a hue value.
 * 
 * @param stringname
 * @param hue
 * @return a Hue reference
 */
Hue::Hue(const char* stringname, float hue)
{
	this->name = stringname;
	this->hue = hue;
	this->isPrimary = false;
}

/**
 * Constructor.
 * Create a hue with a name, initialize a hue value, and set its primary color flag.
 * 
 * @param stringname
 * @param hue
 * @param isPrimary
 * @return a Hue reference
 */
Hue::Hue(const char* stringname, float hue, bool isPrimary)
{
	this->name = stringname;
	this->hue = hue;
	this->isPrimary = isPrimary;
}

/**
 * Get the name of this Hue.
 * 
 * @return name of the Hue
 */
const char* Hue::getName()
{
	return this->name;
}

/**
 * Get the hue value of this Hue.
 * 
 * @return hue value of the Hue
 */
float Hue::getHue()
{
	return this->hue;
}

/**
 * Get this Hue's isPrimary flag.
 * 
 * @return the Hue's isPrimary flag
 */
bool Hue::isHuePrimary()
{
	return this->isPrimary;
}