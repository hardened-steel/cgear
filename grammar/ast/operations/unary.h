// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//	     email: keldgaden@gmail.com
//

#ifndef UNARY_H_
#define UNARY_H_

#include "operation.h"

class ast::operation::unary
{
	friend ast::operation;
protected:
	class implementation: public ast::operation::base
	{
		ast::operation op;
		ast::operation::code code;
	public:
		implementation(ast::operation::code code, ast::operation op): op(op), code(code) {}
		void* operator new(size_t size) {
			return memory_pool.allocate(size);
		}
		void operator delete(void* pointer) {
			memory_pool.deallocate(pointer);
		}
	};
public:
	unary(ast::operation::code code, ast::operation op): impl(new implementation(code, op)) {}
private:
	static pool<sizeof(implementation), 1024> memory_pool;
	std::shared_ptr<implementation> impl;
};

#endif /* UNARY_H_ */
