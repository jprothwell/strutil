strutil ver. 1.1.0
********************

Minimalistic library improving C++ string support with UTF-8 and string handling functions.

The library is designed to be single cpp file only and as easy as possible to integrate.

Supported (optional) config defines:
STRUTIL_STRING // strutil uses std::string if STRUTIL_STRING not defined
STRUTIL_VECTOR // strutil uses std::vector if STRUTIL_VECTOR not defined
STRUTIL_TOLOWER // strutil uses default tolower if STRUTIL_TOLOWER not defined
STRUTIL_TOUPPER // strutil uses toupper if STRUTIL_TOUPPER not defined
STRUTIL_ISSPACE // strutil uses isspace if STRUTIL_STRUTIL not defined

All functions are in str namespace.

strutil library is copyright (C) 2009-2011 Jani Kajala (kajala@gmail.com).
Licensed under BSD/MIT license. See http://code.google.com/p/strutil/

Changes
-------

v1.1.0:
+ added higher level to_utf8/from_utf8

