#pragma once

#include "SFML/Graphics.hpp"

namespace CustomPhysics
{
	template <typename T>
	class Vector2
	{
	public:
		Vector2();
		Vector2(T x, T y);
		template <typename U>
		explicit Vector2(const Vector2<U>& vector);
		T X, Y;

		sf::Vector2<T> static ToSFMLVector(Vector2<T> vector);
		Vector2<T> static ToOwnVector(sf::Vector2<T> vector);
	};

	typedef Vector2<float>  Vector2f;
	typedef Vector2<int>  Vector2i;

	template <typename T>
	inline Vector2<T>::Vector2() : X(0), Y(0)
	{
	}

	template <typename T>
	inline Vector2<T>::Vector2(T x, T y) : X(x), Y(y)
	{
	}

	template <typename T>
	template <typename U>
	inline Vector2<T>::Vector2(const Vector2<U>& vector) :
		X(static_cast<T>(vector.X)),
		Y(static_cast<T>(vector.Y))
	{
	}

	template <typename T>
	inline Vector2<T> Vector2<T>::ToOwnVector(sf::Vector2<T> vector)
	{
		return Vector2<T>(vector.x, vector.y);
	}

	template <typename T>
	inline sf::Vector2<T> Vector2<T>::ToSFMLVector(Vector2<T> vector)
	{
		return sf::Vector2f(vector.X, vector.Y);
	}

	template <typename T>
	inline Vector2<T>& operator +=(Vector2<T>& left, const Vector2<T>& right)
	{
		left.X += right.X;
		left.Y += right.Y;
		return left;
	}
};