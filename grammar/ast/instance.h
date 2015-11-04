// Project: CGear
//
//  Created on: 04.11.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef GRAMMAR_AST_INSTANCE_H_
#define GRAMMAR_AST_INSTANCE_H_

#include <memory>
#include <type_traits>

template<typename T> class instance_t
{
	std::shared_ptr<T> impl;
protected:
	static std::shared_ptr<T> getPtr(const instance_t& i) { return i.impl; }
	static std::shared_ptr<T> getPtr(instance_t&& i) { return std::move(i.impl); }
private:
	template<typename B, typename D, bool HasSpecConstructor> class caster {};
	template<typename B, typename D> class caster<B, D, false>: instance_t<B>, instance_t<D>
	{
		static_assert(std::is_base_of<B, D>::value, "class D must extend class B");
	public:
		static std::shared_ptr<B> getDeriviredPtr(const instance_t<D>& other) {
			return instance_t<D>::getPtr(other);
		}
		static std::shared_ptr<B> getDeriviredPtr(instance_t<D>&& other) {
			return instance_t<D>::getPtr(std::move(other));
		}
	};
	template<typename B, typename D> class caster<B, D, true>: instance_t<B>, instance_t<D>
	{
	public:
		static std::shared_ptr<B> getDeriviredPtr(const instance_t<D>& other) {
			return std::make_shared<B>(other);
		}
		static std::shared_ptr<B> getDeriviredPtr(instance_t<D>&& other) {
			return std::make_shared<B>(std::move(other));
		}
	};
public:
	template<typename...TArgs> instance_t(TArgs&&... args): impl(std::make_shared<T>(std::forward<TArgs>(args)...)) {
		static_assert(std::is_constructible<T, TArgs...>::value, "type T must have appropriate constructor");
	}
	instance_t(instance_t& other): impl(other.impl) {}
	instance_t(const instance_t& other): impl(other.impl) {}
	instance_t(instance_t&& other): impl(std::move(other.impl)) {}
	instance_t& operator=(instance_t& other) {
		impl = other.impl;
		return *this;
	}
	instance_t& operator=(const instance_t& other) {
		impl = other.impl;
		return *this;
	}
	instance_t& operator=(instance_t&& other) {
		impl = std::move(other.impl);
		return *this;
	}
	template<typename D> instance_t(instance_t<D>& other): impl(caster<T, D, std::is_constructible<T, instance_t<D>&>::value>::getDeriviredPtr(other)) {}
	template<typename D> instance_t(const instance_t<D>& other): impl(caster<T, D, std::is_constructible<T, const instance_t<D>&>::value>::getDeriviredPtr(other)) {}
	template<typename D> instance_t(instance_t<D>&& other): impl(caster<T, D, std::is_constructible<T, instance_t<D>&&>::value>::getDeriviredPtr(std::move(other))) {}
	template<typename D> instance_t& operator=(instance_t<D>& other) {
		impl = caster<T, D, std::is_constructible<T, instance_t<D>&>::value>::getDeriviredPtr(other);
		return *this;
	}
	template<typename D> instance_t& operator=(const instance_t<D>& other) {
		impl = caster<T, D, std::is_constructible<T, const instance_t<D>&>::value>::getDeriviredPtr(other);
		return *this;
	}
	template<typename D> instance_t& operator=(instance_t<D>&& other) {
		impl = caster<T, D, std::is_constructible<T, instance_t<D>&&>::value>::getDeriviredPtr(std::move(other));
		return *this;
	}
	const T* operator->() const { return impl.get(); }
	T* operator->() { return impl.get(); }
	~instance_t() {}
};

#endif /* GRAMMAR_AST_INSTANCE_H_ */
