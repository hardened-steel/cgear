// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef BINARY_H
#define BINARY_H

#include "operation.h"

class ast::operation::binary
{
	friend ast::operation;
protected:
	class implementation: public ast::operation::base
	{
		ast::operation left;
		ast::operation right;
		ast::operation::code code;
	public:
		implementation(ast::operation::code code, ast::operation left, ast::operation right):
			left(left), right(right), code(code)
		{}
		void* operator new(size_t size) {
			return memory_pool.allocate(size);
		}
		void operator delete(void* pointer) {
			memory_pool.deallocate(pointer);
		}
	};
public:
	binary(ast::operation::code code, ast::operation left, ast::operation right): impl(new implementation(code, left, right)) {}
private:
	static pool<sizeof(implementation), 1024> memory_pool;
	std::shared_ptr<implementation> impl;
};

#endif /* BINARY_H */
