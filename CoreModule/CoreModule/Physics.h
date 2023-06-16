#pragma once

#include "Vector2.h"

namespace CustomPhysics
{
	template <typename T>
	class Physics
	{
	public:
		bool static circleCollision(float first, Vector2f firstPosition, float second, Vector2f secondPosition);
		double static distance(CustomPhysics::Vector2f first, CustomPhysics::Vector2f second);

		T static Clamp(T& value, T min, T max);

		T static Min(T a, T b);
		T static Max(T a, T b);
	};

	template <typename T>
	inline T Physics<T>::Min(T a, T b)
	{
		return a < b ? a : b;
	}

	template <typename T>
	inline T Physics<T>::Max(T a, T b)
	{
		return a > b ? a : b;
	}

	template <typename T>
	inline T Physics<T>::Clamp(T& value, T min, T max)
	{
		if (value >= max)
		{
			value = max;
		}
		if (value < min)
		{
			value = min;
		}
		return value;
	}

	template <typename T>
	inline double Physics<T>::distance(Vector2f first, Vector2f second)
	{
		double dy = (first.Y - second.Y);
		double dx = (first.X - second.X);
		double distance = sqrt(pow(dy, 2) + pow(dx, 2));
		return distance;
	}

	template <typename T>
	inline bool Physics<T>::circleCollision(float first, Vector2f firstPosition, float second, Vector2f secondPosition)
	{
		double dis = distance(firstPosition, secondPosition);
		return dis <= (first + second);
	}
}

