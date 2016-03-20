// Project: CGear
//
//  Created on: 31.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef GRAMMAR_AST_TYPES_NAME_H_
#define GRAMMAR_AST_TYPES_NAME_H_

#include "type.h"
#include "grammar/lexer/token.h"

class ast::type::name: public ast::type
{
public:
	token::identifier type_name;
public:
	using instance = instance_t<ast::type::name>;
public:
	name(token::identifier type_name): type_name(type_name) {}
	void accept(ast::type::visitor&) const override;
};

#endif /* GRAMMAR_AST_TYPES_NAME_H_ */
