// Project: CGear
//
//  Created on: 10.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef FUNCTION_DEFINITION_H_
#define FUNCTION_DEFINITION_H_

#include "function.h"
#include "prototype.h"
#include "grammar/ast/operators/operator.h"

class ast::function::definition: public ast::function
{
	ast::function::prototype::instance prototype;
	ast::instruction::instance body;
public:
	using instance = instance_t<ast::function::definition>;
public:
	definition(ast::function::prototype::instance prototype, ast::instruction::instance body): prototype(prototype), body(body) {}
	void accept(ast::function::visitor& v) const override;
};

#endif /* FUNCTION_DEFINITION_H_ */
