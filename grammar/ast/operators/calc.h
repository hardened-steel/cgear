// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef INSTRUCTIONS_CALC_H_
#define INSTRUCTIONS_CALC_H_

#include "operator.h"

class ast::instruction::calc: public ast::instruction
{
	ast::operation::instance op;
public:
	using instance = instance_t<ast::instruction::calc>;
public:
	calc(ast::operation::instance op): op(op) {}
	void accept(ast::instruction::visitor&) const override;
};

#endif /* INSTRUCTIONS_CALC_H_ */
