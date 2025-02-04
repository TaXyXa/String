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
	String good("good");
	//good += hiii;
	std::cout << hiii << hiii.Size() << hiii.Capacity()  << std::endl;
	std::cout << good << good.Size() << good.Capacity()  << std::endl;
	std::cout << (good < "Good") << std::strcmp(good.begin(), "Good") << std::endl;
	std::cout << (good > "Good") << std::endl;
	std::cout << (good == "Good") << std::endl;
	return 0;
}