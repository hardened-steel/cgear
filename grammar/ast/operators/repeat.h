// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef INSTRUCTIONS_REPEAT_H_
#define INSTRUCTIONS_REPEAT_H_

#include "operator.h"

class ast::instruction::repeat_i: public ast::instruction
{
	ast::operation::instance condition;
	ast::instruction::instance action;
public:
	using instance = instance_t<ast::instruction::repeat_i>;
public:
	repeat_i(ast::operation::instance condition, ast::instruction::instance action): condition(condition), action(action) {}
	void accept(ast::instruction::visitor&) override;
};

#endif /* INSTRUCTIONS_REPEAT_H_ */
