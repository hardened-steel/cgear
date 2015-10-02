// Project: CGear
//
//  Created on: 10.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef FUNCTION_DEFINITION_H_
#define FUNCTION_DEFINITION_H_

#include "function.h"
#include "prototype.h"
#include "../operators/operator.h"

class ast::function::definition
{
	friend ast::function;
protected:
	class implementation: public ast::function::base
	{
		ast::function::prototype prototype;
		ast::instruction body;
	public:
		implementation(ast::function::prototype prototype, ast::instruction body): prototype(prototype), body(body) {}
		void* operator new(size_t size) {
			return memory_pool.allocate(size);
		}
		void operator delete(void* pointer) {
			memory_pool.deallocate(pointer);
		}
	};
public:
	definition(ast::function::prototype prototype, ast::instruction body): impl(new implementation(prototype, body)) {}
private:
	static pool<sizeof(implementation), 1024> memory_pool;
	std::shared_ptr<implementation> impl;
};

#endif /* FUNCTION_DEFINITION_H_ */
