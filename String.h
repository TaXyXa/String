#pragma once
#include "MemoryHandler.h"

class String
{
public:
    using iterator = char *;
    using const_iterator = const char *;

    String();
    explicit String(size_t size);

    String(const String &otherString);
    String &operator=(const String &otherString);

    explicit String(const char *cStyleString);
    String &operator=(const char *cStyleString);

    String(String &&otherString) noexcept;
    String &operator=(String &&otherString) noexcept;

    String &operator+=(const char *otherString);
    String &operator+=(const String &otherString);

    bool operator<(const char *otherString) const;
    bool operator<(const String &otherString) const;
    bool operator>(const char *otherString) const;
    bool operator>(const String &otherString) const;
    bool operator==(const char *otherString) const;
    bool operator==(const String &otherString) const;
    // for right interpretate like c-string
    operator const char *() const;
    operator char *();

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    size_t GetSize() const noexcept;
    size_t GetCapacity() const noexcept;
    void Swap(String &otherString);

    friend String operator+(const String &lhs, const char *rhs);
    friend String operator+(const char *lhs, const String &rhs);
    friend String operator+(const String &lhs, const String &rhs);

private:
    static String Concatenate(const char *lhs, const char *rhs);
    static int Compare(const char *lhs, const char *rhs);
    static size_t CalcCapacity(size_t size);

    // size_ must be first data member
    size_t size_ = 0;
    MemoryHandler data_;
};

String operator+(const String &lhs, const char *rhs);
String operator+(const char *lhs, const String &rhs);
String operator+(const String &lhs, const String &rhs);
