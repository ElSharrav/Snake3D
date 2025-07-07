#ifndef VEC2_H
#define VEC2_H

#define Vec2f Vec2<float>

template<typename T>
class Vec2
{
public:
	T x;
	T y;
public:
	Vec2(T x = 0, T y = 0);
};


template<class T>
Vec2<T>::Vec2(T x, T y) : x(x),y(y)
{

}

#endif
