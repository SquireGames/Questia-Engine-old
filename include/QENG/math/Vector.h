#ifndef QUESTIAENGINE_VECTOR_H
#define QUESTIAENGINE_VECTOR_H

template <class T, std::size_t N>
struct Vector
{
	// ctor + dtor
	constexpr Vector() noexcept;
	template <class ...Args> constexpr Vector(Args ...args) noexcept;
	~Vector() noexcept = default;

	// copy and assignment operators
	constexpr Vector(Vector&&) noexcept = default;
	constexpr Vector(const Vector&) noexcept = default;
	constexpr Vector& operator=(Vector&&) noexcept = default;
	constexpr Vector& operator=(const Vector&) noexcept = default;

	// operators
	template <class IntegralType> constexpr T operator[](IntegralType index) noexcept;

	// utility functions
	template <std::size_t Index> constexpr T get() noexcept;

	// value
	T values[N];
};

template <class T, std::size_t N>
inline constexpr Vector<T, N>::Vector() noexcept : values {0}
{
}

template <class T, std::size_t N>
template <class ...Args>
inline constexpr Vector<T, N>::Vector(Args ...args) noexcept : values {args...}
{
	static_assert(sizeof...(Args) == N, "Vector size does not match number of arguments in the constructor parameters");
}

template <class T, std::size_t N>
template <class IntegralType>
inline constexpr T Vector<T, N>::operator[](IntegralType index) noexcept
{
	return values[index];
}

template <class T, std::size_t N>
template <std::size_t Index>
constexpr T Vector<T, N>::get() noexcept
{
	return values[Index];
};

#endif //QUESTIAENGINE_VECTOR_H
