#include <cstring>
#include <utility>

#include "MemoryHandler.h"
#include "String.h"

    String::String(const String& otherString)
        :data(otherString.capacity),
        size(otherString.size),
        capacity(otherString.capacity)
    {
        CopyCString(otherString.begin());
    }
    
    void String::operator=(const String& otherString) {
        data = MemoryHandler(otherString.capacity);
        size = otherString.size;
        capacity = otherString.capacity;
        CopyCString(otherString.begin());
    }

    String::String(const char* cStyleString)
    {
        size = std::strlen(cStyleString);
        capacity = 2 * size;
        data = MemoryHandler(capacity);
        CopyCString(cStyleString);
    }

    String& String::operator=(const char* cStyleString) {
        size = std::strlen(cStyleString);
        capacity = 2 * size;
        data = MemoryHandler(capacity);
        CopyCString(cStyleString);
        return *this;
    }

    String::String(String&& otherString) noexcept
        :data(std::move(otherString.data)),
        size(std::move(otherString.size)),
        capacity(std::move(otherString.capacity))
    {}

    String& String::operator=(String&& otherString) noexcept {
        data = std::move(otherString.data);
        size = std::move(otherString.size);
        capacity = std::move(otherString.capacity);
        return *this;
    }
    
    void String::operator+=(const String& otherString) {

    }
    //for right interpretate like c-string
    String::operator char*() {
        return data.GetAddress();
    }
    String::operator const char*() const {
        return data.GetAddress();
    }
    String::iterator String::begin() noexcept {
        return data.GetAddress();
    }
    String::iterator String::end() noexcept {
        return data.GetAddress() + size;
    }
    String::const_iterator String::cbegin() const noexcept {
        return const_cast<char*>(begin());
    }
    String::const_iterator String::cend() const noexcept {
        return const_cast<char*>(end());
    }
    String::const_iterator String::begin() const noexcept {
        return cbegin();
    }
    String::const_iterator String::end() const noexcept {
        return cend();
    }
    size_t String::Size() const noexcept {
        return size;
    }
    size_t String::Capacity() const noexcept {
        return capacity;
    }
    void String::CopyCString(const char* cStyleString){
        for (int i = 0; i < size; i++) {
            data[i] = cStyleString[i];
        }
        data[size] = '\0';
    }
