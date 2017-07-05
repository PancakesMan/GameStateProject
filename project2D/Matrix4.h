#pragma once
#include "Vector4.h"

template <class T>
class DLL Matrix4
{
public:
	Matrix4();
	Matrix4(T Xx, T Xy, T Xz, T Xw,
			T Yx, T Yy, T Yz, T Yw,
			T Zx, T Zy, T Zz, T Zw,
			T Wx, T Wy, T Wz, T Ww);

	// Addition Operators
	Matrix4<T> operator+ (const Matrix4<T>& rhs);
	void operator+= (const Matrix4<T>& rhs);

	// Subtraction Operators
	Matrix4<T> operator- (const Matrix4<T>& rhs);
	void operator-= (const Matrix4<T>& rhs);


	Vector4<T> operator* (const Vector4<T>& rhs);
	Matrix4<T> operator* (const Matrix4<T>& rhs);
	void operator*= (const Matrix4<T>& rhs);
	Matrix4<T> operator* (const T rhs);
	void operator*= (const T rhs);

	// Subscript operator
	Vector4<T> operator[] (int index) const;
	Vector4<T>& operator[] (int index);

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
			T Xx, Xy, Xz, Xw,
			  Yx, Yy, Yz, Yw,
			  Zx, Zy, Zz, Zw,
			  Wx, Wy, Wz, Ww;
		};
		struct { T dd[4][4]; };
		struct { T data[16]; };
		struct { Vector4<T> v[4]; };
	};
};