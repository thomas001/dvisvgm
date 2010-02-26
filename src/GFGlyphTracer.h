/*************************************************************************
** GFGlyphTracer.h                                                      **
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

#ifndef GFGLYPHTRACER_H
#define GFGLYPHTRACER_H

#include <fstream>
#include <string>
#include "GFTracer.h"
#include "Glyph.h"

class GFGlyphTracer : public GFTracer
{
   public:
		GFGlyphTracer ();
      GFGlyphTracer (std::string &fname, double upp);
		void reset (std::string &fname, double upp);
		bool executeChar (UInt8 c);
		void moveTo (double x, double y);
		void lineTo (double x, double y);
		void curveTo (double c1x, double c1y, double c2x, double c2y, double x, double y);
		void closePath ();
		void endChar (UInt32 c);
		void setGlyph (Glyph *glyph)   {_glyph = glyph;}
		const Glyph& getGlyph () const {return *_glyph;}
		bool opened () const           {return _ifs.is_open();}

   private:
		std::ifstream _ifs;
		Glyph *_glyph;
};

#endif
