#include <cstring>
#include <utility>

#include "MemoryHandler.h"
#include "String.h"

String::String(const String& otherString)
    :data(otherString.capacity),
    size(otherString.size),
    capacity(otherString.capacity)
{
    if (otherString.begin() != nullptr) {
        std::strcpy(data.GetAddress(), otherString.begin());
    }
}

String::String(size_t num)
    :size(num),
    capacity(num * 2 + 1),
    data(num * 2 + 1)
{
    data[num] = '\0';
}
void String::operator=(const String& otherString) {
    data = MemoryHandler(otherString.capacity);
    size = otherString.size;
    capacity = otherString.capacity;
    if (otherString.begin() != nullptr) {
        std::strcpy(data.GetAddress(), otherString.begin());
    }
}

String::String(const char* cStyleString)
{
    size = std::strlen(cStyleString);
    capacity = 2 * size + 1;
    data = MemoryHandler(capacity);
    //std::strcpy(data.GetAddress(), cStyleString);
    if (size != 0) {
        std::strcpy(data.GetAddress(), cStyleString);
    }
}

String& String::operator=(const char* cStyleString) {
    size = std::strlen(cStyleString);
    capacity = 2 * size + 1;
    data = MemoryHandler(capacity);
    if (size != 0) {
        std::strcpy(data.GetAddress(), cStyleString);
    }
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

String& String::operator+=(const String& otherString) {

    return *this;
}
//for right interpretate like c-string
String::operator const char*() const {
    return data.GetAddress();
}
String::operator char*() {
    return data.GetAddress();
}
String::iterator String::begin() noexcept {
    return data.GetAddress();
}
String::iterator String::end() noexcept {
    return data + size;
}
String::const_iterator String::cbegin() const noexcept {
    return data.GetAddress();
}
String::const_iterator String::cend() const noexcept {
    return data + size;
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

String String::Concatenate(const char* lhs, size_t lhs_size, const char* rhs, size_t rhs_size) {
    String result(lhs_size + rhs_size);
    std::strcpy(result.begin(), lhs);
    std::strcpy(result.begin() + lhs_size, rhs);
    return result;
}

String operator+(const String& lhs, const char* rhs) {
    return String::Concatenate(lhs.begin(), lhs.size, rhs, std::strlen(rhs));
}
String operator+(const char* lhs, const String& rhs) {
    return String::Concatenate(lhs, std::strlen(lhs), rhs.begin(), rhs.size);
}
String operator+(const String& lhs, const String& rhs) {
    return String::Concatenate(lhs.cbegin(), lhs.Size(), rhs.cbegin(), rhs.Size());
}


