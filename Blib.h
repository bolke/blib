#ifndef BLIB_H
#define BLIB_H

#include "Core.h"
#include "Messages.h"
#include "Serial.h"
#include "FileIO.h"
#include "Network.h"  
#include "Security.h"
#include "Sql.h"                    //uses sqlite, public domain
#include "WebServing.h"             //uses mongoose lib,MIT licensed version
#include "Xml.h"                    //uses pugixml lib,MIT license

#include <stdio.h>
#include <stdlib.h>

#define BLIB_VERSION "1.14.09.2014"
#define BLIB_CORE "x86 device"

#if defined(WINDOWS)
#define BLIB_OS "windows"
#elif defined(LINUX)
#define BLIB_OS "linux"
#endif

#if defined(_DEBUG)
#define BLIB_CONFIGURATION "debug"
#else
#define BLIB_CONFIGURATION "release"
#endif

#define BLIB_LICENSE "\
Copyright (c) 2004-2014\n\
\n\
Permission is hereby granted, free of charge, to any person obtaining a copy\n\
of this software and associated documentation files (the \"Software\"), to deal\n\
in the Software without restriction, including without limitation the rights\n\
to use, copy, modify, merge, publish, distribute, sublicense, and\or sell\n\
copies of the Software, and to permit persons to whom the Software is\n\
furnished to do so, subject to the following conditions:\n\
\n\
The above copyright notice and this permission notice shall be included in\n\
all copies or substantial portions of the Software.\n\
\n\
THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n\
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n\
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n\
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n\
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n\
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN\n\
THE SOFTWARE."

#define BLIB_LICENSE_TYPE "MIT"

#endif
