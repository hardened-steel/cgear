// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef UNARY_H
#define UNARY_H

#include "operation.h"

class ast::operation::unary: public ast::operation
{
	ast::operation::instance op;
	ast::operation::code code;
public:
	using instance = instance_t<ast::operation::unary>;
public:
	unary(ast::operation::code code, ast::operation::instance op): op(op), code(code) {}
	void accept(ast::operation::visitor&) override;
};

#endif /* UNARY_H */
