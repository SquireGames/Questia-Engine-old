#ifndef PIMPL_H
#define PIMPL_H

#include <memory>
#include <utility>

namespace qe
{
	template<typename T>
	class pimpl
	{
	public:
		pimpl() noexcept;
		template<class ...Args> pimpl(Args&& ...) noexcept;
		~pimpl() noexcept;

		T* operator->() noexcept;
		T* operator->() const noexcept;
		T& operator*() noexcept;
		T& operator*() const noexcept;
	private:
		std::unique_ptr<T> pImpl;
	};

	template<typename T>
	pimpl<T>::pimpl() noexcept :
			pimpl{new T{}}
	{}

	template<typename T>
	template<typename... Args>
	pimpl<T>::pimpl(Args&& ...args) noexcept :
			pImpl{new T{std::forward<Args>(args)...}}
	{}

	template<typename T>
	pimpl<T>::~pimpl() noexcept
	{}

	template<typename T>
	T* pimpl<T>::operator->() noexcept
	{
		return pImpl.get();
	}

	template<typename T>
	T& pimpl<T>::operator*() noexcept
	{
		return *pImpl.get();
	}

	template<typename T>
	T* pimpl<T>::operator->() const noexcept
	{
		return pImpl.get();
	}

	template<typename T>
	T& pimpl<T>::operator*() const noexcept
	{
		return *pImpl.get();
	}
}

#endif //PIMPL_H
