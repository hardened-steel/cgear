// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef VARIABLE_H
#define VARIABLE_H

#include <utility/instance.hpp>
#include <lexer/token.h>
#include "operation.h"

class ast::operation::variable: public ast::operation
{
public:
	token::identifier id;
public:
	using instance = utility::instance<ast::operation::variable, utility::copyable>;
public:
	variable(const variable&) = default;
	variable(variable&&) = default;
	variable(token::identifier id): id(std::move(id)) {}
	generator::value& codegen(generator::context& context) const override;
};

#endif /* VARIABLE_H */
