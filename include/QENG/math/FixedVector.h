#ifndef QUESTIAENGINE_FIXEDVECTOR_H
#define QUESTIAENGINE_FIXEDVECTOR_H

template <class T, std::size_t N>
struct FixedVector
{
	// ctor + dtor
	constexpr FixedVector() noexcept;
	template <class ...Args> constexpr FixedVector(Args ...args) noexcept;
	~FixedVector() noexcept = default;

	// copy and assignment operators
	constexpr FixedVector(FixedVector&&) noexcept = default;
	constexpr FixedVector(const FixedVector&) noexcept = default;
	constexpr FixedVector& operator=(FixedVector&&) noexcept = default;
	constexpr FixedVector& operator=(const FixedVector&) noexcept = default;

	// operators
	constexpr T operator[](std::size_t index) noexcept;
	constexpr bool operator==(const FixedVector<T, N>& rhs) noexcept;
	constexpr bool operator!=(const FixedVector<T, N>& rhs) noexcept;

	// utility functions
	template <std::size_t Index> constexpr T get() noexcept;
	constexpr std::size_t getSize() noexcept;

	// value
	T values[N];
};

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
inline constexpr T FixedVector<T, N>::operator[](std::size_t index) noexcept
{
	return values[index];
}

template <class T, std::size_t N>
template <std::size_t Index>
inline constexpr T FixedVector<T, N>::get() noexcept
{
	return values[Index];
}

template<class T, size_t N>
inline constexpr bool FixedVector<T, N>::operator==(const FixedVector<T, N> &rhs) noexcept
{
	return std::equal(std::begin(this->values), std::end(this->values), std::begin(rhs.values));
}

template<class T, size_t N>
inline constexpr bool FixedVector<T, N>::operator!=(const FixedVector<T, N> &rhs) noexcept
{
	return !operator==(rhs);
}

template<class T, size_t N>
inline constexpr std::size_t FixedVector<T, N>::getSize() noexcept
{
	return N;
};

#endif //QUESTIAENGINE_FIXEDVECTOR_H
