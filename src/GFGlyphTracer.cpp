/*************************************************************************
** GFGlyphTracer.cpp                                                    **
**                                                                      **
** This file is part of dvisvgm -- the DVI to SVG converter             **
** Copyright (C) 2005-2010 Martin Gieseking <martin.gieseking@uos.de>   **
**                                                                      **
** This program is free software; you can redistribute it and/or        ** 
** modify it under the terms of the GNU General Public License as       **
** published by the Free Software Foundation; either version 3 of       **
** the License, or (at your option) any later version.                  **
**                                                                      **
** This program is distributed in the hope that it will be useful, but  **
** WITHOUT ANY WARRANTY; without even the implied warranty of           **
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the         **
** GNU General Public License for more details.                         **
**                                                                      **
** You should have received a copy of the GNU General Public License    **
** along with this program; if not, see <http://www.gnu.org/licenses/>. ** 
*************************************************************************/

#include "GFGlyphTracer.h"
#include "Pair.h"

using namespace std;

GFGlyphTracer::GFGlyphTracer () : GFTracer(_ifs, 0), _glyph(0)
{
}

/** Constructs a new glyph tracer. 
 *  @param[in] is GF input stream
 *  @param[in] upp target units per TeX point */
GFGlyphTracer::GFGlyphTracer (string &fname, double upp) : GFTracer(_ifs, upp), _glyph(0)
{
	_ifs.open(fname.c_str(), ios::binary);
}


void GFGlyphTracer::reset (string &fname, double upp) {
	if (_ifs.is_open())
		_ifs.close();
	unitsPerPoint(upp);
	_ifs.open(fname.c_str(), ios::binary);
}


bool GFGlyphTracer::executeChar (UInt8 c) {
	if (_glyph)
		return GFTracer::executeChar(c);
	return false;
}


void GFGlyphTracer::moveTo (double x, double y) {
	_glyph->moveto(x, y);
}


void GFGlyphTracer::lineTo (double x, double y) {
	_glyph->lineto(x, y);
}


void GFGlyphTracer::curveTo (double c1x, double c1y, double c2x, double c2y, double x, double y) {
	_glyph->cubicto(c1x, c1y, c2x, c2y, x, y);
}


void GFGlyphTracer::closePath () {
	_glyph->closepath();
}


void GFGlyphTracer::endChar (UInt32 c) {
	_glyph->newpath();
	GFTracer::endChar(c);
}
