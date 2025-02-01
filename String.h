#pragma once
#include "MemoryHandler.h"

class String {
public:
    using iterator = char*;
    using const_iterator = const char*;

    String() = default;
    String(const String& otherString);
    void operator=(const String& otherString);
    String(const char* cStyleString);
    void operator=(const char* cStyleString);
    String(String&& otherString);
    void operator=(String&& otherString);
    void operator+=(const String& otherString);
    //for right interpretate like c-string
    operator char*();
    operator const char*() const;
    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    size_t Size() const noexcept;
    size_t Capacity() const noexcept;


private:
    MemoryHandler data; 
    size_t size;
    size_t capacity;
};