// Project: CGear
//
//  Created on: 17.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef GRAMMAR_AST_TYPES_INT_H_
#define GRAMMAR_AST_TYPES_INT_H_

#include "type.h"
#include "grammar/lexer/token.h"

class ast::type::t_int: public ast::type
{
public:
	using instance = instance_t<ast::type::t_int>;
	void accept(ast::type::visitor&) override;
};

#endif /* GRAMMAR_AST_TYPES_INT_H_ */
