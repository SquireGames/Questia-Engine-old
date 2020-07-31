#ifndef QUESTIAENGINE_FIXEDVECTOR_H
#define QUESTIAENGINE_FIXEDVECTOR_H

#include <cstddef>

namespace qe
{
	template<class T, std::size_t N>
	struct FixedVector
	{
		// ctor + dtor
		constexpr FixedVector() noexcept;
		template<class ...Args> explicit constexpr FixedVector(Args ...args) noexcept;
		~FixedVector() noexcept = default;

		// copy and assignment operators
		constexpr FixedVector(FixedVector&&) noexcept = default;
		constexpr FixedVector(const FixedVector&) noexcept = default;
		constexpr FixedVector& operator=(FixedVector&&) noexcept = default;
		constexpr FixedVector& operator=(const FixedVector&) noexcept = default;

		// operators
		constexpr T& operator[](std::size_t index) noexcept;
		constexpr bool operator==(const FixedVector<T, N>& rhs) const noexcept;
		constexpr bool operator!=(const FixedVector<T, N>& rhs) const noexcept;
		constexpr FixedVector<T, N> operator+(const FixedVector<T, N>& rhs) const noexcept;
		constexpr FixedVector<T, N>& operator+=(const FixedVector<T, N>& rhs) noexcept;
		constexpr FixedVector<T, N> operator-(const FixedVector<T, N>& rhs) const noexcept;
		constexpr FixedVector<T, N>& operator-=(const FixedVector<T, N>& rhs) noexcept;
		constexpr FixedVector<T, N> operator*(T rhs) const noexcept;
		template<class T2, std::size_t N2> constexpr friend FixedVector<T2, N2> operator*(T2 lhs, const FixedVector<T2, N2>& rhs) noexcept;
		constexpr FixedVector<T, N>& operator*=(T rhs) noexcept;
		constexpr FixedVector<T, N> operator/(T rhs) const noexcept;
		constexpr FixedVector<T, N>& operator/=(T rhs) noexcept;

		// utility functions
		template<std::size_t Index> constexpr T get() const noexcept;
		template<std::size_t Index> constexpr void set(T newValue) noexcept;
		constexpr std::size_t getSize() const noexcept;
		constexpr T x() const noexcept;
		constexpr T y() const noexcept;
		constexpr T z() const noexcept;

		// value
		T values[N];
	};

	using Vector2i = FixedVector<int, 2>;
	using Vector2ui = FixedVector<unsigned int, 2>;
	using Vector2f = FixedVector<float, 2>;
	using Vector2d = FixedVector<double, 2>;

	using Vector3i = FixedVector<int, 3>;
	using Vector3ui = FixedVector<unsigned int, 3>;
	using Vector3f = FixedVector<float, 3>;
	using Vector3d = FixedVector<double, 3>;


	template <class T, std::size_t N>
	inline constexpr FixedVector<T, N>::FixedVector() noexcept : values {0}
	{
	}

	template <class T, std::size_t N>
	template <class ...Args>
	inline constexpr FixedVector<T, N>::FixedVector(Args ...args) noexcept : values {args...}
	{
		static_assert(sizeof...(Args) == N, "FixedVector size does not match number of arguments in the constructor parameters");
	}

	template <class T, std::size_t N>
	inline constexpr T& FixedVector<T, N>::operator[](std::size_t index) noexcept
	{
		return values[index];
	}

	template<class T, std::size_t N>
	inline constexpr bool FixedVector<T, N>::operator==(const FixedVector<T, N> &rhs) const noexcept
	{
		for(std::size_t i = 0; i < N; i++)
		{
			if(!(this->values[i] == rhs.values[i]))
			{
				return false;
			}
		}
		return true;
	}

	template<class T, std::size_t N>
	inline constexpr bool FixedVector<T, N>::operator!=(const FixedVector<T, N> &rhs) const noexcept
	{
		for(std::size_t i = 0; i < N; i++)
		{
			if(this->values[i] != rhs.values[i])
			{
				return true;
			}
		}
		return false;
	}

	template <class T, std::size_t N>
	template <std::size_t Index>
	inline constexpr T FixedVector<T, N>::get() const noexcept
	{
		return values[Index];
	}

	template<class T, std::size_t N>
	template<std::size_t Index>
	inline constexpr void FixedVector<T, N>::set(T newValue) noexcept
	{
		values[Index] = newValue;
	}

	template<class T, std::size_t N>
	inline constexpr FixedVector<T, N> FixedVector<T, N>::operator+(const FixedVector<T, N>& rhs) const noexcept
	{
		return FixedVector<T, N>(*this) += rhs;
	}

	template<class T, std::size_t N>
	inline constexpr FixedVector<T, N> FixedVector<T, N>::operator-(const FixedVector<T, N>& rhs) const noexcept
	{
		return FixedVector<T, N>(*this) -= rhs;
	}

	template<class T, std::size_t N>
	inline constexpr std::size_t FixedVector<T, N>::getSize() const noexcept
	{
		return N;
	}

	template<class T, std::size_t N>
	inline constexpr FixedVector<T, N>& FixedVector<T, N>::operator+=(const FixedVector<T, N>& rhs) noexcept
	{
		for(std::size_t i = 0; i < N; i++)
		{
			this->values[i] += rhs.values[i];
		}
		return *this;
	}

	template<class T, std::size_t N>
	inline constexpr FixedVector<T, N>& FixedVector<T, N>::operator-=(const FixedVector<T, N>& rhs) noexcept
	{
		for(std::size_t i = 0; i < N; i++)
		{
			this->values[i] -= rhs.values[i];
		}
		return *this;
	}

	template<class T, std::size_t N>
	inline constexpr FixedVector<T, N> FixedVector<T, N>::operator*(T rhs) const noexcept
	{
		return FixedVector<T, N>(*this) *= rhs;
	}

	template<class T, std::size_t N>
	inline constexpr FixedVector<T, N>& FixedVector<T, N>::operator*=(T rhs) noexcept
	{
		for(std::size_t i = 0; i < N; i++)
		{
			this->values[i] *= rhs;
		}
		return *this;
	}

	template<class T, std::size_t N>
	inline constexpr FixedVector<T, N> FixedVector<T, N>::operator/(T rhs) const noexcept
	{
		return FixedVector<T, N>(*this) /= rhs;
	}

	template<class T, std::size_t N>
	inline constexpr FixedVector<T, N>& FixedVector<T, N>::operator/=(T rhs) noexcept
	{
		for(std::size_t i = 0; i < N; i++)
		{
			this->values[i] /= rhs;
		}
		return *this;
	}

	template<class T, std::size_t N>
	inline constexpr FixedVector<T, N> operator*(T lhs, const FixedVector<T, N>& rhs) noexcept
	{
		return FixedVector<T, N>(rhs) *= lhs;
	}

	template<class T, std::size_t N>
	inline constexpr T FixedVector<T, N>::x() const noexcept
	{
		return values[0];
	}

	template<class T, std::size_t N>
	inline constexpr T FixedVector<T, N>::y() const noexcept
	{
		static_assert(N > 1, "FixedVector must be at least size 2 to call .y()");
		return values[1];
	}

	template<class T, std::size_t N>
	inline constexpr T FixedVector<T, N>::z() const noexcept
	{
		static_assert(N > 2, "FixedVector must be at least size 3 to call .z()");
		return values[2];
	}

}

#endif //QUESTIAENGINE_FIXEDVECTOR_H
