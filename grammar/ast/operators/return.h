// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef INSTRUCTIONS_RETURN_H_
#define INSTRUCTIONS_RETURN_H_

#include "operator.h"

class ast::instruction::return_i: public ast::instruction
{
	ast::operation::instance op;
public:
	using instance = instance_t<ast::instruction::return_i>;
public:
	return_i(ast::operation::instance op): op(op) {}
	void accept(ast::instruction::visitor&) const override;
};

#endif /* INSTRUCTIONS_RETURN_H_ */
