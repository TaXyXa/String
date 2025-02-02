#include <iostream>
#include <cassert>

#include "MemoryHandler.h"
#include "String.h"

void MemoryHandlerTest() {
	//empty constructor
	MemoryHandler emptyHandler;
	assert(emptyHandler.GetAddress() == nullptr);
	assert(emptyHandler.GetCapacity() == 0);
	//no empty constructor
	MemoryHandler noEmptyHandler(3);
	char* curentAddress = noEmptyHandler.GetAddress();
	//operator[] tests
	noEmptyHandler[0] = '4';
	noEmptyHandler[1] = '2';
	noEmptyHandler[2] = '\0';
	assert(curentAddress != nullptr);
	assert(noEmptyHandler.GetCapacity() == 3);
	//operator+ tests
	assert(*(noEmptyHandler + 1) == '2');
	//move operator
	emptyHandler = std::move(noEmptyHandler);
	assert(emptyHandler.GetAddress() == curentAddress);
	assert(noEmptyHandler.GetAddress() == nullptr);
	assert(emptyHandler.GetCapacity() == 3);
	//move constructor
	MemoryHandler moveHandler(std::move(emptyHandler));
	assert(moveHandler.GetAddress() == curentAddress);
	assert(emptyHandler.GetAddress() == nullptr);
	assert(moveHandler.GetCapacity() == 3);
	//test swap
	MemoryHandler swapHandler(6);
	swapHandler[0] = 'H';
	swapHandler[1] = 'e';
	swapHandler[2] = 'l';
	swapHandler[3] = 'l';
	swapHandler[4] = 'o';
	swapHandler[5] = '\0';
	moveHandler.Swap(swapHandler);
	std::cout << "Move Handler "<< moveHandler.GetAddress() << std::endl;
	std::cout << "Swap Handler "<< swapHandler.GetAddress() << std::endl;
}

int main() {
	MemoryHandlerTest();
	String hiii = "Hello world";
	std::cout << hiii << std::endl;
	return 0;
}