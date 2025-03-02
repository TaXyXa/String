#include <cstring>
#include <utility>

#include "MemoryHandler.h"
#include "String.h"

String::String() : size_(0), data_(CalcCapacity(0))
{
    data_[0] = '\0';
}

String::String(size_t size) : size_(0), data_(CalcCapacity(size))
{
    data_[0] = '\0';
}

String::String(const String &otherString)
    : size_(otherString.GetSize()), data_(otherString.GetCapacity())
{
    strcpy_s(data_.GetAddress(), GetCapacity(), otherString.begin());
}

String &String::operator=(const String &otherString)
{
    if (*this != otherString)
    {
        if (GetCapacity() > otherString.GetSize())
        {
            strcpy_s(data_.GetAddress(), GetCapacity(), otherString.begin());
            size_ = otherString.GetSize();
        }
        else
        {
            String new_string(otherString);
            Swap(new_string);
        }
    }
    return *this;
}

String::String(const char *cStyleString)
    : size_(cStyleString ? std::strlen(cStyleString) : 0),
      data_(CalcCapacity(size_))
{
    if (cStyleString)
    {
        strcpy_s(data_.GetAddress(), GetCapacity(), cStyleString);
    }
    else
    {
        data_[0] = '\0';
    }
}

String &String::operator=(const char *cStyleString)
{
    String new_string(cStyleString);
    Swap(new_string);
    return *this;
}

String::String(String &&otherString) noexcept
    : size_(std::move(otherString.size_)), data_(std::move(otherString.data_))
{
}

String &String::operator=(String &&otherString) noexcept
{
    if (*this != otherString)
    {
        Swap(otherString);
    }
    return *this;
}

String &String::operator+=(const char *otherString)
{
    if (!otherString)
    {
        return *this;
    }

    size_t other_size = std::strlen(otherString);
    if (other_size == 0)
    {
        return *this;
    }

    if (GetCapacity() > size_ + other_size)
    {
        strcpy_s(end(), GetCapacity() - size_, otherString);
    }
    else
    {
        size_t new_capacity = CalcCapacity(size_ + other_size);
        MemoryHandler new_data(new_capacity);
        strcpy_s(new_data.GetAddress(), new_capacity, data_.GetAddress());
        strcpy_s(new_data.GetAddress() + size_, new_capacity - size_, otherString);
        data_.Swap(new_data);
    }
    size_ += other_size;
    return *this;
}
String &String::operator+=(const String &otherString)
{
    return *this += otherString.begin();
}

bool String::operator<(const char *otherString) const
{
    return Compare(begin(), otherString) < 0;
}
bool String::operator<(const String &otherString) const
{
    return Compare(begin(), otherString.begin()) < 0;
}
bool String::operator>(const char *otherString) const
{
    return Compare(begin(), otherString) > 0;
}
bool String::operator>(const String &otherString) const
{
    return Compare(begin(), otherString.begin()) > 0;
}
bool String::operator==(const char *otherString) const
{
    return Compare(begin(), otherString) == 0;
}
bool String::operator==(const String &otherString) const
{
    return Compare(begin(), otherString.begin()) == 0;
}

// for right interpretate like c-string
String::operator const char *() const
{
    return data_.GetAddress();
}
String::operator char *()
{
    return data_.GetAddress();
}

String::iterator String::begin() noexcept
{
    return data_.GetAddress();
}
String::iterator String::end() noexcept
{
    return data_ + size_;
}
String::const_iterator String::cbegin() const noexcept
{
    return data_.GetAddress();
}
String::const_iterator String::cend() const noexcept
{
    return data_ + size_;
}
String::const_iterator String::begin() const noexcept
{
    return cbegin();
}
String::const_iterator String::end() const noexcept
{
    return cend();
}

size_t String::GetSize() const noexcept
{
    return size_;
}

size_t String::GetCapacity() const noexcept
{
    return data_.GetCapacity();
}

void String::Swap(String &otherString)
{
    if (*this != otherString)
    {
        data_.Swap(otherString.data_);
        std::swap(size_, otherString.size_);
    }
}

String String::Concatenate(const char *lhs, const char *rhs)
{
    size_t size = 0;
    if (lhs)
    {
        size += std::strlen(lhs);
    }
    if (rhs)
    {
        size += std::strlen(rhs);
    }
    String new_string(size);
    new_string += lhs;
    new_string += rhs;
    return new_string;
}

// lhs must be valid
int String::Compare(const char *lhs, const char *rhs)
{
    if (!rhs)
    {
        return std::strcmp(lhs, '\0');
    }
    return std::strcmp(lhs, rhs);
}

String operator+(const String &lhs, const char *rhs)
{
    return String::Concatenate(lhs.cbegin(), rhs);
}

String operator+(const char *lhs, const String &rhs)
{
    return String::Concatenate(lhs, rhs.cbegin());
}

String operator+(const String &lhs, const String &rhs)
{
    return String::Concatenate(lhs.cbegin(), rhs.cbegin());
}

size_t String::CalcCapacity(size_t size)
{
    return 2 * size + 1;
}
