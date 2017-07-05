#pragma once
#include <assert.h>

template <typename T>
class DynamicArray
{
	typedef T* iterator;
	typedef const T* const_iterator;

public:
	DynamicArray(unsigned int _capacity = 10)
	{
		size = 0;
		capacity = _capacity;
		data = new T[capacity];
	}

	DynamicArray(const DynamicArray<T>& copy)
	{
		data = new T[copy.capacity];
		size = copy.size;

		for (unsigned int i = 0; i < copy.size; i++)
			data[i] = copy.data[i];
	}

	void operator= (const DynamicArray<T>& copy)
	{
		delete data;
		data = new T[copy.capacity];
		size = copy.size;

		for (int i = 0; i < copy.size; i++)
			data[i] = copy.data[i];
	}

	~DynamicArray()
	{
		delete[] data;
	}
	
	// Add to end of array
	void AddToEnd(T value)
	{
		if (size == capacity)
			expand();
		data[size++] = value;
	}
	
	// Remove last element of array
	void RemoveFromEnd()
	{
		size--;
	}

	T& operator[] (unsigned int index)
	{
		assert(index < size && "Index Out Of Range");
		return data[index];
	}

	void Remove(int index)
	{
		size--;
		for (unsigned int i = index; i < size; i++)
			data[i] = data[i + 1];

	}

	void Clear()
	{
		size = 0;
	}

	iterator begin() { return &data[0]; }
	const_iterator begin() const { return &data[0]; }

	iterator end() { return &data[size]; }
	const_iterator end() const { return &data[size]; }

	int Size() { return size; }

	T back() { return data[size - 1]; }

private:
	T* data;
	unsigned int size, capacity;
	
	void expand()
	{
		unsigned int newCapacity = capacity * 2;
		T* old = data;
		T* newData = new T[newCapacity];
		
		//memset(newData, 0, newCapacity * sizeof(T));
		//memcpy(newData, old, sizeof(T) * capacity);

		for (int i = 0; i < capacity; i++)
			newData[i] = old[i];
		
		data = newData;
		capacity = newCapacity;
  		delete[] old;		
	}
};