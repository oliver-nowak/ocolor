/* 
 * This is a C++ port of the toxi colorutils lib for Java & Processing.
 *
 * This library was inspired by Karsten Schmidt's (AKA toxi) color
 * library for Java & Processing. His excellent code provided the
 * framework for this C++ / openFrameWorks implementation.
 * You can find his color library, as well as his other code at
 *	http://hg.postspectacular.com/toxiclibs/wiki/Home or http://toxiclibs.org/
 *
 *
 * Copyright (c) 2010 Oliver Nowak
 *
 * 
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * http://creativecommons.org/licenses/LGPL/2.1/
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#pragma once
#include "Hue.h"
#include "math.h"
#include "MathUtils.h"
#include "RYB_Struct.h"
#include <vector>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>

// TODO:
// ++ add links between common methods
// ++ refactor params to be easier to read
// ++ add param type info
// DONE refactor signatures to be consistent with docs
// ++ refactor RYB_Struct to be type-def'd inner-class/struct of OColor?
// DONE refactor params that reference static fields or class methods (eg. 'blue')

using namespace std;
/**
 * Floating point color class with implicit RGB, HSV, CMYK access modes,
 * conversion and color theory utils. Based on Toxi's <a href="">TColor</a> class 
 * and his Java/Processing colorutils lib.
 * 
 * 
 */
class OColor {
public:
	OColor();
	OColor(int color);

	static const float INV60DEGREES;
	static const float INV8BIT;
	static const float EPS;
	/**
     * Maximum rgb component value for a color to be classified as black.
     * 
     * @see #isBlack()
     */
	static const float BLACK_POINT;

	/**
     * Minimum rgb component value for a color to be classified as white.
     * 
     * @see #isWhite()
     */
	static const float WHITE_POINT;

	/**
     * Maximum saturations value for a color to be classified as grey
     * 
     * @see #isGrey()
     */
	static const float GREY_THRESHOLD;
	static const RYB_Struct WHEEL_VALUES[];
	static const vector<RYB_Struct> RYB_WHEEL;
	static const OColor RED;
	static const OColor GREEN;
	static const OColor BLUE;
	static const OColor CYAN;
	static const OColor MAGENTA;
	static const OColor YELLOW;
	static const OColor BLACK;
	static const OColor WHITE;

	/**
     * Converts CMYK floats into an RGB vector.
     * 
     * @param c
     * @param m
     * @param y
     * @param k
     * @return rgb vector
     */
	static vector<float> cmykToRGB(float c, float m, float y, float k) 
	{ 
		return cmykToRGB(c, m, y, k, _tempVector);
	}

	/**
     * Converts CMYK floats into an RGB vector.
     * 
     * @param c
     * @param m
     * @param y
     * @param k
     * @return bgr vector
     */
	static vector<float> cmykToBGR(float c, float m, float y, float k) 
	{
		return cmykToBGR(c, m, y, k, _tempVector);
	}
	
	/**
     * Converts CMYK floats into an RGB vector.
     * 
     * @param c
     * @param m
     * @param y
     * @param k
	 * @param rgb
     * @return rgb vector
     */
	static vector<float> cmykToRGB(float c, float m, float y, float k, vector<float> rgb) 
	{
		float _red   = (c+k);
		float _blue  = (m+k);
		float _green = (y+k);
		rgb[0] = (1.0 < (_red)  ? 1.0 : (_red));
		rgb[1] = (1.0 < (_blue) ? 1.0 : (_blue));
		rgb[2] = (1.0 < (_green)? 1.0 : (_green));
		return rgb;
	}

	/**
     * Converts CMYK floats into the given RGB vector.
     * 
     * @param c
     * @param m
     * @param y
     * @param k
     * @param bgr
     * @return bgr vector
     */
	static vector<float> cmykToBGR(float c, float m, float y, float k, vector<float> bgr)
	{
		float _blue  = (m+k);
		float _green = (y+k);
		float _red   = (c+k);
		bgr[0] = (1.0 < (_blue)  ? 1.0 : _blue);
		bgr[1] = (1.0 < (_green) ? 1.0 : _green);
		bgr[3] = (1.0 < (_red)   ? 1.0 : _red);
		return bgr;
	}

	/**
     * Converts hex string into a RGB vector.
     * 
     * @param stringHex
     * @return rgb vector
     */
	static vector<float> hexToRGB(const char* stringHex)
	{
		char* pEnd;
		int hexInt;
		hexInt = (int) strtoul(stringHex, &pEnd, 16);
		_tempVector[0] = ( (hexInt >> 16) &0xFF ) * INV8BIT;
		_tempVector[1] = ( (hexInt >> 8)  &0xFF ) * INV8BIT;
		_tempVector[2] = ( (hexInt     )  &0xFF ) * INV8BIT;

		return _tempVector;
	}

	/**
     * Converts hex string into a BGR vector.
     * 
     * @param stringHex
     * @return bgr vector
     */
	static vector<float> hexToBGR(const char* stringHex)
	{
		char* pEnd;
		int hexInt;
		hexInt = (int) strtoul(stringHex, &pEnd, 16);
		_tempVector[0] = ( (hexInt      )  &0xFF ) * INV8BIT;
		_tempVector[1] = ( (hexInt >> 8 )  &0xFF ) * INV8BIT;
		_tempVector[2] = ( (hexInt >> 16)  &0xFF ) * INV8BIT;
		return _tempVector;	
	}

	/**
     * Converts hex string into a RGB vector.
     * 
     * @param hexString
	 * @param rgb
     * @return rgb vector
     */
	static vector<float> hexToRGB(const char* hexString, vector<float> rgb)
	{
		char * pEnd;
		int hexInt;
		hexInt = strtoul(hexString, &pEnd, 16);

		rgb[0] = ( (hexInt >> 16) &0xFF ) * INV8BIT;
		rgb[1] = ( (hexInt >> 8 ) &0xFF ) * INV8BIT;
		rgb[2] = ( (hexInt      ) &0xFF ) * INV8BIT;

		return rgb;
	}
	
	/**
     * Converts hex string into a BGR vector.
     * 
     * @param hexString
	 * @param bgr
     * @return bgr vector
     */
	static vector<float> hexToBGR(const char* hexString, vector<float> bgr)
	{
		char* pEnd;
		int hexInt;
		hexInt = (int) strtoul(hexString, &pEnd, 16);
		bgr[0] = ( (hexInt      )  &0xFF ) * INV8BIT;
		bgr[1] = ( (hexInt >> 8 )  &0xFF ) * INV8BIT;
		bgr[2] = ( (hexInt >> 16)  &0xFF ) * INV8BIT;
		return bgr;
	}

	/**
     * Converts HSV values into RGB vector.
     * 
     * @param h
     * @param s
     * @param v
     * @return rgb vector
     */
	static vector<float> hsvToRGB(float h, float s, float v)
	{
		return hsvToRGB(h,s,v,_tempVector);
	}
	
	/**
     * Converts HSV values into BGR vector.
     * 
     * @param h
     * @param s
     * @param v
     * @return bgr vector
     */
	static vector<float> hsvToBGR(float h, float s, float v)
	{
		return hsvToBGR(h,s,v, _tempVector);
	}

	/**
     * Converts HSV values into RGB vector.
     * 
     * @param h
     * @param s
     * @param v
	 * @param rgb
     * @return rgb vector
     */
	static vector<float> hsvToRGB(float h, float s, float v, vector<float> rgb)
	{
		if (fabs(s - 0) < 0.0000001) {
			rgb[0] = rgb[1] = rgb[2] = v;
		} else {
			h /= INV60DEGREES;
			int i = (int) h;
			float f = h - i;
			float p = v * (1 - s);
			float q = v * (1 - s * f);
			float t = v * (1 - s * (1 - f));
			if (i == 0) {
				rgb[0] = v;
				rgb[1] = t;
				rgb[2] = p;
			} else if (i == 1) {
				rgb[0] = q;
				rgb[1] = v;
				rgb[2] = p;
			} else if (i == 2) {
				rgb[0] = p;
				rgb[1] = v;
				rgb[2] = t;
			} else if (i == 3) {
				rgb[0] = p;
				rgb[1] = q;
				rgb[2] = v;
			} else if (i == 4) {
				rgb[0] = t;
				rgb[1] = p;
				rgb[2] = v;
			} else {
				rgb[0] = v;
				rgb[1] = p;
				rgb[2] = q;
			}
		}
		return rgb;
	}

	/**
     * Converts HSV values into BGR vector.
     * 
     * @param h
     * @param s
     * @param v
	 * @param bgr
     * @return bgr vector
     */
	static vector<float> hsvToBGR(float h, float s, float v, vector<float> bgr)
	{
		if (fabs(s - 0) < 0.0000001) {
			bgr[0] = bgr[1] = bgr[2] = v;
		} else {
			h /= INV60DEGREES;
			int i = (int) h;
			float f = h - i;
			float p = v * (1 - s);
			float q = v * (1 - s * f);
			float t = v * (1 - s * (1 - f));
			if (i == 0) {
				bgr[0] = p;
				bgr[1] = t;
				bgr[2] = v;
			} else if (i == 1) {
				bgr[0] = p;
				bgr[1] = v;
				bgr[2] = q;
			} else if (i == 2) {
				bgr[0] = t;
				bgr[1] = v;
				bgr[2] = p;
			} else if (i == 3) {
				bgr[0] = v;
				bgr[1] = q;
				bgr[2] = p;
			} else if (i == 4) {
				bgr[0] = v;
				bgr[1] = p;
				bgr[2] = t;
			} else {
				bgr[0] = q;
				bgr[1] = p;
				bgr[2] = v;
			}
		}
		return bgr;
	}

	/**
     * Converts CIE Lab to RGB components.
     * 
     * First we have to convert to XYZ color space. Conversion involves using a
     * white point, in this case D65 which represents daylight illumination.
     * 
     * Algorithm adopted from: http://www.easyrgb.com/math.php
     * 
     * @param l
     * @param a
     * @param b
     * @return rgb vector
     */
	static vector<float> labToRGB(float l, float a, float b)
	{
		return labToRGB(l,a,b, _tempVector);
	}

	/**
     * Converts CIE Lab to BGR components.
     * 
     * First we have to convert to XYZ color space. Conversion involves using a
     * white point, in this case D65 which represents daylight illumination.
     * 
     * Algorithm adopted from: http://www.easyrgb.com/math.php
     * 
     * @param l
     * @param a
     * @param b
     * @return bgr vector
     */
	static vector<float> labToBGR(float l, float a, float b)
	{
		return labToBGR(l,a,b,_tempVector);	
	}

	/**
     * Converts CIE Lab to RGB components.
     * 
     * First we have to convert to XYZ color space. Conversion involves using a
     * white point, in this case D65 which represents daylight illumination.
     * 
     * Algorithm adopted from: http://www.easyrgb.com/math.php
     * 
     * @param l
     * @param a
     * @param b
     * @param rgb
     * @return rgb vector
     */
	static vector<float> labToRGB(float l, float a, float b, vector<float> rgb)
	{
		float y = (l + 16) / 116.0f;
		float x = a / 500.0f + y;
		float z = y - b / 200.0f;
		rgb[0] = x;
		rgb[1] = y;
		rgb[2] = z;
		for (int i = 0; i < 3; i++) {
			float p = (float) pow(rgb[i], 3);
			if (p > 0.008856) {
				rgb[i] = p;
			} else {
				rgb[i] = (rgb[i] - 16 / 116.0f) / 7.787f;
			}
		}

		// Observer = 2, Illuminant = D65
		x = rgb[0] * 0.95047f;
		y = rgb[1];
		z = rgb[2] * 1.08883f;

		rgb[0] = x * 3.2406f + y * -1.5372f + z * -0.4986f;
		rgb[1] = x * -0.9689f + y * 1.8758f + z * 0.0415f;
		rgb[2] = x * 0.0557f + y * -0.2040f + z * 1.0570f;
		float tpow = 1 / 2.4; // converted this var to float from double
		for (int i = 0; i < 3; i++) {
			if (rgb[i] > 0.0031308) {
				rgb[i] = (float) (1.055 * pow(rgb[i], tpow) - 0.055);
			} else {
				rgb[i] = 12.92f * rgb[i];
			}
		}
		return rgb;
	}
	
	/**
     * Converts CIE Lab to BGR components.
     * 
     * First we have to convert to XYZ color space. Conversion involves using a
     * white point, in this case D65 which represents daylight illumination.
     * 
     * Algorithm adopted from: http://www.easyrgb.com/math.php
     * 
     * @param l
     * @param a
     * @param b
     * @param bgr
     * @return bgr vector
     */
	static vector<float> labToBGR(float l, float a, float b, vector<float> bgr)
	{
		float y = (l + 16) / 116.0f;
		float x = a / 500.0f + y;
		float z = y - b / 200.0f;
		bgr[0] = z;
		bgr[1] = y;
		bgr[2] = x;
		for (int i = 0; i < 3; i++) {
			float p = (float) pow(bgr[i], 3);
			if (p > 0.008856) {
				bgr[i] = p;
			} else {
				bgr[i] = (bgr[i] - 16 / 116.0f) / 7.787f;
			}
		}

		// Observer = 2, Illuminant = D65
		z = bgr[0] * 0.95047f;
		y = bgr[1];
		x = bgr[2] * 1.08883f;

		bgr[0] = x * 0.0557f + y * -0.2040f + z * 1.0570f;
		bgr[1] = x * -0.9689f + y * 1.8758f + z * 0.0415f;
		bgr[2] = x * 3.2406f + y * -1.5372f + z * -0.4986f;
		float tpow = 1 / 2.4; // converted this var to float from double
		for (int i = 0; i < 3; i++) {
			if (bgr[i] > 0.0031308) {
				bgr[i] = (float) (1.055 * pow(bgr[i], tpow) - 0.055);
			} else {
				bgr[i] = 12.92f * bgr[i];
			}
		}
		return bgr;
	}	

	/**
     * Factory method. Creates new color from ARGB int.
     * 
     * @param argb
     * @return new color
     */
	static OColor newARGB(int argb)
	{
		return newRGBA(((argb >> 16) & 0xff) * INV8BIT, 
					   ((argb >> 8)  & 0xff) * INV8BIT, 
					    (argb        & 0xff) * INV8BIT, 
						(argb >> 24)         * INV8BIT);
	}

	/**
     * Factory method. Creates new color from BGRA int.
     * 
     * @param bgra
     * @return new color
     */
	static OColor newBGRA(int bgra)
	{
		return newBGRA(		(bgra        & 0xff) * INV8BIT, 
							((bgra >> 8)  & 0xff) * INV8BIT, 
							((bgra >> 16) & 0xff) * INV8BIT, 
							(bgra >> 24) * INV8BIT);
	}

	/**
     * Factory method. Creates new color from CMYK values.
     * 
     * @param c
     * @param m
     * @param y
     * @param k
     * @return new color
     */
	static OColor newCMYK(float c, float m, float y, float k)
	{
		return newCMYKA(c, m, y, k, 1);
	}
	
	/**
     * Factory method. Creates new color from CMYK + alpha values.
     * 
     * @param c
     * @param m
     * @param y
     * @param k
     * @param a
     * @return new color
     */
	static OColor newCMYKA(float c, float m, float y, float k, float a)
	{
		OColor col;
		col.setCMYK(c, m, y, k);
		col.alpha = a < 0 ? 1 : (a > 1 ? 1 : a);
		return col;
	}

	/**
     * Factory method. Creates a new shade of gray + alpha.
     * 
     * @param gray
     * @return new color.
     */
	static OColor newGray(float grey)
	{
		return newGrayAlpha(grey, 1);
	}

	/**
     * Factory method. Creates a new shade of gray + alpha.
     * 
     * @param gray
	 * @param alpha
     * @return new color.
     */
	static OColor newGrayAlpha(float grey, float alpha)
	{
		OColor col;
		col.setRGB(grey, grey, grey);
		col.alpha = alpha < 0 ? 1 : (alpha > 1 ? 1 : alpha);
		return col;
	}

	/**
     * Factory method. New color from hex string.
     * 
     * @param stringHex
     * @return new color
     */
	static OColor newHex(const char* stringHex)
	{
		OColor col;
		col.setRGB(hexToRGB(stringHex));
		col.alpha = 1;
		return col;
	}

	/**
     * Factory method. New color from hsv values.
     * 
     * @param h
     * @param s
     * @param v
     * @return new color
     */
	static OColor newHSV(float h, float s, float v)
	{
		return newHSVA(h,s,v, 1);
	}

	/**
     * Factory method. New color from hsv values.
     * 
     * @param h
     * @param s
     * @param v
	 * @param a
     * @return new color
     */
	static OColor newHSVA(float h, float s, float v, float a)
	{
		OColor col;
		col.setHSV(h,s,v);
		col.alpha = a < 0 ? 1 : (a > 1 ? 1 : a);
		return col;
	}

	/**
     * Factory method. Creates new color from RGB values. Alpha is set to 1.0.
     * 
     * @param red
     * @param green
     * @param blue
     * @return new color
     */
	static OColor newRGB(float red, float green, float blue)
	{
		return newRGBA(red, green, blue, 1);
	}

	/**
     * Factory method. Creates new color from RGBA values.
     * 
     * @param red
     * @param green
     * @param blue
	 * @param alpha
     * @return new color
     */
	static OColor newRGBA(float red, float green, float blue, float alpha)
	{
		OColor c;
		c.setRGB(red, green, blue);
		c.alpha = alpha < 0 ? 1 : (alpha > 1 ? 1 : alpha);
		return c;
	}
	
	/**
     * Factory method. Creates new color from BGR values. Alpha is set to 1.0.
     * 
     * @param blue
     * @param green
     * @param red
     * @return new color
     */
	static OColor newBGR(float blue, float green, float red)
	{
		return newBGRA(blue, green, red, 1);	
	}

	/**
     * Factory method. Creates new color from BGRA values.
     * 
     * @param blue
     * @param green
     * @param red
	 * @param alpha
     * @return new color
     */
	static OColor newBGRA(float blue, float green, float red, float alpha)
	{
		OColor c;
		c.setBGR(blue, green, red);
		c.alpha = alpha < 0 ? 1 : (alpha > 1 ? 1 : alpha);
		return c;
	}

	/**
     * Converts the RGB values into a CMYK vector.
     * 
     * @param r
     * @param g
     * @param b
     * @return cmyk vector
     */
	static vector<float> rgbToCMYK(float r, float g, float b)
	{
		return rgbToCMYK(r, g, b, _tempVector);
	}

	/**
     * Converts the BGR values into a CMYK vector.
     * 
     * @param blue
     * @param green
     * @param red
     * @return cmyk vector
     */
	static vector<float> bgrToCMYK(float blue, float green, float red)
	{
		return bgrToCMYK(blue, green, red, _tempVector);	
	}

	/**
     * Converts the RGB values into a CMYK vector.
     * 
     * @param r
     * @param g
     * @param b
	 * @param cmyk
     * @return cmyk vector
     */
	static vector<float> rgbToCMYK(float r, float g, float b, vector<float> cmyk)
	{
		cmyk[0] = 1 - r;
		cmyk[1] = 1 - g;
		cmyk[2] = 1 - b;
		cmyk[3] = (cmyk[0] < cmyk[1]) ? ((cmyk[0] < cmyk[2]) ? cmyk[0] : cmyk[2]) : ((cmyk[1] < cmyk[2]) ? cmyk[1] : cmyk[2]);

		cmyk[0] = (cmyk[0] - cmyk[3]) < 0 ? 1 : ((cmyk[0] - cmyk[3]) > 1 ? 1 : (cmyk[0] - cmyk[3]));
		cmyk[1] = (cmyk[1] - cmyk[3]) < 0 ? 1 : ((cmyk[1] - cmyk[3]) > 1 ? 1 : (cmyk[1] - cmyk[3]));
		cmyk[2] = (cmyk[2] - cmyk[3]) < 0 ? 1 : ((cmyk[2] - cmyk[3]) > 1 ? 1 : (cmyk[2] - cmyk[3]));
		cmyk[3] = cmyk[3] < 0 ? 1 : (cmyk[3] > 1 ? 1 : cmyk[3]);
		return cmyk;
	}

	/**
     * Converts the BGR values into a CMYK vector.
     * 
     * @param b
     * @param g
     * @param r
	 * @param cmyk
     * @return cmyk vector
     */
	static vector<float> bgrToCMYK(float b, float g, float r, vector<float> cmyk)
	{
		cmyk[0] = 1 - b;
		cmyk[1] = 1 - g;
		cmyk[2] = 1 - r;
		cmyk[3] = (cmyk[0] < cmyk[1]) ? ((cmyk[0] < cmyk[2]) ? cmyk[0] : cmyk[2]) : ((cmyk[1] < cmyk[2]) ? cmyk[1] : cmyk[2]);

		cmyk[3] = (cmyk[2] < cmyk[1]) ? ((cmyk[2] < cmyk[1]) ? cmyk[2] : cmyk[1]) : ((cmyk[1] < cmyk[1]) ? cmyk[1] : cmyk[1]);
		cmyk[0] = (cmyk[0] - cmyk[3]) < 0 ? 1 : ((cmyk[0] - cmyk[3]) > 1 ? 1 : (cmyk[0] - cmyk[3]));
		cmyk[1] = (cmyk[1] - cmyk[3]) < 0 ? 1 : ((cmyk[1] - cmyk[3]) > 1 ? 1 : (cmyk[1] - cmyk[3]));
		cmyk[2] = (cmyk[2] - cmyk[3]) < 0 ? 1 : ((cmyk[2] - cmyk[3]) > 1 ? 1 : (cmyk[2] - cmyk[3]));
		cmyk[3] = cmyk[3] < 0 ? 1 : (cmyk[3] > 1 ? 1 : cmyk[3]);
		return cmyk;
	}

	/**
     * Formats the RGB float values into hex integers.
     * 
     * @param red
     * @param green
     * @param blue
     * @return hex string
     */
	static char* rgbToHex(float red, float green, float blue)
	{
		char buffer[9] = "";
		char hexString[8] = "";

		char* sRed = "";
		int iRed;
		float fRed = red < 0 ? 1 : (red > 1 ? 1 : red);
		iRed = (int) (fRed * 0xFF);
		if (iRed == 0) {
			strcat(buffer, "00");
		} else {
			sRed=itoa(iRed,hexString,16);
			strcat(buffer, sRed);
		}

		char* sGreen = "";
		int iGreen;
		float fGreen = green < 0 ? 1 : (green > 1 ? 1 : green);
		iGreen = (int) (fGreen * 0xFF);
		if (iGreen == 0) {
			strcat(buffer, "00");
		} else {
			sGreen = itoa(iGreen, hexString, 16);
			strcat(buffer, sGreen);
		}

		char* sBlue = "";
		int iBlue;
		float fBlue = blue < 0 ? 1 : (blue > 1 ? 1 : blue);
		iBlue = (int) (fBlue * 0xFF);
		if (iBlue == 0) {
			strcat(buffer, "00");
		} else {
			sBlue = itoa(iBlue, hexString, 16);
			strcat(buffer, sBlue);
		}

		return buffer;
	}
	
	/**
     * Formats the BGR float values into hex integers.
     * 
     * @param blue
     * @param green
     * @param red
     * @return hex string
     */
	static const char* brgToHex(float blue, float green, float red)
	{
		char buffer[9] = "";
		char hexString[8] = "";

		char* sBlue = "";
		int iBlue;
		float fBlue = blue < 0 ? 1 : (blue > 1 ? 1 : blue);
		iBlue = (int) (fBlue * 0xFF);
		if (iBlue == 0) {
			strcat(buffer, "00");
		} else {
			sBlue = itoa(iBlue, hexString, 16);
			strcat(buffer, sBlue);
		}

		char* sGreen = "";
		int iGreen;
		float fGreen = green < 0 ? 1 : (green > 1 ? 1 : green);
		iGreen = (int) (fGreen * 0xFF);
		if (iGreen == 0) {
			strcat(buffer, "00");
		} else {
			sGreen = itoa(iGreen, hexString, 16);
			strcat(buffer, sGreen);
		}

		char* sRed = "";
		int iRed;
		float fRed = red < 0 ? 1 : (red > 1 ? 1 : red);
		iRed = (int) (fRed * 0xFF);
		if (iRed == 0) {
			strcat(buffer, "00");
		} else {
			sRed=itoa(iRed,hexString,16);
			strcat(buffer, sRed);
		}
		return buffer;
	}

	/**
     * Converts the RGB values into an HSV vector.
     * 
     * @param r
     * @param g
     * @param b
     * @return hsv vector
     */
	static vector<float> rgbToHSV(float r, float g, float b)
	{
		return rgbToHSV(r,g,b, _tempVector);
	}

	/**
     * Converts the BGR values into an HSV vector.
     * 
     * @param b
     * @param g
     * @param r
     * @return hsv vector
     */
	static vector<float> bgrToHSV(float b, float g, float r)
	{
		return rgbToHSV(r, g, b, _tempVector);
	}

	/**
     * Converts the RGB values into an HSV vector.
     * 
     * @param r
     * @param g
     * @param b
	 * @param hsv
     * @return hsv vector
     */
	static vector<float> rgbToHSV(float r, float g, float b, vector<float> hsv)
	{ 
		float h = 0, s = 0;
		float v = (r > g) ? ((r > b) ? r : b) : ((g > b) ? g : b);
		float d = v - (r < g) ? ((r < b) ? r : b) : ((g < b) ? g : b);

		if (v != 0.0) {
			s = d / v;
		}
		if (s != 0.0) {
			if (fabs(r - v) < 0.0000001) {
				h = (g - b) / d;
			} else if (fabs(g - v) < 0.0000001) {
				h = 2 + (b - r) / d;
			} else {
				h = 4 + (r - g) / d;
			}
		}

		h *= INV60DEGREES;

		if (h < 0) {
			h += 1.0f;
		}

		hsv[0] = h;
		hsv[1] = s;
		hsv[2] = v;
		return hsv;
	}

	/**
     * Converts the BGR values into an HSV vector.
     * 
     * @param b
     * @param g
     * @param r
	 * @param _hsv
     * @return hsv vector
     */
	static vector<float> bgrToHSV(float b, float g, float r, vector<float> _hsv)
	{
		return rgbToHSV(r, g, b, _hsv);
	}
	
	/**
     * Creates new color from HSV.
     * 
     * @param hue
     * @param s
     * @param v
     * @return new OColor
     */
	static OColor newHSV(Hue hue, float s, float v) {
		return newHSVA(hue.getHue(), s, v, 1.0);
	}

	//static OColor newRandom();

	OColor* adjustContrast(float amount);
	OColor* adjustHSV(float h, float s, float v);
	OColor* adjustRGB(float r, float g, float b);
	OColor* adjustBGR(float b, float g, float r);
	float getAlpha();
	OColor* analog(int angle, float delta);
	OColor* analog(float theta, float delta);
	float getBlack();
	OColor* blend_RGB(OColor c, float t);
	OColor* blend_BGR(OColor c, float t);
	float getBrightness();
	OColor* complement();
	//OColor copy;
	float getCyan();
	OColor* darken(float step);
	OColor* desaturate(float step);
	float distanceToCMYK(OColor color);
	float distanceToHSV(OColor c);
	float distanceToRGB(OColor color);
	//bool equals(Object object);// possibly not relevant
	OColor* getAnalog(float theta, float delta);
	OColor* getAnalog(int angle, float delta);
	OColor* getBlended_RGB(OColor c, float t);
	OColor* getBlended_BGR(OColor c, float t);
	float getBlue_RGB();
	float getBlue_BGR();
	Hue getClosestHue();
	Hue getClosestHue(bool primaryOnly);
	OColor* getComplement();
	//float getComponentValue(AccessCriteria value1);
	OColor* getDarkened(float step);
	OColor* getDesaturated(float step);
	OColor* getInverted_RGB();
	OColor* getInverted_BGR();
	OColor* getLightened(float step);
	OColor* getRotatedRYB(float theta);
	OColor* getRotatedRYB(int angle);
	OColor* getSaturated(float step);
	float getGreen_RGB();
	float getGreen_BGR();
	//int hashCode();// possibly not relevant
	float getHue();
	OColor* invertRGB();
	OColor* invertBGR();
	bool isBlack();
	bool isGrey();
	bool isPrimary();
	bool isWhite();
	OColor* lighten(float step);
	float getLuminance();
	float getMagenta();
	float getRed_RGB();
	float getRed_BGR();
	float getYellow();
	OColor* rotateRYB(float theta);
	OColor* rotateRYB(int theta);
	OColor* saturate(float step);
	float getSaturation();
	OColor* setAlpha(float a);
	OColor* setARGB(int argb);
	OColor* setBlack(float val);
	OColor* setBlue_RGB(float b);
	OColor* setBlue_BGR(float b);
	OColor* setBrightness(float brightness);
	OColor* setCMYK(float c, float m, float y, float k);
	OColor* setCMYK(vector<float> cmykVector);
	//OColor setComponent(AccessCriteria value1, float value2);
	OColor* setCyan(float val);
	OColor* setGreen_RGB(float g);
	OColor* setGreen_BGR(float g);
	OColor* setHSV(float h, float s, float v);
	OColor* setHSV(vector<float> hsvVector);
	OColor* setHue(float hue);
	OColor* setMagenta(float val);
	OColor* setRed_RGB(float r);
	OColor* setRed_BGR(float r);
	OColor* setRGB(float r, float g, float b);
	OColor* setBGR(float b, float g, float r); 
	OColor* setRGB(vector<float> rgbVector);
	OColor* setBGR(vector<float> bgrVector);
	OColor* setSaturation(float saturation);
	OColor* setYellow(float val);
	int toARGB();
	int toBGRA();
	vector<float> toCMYKAArray(vector<float> cmyka);
	vector<float> toCMYKAArray();
	//String toHex(); // possibly not relevant
	vector<float> toHSVAArray(vector<float> hsva);
	vector<float> toHSVAArray();
	vector<float> toRGBAArray(vector<float> rgba);
	vector<float> toRGBAArray(vector<float>, unsigned int offset);
	vector<float> toBGRAArray(vector<float> bgra);
	vector<float> toBGRAArray(vector<float> bgra, unsigned int offset);
	//String toString();

	

private:
	static vector<float> _tempVector;
	vector<float> bgr;
	vector<float> rgb;
	vector<float> cmyk;
	vector<float> hsv;

	float red;
	float blue;
	float green;
	float alpha;
	float black;
	//float cyan;
	//int hue;
	//float luminance;
	//float brightness;
	//float magenta;
	//float saturation;
	//float yellow;
	void unpackColor(int color);
};