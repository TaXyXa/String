#pragma once
#include <iostream>
#include <cassert>
#include <utility>

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

void StringTest() {
    { // empty constructor
        String NewString;
        assert(NewString.begin() == nullptr);
        assert(NewString.end() == nullptr);
        assert(NewString.Size() == 0);
        assert(NewString.Capacity() == 0);
    }
    { // size constructor
        String NewString(5);
        assert(NewString.begin() != nullptr);
        assert(*NewString.end() == '\0');
        assert(NewString.Size() == 5);
        assert(NewString.Capacity() == 11);
    }
    { // copy from c=style constructor
        String NewString("Hi new char");
        assert(*NewString.begin() == 'H');
        assert(*NewString.end() == '\0');
        assert(NewString.Size() == 11);
        assert(NewString.Capacity() == 23);
    }
    { // copy from other String constructor
        String OldString("Hi new char");
        String NewString(OldString);
        assert(NewString.begin() != OldString.begin());
        assert(NewString.Size() == OldString.Size());
        assert(*(NewString.begin() + 3) == 'n');
        assert(*(NewString.begin() + 3) == *(OldString.begin() + 3));
        assert(NewString.Capacity() == 23);
    }
    { // copy from c=style operator
        String NewString = "Hi new char";
        assert(*NewString.begin() == 'H');
        assert(*NewString.end() == '\0');
        assert(NewString.Size() == 11);
        assert(NewString.Capacity() == 23);
    }
    { // copy from other String operator
        String OldString("Hi new char");
        String NewString = OldString;
        assert(NewString.begin() != OldString.begin());
        assert(NewString.Size() == OldString.Size());
        assert(*(NewString.begin() + 3) == 'n');
        assert(*(NewString.begin() + 3) == *(OldString.begin() + 3));
        assert(NewString.Capacity() == 23);
    }
    { // move from other String constructor
        String OldString("Hi new char");
        char* old_ptr = OldString.begin();
        int old_size = OldString.Size();
        String NewString(std::move(OldString));
        assert(OldString.begin() == nullptr);
        assert(NewString.begin() == old_ptr);
        assert(NewString.Size() == old_size);
        assert(*(NewString.begin() + 3) == 'n');
        assert(NewString.Capacity() == 23);
    }
    { // copy from other String operator
        String OldString("Hi new char");
        char* old_ptr = OldString.begin();
        int old_size = OldString.Size();
        String NewString = std::move(OldString);
        assert(OldString.begin() == nullptr);
        assert(NewString.begin() == old_ptr);
        assert(NewString.Size() == old_size);
        assert(*(NewString.begin() + 3) == 'n');
        assert(NewString.Capacity() == 23);
    }
}