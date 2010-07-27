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
#include "MathUtils.h"
#include <vector>
#include <cstdlib>
#include <unordered_map>
#include <limits>

using namespace std;

/**
 * This class defines color hues and allows them to be accessed by name. There
 * are also methods to check if a hue is one of the 7 primary hues (rainbow) or
 * to find the closest defined hue for a given color.
 * 
 * @author toxi (original Java/Processing library)
 * @author oliver nowak ( C++ port )
 * 
 */
class Hue {

public:
	static const Hue RED;
	static const Hue ORANGE;
	static const Hue YELLOW;
	static const Hue LIME;
	static const Hue GREEN;
	static const Hue TEAL;
	static const Hue CYAN;
	static const Hue AZURE;
	static const Hue BLUE;
	static const Hue INDIGO;
	static const Hue PURPLE;
	static const Hue PINK;

	/**
	 * Tolerance value for checking if a given hue is primary (default 0.01)
	 */
	static const float PRIMARY_VARIANCE;

	static vector<Hue> primaryColors;
	static tr1::unordered_map<const char*, Hue> namedColors;

	/**
	 * Finds the closest defined & named Hue for the given hue value.
	 * Optionally, the search can be limited to primary hues only.
	 * 
	 * @param hue
	 *            normalized hue (0.0 ... 1.0) will be automatically wrapped
	 * @param primaryOnly
	 *            only consider the 7 primary hues
	 * @return closest Hue instance
	 */
	static Hue getClosest(float hue, bool primaryOnly) {
		hue = fmod(hue, 1);
		float dist = numeric_limits<float>::max();
		Hue closest;

		if (primaryOnly) {
			for( vector<Hue>::iterator it = primaryColors.begin(); it != primaryColors.end(); ++it) {
				Hue h = *it;
				float d = MathUtils::min( abs(h.getHue() - hue), abs(1+h.getHue() - hue) );
				if (d < dist) {
					dist = d;
					closest = *it;
				}
			}
		} else {
			for( tr1::unordered_map<const char*, Hue>::iterator it = namedColors.begin(); it != namedColors.end(); ++it) {
				Hue h = it->second;
				float d = MathUtils::min(  abs(h.getHue() - hue), abs(1+h.getHue() - hue)    );
				if (d < dist) {
					dist = d;
					closest = h;
				}
			}
		}

		return closest;
	}

/**
 * Get a reference to a Hue from its name.
 * 
 * @param name
 * @return a Hue reference
 */
	static Hue getForName(const char* name) {
		tr1::unordered_map<const char*, Hue>::iterator it = namedColors.find(name);
		if (it != namedColors.end()) return it->second;
	}

/**
 * Check if a Hue is a Primary Color.
 * 
 * @param hue
 * @return bool
 */
	static bool isThisPrimary(float hue) {
		return isThisPrimary(hue, PRIMARY_VARIANCE);
	}

	static bool isThisPrimary(float hue, float variance)
	{
		bool isPrimary = false;
		
		for( vector<Hue>::iterator it = primaryColors.begin(); it != primaryColors.end(); ++it) {
			if ( abs( (hue - it->getHue()) ) < variance ) {
				isPrimary = true;
				break;
			}
		}
		return isPrimary;
	}

	Hue();
	Hue(const char* stringname, float hue);
	Hue(const char* stringname, float hue, bool isPrimary);

	const char* getName();
	float getHue();
	bool isHuePrimary();

private:
	const char* name;
	float hue;
	bool isPrimary;
};