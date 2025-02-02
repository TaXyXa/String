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
    String& operator=(const char* cStyleString);
    String(String&& otherString) noexcept;
    String& operator=(String&& otherString) noexcept;
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
    void CopyCString(const char* cStyleString);

    MemoryHandler data; 
    size_t size;
    size_t capacity;
};