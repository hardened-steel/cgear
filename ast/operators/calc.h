// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef INSTRUCTIONS_CALC_H_
#define INSTRUCTIONS_CALC_H_

#include <utility/instance.hpp>
#include <ast/operations/operation.h>
#include "operator.h"

class ast::instruction::calc: public ast::instruction
{
	ast::operation::instance op;
public:
	using instance = utility::instance<ast::instruction::calc, utility::copyable>;
public:
	calc(const calc&) = default;
	calc(calc&&) = default;
	calc(ast::operation::instance op): op(op) {}
};

#endif /* INSTRUCTIONS_CALC_H_ */
