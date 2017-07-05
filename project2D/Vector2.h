#pragma once
#include "DLLExport.h"

template <class T>
class DLL Vector2
{
public:
	Vector2();
	Vector2(T x, T y);

	// Addition Operators
	Vector2<T> operator+ (const Vector2<T>& rhs);
	void operator+= (const Vector2<T>& rhs);

	// Subtraction Operators
	Vector2<T> operator- (const Vector2<T>& rhs);
	void operator-= (const Vector2<T>& rhs);

	// Multiplication Operators
	Vector2<T> operator* (const T rhs);
	void operator*= (const T rhs);
	friend Vector2<T> operator* (T scalar, Vector2<T>& vector) { return vector * scalar; };

	// Subscript operator
	T operator[] (int index) const;
	T& operator[] (int index);

	// T cast returns magnitude
	operator T();

	// T pointer cast returns union array
	operator T*();

	// Returns dot product of this
	// vector with argument vector
	T dot(Vector2<T>& v);

	// Returns magnitude of this vector
	T magnitude();

	// Normalises this vector
	void normalise();

	// Returns a normalised copy of this vector
	Vector2<T> normalised();

private:
	// Union allowing for multiple variables of
	// the same size to share the same space in
	// memory so they all contain the same data
	// and that data can be accessed interchangeably
	union
	{
		struct { T x, y; };
		struct { T data[2]; };
	};
};