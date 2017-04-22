// Project: CGear
//
//  Created on: 17.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef GRAMMAR_AST_TYPES_INT_H_
#define GRAMMAR_AST_TYPES_INT_H_

#include <lexer/token.h>
#include <memory>
#include "type.h"

class ast::type::integer: public ast::type
{
public:
	using ptr = std::unique_ptr<ast::type::integer>;
	void accept(visitor& v) override {
		v.visit(*this);
	}
};

#endif /* GRAMMAR_AST_TYPES_INT_H_ */
