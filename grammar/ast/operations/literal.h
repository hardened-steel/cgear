// Project: CGear
//
//  Created on: 03.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef LITERAL_H
#define LITERAL_H

#include "operation.h"
#include "../../lexer/token.h"

class ast::operation::literal
{
	friend ast::operation;
protected:
	class implementation: public ast::operation::base
	{
		enum { integer_literal, real_literal, string_literal, symbol_literal };
		union {
			token::intLiteral integer;
			token::realLiteral real;
			token::stringLiteral string;
			token::charLiteral symbol;
		};
		int type;
	public:
		implementation(token::intLiteral integer): integer(integer), type(integer_literal) {}
		implementation(token::realLiteral real): real(real), type(real_literal) {}
		implementation(token::stringLiteral string): string(string), type(string_literal) {}
		implementation(token::charLiteral symbol): symbol(symbol), type(symbol_literal) {}
		void* operator new(size_t size) {
			return memory_pool.allocate(size);
		}
		void operator delete(void* pointer) {
			memory_pool.deallocate(pointer);
		}
	};
public:
	literal(token::intLiteral    value): impl(new implementation(value)) {}
	literal(token::realLiteral   value): impl(new implementation(value)) {}
	literal(token::stringLiteral value): impl(new implementation(value)) {}
	literal(token::charLiteral   value): impl(new implementation(value)) {}
private:
	static pool<sizeof(implementation)> memory_pool;
	std::shared_ptr<implementation> impl;
};



#endif /* LITERAL_H */
