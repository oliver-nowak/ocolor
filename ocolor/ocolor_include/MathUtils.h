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

#include "math.h"

/**
 * Miscellaneous math utilities.
 */
class MathUtils {
public:
	MathUtils();

	/**
	 * Log(2)
	 */
	static const float LOG2;

	/**
	 * PI
	 */
	static const float PI;

	/**
	 * PI/2
	 */
	static const float HALF_PI;

	/**
	 * PI/3
	 */
	static const float THIRD_PI;

	/**
	 * PI/4
	 */
	static const float QUARTER_PI;

	/**
	 * PI*2
	 */
	static const float TWO_PI;

	/**
	 * Epsilon value, approx. 1.19E-7
	 */
	static const float EPS;

	/**
	 * Degrees to radians conversion factor
	 */
	static const float DEG2RAD;

	/**
	 * Radians to degrees conversion factor
	 */
	static const float RAD2DEG;
	static const float SHIFT23;
	static const float INV_SHIFT23;

	/**
	 * @param x
	 * @return absolute value of x
	 */
	static float abs(float x);

	/**
	 * @param x
	 * @return absolute value of x
	 */
	static int abs(int x);

	/**
	 * Rounds up the value to the nearest higher power^2 value.
	 * 
	 * @param x
	 * @return power^2 value
	 */
	static int ceilPowerOf2(float x) {
		return (int) pow(2, (log(x) / (LOG2 + 0.5)));
	}

	/**
	 * Clip a float value to a given minimum and maximum value
	 * 
	 * @param a
	 * @param min
	 * @param max
	 * @return clipped float
	 */
	static float clip(float a, float min, float max) {
		return a < min ? min : (a > max ? max : a);
	}

	/**
	 * Clip an int value to a given minimum and maximum value
	 * 
	 * @param a
	 * @param min
	 * @param max
	 * @return clipped int
	 */
	static int clip(int a, int min, int max) {
		return a < min ? min : (a > max ? max : a);
	}

	/**
	 * Clips the value to the 0.0 .. 1.0 interval.
	 * 
	 * @param a
	 * @return clipped value
	 */
	static float clipNormalized(float a) {
		if (a < 0) {
			return 0;
		}
		else if (a > 1) {
			return 1;
		}
		return a;
	}

	/**
	 * Convert a given value into degrees.
	 * 
	 * @param radians
	 * @return float
	 */
	static float degrees(float radians) {
		return radians * RAD2DEG;
	}

	/**
	 * Find the floor of a value.
	 * 
	 * @param x
	 *            double value to be floored
	 * @return floored value as integer
	 */
	static int floor(double x) {
		return x >= 0 ? (int) x : (int) x - 1;
	}

	/**
	 * Find the floor of a value.
	 * 
	 * @param x
	 *            float value to be floored
	 * @return floored value as integer
	 */
	static int floor(float x) {
		return x >= 0 ? (int) x : (int) x - 1;
	}

	/**
	 * Rounds down the value to the nearest lower power^2 value.
	 * 
	 * @param x
	 * @return power^2 value
	 */
	static int floorPowerOf2(float x) {
		return (int) pow(2, log(x) / LOG2);
	}

	/**
	 * Find the maximum value, given two float inputs.
	 * 
	 * @param a
	 * @param b
	 * @return float
	 */
	static float max(float a, float b) {
		return a > b ? a : b;
	}

	/**
	 * Returns the maximum value of three floats.
	 * 
	 * @param a
	 * @param b
	 * @param c
	 * @return max val
	 */
	static float max(float a, float b, float c) {
		return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
	}

	/**
	 * Find the maximum value, given two int inputs.
	 * 
	 * @param a
	 * @param b
	 * @return int
	 */
	static int max(int a, int b) {
		return a > b ? a : b;
	}

	/**
	 * Returns the maximum value of three ints.
	 * 
	 * @param a
	 * @param b
	 * @param c
	 * @return max val
	 */
	static int max(int a, int b, int c) {
		return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
	}

	/**
	 * Find the minimum value, given two float inputs.
	 * 
	 * @param a
	 * @param b
	 * @return float
	 */
	static float min(float a, float b) {
		return a < b ? a : b;
	}

	/**
	 * Returns the minimum value of three floats.
	 * 
	 * @param a
	 * @param b
	 * @param c
	 * @return min val
	 */
	static float min(float a, float b, float c) {
		return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
	}

	/**
	 * Find the minimum value, given two int inputs.
	 * 
	 * @param a
	 * @param b
	 * @return int
	 */
	static int min(int a, int b) {
		return a < b ? a : b;
	}

	/**
	 * Returns the minimum value of three ints.
	 * 
	 * @param a
	 * @param b
	 * @param c
	 * @return min val
	 */
	static int min(int a, int b, int c) {
		return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
	}

	/**
	 * Returns a random number in the interval -1 .. +1.
	 * 
	 * @return random float
	 */
	static float normalizedRandom() {
		return 0.0;
	}

	//public static final float normalizedRandom(Random rnd);

	/**
	 * Convert a value into radians.
	 * 
	 * @param degrees
	 * @return float
	 */
	static float radians(float degrees) {
		return degrees * DEG2RAD;
	}

	//static float fastPow(float a, float b);
	//static bool flipCoin();
	//public static boolean flipCoin(Random rnd);
	//public static final float random(float max);
	//public static final float random(float min, float max);
	//public static int random(int max);
	//public static int random(int min, int max);
	//public static double random(Random rnd, double max);
	//public static double random(Random rnd, double min, double max);
	//public static float random(Random rnd, float max);
	//public static float random(Random rnd, float min, float max);
	//public static int random(Random rnd, int max);
	//public static int random(Random rnd, int min, int max);

};