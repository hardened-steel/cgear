// Project: CGear
//
//  Created on: 10.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef FUNCTION_PROTOTYPE_H_
#define FUNCTION_PROTOTYPE_H_

#include <vector>
#include "grammar/lexer/token.h"
#include "grammar/ast/types/type.h"
#include "function.h"

class ast::function::prototype: public ast::function
{
public:
	class parameter
	{
		ast::type::instance type;
		token::identifier name;
	public:
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
private:
	token::identifier name;
	std::vector<parameter> parameters;
	ast::type::instance returnType;
public:
	using instance = instance_t<ast::function::prototype>;
public:
	prototype(token::identifier name, std::vector<parameter> parameters, ast::type::instance returnType): name(name), parameters(parameters), returnType(returnType) {}
	void accept(ast::function::visitor& v) override;
};

#endif /* FUNCTION_PROTOTYPE_H_ */
