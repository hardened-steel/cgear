// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef INSTRUCTIONS_REPEAT_H_
#define INSTRUCTIONS_REPEAT_H_

#include "operator.h"

class ast::instruction::repeat_i
{
	friend ast::instruction;
protected:
	class implementation: public ast::instruction::base
	{
		ast::operation condition;
		ast::instruction action;
	public:
		implementation(ast::operation condition, ast::instruction action): condition(condition), action(action) {}
		void* operator new(size_t size) {
			return memory_pool.allocate(size);
		}
		void operator delete(void* pointer) {
			memory_pool.deallocate(pointer);
		}
	};
public:
	repeat_i(ast::operation condition, ast::instruction action): impl(new implementation(condition, action)) {}
private:
	static pool<sizeof(implementation)> memory_pool;
	std::shared_ptr<implementation> impl;
};

#endif /* INSTRUCTIONS_REPEAT_H_ */
