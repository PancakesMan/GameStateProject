#pragma once
#include "Vector3.h"

template <class T>
class DLL Matrix3
{
public:
	Matrix3();
	Matrix3(T Xx, T Xy, T Xz,
			T Yx, T Yy, T Yz,
			T Zx, T Zy, T Zz);

	// Addition Operators
	Matrix3<T> operator+ (const Matrix3<T>& rhs);
	void operator+= (const Matrix3<T>& rhs);

	// Subtraction Operators
	Matrix3<T> operator- (const Matrix3<T>& rhs);
	void operator-= (const Matrix3<T>& rhs);

	// Multiplication Operators
	Vector3<T> operator* (const Vector3<T>& rhs);
	Matrix3<T> operator* (const Matrix3<T>& rhs);
	void operator*= (const Matrix3<T>& rhs);
	Matrix3<T> operator* (const T rhs);
	void operator*= (const T rhs);

	// Subscript operator
	Vector3<T> operator[] (int index) const;
	Vector3<T>& operator[] (int index);

	// T pointer cast operator
	operator T*();

	// Makes the current matrix
	// a rotation matrix based
	// off the identity matrix
	void setRotateX(float angle);
	void setRotateY(float angle);
	void setRotateZ(float angle);

private:
	// Union allowing for multiple variables of
	// the same size to share the same space in
	// memory so they all contain the same data
	// and that data can be accessed interchangeably
	union
	{
		struct { 
			T Xx, Xy, Xz,
			  Yx, Yy, Yz,
			  Zx, Zy, Zz;
		};
		struct { T dd[3][3]; };
		struct { T data[9]; };
		struct { Vector3<T> v[3]; };
	};
};