#pragma once
#include "MemoryHandler.h"

class String {
public:
    using iterator = char*;
    using const_iterator = const char*;

    String() = default;
    String(size_t size);
    String(const String& otherString);
    void operator=(const String& otherString);
    String(const char* cStyleString);
    String& operator=(const char* cStyleString);
    String(String&& otherString) noexcept;
    String& operator=(String&& otherString) noexcept;
    String& operator+=(const String& otherString);
    //for right interpretate like c-string
    operator const char*() const;
    operator char*();

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    size_t Size() const noexcept;
    size_t Capacity() const noexcept;
 
    friend String operator+(const String& lhs, const char* rhs);
    friend String operator+(const char* lhs, const String& rhs);
    friend String operator+(const String& lhs, const String& rhs);
private:

    static String Concatenate(const char* lhs, size_t lhs_size, const char* rhs, size_t rhs_size);

    MemoryHandler data; 
    size_t size = 0;
    size_t capacity = 0;
};
