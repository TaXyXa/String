#pragma once

class MemoryHandler {
public:
    MemoryHandler() = default;

    MemoryHandler(const MemoryHandler& otherMemory) = delete;
    MemoryHandler& operator=(const MemoryHandler& otherMemory) = delete;

    MemoryHandler(MemoryHandler&& otherMemory) noexcept;
    MemoryHandler& operator=(MemoryHandler&& otherMemory) noexcept;

    explicit MemoryHandler(size_t size)
    : capacity_(size),
    buffer_ptr_(Allocate(size))
    {}

    ~MemoryHandler();

    char* operator+(size_t offset) noexcept;
    const char* operator+(size_t offset) const noexcept;
    char& operator[](size_t index) noexcept;
    const char& operator[](size_t index) const noexcept;

    void Swap(MemoryHandler& other) noexcept;

    char* GetAddress() noexcept;
    const char* GetAddress() const noexcept;

    size_t GetCapacity() noexcept;

private:
    char* buffer_ptr_ = nullptr;
    size_t capacity_ = 0;

    char* Allocate(size_t n);
    void Deallocate(char* ptr);

};