#pragma once
template <class T>
class Vec3 {
public:
	Vec3();
	Vec3(T x, T y, T z);

	void print();
	void setCoords(T x, T y, T z);

	void zero();
	bool is_zero();
	void normalise();

	Vec3 operator + (const Vec3 arg);
	Vec3 operator - (const Vec3 arg);
	Vec3& operator += (const Vec3 arg);
	Vec3& operator -= (const Vec3 arg);
	void operator = (const Vec3 arg);
	bool operator == (const Vec3 arg);

private:
	T x, y, z;

};

template<class T>
inline Vec3<T>::Vec3()
{
	x = y = z = 0;
}

template<class T>
inline Vec3<T>::Vec3(T x, T y, T z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

template<class T>
void Vec3<T>::print()
{
	printf("(%d,%d,%d)", x, y, z);
}

template<class T>
void Vec3<T>::setCoords(T x, T y, T z)
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
		z + arg.z
	};

	return result;
}

template<class T>
 Vec3<T> Vec3<T>::operator-(const Vec3 arg)
{
	 Vec3 result = {
		 x - arg.x,
		 y - arg.y,
		 z - arg.z
	 };

	 return result;
}

 template<class T>
Vec3<T> & Vec3<T>::operator+=(const Vec3 arg)
 {
	 x += arg.x;
	 y += arg.y;
	 z += arg.z;
	 return *this;
 }

template<class T>
Vec3<T> & Vec3<T>::operator-=(const Vec3 arg)
{
	x -= arg.x;
	y -= arg.y;
	z -= arg.z;
	return *this;
}

template<class T>
bool Vec3<T>::operator==(const Vec3 arg)
{
	if (x == arg.x&&y == arg.y&&z == arg.z) {
		return true;
	}
	return false;
}

template<class T>
void Vec3<T>::operator=(const Vec3 arg)
{
	x = arg.x;
	y = arg.y;
	z = arg.z; 
}

template<class T>
void Vec3<T>::zero()
{
	x = y = z = 0;
}

template<class T>
bool Vec3<T>::is_zero()
{
	if (x == 0&&y == 0&&z == 0) {
		return true;
	}
	return false;
}

template<class T>
void Vec3<T>::normalise()
{
	T module = sqrt((x * x) + (y * y) + (z * z));

	if (magnitude != 0)
	{
		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
	}
}
