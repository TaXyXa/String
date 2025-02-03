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
	String good("Good");
	good += hiii;
	std::cout << hiii << hiii.Size() << hiii.Capacity()  << std::endl;
	std::cout << good << good.Size() << good.Capacity()  << std::endl;
	return 0;
}