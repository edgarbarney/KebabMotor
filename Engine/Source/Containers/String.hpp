// FranticDreamer 2022
// BaseString Container

#pragma once

#include <iosfwd>
#include <cstddef>

#include "Shared/Platform.hpp"

namespace MyEngine
{
	using Character = char; // Default character is char

	// A Generic Null-Terminated Base Class for Strings
	template <class _T>
	class BaseString
	{
	private:
		size_t baseArraySize; // Character count, not including null terminator
		_T* baseCharArray;

	public:
		BaseString();
		BaseString(const _T* _str);
		BaseString(const BaseString<_T>& _otherStr);
		BaseString(BaseString<_T>&& _otherStr) noexcept;
		~BaseString();

		// ==========
		// Operators
		// ==========

		_T operator[](size_t _index) const; // Will return null terminator if size exceeds

		void operator=(const BaseString<_T>& _other);

		bool operator==(const BaseString<_T>& _other) const;
		bool operator!=(const BaseString<_T>& _other) const;

		BaseString<_T> operator+ (const BaseString<_T>& _other) const;
		BaseString<_T>& operator+=(const BaseString<_T>& _other);

		// ==========
		// Iterators
		// ==========

		_T* begin() { return &baseCharArray[0]; }
		const _T* begin() const { return &baseCharArray[0]; }
		_T* end() { return &baseCharArray[baseArraySize]; }
		const _T* end() const { return &baseCharArray[baseArraySize]; }

		// ==========
		// Functions
		// ==========

		// Clear the String. Will reset length to 0.
		void Clear();

		// Get base array data. For default String, will return c-style string.
		const _T* CharacterArray() const;

		size_t Length() const;

		// Put another string at the end of the String
		void Append(const BaseString<_T>& _strToAppend);
		// Put a character at the end of the String
		void Append(const _T& _charToAppend);

		// Insert another String into an index
		// Will put at the end if position is greater than max
		void Insert(const BaseString<_T>& _strToInsert, size_t _position);
		// Insert a character into an index
		// Will put at the end if position is greater than max
		void Insert(const _T& _charToInsert, size_t _position);

		// Remove an element at the end of the Vector
		void Pop() { PopIndex(baseArraySize - 1); };

		// Remove an element of the Vector
		void PopIndex(size_t _index);

		// Find element. Returns SIZE_MAX if not found
		size_t Find(const _T& _objToFind);

	};

	// ==========
	// External Operators
	// ==========

	template <class _T>
	const bool operator==(const BaseString<_T>& _a, const BaseString<_T>& _b)
	{
		return (_a == _b);
	}

	//template <class _T>
	//const BaseString<_T> operator+(const BaseString<_T>& _a, const BaseString<_T>& _b)
	//{
	//	return (_a + _b);
	//}
	//
	//template <class _T>
	//BaseString<_T> operator+=(BaseString<_T>& _a, BaseString<_T>& _b)
	//{
	//	return (_a += _b);
	//}

	// ==========
	// External Iterators	
	// ==========

	template <class _T>
	_T* begin(BaseString<_T>& container) { return &container.begin(); };

	template <class _T>
	const _T* begin(const BaseString<_T>& container) { return &container.begin(); };

	template <class _T>
	_T* end(BaseString<_T>& container) { return &container.end(); };

	template <class _T>
	const _T* end(const BaseString<_T>& container) { return &container.end(); };
	
	// Only String (BaseString<Character>) is exported.

#ifdef _MYENGINE_ENGINE
	extern template class BaseString<Character>; // No need for individual instantiation on other objects
#else
	template class ENG_DLLEXP BaseString<Character>; // Import if not engine
#endif

	using String = BaseString<Character>;
};