// FranticDreamer 2022
// List Container

#pragma once

#include "Shared/Platform.hpp"

namespace MyEngine
{
	// A Generic "Dynamic Array" container, similar to std::vector
	template <class _T>
	class /*ENG_DLLEXP*/ List
	{
	private:
		_T* baseArrayData;
		size_t baseArraySize;

	public:
		List();
		List(const List& _other);
		~List();

		// ==========
		// Operators
		// ==========

		_T& operator[](size_t _index); //const;

		void operator=(const List<_T>& _other);

		bool operator==(const List<_T>& _other);

		// ==========
		// Iterators
		// ==========

		_T* begin() { return &baseArrayData[0]; }
		const _T* begin() const { return &baseArrayData[0]; }
		_T* end() { return &baseArrayData[baseArraySize]; }
		const _T* end() const { return &baseArrayData[baseArraySize]; }

		// ==========
		// Functions
		// ==========

		// Size of the vector AKA. Number of elements.
		_T* Data();

		// Add an element at the end of the Vector
		void Append(const _T& _objToAppend);

		// Add an element at a position into the Vector
		// Resize if the index is greater than size.
		void Insert(const _T& _objToInsert, size_t _position);

		// Remove an element at the end of the Vector
		void Pop() { PopIndex(baseArraySize - 1); };

		// Remove an element of the Vector
		void PopIndex(size_t _index);

		// Find element. Returns SIZE_MAX if not found
		size_t Find(const _T& _objToFind);

		// Size of the vector AKA. Number of elements.
		size_t Size();

		// Resize the Vector
		// Removes elements from the end if new size is less than current size.
		// Adds elements with default constructor if new size is greater that current size.
		void Resize(size_t _newSize);

		// Clear the Vector
		void Clear();

		bool IsEmpty() const;

		// ==========
		// STL Vector Compatibility. Not Finished yet.
		// ==========
#ifdef LIST_STL_COMP
		void push_back(const _T& _objToAppend) { Append(_objToAppend); };
		//void emplace_back(const _T& _objToAppend) { Append(_objToAppend); };

		_T& at(size_t _index) const { return operator[](_index); };
		_T& front() const { return operator[](0); };
		_T& back() const { return operator[](baseArraySize - 1); };

		bool empty() const { return IsEmpty(); };
#endif
	};

	// ==========
	// External Operators
	// ==========

	template <class _T>
	bool operator==(const List<_T>& _a, const List<_T>& _b)
	{
		return (_a == _b);
	}

	// ==========
	// External Iterators	
	// ==========

	template <class _T>
	_T* begin(List<_T>& container) { return &container.begin(); };

	template <class _T>
	const _T* begin(const List<_T>& container) { return &container.begin(); };

	template <class _T>
	_T* end(List<_T>& container) { return &container.end(); };

	template <class _T>
	const _T* end(const List<_T>& container) { return &container.end(); };

};

// =========
// Definitions
// =========

template <class _T>
MyEngine::List<_T>::List()
{
	baseArraySize = 0;
	baseArrayData = nullptr;
}

template <class _T>
MyEngine::List<_T>::List(const List& _other)
{
	baseArraySize = 0;

	for (size_t i = 0; i < _other.baseArraySize; ++i)
		Append(_other.baseArrayData[i]);
}

template<class _T>
MyEngine::List<_T>::~List()
{
	delete[] baseArrayData;
}

template <class _T>
_T& MyEngine::List<_T>::operator[](size_t _index)// const
{
	if (_index >= baseArraySize)
		// throw std::out_of_range("Subscript: Out Of Range!!");
	{
		Resize(_index);
	}

	return baseArrayData[_index];
}

template <class _T>
void MyEngine::List<_T>::operator=(const List<_T>& _other)
{
	Clear();

	baseArrayData = new _T[_other.baseArraySize];

	baseArraySize = _other.baseArraySize;

	// Copy other data into the current array
	for (size_t i = 0; i < baseArraySize; ++i)
		baseArrayData[i] = _other.baseArrayData[i];
}

template<class _T>
bool MyEngine::List<_T>::operator==(const List<_T>& _other)
{
	if (baseArraySize != _other.baseArraySize)
		return false;

	for (size_t i = 0; i < baseArraySize; ++i)
		if (baseArrayData[i] != _other.baseArrayData[i])
			return false;

	return true;
}

template <class _T>
_T* MyEngine::List<_T>::Data()
{
	return baseArrayData;
}

template <class _T>
void MyEngine::List<_T>::Append(const _T& _objToAppend)
{
	_T* tempArray = new _T[baseArraySize + 1]();

	// Copy old data into the new array
	for (size_t i = 0; i < baseArraySize; ++i)
		tempArray[i] = baseArrayData[i];

	// Add the last object, then increment base array size
	tempArray[baseArraySize++] = _objToAppend;

	// Remove old data
	delete[] baseArrayData;

	baseArrayData = tempArray;
}

template<class _T>
inline void MyEngine::List<_T>::Insert(const _T& _objToInsert, size_t _position)
{
	if (_position > baseArraySize)
	{
		Resize(_position + 1);
		baseArrayData[_position] = _objToInsert;
		return;
	}

	_T* tempArray = new _T[baseArraySize + 1]();

	// Copy old data into the new array
	for (size_t i = 0; i < baseArraySize + 1; ++i)
		if (i >= _position)
			tempArray[i + 1] = baseArrayData[i];
		else
			tempArray[i] = baseArrayData[i];

	// Add the last object, then increment base array size
	tempArray[_position] = _objToInsert;
	baseArraySize++;

	// Remove old data
	delete[] baseArrayData;

	baseArrayData = tempArray;
}

template <class _T>
void MyEngine::List<_T>::PopIndex(size_t _index)
{
	if (baseArraySize < 1 || _index >= baseArraySize)
		return; //throw std::out_of_range("PopIndex: Out Of Range!!");

	_T* tempArray = new _T[baseArraySize - 1];

	// Copy old data into the new array
	for (size_t i = 0; i < baseArraySize - 1; ++i)
		if (i >= _index)
			tempArray[i] = baseArrayData[i + 1];
		else
			tempArray[i] = baseArrayData[i];

	// Remove old data
	delete[] baseArrayData;

	// Decrement array size
	baseArraySize--;

	baseArrayData = tempArray;
}

template <class _T>
size_t MyEngine::List<_T>::Find(const _T& _objToFind)
{
	for (size_t i = 0; i < baseArraySize; ++i)
	{
		if (baseArrayData[i] == _objToFind)
			return i;
	}
	return SIZE_MAX;
}

template<class _T>
inline size_t MyEngine::List<_T>::Size()
{
	return baseArraySize;
}

template<class _T>
inline void MyEngine::List<_T>::Resize(size_t _newSize)
{
	_T* tempArray = new _T[_newSize]();

	// Copy old data into the new array
	for (size_t i = 0; i < std::min(_newSize, baseArraySize); ++i)
		tempArray[i] = baseArrayData[i];

	baseArraySize = _newSize;

	// Remove old data
	delete[] baseArrayData;

	baseArrayData = tempArray;
}

template <class _T>
void MyEngine::List<_T>::Clear()
{
	// Remove old data
	if (baseArrayData)
	{
		delete[] baseArrayData;
		baseArrayData = nullptr;
	}

	baseArraySize = 0;
}

template<class _T>
bool MyEngine::List<_T>::IsEmpty() const
{
	return baseArraySize == 0;
}