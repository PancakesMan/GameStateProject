#pragma once

template <typename T>
class Stack {
	typedef T* iterator;
	typedef const T* const_iterator;

public:
	Stack(unsigned int _capacity = 10) {
		capacity = _capacity;
		size = 0;
		data = new T[capacity];
	}
	~Stack() { delete[] data; }

	// Add item to top of stack
	void push(T item) {
		if (size == capacity) expand();
		data[size++] = item;
	}

	// Remove item from top of stack
	void pop() {
		size--;
	}

	// Get item from top of stack
	T top() {
		return data[size - 1];
	}

	void clear() {
		// Delete current array
		delete[] data;

		// Create new empty array
		data = new T[capacity];
		size = 0;
	}

	int count() {
		return size;
	}

	bool empty() {
		return size == 0;
	}

	iterator begin() { return &data[0]; }
	const_iterator begin() const { return &data[0]; }

	iterator end() { return &data[size]; }
	const_iterator end() const { return &data[size]; }

private:
	T* data;
	int size, capacity;

	// Make the internal array bigger
	void expand() {

		// Double the capacity
		unsigned int newCapacity = capacity * 2;

		// Store pointer to old aray
		T* old = data;

		// Create new array with new capacity
		T* newData = new T[newCapacity];

		// Copy data from old array into new array
		for (int i = 0; i < capacity; i++)
			newData[i] = data[i];

		// Set the internal pointer to array
		// to the new array
		data = newData;

		// Update the capacity of the array
		capacity = newCapacity;

		// Delete the old array
		delete[] old;
	}
};