// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef BINARY_H
#define BINARY_H

#include "operation.h"

class ast::operation::binary: public ast::operation
{
	ast::operation::instance left;
	ast::operation::instance right;
	ast::operation::code code;
public:
	using instance = instance_t<ast::operation::binary>;
public:
	binary(ast::operation::code code, ast::operation::instance left, ast::operation::instance right): left(left), right(right), code(code) {}
	void accept(ast::operation::visitor&) override;
};

#endif /* BINARY_H */
