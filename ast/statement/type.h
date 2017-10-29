// Project: CGear
//
//  Created on: 23.04.2017
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef AST_STATEMENT_TYPE_H_
#define AST_STATEMENT_TYPE_H_

#include <utility/instance.hpp>
#include <ast/types/type.h>
#include "statement.h"

class ast::statement::type: public ast::statement
{
	ast::type::instance t;
public:
	using instance = utility::instance<ast::statement::type, utility::copyable>;
public:
	type(const type&) = default;
	type(type&&) = default;
	type(ast::type::instance t): t(std::move(t)) {}
};

#endif /* AST_STATEMENT_TYPE_H_ */
