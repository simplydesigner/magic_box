#pragma once 
#include <iostream>
#include <stdexcept>
#include <vector>

#ifndef STACK_HPP
#define STACK_HPP

using std::size_t;
using std::ostream;

template<typename T>
auto copy(const T * rhs, size_t sizeLeft, size_t sizeRight) -> T *; /*strong*/
template <typename T1, typename T2>
auto construct(T1 * ptr, T2 const & value) -> void;
template <typename T>
auto destroy(T * ptr) noexcept -> void;
template <typename FwdIter>
auto destroy(FwdIter first, FwdIter last) noexcept -> void;

class dynamic_bitset {
public:
	explicit dynamic_bitset(size_t size = 0) noexcept; /*noexcept*/

	auto all() const noexcept -> bool; /*noexcept*/
	auto any() noexcept -> bool; /*noexcept*/
	auto count() const noexcept -> size_t; /*noexcept*/
	auto flip() noexcept -> void; /*noexcept*/
	auto flip(size_t pos) throw(std::out_of_range) -> void; /*strong*/
	auto none() const noexcept -> bool; /*noexcept*/
	auto resize() noexcept -> void; /*noexcept*/
	auto reset() noexcept -> void; /*noexcept*/
	auto reset(size_t pos) throw(std::out_of_range) -> void; /*strong*/
	auto set() noexcept -> void; /*noexcept*/
	auto set(size_t pos) throw(std::out_of_range) -> void; /*strong*/
	auto size() const noexcept -> size_t; /*noexcept*/
	auto test(size_t pos) const throw(std::out_of_range) -> bool; /*strong*/

	auto operator[](size_t pos) throw(std::out_of_range) -> bool; /*strong*/
private:
	std::vector<bool> bits;
};

template <typename T>
class allocator {
public:
	explicit allocator(size_t size = 0); /*strong*/
	allocator(allocator const & other); /*strong*/
	auto operator=(allocator const & other) -> allocator & = delete;
	~allocator(); /*strong*/

	auto construct(T * ptr, T const & value) -> void; /*strong*/
	auto count() const -> size_t; /*noxecept*/
	auto destroy(T * ptr) -> void;
	auto empty() const -> bool; /*noexecpt*/
	auto full() const -> bool; /*noexecpt*/
	auto get() -> T *;
	auto get() const -> T const *;
	auto resize() -> void;
	auto swap(allocator & other) -> void;
private:
	T * ptr_;
	size_t size_;
	size_t count_;
	dynamic_bitset bitset_;

	template <typename FwdIter>
	auto destroy(FwdIter first, FwdIter last) noexcept -> void;
};

template<typename T>
class stack {
public:
	explicit stack(size_t size = 0); /*noexcept*/
	stack(stack const & rhs); /*strong*/
	~stack(); /*noexcept*/

	auto count() const noexcept->size_t; /*noexcept*/
	auto empty() const noexcept -> bool; /*noexcept*/
	auto top() const -> const T&; /*strong*/
	auto pop() -> void; /*strong*/
	auto push(T const & value) -> void; /*strong*/

	auto print() -> void;

	auto operator=(stack const & rhs) -> stack &; /*strong*/
	auto operator==(stack const & rhs) -> bool; /*noexcept*/
private:
	allocator<T> alloc;
};

#include "stack.cpp"

#endif
