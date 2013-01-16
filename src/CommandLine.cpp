// This file was automatically generated by opt2cpp.
// It is part of the dvisvgm package and published under the terms
// of the GNU General Public License version 3, or (at your option) any later version.
// See file COPYING for further details.
// (C) 2009-2013 Martin Gieseking <martin.gieseking@uos.de>

#include <cstdio>
#include <iostream>
#include <iomanip>
#include "InputReader.h"
#include "CommandLine.h"

using namespace std;

const CmdLineParserBase::Option CommandLine::_options[] = {
   {'b', "bbox", 'r', new OptionHandlerImpl<CommandLine>(&CommandLine::handle_bbox)},
   {'C', "cache", 'o', new OptionHandlerImpl<CommandLine>(&CommandLine::handle_cache)},
   {'\0', "color", 0, new OptionHandlerImpl<CommandLine>(&CommandLine::handle_color)},
   {'e', "exact", 0, new OptionHandlerImpl<CommandLine>(&CommandLine::handle_exact)},
   {'m', "fontmap", 'r', new OptionHandlerImpl<CommandLine>(&CommandLine::handle_fontmap)},
   {'h', "help", 0, new OptionHandlerImpl<CommandLine>(&CommandLine::handle_help)},
   {'\0', "keep", 0, new OptionHandlerImpl<CommandLine>(&CommandLine::handle_keep)},
#if !defined(HAVE_LIBGS) && !defined(DISABLE_GS)
   {'\0', "libgs", 'r', new OptionHandlerImpl<CommandLine>(&CommandLine::handle_libgs)},
#endif
   {'l', "list-specials", 0, new OptionHandlerImpl<CommandLine>(&CommandLine::handle_list_specials)},
   {'M', "mag", 'r', new OptionHandlerImpl<CommandLine>(&CommandLine::handle_mag)},
   {'n', "no-fonts", 'o', new OptionHandlerImpl<CommandLine>(&CommandLine::handle_no_fonts)},
   {'\0', "no-mktexmf", 0, new OptionHandlerImpl<CommandLine>(&CommandLine::handle_no_mktexmf)},
   {'S', "no-specials", 'o', new OptionHandlerImpl<CommandLine>(&CommandLine::handle_no_specials)},
   {'\0', "no-styles", 0, new OptionHandlerImpl<CommandLine>(&CommandLine::handle_no_styles)},
   {'o', "output", 'r', new OptionHandlerImpl<CommandLine>(&CommandLine::handle_output)},
   {'p', "page", 'r', new OptionHandlerImpl<CommandLine>(&CommandLine::handle_page)},
   {'P', "progress", 'o', new OptionHandlerImpl<CommandLine>(&CommandLine::handle_progress)},
   {'r', "rotate", 'r', new OptionHandlerImpl<CommandLine>(&CommandLine::handle_rotate)},
   {'c', "scale", 'r', new OptionHandlerImpl<CommandLine>(&CommandLine::handle_scale)},
   {'s', "stdout", 0, new OptionHandlerImpl<CommandLine>(&CommandLine::handle_stdout)},
   {'a', "trace-all", 'o', new OptionHandlerImpl<CommandLine>(&CommandLine::handle_trace_all)},
   {'T', "transform", 'r', new OptionHandlerImpl<CommandLine>(&CommandLine::handle_transform)},
   {'t', "translate", 'r', new OptionHandlerImpl<CommandLine>(&CommandLine::handle_translate)},
   {'v', "verbosity", 'r', new OptionHandlerImpl<CommandLine>(&CommandLine::handle_verbosity)},
   {'V', "version", 'o', new OptionHandlerImpl<CommandLine>(&CommandLine::handle_version)},
   {'z', "zip", 'o', new OptionHandlerImpl<CommandLine>(&CommandLine::handle_zip)},
   {0, 0, 0, 0}
};

void CommandLine::init () {
   CmdLineParserBase::init();
   _bbox_given = false;
   _cache_given = false;
   _color_given = false;
   _exact_given = false;
   _fontmap_given = false;
   _help_given = false;
   _keep_given = false;
#if !defined(HAVE_LIBGS) && !defined(DISABLE_GS)
   _libgs_given = false;
#endif
   _list_specials_given = false;
   _mag_given = false;
   _no_fonts_given = false;
   _no_mktexmf_given = false;
   _no_specials_given = false;
   _no_styles_given = false;
   _output_given = false;
   _page_given = false;
   _progress_given = false;
   _rotate_given = false;
   _scale_given = false;
   _stdout_given = false;
   _trace_all_given = false;
   _transform_given = false;
   _translate_given = false;
   _verbosity_given = false;
   _version_given = false;
   _zip_given = false;

   _bbox_arg = "min";
   _cache_arg.clear();
   _fontmap_arg.clear();
#if !defined(HAVE_LIBGS) && !defined(DISABLE_GS)
   _libgs_arg.clear();
#endif
   _mag_arg = 4;
   _no_fonts_arg = 0;
   _no_specials_arg.clear();
   _output_arg.clear();
   _page_arg = "1";
   _progress_arg = 0.5;
   _rotate_arg = 0;
   _scale_arg.clear();
   _trace_all_arg = false;
   _transform_arg.clear();
   _translate_arg.clear();
   _verbosity_arg = 7;
   _version_arg = false;
   _zip_arg = 9;
}

void CommandLine::help () const {
   puts("This program converts DVI files, as created by TeX/LaTeX, to\nthe XML-based scalable vector graphics format SVG.\n\nUsage: dvisvgm [options] dvifile\n");
   puts("Input options:");
   puts("  -p, --page=ranges             choose pages to convert [1]");
   puts("  -m, --fontmap=filenames       evaluate (additional) font map files");
   puts("\nSVG output options:");
   puts("  -b, --bbox=size               set size of bounding box [min]");
   puts("  -o, --output=pattern          set name pattern of output files");
   puts("  -s, --stdout                  write SVG output to stdout");
   puts("  -n, --no-fonts[=variant]      draw glyphs by using path elements [0]");
   puts("      --no-styles               don't use styles to reference fonts");
   puts("  -z, --zip[=level]             create compressed .svgz file [9]");
   puts("\nSVG transformations:");
   puts("  -r, --rotate=angle            rotate page content clockwise");
   puts("  -c, --scale=sx[,sy]           scale page content");
   puts("  -t, --translate=tx[,ty]       shift page content");
   puts("  -T, --transform=commands      transform page content");
   puts("\nProcessing options:");
   puts("  -C, --cache[=dir]             set/print path of cache directory");
   puts("  -e, --exact                   compute exact glyph boxes");
   puts("      --keep                    keep temporary files");
#if !defined(HAVE_LIBGS) && !defined(DISABLE_GS)
   puts("      --libgs=filename          set name of Ghostscript shared library");
#endif
   puts("  -M, --mag=factor              magnification of Metafont output [4]");
   puts("      --no-mktexmf              don't try to create missing fonts");
   puts("  -S, --no-specials[=prefixes]  don't process [selected] specials");
   puts("  -a, --trace-all[=retrace]     trace all glyphs of bitmap fonts [no]");
   puts("\nMessage options:");
   puts("      --color                   colorize messages");
   puts("  -h, --help                    print this help and exit");
   puts("  -l, --list-specials           print supported special sets and exit");
   puts("  -P, --progress[=delay]        enable progess indicator [0.5]");
   puts("  -v, --verbosity=level         set verbosity level (0-7) [7]");
   puts("  -V, --version[=extended]      print version and exit [no]");
}


void CommandLine::handle_bbox(InputReader &ir, const Option &opt, bool longopt) {
   if (getStringArg(ir, opt, longopt, _bbox_arg))
      _bbox_given = true;
}


void CommandLine::handle_cache(InputReader &ir, const Option &opt, bool longopt) {
   if (ir.eof() || getStringArg(ir, opt, longopt, _cache_arg))
      _cache_given = true;
}


void CommandLine::handle_color(InputReader &ir, const Option &opt, bool longopt) {
   _color_given = true;
}


void CommandLine::handle_exact(InputReader &ir, const Option &opt, bool longopt) {
   _exact_given = true;
}


void CommandLine::handle_fontmap(InputReader &ir, const Option &opt, bool longopt) {
   if (getStringArg(ir, opt, longopt, _fontmap_arg))
      _fontmap_given = true;
}


void CommandLine::handle_help(InputReader &ir, const Option &opt, bool longopt) {
   _help_given = true;
}


void CommandLine::handle_keep(InputReader &ir, const Option &opt, bool longopt) {
   _keep_given = true;
}


#if !defined(HAVE_LIBGS) && !defined(DISABLE_GS)
void CommandLine::handle_libgs(InputReader &ir, const Option &opt, bool longopt) {
   if (getStringArg(ir, opt, longopt, _libgs_arg))
      _libgs_given = true;
}
#endif


void CommandLine::handle_list_specials(InputReader &ir, const Option &opt, bool longopt) {
   _list_specials_given = true;
}


void CommandLine::handle_mag(InputReader &ir, const Option &opt, bool longopt) {
   if (getDoubleArg(ir, opt, longopt, _mag_arg))
      _mag_given = true;
}


void CommandLine::handle_no_fonts(InputReader &ir, const Option &opt, bool longopt) {
   if (ir.eof() || getIntArg(ir, opt, longopt, _no_fonts_arg))
      _no_fonts_given = true;
}


void CommandLine::handle_no_mktexmf(InputReader &ir, const Option &opt, bool longopt) {
   _no_mktexmf_given = true;
}


void CommandLine::handle_no_specials(InputReader &ir, const Option &opt, bool longopt) {
   if (ir.eof() || getStringArg(ir, opt, longopt, _no_specials_arg))
      _no_specials_given = true;
}


void CommandLine::handle_no_styles(InputReader &ir, const Option &opt, bool longopt) {
   _no_styles_given = true;
}


void CommandLine::handle_output(InputReader &ir, const Option &opt, bool longopt) {
   if (getStringArg(ir, opt, longopt, _output_arg))
      _output_given = true;
}


void CommandLine::handle_page(InputReader &ir, const Option &opt, bool longopt) {
   if (getStringArg(ir, opt, longopt, _page_arg))
      _page_given = true;
}


void CommandLine::handle_progress(InputReader &ir, const Option &opt, bool longopt) {
   if (ir.eof() || getDoubleArg(ir, opt, longopt, _progress_arg))
      _progress_given = true;
}


void CommandLine::handle_rotate(InputReader &ir, const Option &opt, bool longopt) {
   if (getDoubleArg(ir, opt, longopt, _rotate_arg))
      _rotate_given = true;
}


void CommandLine::handle_scale(InputReader &ir, const Option &opt, bool longopt) {
   if (getStringArg(ir, opt, longopt, _scale_arg))
      _scale_given = true;
}


void CommandLine::handle_stdout(InputReader &ir, const Option &opt, bool longopt) {
   _stdout_given = true;
}


void CommandLine::handle_trace_all(InputReader &ir, const Option &opt, bool longopt) {
   if (ir.eof() || getBoolArg(ir, opt, longopt, _trace_all_arg))
      _trace_all_given = true;
}


void CommandLine::handle_transform(InputReader &ir, const Option &opt, bool longopt) {
   if (getStringArg(ir, opt, longopt, _transform_arg))
      _transform_given = true;
}


void CommandLine::handle_translate(InputReader &ir, const Option &opt, bool longopt) {
   if (getStringArg(ir, opt, longopt, _translate_arg))
      _translate_given = true;
}


void CommandLine::handle_verbosity(InputReader &ir, const Option &opt, bool longopt) {
   if (getUIntArg(ir, opt, longopt, _verbosity_arg))
      _verbosity_given = true;
}


void CommandLine::handle_version(InputReader &ir, const Option &opt, bool longopt) {
   if (ir.eof() || getBoolArg(ir, opt, longopt, _version_arg))
      _version_given = true;
}


void CommandLine::handle_zip(InputReader &ir, const Option &opt, bool longopt) {
   if (ir.eof() || getIntArg(ir, opt, longopt, _zip_arg))
      _zip_given = true;
}


void CommandLine::status () const {
   cout << 'b'<< setw(20) << "bbox " << bbox_given() << setw(10) << bbox_arg() << endl;
   cout << 'C'<< setw(20) << "cache " << cache_given() << setw(10) << cache_arg() << endl;
   cout << ' '<< setw(20) << "color " << color_given() << endl;
   cout << 'e'<< setw(20) << "exact " << exact_given() << endl;
   cout << 'm'<< setw(20) << "fontmap " << fontmap_given() << setw(10) << fontmap_arg() << endl;
   cout << 'h'<< setw(20) << "help " << help_given() << endl;
   cout << ' '<< setw(20) << "keep " << keep_given() << endl;
#if !defined(HAVE_LIBGS) && !defined(DISABLE_GS)
   cout << ' '<< setw(20) << "libgs " << libgs_given() << setw(10) << libgs_arg() << endl;
#endif
   cout << 'l'<< setw(20) << "list-specials " << list_specials_given() << endl;
   cout << 'M'<< setw(20) << "mag " << mag_given() << setw(10) << mag_arg() << endl;
   cout << 'n'<< setw(20) << "no-fonts " << no_fonts_given() << setw(10) << no_fonts_arg() << endl;
   cout << ' '<< setw(20) << "no-mktexmf " << no_mktexmf_given() << endl;
   cout << 'S'<< setw(20) << "no-specials " << no_specials_given() << setw(10) << no_specials_arg() << endl;
   cout << ' '<< setw(20) << "no-styles " << no_styles_given() << endl;
   cout << 'o'<< setw(20) << "output " << output_given() << setw(10) << output_arg() << endl;
   cout << 'p'<< setw(20) << "page " << page_given() << setw(10) << page_arg() << endl;
   cout << 'P'<< setw(20) << "progress " << progress_given() << setw(10) << progress_arg() << endl;
   cout << 'r'<< setw(20) << "rotate " << rotate_given() << setw(10) << rotate_arg() << endl;
   cout << 'c'<< setw(20) << "scale " << scale_given() << setw(10) << scale_arg() << endl;
   cout << 's'<< setw(20) << "stdout " << stdout_given() << endl;
   cout << 'a'<< setw(20) << "trace-all " << trace_all_given() << setw(10) << trace_all_arg() << endl;
   cout << 'T'<< setw(20) << "transform " << transform_given() << setw(10) << transform_arg() << endl;
   cout << 't'<< setw(20) << "translate " << translate_given() << setw(10) << translate_arg() << endl;
   cout << 'v'<< setw(20) << "verbosity " << verbosity_given() << setw(10) << verbosity_arg() << endl;
   cout << 'V'<< setw(20) << "version " << version_given() << setw(10) << version_arg() << endl;
   cout << 'z'<< setw(20) << "zip " << zip_given() << setw(10) << zip_arg() << endl;
   CmdLineParserBase::status();
}

