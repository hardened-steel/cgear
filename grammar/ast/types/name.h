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

class ast::type::name
{
	friend ast::type;
protected:
	class implementation: public ast::type::base
	{
		token::identifier name;
	public:
		implementation(token::identifier name): name(name) {}
		void accept(ast::type::visitor&) override;
		void* operator new(size_t size) {
			return memory_pool.allocate(size);
		}
		void operator delete(void* pointer) {
			memory_pool.deallocate(pointer);
		}
	};
public:
	name(token::identifier name): impl(new implementation(name)) {}
private:
	static pool<sizeof(implementation)> memory_pool;
	std::shared_ptr<implementation> impl;
};

#endif /* GRAMMAR_AST_TYPES_NAME_H_ */
