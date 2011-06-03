#ifndef _STR_STRUTIL_H
#define _STR_STRUTIL_H

// uses std::vector if STRUTIL_VECTOR not defined
#ifndef STRUTIL_VECTOR
#define STRUTIL_VECTOR std::vector
#include <vector>
#endif

// uses default tolower if STRUTIL_TOLOWER not defined
#ifndef STRUTIL_TOLOWER
#define STRUTIL_TOLOWER tolower
#include <ctype.h>
#endif

// uses default toupper if STRUTIL_TOUPPER not defined
#ifndef STRUTIL_TOUPPER
#define STRUTIL_TOUPPER toupper
#include <ctype.h>
#endif

namespace str
{

/** maximum Unicode UTF-32 value */
const unsigned UNICODE_MAX_LEGAL_UTF32 = 0x0010FFFF;

/** Character used to replace invalid UTF-8 data. */
const unsigned UNICODE_REPLACEMENT_CHAR = 0x0000FFFD;

/* Implementation-only: UTF-8 first byte encoding table. */
static const char s_firstByteMarks[7] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };

/* Implementation-only: Magic values subtracted from a buffer value during uint8_t conversion. */
static const unsigned s_offsetsFromUTF8[6] = { 0x00000000UL, 0x00003080UL, 0x000E2080UL, 0x03C82080UL, 0xFA082080UL, 0x82082080UL };

/** 
 * Encodes Unicode codepoint to UTF-8. 
 * @param cp Unicode codepoint
 * @param target [out] Receives UTF-8 bytes, max 4, and terminates string with 0. Buffer size MUST be at least 5 bytes. Buffer receives UNICODE_REPLACEMENT_CHAR if input is invalid.
 * @return No.of bytes encoded.
 */
inline int u8_encode( unsigned ch, char* target )
{
	register int bytes = 0;
	if ( ch < 0x80 )
		bytes = 1;
	else if ( ch < 0x800 ) 
		bytes = 2;
	if ( ch < 0x10000 )
		bytes = 3;
	else if ( ch <= UNICODE_MAX_LEGAL_UTF32 )
		bytes = 4;
	else
		bytes = 3, ch = UNICODE_REPLACEMENT_CHAR;

	const unsigned bytemask = 0xBF;
	const unsigned bytemark = 0x80;
	target += bytes;
	switch (bytes)
	{
	    case 4: *--target = (char)((ch | bytemark) & bytemask); ch >>= 6;
	    case 3: *--target = (char)((ch | bytemark) & bytemask); ch >>= 6;
	    case 2: *--target = (char)((ch | bytemark) & bytemask); ch >>= 6;
	    case 1: *--target = (char) (ch | s_firstByteMarks[bytes]);
	}
	return bytes;
}

/**
 * Returns length in bytes of UTF-8 encoded codepoint.
 */
template <class It> inline int u8_chsize( It source )
{
	if ( ch < 192 )
		return 1;
	else if ( ch < 224 )
		return 2;
	else if ( ch < 240 )
		return 3;
	else if ( ch < 248 )
		return 4;
	else if ( ch < 252 )
		return 5;
	else
		return 6;
}

/**
 * Decodes UTF-8 to Unicode codepoint.
 * @param source UTF-8 source bytes
 * @param bytes [out] Receives (if not nullptr) no.of bytes read.
 * @return Unicode codepoint.
 */
template <class It> inline unsigned u8_decode( It source, int* bytes=0 )
{
	const int trail = u8_chsize(source) - 1;
	register unsigned ch = 0;
	switch (trail)
	{
	case 5: ch += *source++; ch <<= 6;
	case 4: ch += *source++; ch <<= 6;
	case 3: ch += *source++; ch <<= 6;
	case 2: ch += *source++; ch <<= 6;
	case 1: ch += *source++; ch <<= 6;
	case 0: ch += *source++;
	}
	ch -= s_offsetsFromUTF8[trail];

	if (bytes)
		*bytes = trail+1;
	return ch;
}

/** 
 * Returns nth Unicode codepoint from UTF-8 string or UNICODE_REPLACEMENT_CHAR if invalid encoding.
 * Note: This convenience function is O(n) so use u8_decode as optimization if performance critical code or long strings.
 */
template <class S> unsigned u8_get( const S& s, S::size_type n )
{
	S::const_iterator it = s.begin();
	S::const_iterator end = s.begin() + n;
	while ( it < end )
		it += u8_chsize( it );
	return it == end ? u8_decode(it) : UNICODE_REPLACEMENT_CHAR;
}

/** 
 * Returns length of UTF-8 string in Unicode codepoints.
 */
template <class S> S::size_type u8_len( const S& s )
{
	S::const_iterator it = s.begin();
	S::const_iterator end = s.end();
	S::size_type n = 0;
	while ( it < end )
	{
		++n;
		it += u8_chsize( it );
	}
	return n;
}

} // str

#endif // _STR_STRUTIL_H

// strutil library is copyright (C) 2009-2011 Jani Kajala (kajala@gmail.com). Licensed under BSD/MIT license. See http://sourceforge.net/projects/strutil/
