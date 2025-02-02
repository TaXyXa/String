#include <iostream>

#include "MemoryHandler.h"
#include "String.h"
#include "Test.h"

int main() {
	MemoryHandlerTest();
	StringTest();
	String hiii = String("Hello") + " world";
	std::cout << hiii << std::endl;
	return 0;
}