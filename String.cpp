#include <cstring>
#include <utility>

#include "MemoryHandler.h"
#include "String.h"

    String::String(const String& otherString)
    {

    }
    void String::operator=(const String& otherString) {

    }
    String::String(const char* cStyleString)
    {
        size = std::strlen(cStyleString);
        capacity = 2 * size;
        data = MemoryHandler(capacity);
        for (int i = 0; i < size; i++) {
            data[i] = cStyleString[i];
        }
        data[size + 1] = '\0';
    }
    void String::operator=(const char* cStyleString) {
        size = std::strlen(cStyleString);
        capacity = 2 * size;
        data = MemoryHandler(capacity);
        for (int i = 0; i < size; i++) {
            data[i] = cStyleString[i];
        }
        data[size + 1] = '\0';
    }
    String::String(String&& otherString) {

    }
    void String::operator=(String&& otherString) {

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
