/*
Example of strutil library usage.
*/
#include "strutil.h"
#include <stdio.h>

#ifdef _MSC_VER
#pragma warning( disable : 4996 )
#endif // _MSC_VER

using namespace str;

/** Simple unit test "framework" */
#define check(A) if (A) {} else {printf( "ERROR @ %s(%d): (%s) is false\n", __FILE__, __LINE__, #A ); abort();}

void strutil_test()
{
	// load UTF-8 encoded text file
	FILE* fh = fopen( "../data.txt", "r" );
	if ( !fh )
	{
		printf( "File not found\n" );
		return;
	}
	char_vector_type file;
	while (true)
	{
		int ch = fgetc(fh);
		if ( ch == EOF )
			break;
		file.push_back( char(ch) );
	}
	file.push_back(0);
	fclose(fh);
	string_type s = &file[0];

	unsigned ch = u8_get(s,1);
	check( ch == 228 );
	check( ch == u8_get(s,3) );
	check( u8_len(s) == 28 );
	char buf[8];
	int bytes = u8_encode( 228, buf );
	check( bytes == 2 );
	check( u8_decode(buf) == 228 );
	check( trim("a bc") == "a bc" );
	check( trim("a bc  ") == "a bc" );
	check( trim("  a bc  ") == "a bc" );
	check( trim("  a bc") == "a bc" );
	check( ltrim("a bc") == "a bc" );
	check( ltrim("a bc  ") == "a bc  " );
	check( ltrim("  a bc  ") == "a bc  " );
	check( ltrim("  a bc") == "a bc" );
	check( rtrim("a bc") == "a bc" );
	check( rtrim("a bc  ") == "a bc" );
	check( rtrim("  a bc  ") == "  a bc" );
	check( rtrim("  a bc") == "  a bc" );
	check( ssprintf("123=%d",123) == "123=123" );
	check( uppercase("AbCd") == "ABCD" );
	check( lowercase("AbCd") == "abcd" );
	check( uppercase("AbCdäÖ") == "ABCDäÖ" );
	check( lowercase("AbCdäÖ") == "abcdäÖ" );

	string_vector_type e = explode( ",", "jani,markus,kajala," );
	check( e.size() == 4 );
	check( e[0] == "jani" );
	check( e[1] == "markus" );
	check( e[2] == "kajala" );
	check( e[3] == "" );
	check( implode(",",e) == "jani,markus,kajala," );

	e = explode( ",", "jani,markus,kajala,," );
	check( e.size() == 5 );
	check( e[0] == "jani" );
	check( e[1] == "markus" );
	check( e[2] == "kajala" );
	check( e[3] == "" );
	check( e[4] == "" );
	check( implode(",",e) == "jani,markus,kajala,," );

	e = explode( ",", "jani,markus,kajala" );
	check( e.size() == 3 );
	check( e[0] == "jani" );
	check( e[1] == "markus" );
	check( e[2] == "kajala" );
	check( implode(",",e) == "jani,markus,kajala" );

	e = explode( ",", ",jani,markus,kajala" );
	check( e.size() == 4 );
	check( e[0] == "" );
	check( e[1] == "jani" );
	check( e[2] == "markus" );
	check( e[3] == "kajala" );
	check( implode(",",e) == ",jani,markus,kajala" );
}

int main()
{
	strutil_test();
	return 0;
}

// strutil library is copyright (C) 2009-2011 Jani Kajala (kajala@gmail.com). Licensed under BSD/MIT license. See http://code.google.com/p/strutil/
