#pragma once
#include "Vector2.h"

template <class T>
class DLL Matrix2
{
public:
	Matrix2();
	Matrix2(T Xx, T Xy,
			T Yx, T Yy);

	// Addition Operators
	Matrix2<T> operator+ (const Matrix2<T>& rhs);
	void operator+= (const Matrix2<T>& rhs);

	// Subtraction Operators
	Matrix2<T> operator- (const Matrix2<T>& rhs);
	void operator-= (const Matrix2<T>& rhs);

	// Multiplication Operators
	Vector2<T> operator* (const Vector2<T>& rhs);
	Matrix2<T> operator* (const Matrix2<T>& rhs);
	void operator*= (const Matrix2<T>& rhs);
	Matrix2<T> operator* (const T rhs);
	void operator*= (const T rhs);

	// Subscript Operator
	Vector2<T> operator[] (int index) const;
	Vector2<T>& operator[] (int index);

	// T pointer cast operator
	operator T*();

	// Makes the current matrix
	// a rotation matrix based
	// off the identity matrix
	void setRotate(float angle);

private:
	// Union allowing for multiple variables of
	// the same size to share the same space in
	// memory so they all contain the same data
	// and that data can be accessed interchangeably
	union
	{
		struct {
			T Xx, Xy,
			  Yx, Yy;
		};
		struct { T dd[2][2]; };
		struct { T data[4]; };
		struct { Vector2<T> v[2]; };
	};
};