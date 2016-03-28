// Project: CGear
//
//  Created on: 10.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef FUNCTION_PROTOTYPE_H_
#define FUNCTION_PROTOTYPE_H_

#include <vector>
#include <utility/instance.hpp>
#include <lexer/token.h>
#include <ast/types/type.h>
#include "function.h"

class ast::function::prototype: public ast::function
{
public:
	class parameter
	{
		friend prototype;
	public:
		ast::type::instance type;
		token::identifier name;
	public:
		parameter() {}
		parameter(ast::type::instance type, token::identifier name): type(type), name(name) {}
		parameter(const parameter& other): type(other.type), name(other.name) {}
		parameter& operator = (const parameter& other) {
			type = other.type;
			name = other.name;
			return *this;
		}
		parameter& operator = (parameter&& other) {
			type = std::move(other.type);
			name = std::move(other.name);
			return *this;
		}
	};
	using instance = utility::instance<ast::function::prototype, utility::copyable>;
private:
	token::identifier name;
	std::vector<parameter> parameters;
	ast::type::instance returnType;
public:
	prototype() {}
	prototype(const prototype&)  = default;
	prototype(prototype&& other) = default;
	prototype(token::identifier name, std::vector<parameter> parameters, ast::type::instance returnType)
	: name(std::move(name)), parameters(std::move(parameters)), returnType(std::move(returnType)) {}
	void codegen(generator::context& context) const override;
};

#endif /* FUNCTION_PROTOTYPE_H_ */
