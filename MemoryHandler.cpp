#include <cassert>
#include <utility>

#include "MemoryHandler.h"

MemoryHandler::MemoryHandler(MemoryHandler&& otherMemory) noexcept 
:buffer_ptr(std::move(otherMemory.buffer_ptr)),
capacity(otherMemory.capacity)
{
    otherMemory.buffer_ptr = nullptr;
}

MemoryHandler& MemoryHandler::operator=(MemoryHandler&& otherMemory) noexcept {
    if (this != &otherMemory) {
        buffer_ptr = std::move(otherMemory.buffer_ptr);
        capacity = otherMemory.capacity;
        otherMemory.buffer_ptr = nullptr;
    }
    return *this;
}

MemoryHandler::~MemoryHandler() {
    Deallocate(buffer_ptr);
}

char* MemoryHandler::operator+(size_t offset) noexcept {
    return buffer_ptr + offset;
}
const char* MemoryHandler::operator+(size_t offset) const noexcept {
    return buffer_ptr + offset;
}
char& MemoryHandler::operator[](size_t index) noexcept {
    assert(index < capacity);
    return buffer_ptr[index];
}
const char& MemoryHandler::operator[](size_t index) const noexcept {
    assert(index < capacity);
    return buffer_ptr[index];
}

void MemoryHandler::Swap(MemoryHandler& other) {
    std::swap(buffer_ptr, other.buffer_ptr);
    std::swap(capacity, other.capacity);
}

char* MemoryHandler::GetAddress() noexcept {
    return buffer_ptr;
}
const char* MemoryHandler::GetAddress() const noexcept {
    return buffer_ptr;
}

size_t MemoryHandler::GetCapacity() {
    return capacity;
}

char* MemoryHandler::Allocate(size_t n) {
    return (n != 0) ? static_cast<char*>(operator new (n * sizeof(char))) : nullptr;
}

void MemoryHandler::Deallocate(char* ptr) {
    operator delete(ptr);
}