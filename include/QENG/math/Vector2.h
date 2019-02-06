
#ifndef QUESTIAENGINE_VECTOR2_H
#define QUESTIAENGINE_VECTOR2_H

namespace qe
{

    template<class T>
    struct Vector2
    {
        Vector2() noexcept;
        Vector2(T x, T y) noexcept;
        ~Vector2() noexcept = default;

		Vector2(Vector2&&) noexcept = default;
		Vector2(const Vector2&) noexcept = default;
		template<class U> Vector2(const Vector2<U>& pos) noexcept;
		Vector2& operator=(Vector2&&) noexcept = default;
		Vector2& operator=(const Vector2&) noexcept = default;
		template<class U> Vector2<T>& operator=(const Vector2<U>& rhs) noexcept;

		double getMagnitude() const noexcept;
		float getMagnitudef() const noexcept;
		Vector2<T> normalize() const noexcept;
		template<class U> Vector2<U> normalize() const noexcept;
		Vector2<T> safeNormalize() const noexcept;
		template<class U> Vector2<U> safeNormalize() const noexcept;
		Vector2 scale(T scaleFactor) const noexcept;

        //operators
        bool operator==(const Vector2& rhs);
        bool operator!=(const Vector2& rhs);
        Vector2 operator+(const Vector2& rhs) const;
        Vector2 operator-(const Vector2& rhs) const;
        Vector2 operator*(const T& rhs) const;
        Vector2 operator/(const T& rhs) const;
        Vector2& operator+=(const Vector2& rhs);
        Vector2& operator-=(const Vector2& rhs);
        Vector2& operator*=(const T& rhs);
        Vector2& operator/=(const T& rhs);
        T x, y;
    };

//common typedefs
    typedef Vector2<int> Vector2i;
    typedef Vector2<unsigned int> Vector2ui;
    typedef Vector2<float> Vector2f;
    typedef Vector2<double> Vector2d;
}

//include template implementations
#include "Vector2.tpp"

#endif //QUESTIAENGINE_VECTOR2_H
