#pragma once
#include "DLLExport.h"

template <class T>
class DLL Vector4
{
public:
	Vector4();
	Vector4(T x, T y, T z, T w);

	// Addition Operators
	Vector4<T> operator+ (const Vector4<T>& rhs);
	void operator+= (const Vector4<T>& rhs);

	// Subtraction Operators
	Vector4<T> operator- (const Vector4<T>& rhs);
	void operator-= (const Vector4<T>& rhs);

	// Multiplication Operators
	Vector4<T> operator* (const T rhs);
	void operator*= (const T rhs);
	friend Vector4<T> operator* (T scalar, Vector4<T>& vector) { return vector * scalar; };

	// Subscript operator
	T operator[] (int index) const;
	T& operator[] (int index);

	// T cast returns Magnitude
	operator T();

	// T pointer cast returns union array
	operator T*();

	// Returns cross product of this
	// vector with the argument vector
	Vector4<T> cross(Vector4<T>& v);

	// Returns dot product of this
	// vector with argument vector
	T dot(Vector4<T>& v);

	// Returns magnitude of this vector
	T magnitude();

	// Normalises this vector
	void normalise();

	// Returns normalised copy of this vector
	Vector4<T> normalised();

private:
	// Union allowing for multiple variables of
	// the same size to share the same space in
	// memory so they all contain the same data
	// and that data can be accessed interchangeably
	union
	{
		struct { T x, y, z, w; };
		struct { T data[4]; };
	};
};