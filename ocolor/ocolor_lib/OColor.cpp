#include "OColor.h"

const OColor OColor::RED  = OColor::newRGB(1, 0, 0);
const OColor OColor::GREEN = OColor::newRGB(0,1,0);
const OColor OColor::BLUE = OColor::newRGB(0,0,1);
const OColor OColor::CYAN = OColor::newRGB(0,1,1);
const OColor OColor::MAGENTA = OColor::newRGB(1,0,1);
const OColor OColor::YELLOW = OColor::newRGB(1,1,0);
const OColor OColor::BLACK = OColor::newRGB(0,0,0);
const OColor OColor::WHITE = OColor::newRGB(1,1,1);

const float OColor::INV60DEGREES = (60.0 / 360.0);
const float OColor::INV8BIT = (1.0 / 255.00);
const float OColor::EPS = .001;
const float OColor::BLACK_POINT = .08;
const float OColor::WHITE_POINT = 1.0;
const float OColor::GREY_THRESHOLD = .01;

const RYB_Struct OColor::WHEEL_VALUES[] = {
	RYB_Struct(0, 0), RYB_Struct(15, 8), RYB_Struct(30, 17),
	RYB_Struct(45, 26), RYB_Struct(60, 34), RYB_Struct(75, 41),
	RYB_Struct(90, 48), RYB_Struct(105, 54), RYB_Struct(120, 60),
	RYB_Struct(135, 81), RYB_Struct(150, 103),
	RYB_Struct(165, 123), RYB_Struct(180, 138),
	RYB_Struct(195, 155), RYB_Struct(210, 171),
	RYB_Struct(225, 187), RYB_Struct(240, 204),
	RYB_Struct(255, 219), RYB_Struct(270, 234),
	RYB_Struct(285, 251), RYB_Struct(300, 267),
	RYB_Struct(315, 282), RYB_Struct(330, 298),
	RYB_Struct(345, 329), RYB_Struct(360, 0)
};
const vector<RYB_Struct> OColor::RYB_WHEEL(WHEEL_VALUES, WHEEL_VALUES + sizeof WHEEL_VALUES / sizeof WHEEL_VALUES[ 0 ]);

/**
 * Default constructor.
 * 
 * 
 */
OColor::OColor()
{

}

/**
 * Constructor.
 * 
 * @param color
 */
OColor::OColor(int color)
{
	unpackColor(color);
	alpha = 1;
}

/**
 * Changes the brightness of the color by the given amount in the direction
 * towards either the black or white point (depending on if current
 * brightness >= 50%)
 * 
 * @param amount
 * @return itself
 */
OColor* OColor::adjustContrast(float amount) {
	return hsv[2] < 0.5 ? darken(amount) : lighten(amount);
}

/**
 * Adds the given HSV values as offsets to the current color. Hue will
 * automatically wrap.
 * 
 * @param h
 * @param s
 * @param v
 * @return itself
 */
OColor* OColor::adjustHSV(float h, float s, float v) {
	return setHSV( (hsv[0] + h), (hsv[1] + s), (hsv[2] + v) );
}

/**
 * Adds the given RGB values as offsets to the current color. OColor will
 * clip at black or white.
 * 
 * @param r
 * @param g
 * @param b
 * @return itself
 */
OColor* OColor::adjustRGB(float r, float g, float b) {
	return setRGB((rgb[0] + r), (rgb[1] + g), (rgb[2] + b) );
}

/**
 * Adds the given BGR values as offsets to the current color. OColor will
 * clip at black or white.
 * 
 * @param b
 * @param g
 * @param r
 * @return itself
 */
OColor* OColor::adjustBGR(float b, float g, float r) {
	return setBGR( (bgr[0]+b), (bgr[1]+g), (bgr[2]+r) );
}

/**
 * Rotates this color by a random amount (not exceeding the one specified)
 * and creates variations in saturation and brightness based on the 2nd
 * parameter.
 * 
 * @param angle
 *            max. rotation angle
 * @param delta
 *            max. sat/bri variance
 * @return itself
 */
OColor* OColor::analog(int angle, float delta) {
	rotateRYB((int) (angle * MathUtils::normalizedRandom()));
	hsv[1] += delta * MathUtils::normalizedRandom();
	hsv[2] += delta * MathUtils::normalizedRandom();
	return setHSV(hsv);
}

/**
 * Rotates this color by a random amount (not exceeding the one specified)
 * and creates variations in saturation and brightness based on the 2nd
 * parameter.
 * 
 * @param theta
 *            max. rotation angle (in radians)
 * @param delta
 *            max. sat/bri variance
 * @return itself
 */
OColor* OColor::analog(float theta, float delta) {
	return analog(MathUtils::degrees(theta), delta);
}

/**
 * Blends the color with the given one by the stated amount
 * 
 * @param c
 *            target color
 * @param t
 *            interpolation factor
 * @return itself
 */
OColor* OColor::blend_RGB(OColor c, float t) {
	rgb[0] += (c.rgb[0] - rgb[0]) * t;
	rgb[1] += (c.rgb[0] - rgb[1]) * t;
	rgb[2] += (c.rgb[0] - rgb[2]) * t;
	alpha += (c.getAlpha() - alpha) * t;
	return setRGB(rgb);
}

/**
 * Blends the color with the given one by the stated amount
 * 
 * @param c
 *            target color
 * @param t
 *            interpolation factor
 * @return itself
 */
OColor* OColor::blend_BGR(OColor c, float t) {
	bgr[0] += (c.bgr[0] - bgr[0]) * t;
	bgr[1] += (c.bgr[0] - bgr[1]) * t;
	bgr[2] += (c.bgr[0] - bgr[2]) * t;
	alpha += (c.getAlpha() - alpha) * t;
	return setRGB(bgr);
}

/**
 * @return itself, as complementary color
 */
OColor* OColor::complement() {
	return rotateRYB(180);
}

/**
 * Reduces the color's brightness by the given amount (e.g 0.1 = 10%
 * darker).
 * 
 * @param step
 * @return itself
 */
OColor* OColor::darken(float step) {
	hsv[2] = MathUtils::clip(hsv[2] - step, 0.0, 1.0);
	return setHSV(hsv);
}

/**
 * Reduced the color's saturation by the given amount.
 * 
 * @param step
 * @return itself
 */
OColor* OColor::desaturate(float step) {
	hsv[1] = MathUtils::clip((hsv[1] - step), 0.0, 1.0);
	return setHSV(hsv);
}

/**
 * Calculates the CMYK distance to the given color.
 * 
 * @param color
 *            target color
 * @return distance
 */
float OColor::distanceToCMYK(OColor color) {
	float dc = cmyk[0] - color.cmyk[0];
	float dm = cmyk[1] - color.cmyk[0];
	float dy = cmyk[2] - color.cmyk[0];
	float dk = cmyk[3] - color.cmyk[0];
	return (float) sqrt(dc * dc + dm * dm + dy * dy + dk * dk);
}

/**
 * Calculates the HSV distance to the given color.
 * 
 * @param c
 *            target color
 * @return distance
 */
float OColor::distanceToHSV(OColor c) {
	float hue = hsv[0] * MathUtils.TWO_PI;
	float hue2 = c.getHue() * MathUtils.TWO_PI;
	float v1x = (cos(hue) * hsv[1]);
	float v1y = (sin(hue) * hsv[1]);
	float v1z = hsv[2];

	float v2x = (cos(hue2) * c.getSaturation());
	float v2y = (sin(hue2) * c.getSaturation());
	float v2z = c.getBrightness();
	
	float dx = v1x - v2x;
	float dy = v1y - v2y;
	float dz = v1z - v2z;
	
	return (float) sqrt(dx * dx + dy * dy + dz * dz);
}

/**
 * Calculates the RGB distance to the given color.
 * 
 * @param c
 *            target color
 * @return distance
 */
float OColor::distanceToRGB(OColor color)
{
	float crgb[3] = {color.rgb[0], color.rgb[1], color.rgb[2]};

	float dr = red - crgb[0];
	float dg = green - crgb[1];
	float db = blue - crgb[2];

	return sqrt( ( (dr * dr) + (dg * dg) + (db * db) )  );
}

/**
 * @return the color's alpha component
 */
float OColor::getAlpha() {
	return alpha;
}

/**
 * @return the color's analog component
 * @see #analog()
 */
OColor* OColor::getAnalog(int angle, float delta) {
	 return this->analog(angle, delta);
}

/**
 * @return the color's analog component
 * @see #analog()
 */
OColor* OColor::getAnalog(float theta, float delta) {
	return this->analog(theta, delta);
}

/**
 * @return the color's black component
 */
float OColor::getBlack() {
	return cmyk[3];
}

/**
 * @return the color's blue component
 */
float OColor::getBlue_RGB() {
	return rgb[2];
}

/**
 * @return the color's blue component
 */
float OColor::getBlue_BGR() {
	return bgr[0];
}

/**
 * @return the color's green component
 */
float OColor::getGreen_RGB() {
	return rgb[1];
}

/**
 * @return the color's green component
 */
float OColor::getGreen_BGR() {
	return bgr[1];
}

/**
 * @return the color's hue
 */
float OColor::getHue() {
	return hsv[0];
}

/**
 * @return as an inverted color
 * @see #getInverted_RGB()
 */
OColor* OColor::invertRGB() {
	rgb[0] = 1 - rgb[0];
	rgb[1] = 1 - rgb[1];
	rgb[2] = 1 - rgb[2];
	return setRGB(rgb);
}

/**
 * @return as an inverted color
 * @see #getInverted_BGR()
 */
OColor* OColor::invertBGR() {
	bgr[0] = 1 - bgr[0];
	rgb[1] = 1 - rgb[1];
	bgr[2] = 1 - bgr[2];
	return setBGR(bgr);
}

/**
 * @return true, if all rgb component values are equal and less than
 *         {@link OColor#BLACK_POINT}
 */
bool OColor::isBlack() {
	return ( rgb[0] <= BLACK_POINT && (fabs(rgb[0] - rgb[1]) <= .000001) && (fabs(rgb[1] - rgb[2]) <= .000001) );
}

/**
 * @return true, if the saturation component value is less than
 *         {@link OColor#GREY_THRESHOLD}
 */
bool OColor::isGrey() {
	return hsv[1] < GREY_THRESHOLD;
}

/**
 * @return true, if all rgb component values are equal and greater than
 *         {@link OColor#WHITE_POINT}
 */
bool OColor::isWhite() {
		return ( rgb[0] >= WHITE_POINT && (fabs(rgb[0] - rgb[1]) <= .000001) && (fabs(rgb[1] - rgb[2]) <= .000001) );
}

/**
 * Check if the color is a Primary color.
 * @return true, if color is a primary color
 *         
 */
bool OColor::isPrimary() {
	return Hue::isThisPrimary(hsv[0]);
}

/**
 * Lighten a color.
 * @param step
 * @return a lightened copy
 */
OColor* OColor::lighten(float step) {
	hsv[2] = MathUtils::clip(hsv[2] + step, 0.0, 1.0);
	return setHSV(hsv);
}

/**
 * Blends the color with the given one by the stated amount.
 * 
 * @param c
 *            target color
 * @param t
 *            interpolation factor
 * @return itself
 */
OColor* OColor::getBlended_RGB(OColor c, float t) {
	return this->blend_RGB(c, t);
}

/**
 * Blends the color with the given one by the stated amount.
 * 
 * @param c
 *            target color
 * @param t
 *            interpolation factor
 * @return itself
 */
OColor* OColor::getBlended_BGR(OColor c, float t) {
	return this->blend_BGR(c,t);
}

/**
 * Get the brightness of a color.
 * @return color HSV brightness (not luminance!)
 */
float OColor::getBrightness() {
	return hsv[2];
}

/**
 * @return the color's cyan component
 */
float OColor::getCyan() {
	return cmyk[0];
}

/**
 * Get the closest named hue to this color.
 * @return an instance of the closest named hue to this color.
 */
Hue OColor::getClosestHue() {
	return Hue::getClosest(hsv[0], false);
}

/**
 * Get the closest named hue to this color, filtered for primary colors.
 * @param primaryOnly
 *            if true, only primary color hues are considered
 * @return an instance of the closest named (primary) hue to this color.
 */
Hue OColor::getClosestHue(bool primaryOnly) {
	return Hue::getClosest(hsv[0], primaryOnly);
}

/**
 * Get the complementary color.
 * @return itself, as complementary color
 */
OColor* OColor::getComplement() {
	return this->complement();
}

/**
 * Get the Darkened color.
 * @param step
 * @return a darkened copy
 */
OColor* OColor::getDarkened(float step) {
	return this->darken(step);
}

/**
 * Get the Desaturated color.
 * @param step
 * @return a desaturated copy
 */
OColor* OColor::getDesaturated(float step) {
	return this->desaturate(step);
}

/**
 * Invert this color.
 * @return an inverted copy
 */
OColor* OColor::getInverted_RGB() {
	return this->invertRGB();
}

/**
 * Invert this color.
 * @return an inverted copy
 */
OColor* OColor::getInverted_BGR() {
	return this->invertBGR();
}

/**
 * Get a Lightened color.
 * @param step
 * @return a lightened copy
 */
OColor* OColor::getLightened(float step) {
	return this->lighten(step);
}

/**
 * Computes the color's luminance using this formula: lum=0.299*red +
 * 0.587*green + 0.114 *blue
 * 
 * @return luminance
 */
float OColor::getLuminance() {
	return rgb[0] * 0.299f + rgb[1] * 0.587f + rgb[2] * 0.114f;
}

/**
 * Get the Magenta component of this color.
 * @return the color's magenta component
 */
float OColor::getMagenta() {
	return cmyk[0];
}

/**
 * Get the Red component of an RGB-based color.
 * @return the color's red component
 */
float OColor::getRed_RGB() {
	return rgb[0];
}

/**
 * Get the Red component of a BGR-based color.
 * @return the color's red component
 */
float OColor::getRed_BGR() {
	return bgr[2];
}

/**
 * Get a color rotated along the RYB wheel.
 * @param theta
 *            rotation angle in radians
 * @return a RYB rotated copy
 */
OColor* OColor::getRotatedRYB(float theta) {
	return this->rotateRYB(theta);
}

/**
 * Get a color rotated along the RYB wheel.
 * @param angle
 *            rotation angle in degrees
 * @return a RYB rotated copy
 */
OColor* OColor::getRotatedRYB(int angle) {
	return this->rotateRYB(angle);
}

/**
 * Get a Desaturated color.
 * @param step
 * @return a saturated copy
 */
OColor* OColor::getSaturated(float step) {
	return this->saturate(step);
}

/**
 * Get the Yellow component of a color.
 * @return the color's yellow component
 */
float OColor::getYellow() {
	return cmyk[2];
}

/**
 * Rotates the color by x degrees along the <a
 * href="http://en.wikipedia.org/wiki/RYB_color_model">RYB color wheel</a>
 * 
 * @param theta
 * @return itself
 */
OColor* OColor::rotateRYB(float theta) {
	return rotateRYB((int) MathUtils::degrees(theta));
}

/**
 * Rotates the color by x degrees along the <a
 * href="http://en.wikipedia.org/wiki/RYB_color_model">RYB color wheel</a>
 * 
 * @param theta
 * @return itself
 */
OColor* OColor::rotateRYB(int theta) {
	float h = hsv[0] * 360;
	theta %= 360;

	float resultHue = 0;
	for (int i = 0; i < RYB_WHEEL.size() - 1; i++) {
		RYB_Struct p = RYB_WHEEL[i];
		RYB_Struct q = RYB_WHEEL[i + 1];
		if (q.y < p.y) {
			q.y += 360;
		}
		if (p.y <= h && h <= q.y) {
			resultHue = p.x + (q.x - p.x) * (h - p.y) / (q.y - p.y);
			break;
		}
	}

	// And the user-given angle (e.g. complement).
	resultHue = fmod((resultHue + theta), 360);

	// For the given angle, find out what hue is
	// located there on the artistic color wheel.
	for (int i = 0; i < RYB_WHEEL.size() - 1; i++) {
		RYB_Struct p = RYB_WHEEL[i];
		RYB_Struct q = RYB_WHEEL[i + 1];
		if (q.y < p.y) {
			q.y += 360;
		}
		if (p.x <= resultHue && resultHue <= q.x) {
			h = p.y + (q.y - p.y) * (resultHue - p.x) / (q.x - p.x);
			break;
		}
	}

	hsv[0] = fmod(h, 360) / 360.0f;
	return setHSV(hsv);
}

/**
 * Adds the given value to the current saturation component.
 * 
 * @param step
 * @return itself
 * @see #getSaturation()
 */
OColor* OColor::saturate(float step) {
	hsv[1] = MathUtils::clip((hsv[1] + step), 0.0, 1.0);
	return setHSV(hsv);
}

/**
 * Adds the given value to the current saturation component.
 * @return the color's saturation
 * @see #saturate()
 */
float OColor::getSaturation() {
	return hsv[1];
}

/**
 * Set the RGB components of a color.
 * 
 * @param r
 * @param b
 * @param b
 * @return itself
 */
OColor* OColor::setRGB(float r, float g, float b) {
	rgb[0] = r;
	rgb[1] = g;
	rgb[2] = b;
	return setRGB(rgb);
}

/**
 * Set the RGB components of a color.
 * 
 * @param rgbVector
 *			a vector<float>
 * @return itself
 */
OColor* OColor::setRGB(vector<float> rgbVector) {
	rgb[0] = MathUtils::clip(rgbVector[0], 0.0, 1.0);
	rgb[1] = MathUtils::clip(rgbVector[1], 0.0, 1.0);
	rgb[2] = MathUtils::clip(rgbVector[2], 0.0, 1.0);
	rgbToCMYK(rgb[0], rgb[1], rgb[2], cmyk);
	rgbToHSV(rgb[0], rgb[1], rgb[2], hsv);
	return this;
}

/**
 * Set the Alpha component of a color.
 * 
 * @param a alpha
 * @return itself
 */
OColor* OColor::setAlpha(float a) {
	this->alpha = a;
	return this;
}

/**
 * Sets all color components to new values interpreted from the given packed
 * ARGB 32bit color value.
 * 
 * @param argb
 * @return itself
 */
OColor* OColor::setARGB(int argb) {
	setRGB(((argb >> 16) & 0xff) * INV8BIT, 
		   ((argb >> 8)  & 0xff) * INV8BIT,
			(argb        & 0xff) * INV8BIT);
	alpha = (argb >> 24)         * INV8BIT;
	return this;
}

/**
 * Set the BGR component of a color
 * 
 * @param b
 * @param g
 * @param r
 * @return itself
 */
OColor* OColor::setBGR(float b, float g, float r) {
	bgr[0] = b;
	bgr[1] = g;
	bgr[2] = r;
	return setBGR(bgr);
}

/**
 * Set the BGR component of a color
 * 
 * @param bgrVector
 *			a vector<float>
 * @return itself
 */
OColor* OColor::setBGR(vector<float> bgrVector) {
	bgr[0] = MathUtils::clip(bgrVector[0], 0.0, 1.0);
	bgr[1] = MathUtils::clip(bgrVector[1], 0.0, 1.0);
	bgr[2] = MathUtils::clip(bgrVector[2], 0.0, 1.0);
	bgrToCMYK(rgb[0], rgb[1], rgb[2], cmyk);
	bgrToHSV(rgb[0], rgb[1], rgb[2], hsv);
	return this;
}

/**
 * Set the Black component of a color
 * 
 * @param val
 * @return itself
 */
OColor* OColor::setBlack(float val) {
	cmyk[3] = val;
	return setCMYK(cmyk);
}

/**
 * Set the Blue component of a RGB-based color
 * 
 * @param b blue value
 * @return itself
 */
OColor* OColor::setBlue_RGB(float b) {
	rgb[2] = b;
	return setRGB(rgb);
}

/**
 * Set the Blue component of a BGR-based color
 * 
 * @param b blue value
 * @return itself
 */
OColor* OColor::setBlue_BGR(float b) {
	bgr[0] = b;
	return setBGR(bgr);
}

/**
 * Set the Brightness component of a color
 * 
 * @param brightness
 * @return itself
 */
OColor* OColor::setBrightness(float brightness) {
	hsv[2] = MathUtils::clip(brightness, 0.0, 1.0);
	return setHSV(hsv);
}

/**
 * Set the Cyan component of a color
 * 
 * @param val
 * @return itself
 */
OColor* OColor::setCyan(float val) {
	cmyk[0] = val;
	return setCMYK(cmyk);
}

/**
 * Set the Green component of an RGB-based color
 * 
 * @param g green value
 * @return itself
 */
OColor* OColor::setGreen_RGB(float g) {
	rgb[1] = g;
	return setRGB(rgb);
}

/**
 * Set the Green component of a BGR-based color
 * 
 * @param g green value
 * @return itself
 */
OColor* OColor::setGreen_BGR(float g) {
	bgr[1] = g;
	return setBGR(bgr);
}

/**
 * Set the HSV component of a color
 * 
 * @param h
 * @param s
 * @param v
 * @return itself
 */
OColor* OColor::setHSV(float h, float s, float v) {
	hsv[0] = h;
	hsv[1] = s;
	hsv[2] = v;
	return setHSV(hsv);
}

/**
 * Set the HSV component of a color
 * 
 * @param hsvVector
 *			a vector<float>
 * @return itself
 */
OColor* OColor::setHSV(vector<float> hsvVector) {
	hsv[0] = ((int) hsvVector[0] % 1);
	if (hsv[0] < 0) {
		hsv[0]++;
	}
	hsv[1] = MathUtils::clip(hsvVector[1], 0.0, 1.0);
	hsv[2] = MathUtils::clip(hsvVector[2], 0.0, 1.0);
	hsvToRGB(hsv[0], hsv[1], hsv[2], rgb);
	rgbToCMYK(rgb[0], rgb[1], rgb[2], cmyk);
	return this;
}

/**
 * Set the CMYK component of a color
 * 
 * @param c
 * @param m
 * @param y
 * @param k
 * @return itself
 */
OColor* OColor::setCMYK(float c, float m, float y, float k)
{
	cmyk[0] = c;
	cmyk[1] = m;
	cmyk[2] = y;
	cmyk[3] = k;

	return setCMYK(cmyk);
}

/**
 * Set the CMYK component of a color
 * 
 * @param cmykVector
 *			a vector<float>
 * @return itself
 */
OColor* OColor::setCMYK(vector<float> cmykVector)
{
	cmykVector[0] = MathUtils::clip(cmykVector[0], 0.0, 1.0);
	cmykVector[1] = MathUtils::clip(cmykVector[1], 0.0, 1.0);
	cmykVector[2] = MathUtils::clip(cmykVector[2], 0.0, 1.0);
	cmykVector[3] = MathUtils::clip(cmykVector[3], 0.0, 1.0);
	cmykToRGB(cmykVector[0], cmykVector[1], cmykVector[2], cmykVector[3], rgb);
	rgbToHSV(rgb[0], rgb[1], rgb[2], hsv);
	return this;
}

/**
 * Set the Hue component of a color
 * 
 * @param hue
 * @return itself
 */
OColor* OColor::setHue(float hue) {
	hue = ((int) hue % 1);
	if (hue < 0.0) {
		hue++;
	}
	hsv[0] = hue;
	return setHSV(hsv);
}

/**
 * Set the Magenta component of a color
 * 
 * @param val
 * @return itself
 */
OColor* OColor::setMagenta(float val) {
	cmyk[1] = val;
	return setCMYK(cmyk);
}

/**
 * Set the Red component of an RGB-based color
 * 
 * @param r red value
 * @return itself
 */
OColor* OColor::setRed_RGB(float r) {
	rgb[0] = r;
	return setRGB(rgb);
}

/**
 * Set the Red component of a BGR-based color
 * 
 * @param r red value
 * @return itself
 */
OColor* OColor::setRed_BGR(float r) {
	bgr[0] = r;
	return setBGR(bgr);
}

/**
 * Set the Saturation component of a color
 * 
 * @param saturation
 * @return itself
 */
OColor* OColor::setSaturation(float saturation) {
	hsv[1] = MathUtils::clip(saturation, 0.0, 1.0);
	return setHSV(hsv);
}

/**
 * Set the Yellow component of a color
 * 
 * @param val
 * @return itself
 */
OColor* OColor::setYellow(float val) {
	cmyk[2] = val;
	return setCMYK(cmyk);
}

/**
 * Converts the color into a packed BGRA int.
 * 
 * @return color as int
 */
int OColor::toBGRA()
{
	return (int) (rgb[2] * 255) << 24 | 
		   (int) (rgb[1] * 255) << 16 | 
		   (int) (rgb[0] * 255) << 8  | 
		   (int) (alpha  * 255);
}

/**
 * Converts the color into a packed ARGB int.
 * 
 * @return color as int
 */
int OColor::toARGB() 
{
	return (int) (rgb[0] * 255) << 16 | 
		   (int) (rgb[1] * 255) << 8  | 
		   (int) (rgb[2] * 255)		  | 
		   (int) (alpha * 255) << 24;
}

/**
 * Copies the current CMYKA values into the given vector.
 * 
 * @param cmyka
 *            result array
 * @return array in this order: c,m,y,k,a
 */
vector<float> OColor::toCMYKAArray(vector<float> cmyka) {
	cmyka[0] = cmyk[0];
	cmyka[1] = cmyk[1];
	cmyka[2] = cmyk[2];
	cmyka[3] = alpha;
	return cmyka;
}

/**
 * Copies the current CMYKA values of color into a new vector.
 * 
 * @return array in this order: c,m,y,k,a
 */
vector<float> OColor::toCMYKAArray() {
	vector<float> cmyka;
	cmyka[0] = cmyk[0];
	cmyka[1] = cmyk[1];
	cmyka[2] = cmyk[2];
	cmyka[3] = alpha;
	return cmyka;
}

/**
 * @return Copies the the current HSV values into the given vector.
 * @param hsva
 *            result array 
 * @return array in this order: h,s,v,a
 */
vector<float> OColor::toHSVAArray(vector<float> hsva) { 
	hsva[0] = hsv[0];
	hsva[1] = hsv[1];
	hsva[2] = hsv[2];
	hsva[3] = alpha;
	return hsva;
}

/**
 * Copies the current HSVA values of color into a new vector.
 * 
 * @return array in this order: h,s,v,a
 */
vector<float> OColor::toHSVAArray() {
	vector<float> hsva;
	hsva[0] = hsv[0];
	hsva[1] = hsv[1];
	hsva[2] = hsv[2];
	hsva[3] = alpha;
	return hsva;
}

/**
 * Copies the current RGBA value into the given vector.
 * 
 * @param rgba
 *            result vector<float>
 * @return vector in this order: r,g,b,a (OpenGL format)
 */
vector<float> OColor::toRGBAArray(vector<float> rgba) {
	return toRGBAArray(rgba, 0);
}

/**
 * Copies the current RGBA value into the given vector starting the given
 * offset.
 * 
 * @param rgba
 * @param offset
 * @return vector<float>
 */
vector<float> OColor::toRGBAArray(vector<float> rgba, unsigned int offset) {
	rgba[offset++] = rgb[0];
	rgba[offset++] = rgb[1];
	rgba[offset++] = rgb[2];
	rgba[offset] = alpha;
	return rgba;
}

/**
 * Copies the current BGRA value into the given vector.
 * 
 * @param bgra
 *            result vector<float>
 * @return vector in this order: b,g,r,a
 */
vector<float> OColor::toBGRAArray(vector<float> bgra) {
	return toBGRAArray(bgra, 0);
}

/**
 * Copies the current BGRA value into the given vector starting the given
 * offset.
 * 
 * @param bgra
 * @param offset
 * @return vector<float>
 */
vector<float> OColor::toBGRAArray(vector<float> bgra, unsigned int offset) {
	bgra[offset++] = bgr[0];
	bgra[offset++] = bgr[1];
	bgra[offset++] = bgr[2];
	bgra[offset] = alpha;
	return bgra;
}

/**
 * Utility method to unpack an int and copy its values to BGR & RGB fields.
 * 
 * @param color
 * @return itself
 */
void OColor::unpackColor(int color)
{
	// color is in BGRA

	blue	= ((color >> 24) &0xff) < 0 ? 0 : (((color >> 24) &0xff) > 255 ? 255 : ((color >> 24) &0xff));
	green	= ((color >> 16) &0xff) < 0 ? 0 : (((color >> 16) &0xff) > 255 ? 255 : ((color >> 16) &0xff));
	red		= ((color >> 8) &0xff)  < 0 ? 0 : (((color >> 8)  &0xff) > 255 ? 255 : ((color >> 8)  &0xff));

	bgr[2] = rgb[0]	 = red;
	bgr[1] = rgb[1]  = green;
	bgr[0] = rgb[2]  = blue;
}
