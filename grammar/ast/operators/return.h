// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//	     email: keldgaden@gmail.com
//

#ifndef INSTRUCTIONS_RETURN_H_
#define INSTRUCTIONS_RETURN_H_

#include "operator.h"

class ast::instruction::return_i
{
	friend ast::instruction;
protected:
	class implementation: public ast::instruction::base
	{
		ast::operation op;
	public:
		implementation(ast::operation op): op(op) {}
		void* operator new(size_t size) {
			return memory_pool.allocate(size);
		}
		void operator delete(void* pointer) {
			memory_pool.deallocate(pointer);
		}
	};
public:
	return_i(ast::operation op): impl(new implementation(op)) {}
private:
	static pool<sizeof(implementation), 1024> memory_pool;
	std::shared_ptr<implementation> impl;
};

#endif /* INSTRUCTIONS_RETURN_H_ */
