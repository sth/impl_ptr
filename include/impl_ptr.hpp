#include <utility>

template<typename T>
class impl_ptr {
protected:
	T *raw;

public:
	template<typename ...Args>
	impl_ptr(Args... args) : raw(new T(std::forward<Args>(args)...)) {
	}

	impl_ptr(const impl_ptr<T> &other) : raw(new T(*other.raw)) {
	}

	impl_ptr(impl_ptr<T> &&other) : raw(new T(std::move(*other.raw))) {
	}

	~impl_ptr() noexcept (std::is_nothrow_destructible<T>::value) {
		delete raw;
	}

	impl_ptr& operator=(const impl_ptr<T> &other) noexcept(std::is_nothrow_copy_assignable<T>::value) {
		*raw = *other.raw;
		return *this;
	}

	impl_ptr& operator=(impl_ptr<T> &&other) noexcept(std::is_nothrow_move_assignable<T>::value) {
		*raw = std::move(*other.raw);
		return *this;
	}

	T* operator->() noexcept {
		return raw;
	}

	const T* operator->() const noexcept {
		return raw;
	}

	T& operator*() & noexcept {
		return *raw;
	}

	const T& operator*() const & noexcept {
		return *raw;
	}

	T&& operator*() && noexcept {
		return *raw;
	}
};

