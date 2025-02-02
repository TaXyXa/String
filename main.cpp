#include <iostream>

#include "MemoryHandler.h"
#include "String.h"
#include "Test.h"

int main() {
	MemoryHandlerTest();
	StringTest();
	String hiii;
	hiii = "Hello";
	hiii += " world";
	std::cout << hiii << hiii.Size() << hiii.Capacity() << std::endl;
	return 0;
}