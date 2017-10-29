// Project: CGear
//
//  Created on: 23.04.2017
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef AST_STATEMENT_VARIABLE_H_
#define AST_STATEMENT_VARIABLE_H_

#include <utility/instance.hpp>
#include <ast/operations/operation.h>
#include <ast/types/type.h>
#include <lexer/token.h>
#include "statement.h"

class ast::statement::variable: public ast::statement
{
	ast::type::instance type;
	token::identifier id;
	ast::operation::instance initval;
public:
	using instance = utility::instance<ast::statement::variable, utility::copyable>;
public:
	variable(const variable&) = default;
	variable(variable&&) = default;
	variable(ast::type::instance type, token::identifier id, ast::operation::instance initval)
	: type(std::move(type)), id(std::move(id)), initval(std::move(initval)) {}
	variable(ast::type::instance type, token::identifier id)
	: type(std::move(type)), id(std::move(id)) {}
};

#endif /* AST_STATEMENT_VARIABLE_H_ */
