// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef INSTRUCTIONS_RETURN_H_
#define INSTRUCTIONS_RETURN_H_

#include <utility/instance.hpp>
#include "operator.h"

class ast::instruction::return_i: public ast::instruction
{
	ast::operation::instance op;
public:
	using instance = utility::instance<ast::instruction::return_i, utility::copyable>;
public:
	return_i(const return_i&) = default;
	return_i(return_i&&) = default;
	return_i(ast::operation::instance op): op(op) {}
};

#endif /* INSTRUCTIONS_RETURN_H_ */
