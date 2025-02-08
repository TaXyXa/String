#include <cassert>
#include <utility>

#include "MemoryHandler.h"

MemoryHandler::MemoryHandler( MemoryHandler&& otherMemory ) noexcept
	: buffer_ptr_( std::move( otherMemory.buffer_ptr_ ) ), capacity_( std::move( otherMemory.capacity_ ) ) {
	otherMemory.buffer_ptr_ = nullptr;
}

MemoryHandler& MemoryHandler::operator=( MemoryHandler&& otherMemory ) noexcept {
	if ( this != &otherMemory ) {
		buffer_ptr_ = std::move( otherMemory.buffer_ptr_ );
		capacity_ = otherMemory.capacity_;
		otherMemory.buffer_ptr_ = nullptr;
	}
	return *this;
}

MemoryHandler::MemoryHandler( size_t size ) : capacity_( size ), buffer_ptr_( Allocate( size ) ) {}

MemoryHandler::~MemoryHandler() {
	Deallocate( buffer_ptr_ );
}

char* MemoryHandler::operator+( size_t offset ) noexcept {
	return buffer_ptr_ + offset;
}
const char* MemoryHandler::operator+( size_t offset ) const noexcept {
	return buffer_ptr_ + offset;
}
char& MemoryHandler::operator[]( size_t index ) noexcept {
	assert( index < capacity_ );
	return buffer_ptr_[ index ];
}
const char& MemoryHandler::operator[]( size_t index ) const noexcept {
	assert( index < capacity_ );
	return buffer_ptr_[ index ];
}

void MemoryHandler::Swap( MemoryHandler& other ) noexcept {
	std::swap( buffer_ptr_, other.buffer_ptr_ );
	std::swap( capacity_, other.capacity_ );
}

char* MemoryHandler::GetAddress() noexcept {
	return buffer_ptr_;
}
const char* MemoryHandler::GetAddress() const noexcept {
	return buffer_ptr_;
}

size_t MemoryHandler::GetCapacity() noexcept {
	return capacity_;
}

char* MemoryHandler::Allocate( size_t n ) {
	return ( n != 0 ) ? static_cast<char*>( operator new( n * sizeof( char ) ) ) : nullptr;
}

void MemoryHandler::Deallocate( char* ptr ) {
	operator delete( ptr );
}