// Project: CGear
//
//  Created on: 10.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef FUNCTION_DEFINITION_H_
#define FUNCTION_DEFINITION_H_

#include <utility/instance.hpp>
#include <ast/operators/operator.h>
#include "function.h"
#include "prototype.h"

class ast::function::definition: public ast::function
{
	ast::function::prototype::instance prototype;
	ast::instruction::instance body;
public:
	using instance = utility::instance<ast::function::definition, utility::copyable>;
public:
	definition(const definition&)  = default;
	definition(definition&& other) = default;
	definition(ast::function::prototype::instance prototype, ast::instruction::instance body)
	: prototype(std::move(prototype)), body(std::move(body)) {}
};

#endif /* FUNCTION_DEFINITION_H_ */
