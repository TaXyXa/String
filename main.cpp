#include <algorithm>
#include <cctype>
#include <iostream>
#include <vector>

#include "MemoryHandler.h"
#include "String.h"
#include "Test.h"

int main(int argc, char* argv[]) {
	MemoryHandlerTest();
	StringTest();
	std::vector<String> lines;
	for (int i = 1; i < argc; i++) {
		lines.emplace_back(argv[i]);
		for (char& ch : lines[i - 1]) {
			ch = std::tolower(ch);
		}
	}
	std::sort(lines.begin(), lines.end(), [](const String& lhs, const String& rhs) {
		return lhs > rhs;
	});
	for (const auto& line : lines) {
		std::cout << line << '\n';
	}
	return 0;
}