// FranticDreamer 2022
// String Container

#include <algorithm>

#include "String.hpp"
#include <iostream>

namespace KebabMotor
{
	template<class _T>
	BaseString<_T>::BaseString() :
		baseArraySize(0)
	{
		baseCharArray = new _T[1];
		baseCharArray[0] = '\0';
	}

	template<class _T>
	BaseString<_T>::BaseString(const _T* _str) :
		baseArraySize(std::strlen(_str))
	{
		baseCharArray = new _T[baseArraySize + 1];

		std::copy_n(_str, baseArraySize, baseCharArray);
		baseCharArray[baseArraySize] = '\0';
	}

	template<class _T>
	BaseString<_T>::BaseString(const BaseString<_T>& _otherStr) :
		baseArraySize(_otherStr.baseArraySize)
	{
		baseCharArray = new _T[baseArraySize + 1];

		std::copy_n(_otherStr.baseCharArray, baseArraySize, baseCharArray);
		baseCharArray[baseArraySize] = '\0';
	}

	template<class _T>
	BaseString<_T>::BaseString(BaseString<_T>&& _otherStr) noexcept
		: BaseString()
	{
		//_otherStr.baseArraySize = 0;
		//_otherStr.baseCharArray = new _T[1];
		//_otherStr.baseCharArray[baseArraySize] = '\0';

		std::swap(baseArraySize, _otherStr.baseArraySize);
		std::swap(baseCharArray, _otherStr.baseCharArray);
	}

	template<class _T>
	BaseString<_T>::~BaseString()
	{
		delete[] baseCharArray;
	}

	template<class _T>
	_T BaseString<_T>::operator[](size_t _index) const
	{
		if (_index > baseArraySize)
			return _T('\0');

		return baseCharArray[_index];
	}

	template<class _T>
	void BaseString<_T>::operator=(const BaseString<_T>& _other)
	{
		baseCharArray = new _T[baseArraySize + 1];

		std::copy_n(_other.baseCharArray, baseArraySize, baseCharArray);
		baseCharArray[baseArraySize] = '\0';
	}

	template<class _T>
	bool BaseString<_T>::operator==(const BaseString<_T>& _other) const
	{
		return std::equal(begin(), end(), _other.begin(), _other.end());
	}

	template<class _T>
	bool BaseString<_T>::operator!=(const BaseString<_T>& _other) const
	{
		return !(*this == _other);
	}

	template<class _T>
	BaseString<_T> BaseString<_T>::operator+(const BaseString<_T>& _other) const
	{
		BaseString<_T> tempData(*this);
		tempData.Append(_other);
		return tempData;
	}

	template<class _T>
	BaseString<_T>& BaseString<_T>::operator+=(const BaseString<_T>& _other)
	{
		this->Append(_other);
		return *this;
	}

	template<class _T>
	void BaseString<_T>::Clear()
	{
		delete[] baseCharArray;

		baseArraySize = 0;

		baseCharArray = new _T[1];
		baseCharArray[0] = '\0';
	}

	template<class _T>
	const _T* BaseString<_T>::CharacterArray() const
	{
		return baseCharArray;
	}

	template<class _T>
	size_t BaseString<_T>::Length() const
	{
		return baseArraySize;
	}

	template<class _T>
	void BaseString<_T>::Append(const BaseString<_T>& _strToAppend)
	{
		Insert(_strToAppend, Length());
	}

	template<class _T>
	void BaseString<_T>::Append(const _T& _charToAppend)
	{
		Insert(_charToAppend, Length());
	}

	template<class _T>
	void BaseString<_T>::Insert(const BaseString<_T>& _strToInsert, size_t _position)
	{
		if (_position > baseArraySize)
			_position = baseArraySize;

		_T* tempArray = new _T[baseArraySize + _strToInsert.baseArraySize + 1]();

		// Copy data into the new array
		for (size_t i = 0; i < baseArraySize + _strToInsert.baseArraySize + 1; ++i)
			if (i >= _position && i >= (_position + _strToInsert.baseArraySize))
				tempArray[i] = baseCharArray[i - _strToInsert.baseArraySize]; // Old string, After Position
			else if (i >= _position)
				tempArray[i] = _strToInsert.baseCharArray[i - _position]; // String to insert
			else
				tempArray[i] = baseCharArray[i]; // Old string, before position

		baseArraySize = baseArraySize + _strToInsert.baseArraySize; // New array size

		// Remove old data
		delete[] baseCharArray;

		baseCharArray = tempArray;
	}

	template<class _T>
	void BaseString<_T>::Insert(const _T& _charToInsert, size_t _position)
	{
		if (_position > baseArraySize)
			_position = baseArraySize;

		_T* tempArray = new _T[baseArraySize + 2]();
		
		// Copy old data into the new array
		for (size_t i = 0; i < baseArraySize + 1; ++i)
			if (i >= _position)
				tempArray[i + 1] = baseCharArray[i];
			else
				tempArray[i] = baseCharArray[i];

		// Add the last object, then increment base array size
		tempArray[_position] = _charToInsert;
		baseArraySize++;

		// Remove old data
		delete[] baseCharArray;

		baseCharArray = tempArray;
	}

	template<class _T>
	void BaseString<_T>::PopIndex(size_t _index)
	{
		if (baseArraySize < 1 || _index >= baseArraySize)
			return; //throw std::out_of_range("PopIndex: Out Of Range!!");

		_T* tempArray = new _T[baseArraySize - 1];

		// Copy old data into the new array
		for (size_t i = 0; i < baseArraySize - 1; ++i)
			if (i >= _index)
				tempArray[i] = baseCharArray[i + 1];
			else
				tempArray[i] = baseCharArray[i];

		// Remove old data
		delete[] baseCharArray;

		// Decrement array size
		baseArraySize--;

		baseCharArray = tempArray;
	}

	template<class _T>
	size_t BaseString<_T>::Find(const _T& _objToFind)
	{
		for (size_t i = 0; i < baseArraySize; ++i)
		{
			if (baseCharArray[i] == _objToFind)
				return i;
		}
		return SIZE_MAX;
	}

	template class ENG_DLLEXP BaseString<Character>;
};