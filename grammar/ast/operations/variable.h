// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef VARIABLE_H
#define VARIABLE_H

#include "../../lexer/token.h"
#include "operation.h"

class ast::operation::variable
{
	friend ast::operation;
protected:
	class implementation: public ast::operation::base
	{
		token::identifier id;
	public:
		implementation(token::identifier id): id(id) {}
		void* operator new(size_t size) {
			return memory_pool.allocate(size);
		}
		void operator delete(void* pointer) {
			memory_pool.deallocate(pointer);
		}
	};
public:
	variable(token::identifier id): impl(new implementation(id)) {}
private:
	static pool<sizeof(implementation)> memory_pool;
	std::shared_ptr<implementation> impl;
};

#endif /* VARIABLE_H */
