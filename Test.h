#pragma once
#include <iostream>
#include <cassert>
#include <utility>

#include "MemoryHandler.h"
#include "String.h"

void MemoryHandlerTest()
{
    // empty constructor
    MemoryHandler emptyHandler;
    assert(emptyHandler.GetAddress() == nullptr);
    assert(emptyHandler.GetCapacity() == 0);
    // no empty constructor
    MemoryHandler noEmptyHandler(3);
    char *curentAddress = noEmptyHandler.GetAddress();
    // operator[] tests
    noEmptyHandler[0] = '4';
    noEmptyHandler[1] = '2';
    noEmptyHandler[2] = '\0';
    assert(curentAddress != nullptr);
    assert(noEmptyHandler.GetCapacity() == 3);
    // operator+ tests
    assert(*(noEmptyHandler + 1) == '2');
    // move operator
    emptyHandler = std::move(noEmptyHandler);
    assert(emptyHandler.GetAddress() == curentAddress);
    assert(noEmptyHandler.GetAddress() == nullptr);
    assert(emptyHandler.GetCapacity() == 3);
    // move constructor
    MemoryHandler moveHandler(std::move(emptyHandler));
    assert(moveHandler.GetAddress() == curentAddress);
    assert(emptyHandler.GetAddress() == nullptr);
    assert(moveHandler.GetCapacity() == 3);
    // test swap
    MemoryHandler swapHandler(6);
    swapHandler[0] = 'H';
    swapHandler[1] = 'e';
    swapHandler[2] = 'l';
    swapHandler[3] = 'l';
    swapHandler[4] = 'o';
    swapHandler[5] = '\0';
    moveHandler.Swap(swapHandler);
}

void StringTest()
{
    { // empty constructor
        String NewString;
        assert(*NewString.begin() == '\0');
        assert(*NewString.end() == '\0');
        assert(NewString.GetSize() == 0);
        assert(NewString.GetCapacity() == 1);
    }
    { // size constructor
        String NewString(5);
        assert(*NewString.begin() == '\0');
        assert(*NewString.end() == '\0');
        assert(NewString.GetSize() == 0);
        assert(NewString.GetCapacity() == 11);
    }
    { // copy from c=style constructor
        String NewString("Hi new char");
        assert(*NewString.begin() == 'H');
        assert(*NewString.end() == '\0');
        assert(NewString.GetSize() == 11);
        assert(NewString.GetCapacity() == 23);
        String NullString(nullptr);
        assert(*NullString.begin() == '\0');
        assert(NullString.GetCapacity() == 1);
    }
    { // copy from other String constructor
        String OldString("Hi new char");
        String NewString(OldString);
        assert(NewString.begin() != OldString.begin());
        assert(NewString.GetSize() == OldString.GetSize());
        assert(*(NewString.begin() + 3) == 'n');
        assert(*(NewString.begin() + 3) == *(OldString.begin() + 3));
        assert(NewString.GetCapacity() == 23);
    }
    { // copy from c=style operator
        String NewString;
        NewString = "Hi new char";
        assert(*NewString.begin() == 'H');
        assert(*NewString.end() == '\0');
        assert(NewString.GetSize() == 11);
        assert(NewString.GetCapacity() == 23);
    }
    { // copy from other String operator
        String OldString("Hi new char");
        String NewString = OldString;
        assert(NewString.begin() != OldString.begin());
        assert(NewString.GetSize() == OldString.GetSize());
        assert(*(NewString.begin() + 3) == 'n');
        assert(*(NewString.begin() + 3) == *(OldString.begin() + 3));
        assert(NewString.GetCapacity() == 23);
    }
    { // move from other String constructor
        String OldString("Hi new char");
        char *old_ptr = OldString.begin();
        size_t old_size = OldString.GetSize();
        String NewString(std::move(OldString));
        assert(NewString.begin() == old_ptr);
        assert(NewString.GetSize() == old_size);
        assert(*(NewString.begin() + 3) == 'n');
        assert(NewString.GetCapacity() == 23);
    }
    { // copy from other String operator
        String OldString("Hi new char");
        char *old_ptr = OldString.begin();
        size_t old_size = OldString.GetSize();
        String NewString = std::move(OldString);
        assert(NewString.begin() == old_ptr);
        assert(NewString.GetSize() == old_size);
        assert(*(NewString.begin() + 3) == 'n');
        assert(NewString.GetCapacity() == 23);
    }
    { // += const char* with reallocate
        String FirstString("Hi");
        const char *SecondString = " new char";
        FirstString += SecondString;
        assert(strcmp(FirstString.begin(), "Hi new char") == 0);
        assert(*(FirstString.begin() + 11) == '\0');
        assert(FirstString.GetSize() == 11);
        assert(FirstString.GetCapacity() == 23);
    }
    { // += const char* without reallocate
        String FirstString(15);
        const char *SecondString = "Hi new char";
        FirstString += SecondString;
        assert(strcmp(FirstString.begin(), SecondString) == 0);
        assert(*(FirstString.begin() + 11) == '\0');
        assert(FirstString.GetSize() == 11);
        assert(FirstString.GetCapacity() == 31);
    }
    { // += String with reallocate
        String FirstString("Hi");
        String SecondString(" new char");
        FirstString += SecondString;
        assert(strcmp(FirstString.begin(), "Hi new char") == 0);
        assert(*(FirstString.begin() + 11) == '\0');
        assert(FirstString.GetSize() == 11);
        assert(FirstString.GetCapacity() == 23);
    }
    { // += String without reallocate
        String FirstString(15);
        String SecondString("Hi new char");
        FirstString += SecondString;
        assert(strcmp(FirstString.begin(), SecondString.begin()) == 0);
        assert(*(FirstString.begin() + 11) == '\0');
        assert(FirstString.GetSize() == 11);
        assert(FirstString.GetCapacity() == 31);
    }
    { // += ""
        String FirstString("Hi");
        const char *SecondString = "";
        FirstString += SecondString;
        assert(strcmp(FirstString.begin(), "Hi") == 0);
        assert(FirstString.GetSize() == 2);
        assert(FirstString.GetCapacity() == 5);
    }
    { // + operator
        String Sum;
        String FirstString("Hi");
        String SecondString(" new char");
        Sum = FirstString + SecondString;
        assert(strcmp(Sum.begin(), "Hi new char") == 0);
        assert(*(Sum.begin() + 11) == '\0');
        assert(Sum.GetSize() == 11);
        assert(Sum.GetCapacity() == 23);
    }
    { // < == > const char*
        String FirstString("first");
        const char *SecondString = "second";
        assert(FirstString < SecondString);
        assert(!(FirstString > SecondString));
        assert(FirstString == "first");
    }
    { // < == > String
        String FirstString("first");
        String SecondString("second");
        assert(FirstString < SecondString);
        assert(!(FirstString > SecondString));
        assert(FirstString == "first");
    }
}