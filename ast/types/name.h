// Project: CGear
//
//  Created on: 31.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef GRAMMAR_AST_TYPES_NAME_H_
#define GRAMMAR_AST_TYPES_NAME_H_

#include <lexer/token.h>
#include <memory>
#include "type.h"

class ast::type::name: public ast::type
{
	token::identifier type_name;
public:
	using ptr = std::unique_ptr<ast::type::name>;
public:
	name(token::identifier type_name): type_name(type_name) {}
	void accept(visitor& v) override {
		v.visit(*this);
	}
};

#endif /* GRAMMAR_AST_TYPES_NAME_H_ */
