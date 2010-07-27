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

/**
 * A struct object for creating an RYB_WHEEL.
 * 
 * 
 */
struct RYB_Struct {

	RYB_Struct();
	RYB_Struct(int x, int y);

	int x;
	int y;

};