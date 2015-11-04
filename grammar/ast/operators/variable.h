// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef INSTRUCTION_VARIABLE_H_
#define INSTRUCTION_VARIABLE_H_

#include "grammar/ast/types/type.h"
#include "grammar/lexer/token.h"
#include "operator.h"

class ast::instruction::variable: public ast::instruction
{
	ast::type::instance type;
	token::identifier id;
	ast::operation::instance init;
public:
	using instance = instance_t<ast::instruction::variable>;
public:
	variable(ast::type::instance type, token::identifier id, ast::operation::instance init): type(type), id(id), init(init) {}
	void accept(ast::instruction::visitor&) override;
};

#endif /* INSTRUCTION_VARIABLE_H_ */
