// Project: CGear
//
//  Created on: 10.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef AST_FUNCTION_H_
#define AST_FUNCTION_H_

#include "grammar/ast/pool.h"
#include "grammar/ast/ast.h"
#include <memory>

class ast::function
{
public:
	class visitor;
	class base: public ast::node
	{
	public:
		virtual void accept(ast::function::visitor&) = 0;
		virtual ~base() {}
	};
	class definition;
	class prototype;
public:
	function(): impl(nullptr) {}
	function(function&& other): impl(std::move(other.impl)) {}
	function(const function& other): impl(other.impl) {}
	template<typename T> function(T&& other): impl(std::move(other.impl)) {}
	template<typename T> function(const T& other): impl(other.impl) {}
	template<typename T> function& operator=(T&& other) {
		this->impl = std::move(other.impl);
		return *this;
	}
	template<typename T> function& operator=(const T& other) {
		this->impl = other.impl;
		return *this;
	}
	void accept(ast::function::visitor& v) { impl->accept(v); }
private:
	std::shared_ptr<base> impl;
};

#endif /* AST_FUNCTION_H_ */
