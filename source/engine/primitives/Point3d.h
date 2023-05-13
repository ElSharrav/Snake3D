#ifndef VEC3_H
#define VEC3_H

#define Vec3f Vec3<float>

template<typename T>
class Vec3
{
public:
	T x;
	T y;
	T z;
public:
	Vec3(T x = 0, T y = 0, T z = 0);
};


template<class T>
Vec3<T>::Vec3(T x, T y, T z) : x(x),y(y),z(z)
{

}

#endif
