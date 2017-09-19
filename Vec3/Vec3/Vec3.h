#pragma once
template <class T>
class Vec3 {
public:
	void print();
	inline void setCoords(T x, T y, T z);
	Vec3 operator + (const Vec3 arg);
	//Vec3 operator - (const Vec3 arg);
	//Vec3& operator += (const Vec3 arg);
	//Vec3& operator -= (const Vec3 arg);
	//Vec3& operator = (const Vec3 arg);
	//bool operator == (const Vec3 arg);

private:
	T x, y, z;

};

#include "Vec3.h"
#include <stdio.h>


template<class T>
void Vec3<T>::print()
{
	printf("(%d,%d,%d)", x, y, z);
}

template<class T>
inline void Vec3<T>::setCoords(T x, T y, T z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

template<class T>
Vec3<T> Vec3<T>::operator+(const Vec3 arg)
{
	Vec3 result = {
		x + arg.x,
		y + arg.y,
		z + arg.z,
	}
}


