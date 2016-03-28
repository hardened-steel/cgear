// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef INSTRUCTION_VARIABLE_H_
#define INSTRUCTION_VARIABLE_H_

#include <utility/instance.hpp>
#include <ast/types/type.h>
#include <lexer/token.h>
#include "operator.h"

class ast::instruction::variable: public ast::instruction
{
	ast::type::instance type;
	token::identifier id;
	ast::operation::instance init;
public:
	using instance = utility::instance<ast::instruction::variable, utility::copyable>;
public:
	variable(const variable&) = default;
	variable(variable&&) = default;
	variable(ast::type::instance type, token::identifier id, ast::operation::instance init): type(type), id(id), init(init) {}
	void codegen(generator::context& context) const override;
};

#endif /* INSTRUCTION_VARIABLE_H_ */
