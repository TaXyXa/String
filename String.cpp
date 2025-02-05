#include <cstring>
#include <utility>

#include "MemoryHandler.h"
#include "String.h"

String::String(const String& otherString)
    :data_(otherString.capacity_),
    size_(otherString.size_),
    capacity_(otherString.capacity_)
{
    if (otherString.begin() != nullptr) {
        strcpy_s(data_.GetAddress(), capacity_, otherString.begin());
    }
}

String::String(size_t size)
    :size_(0),
    capacity_(CalcCapacity(size)),
    data_(CalcCapacity(size))
{
    data_[0] = '\0';
}
String& String::operator=(const String& otherString) {
    String NewString(otherString);
    Swap(NewString);
    return *this;
}

String::String(const char* cStyleString)
    :size_ (std::strlen(cStyleString)),
    capacity_ (CalcCapacity(std::strlen(cStyleString))),
    data_ (CalcCapacity(std::strlen(cStyleString)))
{
    if (size_ != 0) {
        strcpy_s(data_.GetAddress(), capacity_, cStyleString);
    }
}

String& String::operator=(const char* cStyleString) {
    String NewString(cStyleString);
    Swap(NewString);
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
    size_t otherSize = std::strlen(otherString);
    if (otherSize == 0) {
        return *this;
    }
    if (capacity_ > size_ + otherSize) {
        strcpy_s(begin() + size_, capacity_ - size_, otherString);
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
    return Compare(otherString, begin()) < 0;
}
bool String::operator>(const String& otherString) const {
    return Compare(otherString.begin(), begin()) < 0;
}
bool String::operator==(const char* otherString) const {
    return !(*this < otherString) && !(*this > otherString);
}
bool String::operator==(const String& otherString) const {
    return !(*this < otherString) && !(*this > otherString);
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
    std::swap(data_, otherString.data_);
    std::swap(size_, otherString.size_);
    std::swap(capacity_, otherString.capacity_);
}

String String::Concatenate(const char* lhs, size_t lhs_size, const char* rhs, size_t rhs_size) {
    String result(lhs_size + rhs_size);
    strcpy_s(result.begin(), lhs_size + 1, lhs);
    strcpy_s(result.begin() + lhs_size, rhs_size + 1, rhs);
    return result;
}

int String::Compare(const char* lhs, const char* rhs) {
    return std::strcmp(lhs, rhs);
}

String operator+(const String& lhs, const char* rhs) {
    return String::Concatenate(lhs.begin(), lhs.size_, rhs, std::strlen(rhs));
}
String operator+(const char* lhs, const String& rhs) {
    return String::Concatenate(lhs, std::strlen(lhs), rhs.begin(), rhs.size_);
}
String operator+(const String& lhs, const String& rhs) {
    return String::Concatenate(lhs.cbegin(), lhs.Size(), rhs.cbegin(), rhs.Size());
}

size_t String::CalcCapacity(size_t size) {
    return 2 * size + 1;
}


