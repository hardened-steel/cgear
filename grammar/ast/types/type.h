// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef TYPE_H_
#define TYPE_H_

#include "../pool.h"
#include "../ast.h"
#include <memory>

class ast::type
{
public:
	class base: public ast
	{
	public:
		virtual ~base() {}
	};
	class t_bool;
	class t_int;
	class t_real;
	class t_void;
	class array;
	class pointer;
	class tuple;
	class t_class;
	class t_struct;
public:
	type(): impl(nullptr) {}
	type(type&& other): impl(std::move(other.impl)) {}
	type(const type& other): impl(other.impl) {}
	template<typename T> type(T&& other): impl(std::move(other.impl)) {}
	template<typename T> type(const T& other): impl(other.impl) {}
	template<typename T> type& operator=(T&& other) {
		this->impl = std::move(other.impl);
		return *this;
	}
	template<typename T> type& operator=(const T& other) {
		this->impl = other.impl;
		return *this;
	}
	type& operator=(type&& other) {
		this->impl = std::move(other.impl);
		return *this;
	}
	type& operator=(const type& other) {
		this->impl = other.impl;
		return *this;
	}
private:
	std::shared_ptr<base> impl;
};

#endif /* TYPE_H_ */
