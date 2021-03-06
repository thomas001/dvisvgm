/*************************************************************************
** GFGlyphTracerTest.cpp                                                **
**                                                                      **
** This file is part of dvisvgm -- a fast DVI to SVG converter          **
** Copyright (C) 2005-2016 Martin Gieseking <martin.gieseking@uos.de>   **
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

#include <gtest/gtest.h>
#include <string>
#include "GFGlyphTracer.h"

#ifndef SRCDIR
#define SRCDIR "."
#endif

using namespace std;

class Callback : public GFGlyphTracer::Callback {
	public:
		void beginChar (UInt8 c) {_oss << "begin(" << int(c) << ")";}
		void endChar (UInt8 c)   {_oss << "end(" << int(c) << ")";}
		void emptyChar (UInt8 c) {_oss << "empty(" << int(c) << ")";}
		string getLog () const   {return _oss.str();}
		void reset ()            {_oss.str("");}

	private:
		ostringstream _oss;
};


// Returns an SVG path string with scaled values.
static string scaled_pathstr (const Glyph &glyph) {
	ostringstream oss;
	glyph.writeSVG(oss, false);
	istringstream iss(oss.str());
	ostringstream resultstream;
	XMLString::DECIMAL_PLACES = 1;
	while (iss.peek() > 0) {
		if (isalpha(iss.peek()) || isspace(iss.peek()))
			resultstream << char(iss.get());
		else {
			int num;
			iss >> num;
			resultstream << XMLString(double(num)/10000);
		}
	}
	return resultstream.str();
}


TEST(GFGlyphTracerTest, executeChar) {
	string gfname = string(SRCDIR)+"/cmr10.600gf";
	Callback callback;
	GFGlyphTracer tracer(gfname, 10000, &callback);
	Glyph glyph;
	tracer.setGlyph(glyph);
	EXPECT_FALSE(tracer.executeChar(128));
	EXPECT_EQ(callback.getLog(), "begin(128)empty(128)");

	callback.reset();
	EXPECT_TRUE(tracer.executeChar('g'));
	ostringstream oss;
	glyph.closeOpenSubPaths();
	EXPECT_EQ(scaled_pathstr(glyph),
		"M3.6 4.4C3.2 4.2 3.1 4.2 2.9 4.3C2 4.8 0.6 4.1 0.6 3C0.6 2.8 0.7 2.5 0.8 2.3C1 2.1 1 2 0.9 1.7"
		"C0.7 1.3 0.7 0.8 0.9 0.5C1 0.3 1 0.3 0.6 -0.1C-0 -0.7 0.1 -1.4 1.1 -1.9C1.7 -2.2 3.3 -2.2 3.8 -1.9"
		"C4.4 -1.6 4.7 -1.2 4.7 -0.8C4.7 0.2 3.9 0.7 2.4 0.7C1.4 0.7 1 0.9 1.1 1.4C1.1 1.7 1.2 1.7 1.4 1.7"
		"C1.5 1.7 1.8 1.6 2 1.6C3.2 1.4 4.2 2.8 3.6 3.7C3.4 4 3.4 4 3.7 4.2C4 4.4 4.4 4.4 4.3 4.2"
		"C4.2 3.9 4.4 3.7 4.7 3.8C4.8 3.9 4.8 4 4.8 4.1C4.8 4.6 4.2 4.7 3.6 4.4Z"
		"M2.7 4C2.9 3.8 3 3.5 3 3C3 2.2 2.7 1.8 2.2 1.8C1.7 1.8 1.4 2.2 1.4 3S1.7 4.2 2.2 4.2C2.4 4.2 2.6 4.1 2.7 4Z"
		"M3.6 -0.1C4 -0.2 4.2 -0.7 4 -1.2C3.6 -2.1 1.7 -2.2 1.1 -1.4C0.8 -1 0.8 -0.6 1.1 -0.2C1.3 0.1 1.4 0.1 2.2 0.1C2.8 0.1 3.3 0 3.6 -0.1Z");

	EXPECT_EQ(callback.getLog(), "begin(103)end(103)");

	tracer.reset(gfname, 1000);
	glyph.clear();
	callback.reset();
	EXPECT_TRUE(tracer.executeChar('I'));
	glyph.closeOpenSubPaths();
	oss.str("");
	EXPECT_EQ(scaled_pathstr(glyph),
		"M0 0.7C0 0.7 0 0.7 0.1 0.7L0.1 0.6V0.3V0L0.1 0C0 0 0 0 0 0C0 0 0.1 0 0.2 0S0.3 0 0.3 0"
		"C0.3 0 0.3 0 0.3 0L0.2 0V0.3V0.6L0.3 0.7C0.3 0.7 0.3 0.7 0.3 0.7C0.3 0.7 0.3 0.7 0.2 0.7S0 0.7 0 0.7Z");
	EXPECT_EQ(callback.getLog(), "begin(73)end(73)");
}


TEST(GFGlyphTracerTest, defaultCallback) {
	string gfname = string(SRCDIR)+"/cmr10.600gf";
	GFGlyphTracer::Callback callback;
	GFGlyphTracer tracer(gfname, 1000, &callback);
	Glyph glyph;
	tracer.setGlyph(glyph);
	tracer.closePath();
	EXPECT_FALSE(tracer.executeChar(128));
	EXPECT_TRUE(tracer.executeChar('g'));
}


TEST(GFGlyphTracerTest, fail) {
	GFGlyphTracer tracer;
	EXPECT_FALSE(tracer.executeChar('M'));

	Glyph glyph;
	tracer.setGlyph(glyph);
	EXPECT_THROW(tracer.executeChar('M'), GFException);

	string gfname = string(SRCDIR)+"/cmr10.600gf";
	tracer.reset(gfname, 1000);
	EXPECT_TRUE(tracer.executeChar('M'));
}
