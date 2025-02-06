#include <cstring>
#include <utility>

#include "MemoryHandler.h"
#include "String.h"

String::String() 
    :size_(0),
    capacity_(CalcCapacity(0)),
    data_(CalcCapacity(0))
{
    data_[0] = '\0';
}

String::String(size_t size)
    :size_(0),
    capacity_(CalcCapacity(size)),
    data_(CalcCapacity(size))
{
    data_[0] = '\0';
}

String::String(const String& otherString)
    :size_(otherString.size_),
    capacity_(otherString.capacity_),
    data_(otherString.capacity_)
{
    strcpy_s(data_.GetAddress(), capacity_, otherString.begin());
}

String& String::operator=(const String& otherString) {
    if (*this != otherString) {
        if (capacity_ > otherString.Size()) {
            strcpy_s(data_.GetAddress(), capacity_, otherString.begin());
        } else {
            String NewString(otherString);
            Swap(NewString);
        }
    }
    return *this;
}

String::String(const char* cStyleString)
    :size_ (cStyleString ? std::strlen(cStyleString) : 0),
    capacity_ (CalcCapacity(cStyleString ? std::strlen(cStyleString) : 0)),
    data_ (CalcCapacity(cStyleString ? std::strlen(cStyleString) : 0))
{
    if (cStyleString) {
        strcpy_s(data_.GetAddress(), capacity_, cStyleString);
    } else {
        data_[0] = '\0';
    }
}

String& String::operator=(const char* cStyleString) {
    if (cStyleString && capacity_ > std::strlen(cStyleString)) {
        strcpy_s(data_.GetAddress(), capacity_, cStyleString);
    } else {
        String NewString(cStyleString);
        Swap(NewString);
    }
    return *this;
}

String::String(String&& otherString) noexcept
    :data_(std::move(otherString.data_)),
    size_(std::move(otherString.size_)),
    capacity_(std::move(otherString.capacity_))
{}

String& String::operator=(String&& otherString) noexcept {
    if (*this != otherString) {
        Swap(otherString);
    }
    return *this;
}

String& String::operator+=(const char* otherString) {
    if (!otherString) {
        return *this;
    }
    size_t otherSize = std::strlen(otherString);
    if (otherSize == 0) {
        return *this;
    }

    if (capacity_ > size_ + otherSize) {
        strcpy_s(end(), capacity_ - size_, otherString);
    } else {
        size_t new_capacity = CalcCapacity(size_ + otherSize);
        MemoryHandler new_data(new_capacity);
        strcpy_s(new_data.GetAddress(), new_capacity, data_.GetAddress());
        strcpy_s(new_data.GetAddress() + size_, new_capacity - size_, otherString);
        data_.Swap(new_data);
        capacity_ = new_capacity;
    }
    size_ += otherSize;
    return *this;
}
String& String::operator+=(const String& otherString) {
    return *this += otherString.begin();
}
bool String::operator<(const char* otherString) const {
    return Compare(begin(), otherString) < 0;
}
bool String::operator<(const String& otherString) const {
    return Compare(begin(), otherString.begin()) < 0;
}
bool String::operator>(const char* otherString) const {
    return Compare(begin(), otherString) > 0;
}
bool String::operator>(const String& otherString) const {
    return Compare(begin(), otherString.begin()) > 0;
}
bool String::operator==(const char* otherString) const {
    return Compare(begin(), otherString) == 0;
}
bool String::operator==(const String& otherString) const {
    return Compare(begin(), otherString.begin()) == 0;
}

//for right interpretate like c-string
String::operator const char*() const {
    return data_.GetAddress();
}
String::operator char*() {
    return data_.GetAddress();
}

String::iterator String::begin() noexcept {
    return data_.GetAddress();
}
String::iterator String::end() noexcept {
    return data_ + size_;
}
String::const_iterator String::cbegin() const noexcept {
    return data_.GetAddress();
}
String::const_iterator String::cend() const noexcept {
    return data_ + size_;
}
String::const_iterator String::begin() const noexcept {
    return cbegin();
}
String::const_iterator String::end() const noexcept {
    return cend();
}
size_t String::Size() const noexcept {
    return size_;
}
size_t String::Capacity() const noexcept {
    return capacity_;
}

void String::Swap(String& otherString) {
    if (*this != otherString) {
        data_.Swap(otherString.data_);
        std::swap(size_, otherString.size_);
        std::swap(capacity_, otherString.capacity_);
    }
}

String String::Concatenate(const char* lhs, const char* rhs) {
    size_t size = 0;
    if (lhs) {
        size += std::strlen(lhs);
    }    
    if (rhs) {
        size += std::strlen(rhs);
    }
    String result(size);
    result += lhs;
    result += rhs;
    return result;
}

//lhs must be valid
int String::Compare(const char* lhs, const char* rhs) {
    if (!rhs) {
        return std::strcmp(lhs, '\0');
    }
    return std::strcmp(lhs, rhs);
}

String operator+(const String& lhs, const char* rhs) {
    return String::Concatenate(lhs.cbegin(), rhs);
}
String operator+(const char* lhs, const String& rhs) {
    return String::Concatenate(lhs, rhs.cbegin());
}
String operator+(const String& lhs, const String& rhs) {
    return String::Concatenate(lhs.cbegin(), rhs.cbegin());
}

size_t String::CalcCapacity(size_t size) {
    return 2 * size + 1;
}


