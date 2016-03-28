// Project: CGear
//
//  Created on: 03.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef LITERAL_H
#define LITERAL_H

#include <utility/instance.hpp>
#include "operation.h"

class ast::operation::literal: public ast::operation
{
	enum { boolean, integer, real, string } type;
	union value_t {
		bool boolean;
		token::intLiteral integer;
		token::realLiteral real;
		token::stringLiteral string;

		value_t(): boolean(false) {}
		value_t(bool value): boolean(value) {}
		value_t(token::intLiteral&&    value): integer(std::move(value)) {}
		value_t(token::realLiteral&&   value):    real(std::move(value)) {}
		value_t(token::stringLiteral&& value):  string(std::move(value)) {}
	} value;
public:
	using instance = utility::instance<ast::operation::literal, utility::copyable>;
public:
	literal(const literal& other): type(other.type) {
		switch(type) {
		case boolean: value.boolean = other.value.boolean; break;
		case integer: value.integer = other.value.integer; break;
		case real:    value.real    = other.value.real;    break;
		case string:  value.string  = other.value.string;  break;
		}
	}

	literal(bool value):                 type(boolean), value(std::move(value)) {}
	literal(token::intLiteral value):    type(integer), value(std::move(value)) {}
	literal(token::realLiteral value):   type(real),    value(std::move(value)) {}
	literal(token::stringLiteral value): type(string),  value(std::move(value)) {}
};

#endif /* LITERAL_H */
