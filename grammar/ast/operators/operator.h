// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//	     email: keldgaden@gmail.com
//

#ifndef OPERATOR_H_
#define OPERATOR_H_

#include "../operations/operation.h"
#include "../pool.h"
#include "../ast.h"
#include <memory>

class ast::instruction
{
public:
	class base
	{
	public:
		virtual ~base() {}
	};
	class variable;
	class calc;
	class if_i;
	class ifelse_i;
	class while_i;
	class for_i;
	class repeat_i;
	class try_catch_i;
	class switch_i;
	class return_i;
	class block;
	class nope;
public:
	instruction(): impl(nullptr) {}
	instruction(instruction&& other): impl(std::move(other.impl)) {}
	instruction(const instruction& other): impl(other.impl) {}
	template<typename T> instruction(T&& other): impl(std::move(other.impl)) {}
	template<typename T> instruction(const T& other): impl(other.impl) {}
	template<typename T> instruction& operator=(T&& other) {
		this->impl = std::move(other.impl);
		return *this;
	}
	template<typename T> instruction& operator=(const T& other) {
		this->impl = other.impl;
		return *this;
	}
private:
	std::shared_ptr<base> impl;
};

#endif /* OPERATOR_H_ */
