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
        strcpy_s(data.GetAddress(), capacity, otherString.begin());
    }
}

String::String(size_t num)
    :size(num),
    capacity(num * 2 + 1),
    data(num * 2 + 1)
{
    data[num] = '\0';
}
String& String::operator=(const String& otherString) {
    String NewString(otherString);
    Swap(NewString);
    return *this;
}

String::String(const char* cStyleString)
    :size (std::strlen(cStyleString)),
    capacity (2 * std::strlen(cStyleString) + 1),
    data (2 * std::strlen(cStyleString) + 1)
{
    if (size != 0) {
        strcpy_s(data.GetAddress(), capacity, cStyleString);
    }
}

String& String::operator=(const char* cStyleString) {
    String NewString(cStyleString);
    Swap(NewString);
    return *this;
}

String::String(String&& otherString) noexcept
    :data(std::move(otherString.data)),
    size(std::move(otherString.size)),
    capacity(std::move(otherString.capacity))
{}

String& String::operator=(String&& otherString) noexcept {
    if (*this != otherString) {
        Swap(otherString);
    }
    return *this;
}

String& String::operator+=(const char* otherString) {
    size_t otherSize = std::strlen(otherString);
    if (otherSize == 0) {
        return *this;
    }
    if (capacity > size + otherSize) {
        strcpy_s(begin() + size, capacity, otherString);
    } else {
        size_t new_capacity = size + otherSize + 1;
        MemoryHandler new_data(new_capacity);
        strcpy_s(new_data.GetAddress(), new_capacity, data.GetAddress());
        strcpy_s(new_data.GetAddress() + size, new_capacity - size, otherString);
        data.Swap(new_data);
    }
    return *this;
}
/*String& String::operator+=(const String& otherString) {
    return *this += otherString.begin();
}
bool String::operator<(const char* otherString) {
    return std::strcmp(begin(), otherString) < 0;
}
bool String::operator<(const String& otherString) {
    return *this < otherString;
}
bool String::operator>(const char* otherString) {
    return otherString < *this;
}
bool String::operator>(const String& otherString) {
    return otherString < *this;
}
bool String::operator==(const char* otherString) {
    return !(*this < otherString) && !(otherString < *this);
}
bool String::operator==(const String& otherString) {
    return !(*this < otherString) && !(otherString < *this);
}*/

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

void String::Swap(String& otherString) {
    std::swap(data, otherString.data);
    std::swap(size, otherString.size);
    std::swap(capacity, otherString.capacity);
}

String String::Concatenate(const char* lhs, size_t lhs_size, const char* rhs, size_t rhs_size) {
    String result(lhs_size + rhs_size);
    strcpy_s(result.begin(), lhs_size + 1, lhs);
    strcpy_s(result.begin() + lhs_size, rhs_size + 1, rhs);
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


