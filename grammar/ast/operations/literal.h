// Project: CGear
//
//  Created on: 03.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef LITERAL_H
#define LITERAL_H

#include "operation.h"

class ast::operation::literal: public ast::operation
{
	enum { boolean_literal, integer_literal, real_literal, string_literal, symbol_literal };
	union {
		bool boolean;
		token::intLiteral integer;
		token::realLiteral real;
		token::stringLiteral string;
		token::charLiteral symbol;
	};
	int type;
public:
	using instance = instance_t<ast::operation::literal>;
public:
	literal(bool boolean): boolean(boolean), type(boolean_literal) {}
	literal(token::intLiteral integer): integer(integer), type(integer_literal) {}
	literal(token::realLiteral real): real(real), type(real_literal) {}
	literal(token::stringLiteral string): string(string), type(string_literal) {}
	literal(token::charLiteral symbol): symbol(symbol), type(symbol_literal) {}

	void accept(ast::operation::visitor&) const override;
};

#endif /* LITERAL_H */
