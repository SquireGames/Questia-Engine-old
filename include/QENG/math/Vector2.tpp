#include <cmath>
#include <string>

namespace qe
{
	template<class T>
	inline Vector2<T>::Vector2() noexcept:
			x(0), y(0)
	{
	}

	template<class T>
	inline Vector2<T>::Vector2(T x, T y) noexcept:
			x(x), y(y)
	{
	}

	template<class T>
	template<class U>
	inline Vector2<T>::Vector2(const Vector2<U> &pos) noexcept:
			x(static_cast<T>(pos.x)), y(static_cast<T>(pos.y))
	{
	}

	template<class T>
	template<class U>
	Vector2<T> &Vector2<T>::operator=(const Vector2<U> &rhs) noexcept
	{
		x = static_cast<T>(rhs.x);
		y = static_cast<T>(rhs.y);
		return *this;
	}

	template<class T>
	double Vector2<T>::getMagnitude() const noexcept
	{
		return std::sqrt(x * x + y * y);
	}

	template<class T>
	float Vector2<T>::getMagnitudef() const noexcept
	{
		return std::sqrtf(x * x + y * y);
	}

	template<class T>
	template<class U>
	Vector2<U> Vector2<T>::normalize() const noexcept
	{
		U newX, newY;
		double length = getMagnitude();
		newX = static_cast<U>(static_cast<double>(x) / length);
		newY = static_cast<U>(static_cast<double>(y) / length);
		return {newX, newY};
	}

	template<class T>
	Vector2<T> Vector2<T>::normalize() const noexcept
	{
		T newX, newY;
		double length = getMagnitude();
		newX = static_cast<T>(static_cast<double>(x) / length);
		newY = static_cast<T>(static_cast<double>(y) / length);
		return {newX, newY};
	}

	template<class T>
	template<class U>
	Vector2<U> Vector2<T>::safeNormalize() const noexcept
	{
		U newX, newY;
		double length = getMagnitude();
		if (length > 0)
		{
			newX = static_cast<U>(static_cast<U>(x) / length);
			newY = static_cast<U>(static_cast<U>(y) / length);
			return {newX, newY};
		}
		return {0, 0};
	}

	template<class T>
	Vector2<T> Vector2<T>::scale(T scaleFactor) const noexcept
	{
		T newX, newY;
		newX *= scaleFactor;
		newY *= scaleFactor;
		return {newX, newY};
	}

	template<class T>
	bool Vector2<T>::operator==(const Vector2<T> &rhs)
	{
		const float epsilon = 0.0001;
		return (fabs(x - rhs.x) < epsilon) && (fabs(y - rhs.y) < epsilon);
	}

	template<class T>
	bool Vector2<T>::operator!=(const Vector2<T> &rhs)
	{
		return (x != rhs.x) || (y != rhs.y);;
	}

	template<class T>
	Vector2<T> Vector2<T>::operator+(const Vector2 <T> &rhs) const
	{
		return Vector2<T>(x + rhs.x, y + rhs.y);
	}

	template<class T>
	Vector2<T> Vector2<T>::operator-(const Vector2 <T> &rhs) const
	{
		return Vector2<T>(x - rhs.x, y - rhs.y);
	}

	template<class T>
	Vector2<T> Vector2<T>::operator*(const T &rhs) const
	{
		return Vector2<T>(x * rhs, y * rhs);
	}

	template<class T>
	Vector2<T> Vector2<T>::operator/(const T &rhs) const
	{
		return Vector2<T>(x / rhs, y / rhs);
	}

	template<class T>
	Vector2<T> &Vector2<T>::operator+=(const Vector2<T> &rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	template<class T>
	Vector2<T> &Vector2<T>::operator-=(const Vector2<T> &rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	template<class T>
	Vector2<T> &Vector2<T>::operator*=(const T &rhs)
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}

	template<class T>
	Vector2<T> &Vector2<T>::operator/=(const T &rhs)
	{
		x /= rhs;
		y /= rhs;
		return *this;
	}

}