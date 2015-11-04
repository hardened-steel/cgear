// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef VARIABLE_H
#define VARIABLE_H

#include "grammar/lexer/token.h"
#include "operation.h"

class ast::operation::variable: public ast::operation
{
	token::identifier id;
public:
	using instance = instance_t<ast::operation::variable>;
public:
	variable(token::identifier id): id(id) {}
	void accept(ast::operation::visitor&) override;
};

#endif /* VARIABLE_H */
