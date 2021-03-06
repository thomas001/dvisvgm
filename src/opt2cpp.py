##########################################################################
## options.xml                                                          ##
##                                                                      ##
## This file is part of dvisvgm - a fast DVI to SVG converter           ##
## Copyright (C) 2014-2016 Khaled Hosny <khaled.hosny@hindawi.com>      ##
##                                                                      ##
## This program is free software; you can redistribute it and/or        ##
## modify it under the terms of the GNU General Public License as       ##
## published by the Free Software Foundation; either version 3 of       ##
## the License, or (at your option) any later version.                  ##
##                                                                      ##
## This program is distributed in the hope that it will be useful, but  ##
## WITHOUT ANY WARRANTY; without even the implied warranty of           ##
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the         ##
## GNU General Public License for more details.                         ##
##                                                                      ##
## You should have received a copy of the GNU General Public License    ##
## along with this program; if not, see <http://www.gnu.org/licenses/>. ##
##########################################################################

from lxml import etree
import sys
import operator

header_template = """// This file was automatically generated by opt2cpp.
// It is part of the dvisvgm package and published under the terms
// of the GNU General Public License version 3, or (at your option) any later version.
// See file COPYING for further details.
// (C) 2009-2016 Martin Gieseking <martin.gieseking@uos.de>

#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <config.h>
#include "CmdLineParserBase.h"

class %(class)s : public CmdLineParserBase
{
\tpublic:
\t\t%(class)s () {init();}
\t\t%(class)s (int argc, char **argv, bool printErrors) {parse(argc, argv, printErrors);}
%(public)s\tprotected:
\t\tvoid init ();
\t\tconst CmdLineParserBase::Option* options (size_t *numopts) const;
\t\tconst char** helplines (size_t *numlines) const;
%(protected)s
\tprivate:
\t\tstatic const CmdLineParserBase::Option _options[];
%(private)s};

#endif
"""

cxx_template = """// This file was automatically generated by opt2cpp.
// It is part of the dvisvgm package and published under the terms
// of the GNU General Public License version 3, or (at your option) any later version.
// See file COPYING for further details.
// (C) 2009-2016 Martin Gieseking <martin.gieseking@uos.de>

#include <config.h>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include "InputReader.h"
#include "CommandLine.h"

using namespace std;

const CmdLineParserBase::Option %(class)s::_options[] = {
%(_options)s};

const CmdLineParserBase::Option* %(class)s::options (size_t *numopts) const {
\t*numopts = sizeof(_options)/sizeof(CmdLineParserBase::Option);
\treturn _options;
}

void %(class)s::init () {
\tCmdLineParserBase::init();

\t// disable all options by default
%(initopts)s
\t// set default option values
%(initargs)s}

const char** %(class)s::helplines (size_t *numlines) const {
\tstatic const char *lines[] = {
%(helplines)s\t};
\t*numlines = sizeof(lines)/sizeof(char*);
\treturn lines;
}

%(functions)s"""


def main(optfile):
    parser = etree.XMLParser(dtd_validation=True)
    tree = etree.parse(optfile, parser=parser)
    root = tree.getroot()

    vars = {}
    vars["class"] = root.get("class")

    options = {}
    public = ""
    protected = ""
    private = ""
    _options = ""
    initopts = ""
    initargs = ""
    helplines = ""
    functions = ""

    name = root.find("./program/name")
    description = root.find("./program/description")
    helplines += '\t\t"d%s\\n\\nUsage:' % description.text
    for usage in root.findall("./program/usage"):
        helplines += " %s %s\\n      "  % (name.text, usage.text)
    helplines = helplines.rstrip()[:-2]
    helplines += '",\n'

    for section in root.findall("./options/section"):
        helplines += '\t\t"s%s:",\n' % section.get("title")
        for opt in section.getchildren():
            line = ""
            arg = opt.find("./arg")
            desc = opt.find("./description")
            cond = opt.get("if", None)
            s = opt.get("short", None)
            l = opt.get("long", None)
            line += "o"
            if s:
                line += "-%s, " % s
            else:
                line += "    "
            line += "--%s" % l
            if arg is not None:
                if arg.get("optional"):
                    line += "["
                line += "="
                line += arg.get("name")
                if arg.get("optional"):
                    line += "]"
            line = line.ljust(30)
            line += " %s" % desc.text
            if arg is not None:
                default = arg.get("default")
                if default:
                    line += " [%s]" % default
            if cond:
                helplines += "#if %s\n" % cond
            helplines += '\t\t"%s",\n' % line
            if cond:
                helplines += "#endif\n"

    for option in root.findall("./options/section/option"):
        name = option.get("long").replace("-", "_")
        arg = option.find("./arg")

        options[name] = {
            "name": name,
            "short": option.get("short", r"\0"),
            "condition": option.get("if"),
        }

        if arg is not None:
            options[name]["arg_type"] = arg.get("type")
            if arg.get("optional") and arg.get("optional") == "yes":
                options[name]["arg_mode"] = "ARG_OPTIONAL"
            else:
                options[name]["arg_mode"] = "ARG_REQUIRED"
            options[name]["arg_default"] = arg.get("default")
        else:
            options[name]["arg_type"] = None
            options[name]["arg_mode"] = "ARG_NONE"

    keys = sorted(options.keys())

    for key in keys:
        option = options[key]
        condition = option["condition"]
        arg = option["arg_type"]

        if condition:
            text = "#if %s\n" % condition
            public += text
            protected += text
            private += text
            _options += text
            initopts += text
            if arg:
                initargs += text
            functions += text

        public += "\t\t"
        protected += "\t\t"
        private += "\t\t"
        _options += "\t"
        initopts += "\t"

        public += "bool %(name)s_given () const {return _%(name)s_given;}\n" % option
        if arg:
            public += "\t\t"
            if option["arg_type"] == "string":
                public += "const std::string&"
            else:
                public += option["arg_type"]
            public += " %(name)s_arg () const {return _%(name)s_arg;}\n" % option

        protected += "void handle_%(name)s (InputReader &ir, const Option &opt, bool longopt);\n" % option

        private += "bool _%(name)s_given;\n" % option
        if arg:
            private += "\t\t"
            if option["arg_type"] == "string":
                private += "std::string"
            else:
                private += option["arg_type"]
            private += " _%(name)s_arg;\n" % option

        _options += "{'%(short)s', " % option
        _options += '"%s", ' % option["name"].replace("_", "-")
        _options += "%(arg_mode)s, new OptionHandlerImpl<%(class)s>(&%(class)s::handle_%(name)s)},\n" % dict({"class": vars["class"]}, **option)

        initopts += "_%(name)s_given = false;\n" % option

        if arg:
            initargs += "\t_%(name)s_arg" % option
            arg_type = option["arg_type"]
            arg_default = option["arg_default"]
            if arg_type == "string" and arg_default is None:
                initargs += ".clear()"
            elif arg_type == "bool":
                initargs += " = %s" % (arg_default == "yes" and "true" or "false")
            elif arg_type == "string":
                initargs += " = \"%s\"" % arg_default
            else:
                initargs += " = %s" % (arg_default and arg_default or "0")
            initargs += ";\n"

        functions += "void %(class)s::handle_%(name)s (InputReader &ir, const Option &opt, bool longopt) {\n" % dict({"class": vars["class"]}, **option)
        if arg:
            functions += "\tif ("
            arg_type = option["arg_type"]
            arg_mode = option["arg_mode"]
            if arg_mode == "ARG_OPTIONAL":
                functions += "ir.eof() || "
            functions += "get%sArg(ir, opt, longopt, _%s_arg))\n\t" % (arg_type.title(), option["name"])
            functions = functions.replace("Unsigned", "UInt")

        functions += "\t_%(name)s_given = true;\n}\n" % option

        if condition:
            text = "#endif\n"
            public += text
            protected += text
            private += text
            _options += text
            initopts += text
            if arg:
                initargs += text
            functions += text

        functions += "\n"

    vars["public"] = public
    vars["private"] = private
    vars["protected"] = protected
    vars["_options"] = _options
    vars["initopts"] = initopts
    vars["initargs"] = initargs
    vars["helplines"] = helplines
    vars["functions"] = functions

    return header_template % vars, cxx_template % vars

if __name__ == "__main__":
    optfile = sys.argv[1]
    cxxfile = sys.argv[2]
    hxxfile = sys.argv[3]
    hxx, cxx = main(optfile)
    open(cxxfile, "w").write(cxx)
    open(hxxfile, "w").write(hxx)
