// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef INSTRUCTIONS_WHILE_H_
#define INSTRUCTIONS_WHILE_H_

#include "operator.h"

class ast::instruction::while_i: public ast::instruction
{
	ast::operation::instance condition;
	ast::instruction::instance action;
public:
	using instance = instance_t<ast::instruction::while_i>;
public:
	while_i(ast::operation::instance condition, ast::instruction::instance action): condition(condition), action(action) {}
	void accept(ast::instruction::visitor&) const override;
};

#endif /* INSTRUCTIONS_WHILE_H_ */
