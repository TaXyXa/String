#include <algorithm>
#include <cctype>
#include <iostream>
#include <vector>

#include "MemoryHandler.h"
#include "String.h"
#include "Test.h"

int main( int argc, char* argv[] ) {
	//MemoryHandlerTest();
	//StringTest();
	std::vector<std::pair<String, String>> lines_lowlines;
	for ( int i = 1; i < argc ; i++ ) {
		lines_lowlines.emplace_back( argv[ i ], argv[ i ] );
		for ( char& ch : lines_lowlines[ i - 1 ].second ) {
			ch = std::tolower( ch );
		}
	}
	std::sort(	lines_lowlines.begin(),
				lines_lowlines.end(),
				[]( const std::pair<String, String>& lhs, const std::pair<String, String>& rhs ) {
					return lhs.second > rhs.second;
				});
	for ( const auto& line : lines_lowlines ) {
		std::cout << line.first << ' ';
	}
	std::cout << std::endl;
	return 0;
}