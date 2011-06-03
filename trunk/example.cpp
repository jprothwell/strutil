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
#define check(A) if (A) {} else {printf( "ERROR @ %s(%d): (%s) is false\n", __FILE__, __LINE__, #A );}

int main()
{
	// load UTF-8 encoded text file
	FILE* fh = fopen( "../data.txt", "r" );
	if ( !fh )
	{
		printf( "File not found\n" );
		return 1;
	}
	std::vector<char> file;
	while (true)
	{
		int ch = fgetc(fh);
		if ( ch == EOF )
			break;
		file.push_back( char(ch) );
	}
	file.push_back(0);
	fclose(fh);
	std::string s = &file[0];

	// unit tests
	unsigned ch = u8_get(s,1);
	check( ch == 228 );
	check( ch == u8_get(s,3) );
	check( u8_len(s) == 28 );
	char buf[8];
	int bytes = u8_encode( 228, buf );
	check( bytes == 2 );
	check( u8_decode(buf) == 228 );
	return 0;
}
