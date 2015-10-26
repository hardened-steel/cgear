// Project: CGear
//
//  Created on: 17.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef GRAMMAR_AST_TYPES_INT_H_
#define GRAMMAR_AST_TYPES_INT_H_

#include "type.h"
#include "../../lexer/token.h"

class ast::type::t_int
{
	friend ast::type;
protected:
	class implementation: public ast::type::base
	{
	public:
		void* operator new(size_t size) {
			return memory_pool.allocate(size);
		}
		void operator delete(void* pointer) {
			memory_pool.deallocate(pointer);
		}
	};
public:
	t_int(): impl(new implementation()) {}
private:
	static pool<sizeof(implementation)> memory_pool;
	std::shared_ptr<implementation> impl;
};

#endif /* GRAMMAR_AST_TYPES_INT_H_ */
