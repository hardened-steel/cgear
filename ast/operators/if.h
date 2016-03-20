// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef INSTRUCTIONS_IF_H_
#define INSTRUCTIONS_IF_H_

#include "operator.h"

class ast::instruction::if_i: public ast::instruction
{
public:
	ast::operation::instance condition;
	ast::instruction::instance true_action;
public:
	using instance = instance_t<ast::instruction::if_i>;
public:
	if_i(ast::operation::instance condition, ast::instruction::instance true_action)
	: condition(condition), true_action(true_action) {}

	void accept(ast::instruction::visitor&) const override;
};

class ast::instruction::ifelse_i: public ast::instruction::if_i
{
public:
	ast::instruction::instance false_action;
public:
	using instance = instance_t<ast::instruction::ifelse_i>;
public:
	ifelse_i(ast::operation::instance condition, ast::instruction::instance true_action, ast::instruction::instance false_action)
	: ast::instruction::if_i(condition, true_action), false_action(false_action) {}

	void accept(ast::instruction::visitor&) const override;
};

#endif /* INSTRUCTIONS_IF_H_ */
