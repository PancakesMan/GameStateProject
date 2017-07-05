#pragma once
#include "DLLExport.h"

template <class T>
class DLL Vector3
{
public:
	Vector3();
	Vector3(T x, T y, T z);

	// Addition Operators
	Vector3<T> operator+ (const Vector3<T>& rhs);
	void operator+= (const Vector3<T>& rhs);

	// Subtraction Operators
	Vector3<T> operator- (const Vector3<T>& rhs);
	void operator-= (const Vector3<T>& rhs);

	// Multiplication Operators
	Vector3<T> operator* (const T rhs);
	void operator*= (const T rhs);
	friend Vector3<T> operator* (T scalar, Vector3<T>& vector) { return vector * scalar; };

	// Subscript Operator
	T operator[] (int index) const;
	T& operator[] (int index);

	// T cast returns magnitude
	operator T();

	// T pointer cast returns union array
	operator T*();

	// Returns cross product of this
	// vector with the argument vector
	Vector3<T> cross(Vector3<T>& v);

	// Returns dot product of this
	// vector with argument vector
	T dot(Vector3<T>& v);

	// Returns magnitude of this vector
	T magnitude();

	// Normalises this vector
	void normalise();

	// Returns normalised copy of this vector
	Vector3<T> normalised();

private:
	// Union allowing for multiple variables of
	// the same size to share the same space in
	// memory so they all contain the same data
	// and that data can be accessed interchangeably
	union
	{
		struct { T x, y, z; };
		struct { T data[3]; };
	};
};