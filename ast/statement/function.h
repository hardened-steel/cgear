// Project: CGear
//
//  Created on: 23.04.2017
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef AST_STATEMENT_FUNCTION_H_
#define AST_STATEMENT_FUNCTION_H_

#include <utility/instance.hpp>
#include <ast/function/function.h>
#include "statement.h"

class ast::statement::function: public ast::statement
{
	ast::function::instance f;
public:
	using instance = utility::instance<ast::statement::function, utility::copyable>;
public:
	function(const function&) = default;
	function(function&&) = default;
	function(ast::function::instance f): f(std::move(f)) {}
};

#endif /* AST_STATEMENT_FUNCTION_H_ */
