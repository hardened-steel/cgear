// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef INSTRUCTIONS_IF_H_
#define INSTRUCTIONS_IF_H_

#include "operator.h"

class ast::instruction::if_i
{
	friend ast::instruction;
protected:
	class implementation: public ast::instruction::base
	{
	protected:
		ast::operation condition;
		ast::instruction true_action;
	public:
		implementation(ast::operation condition, ast::instruction true_action):
			condition(condition), true_action(true_action)
		{}
		void* operator new(size_t size) {
			return memory_pool.allocate(size);
		}
		void operator delete(void* pointer) {
			memory_pool.deallocate(pointer);
		}
	};
public:
	if_i(ast::operation condition, ast::instruction true_action): impl(new implementation(condition, true_action)) {}
private:
	static pool<sizeof(implementation)> memory_pool;
	std::shared_ptr<implementation> impl;
};

class ast::instruction::ifelse_i
{
	friend ast::instruction;
protected:
	class implementation: public ast::instruction::base
	{
		ast::operation condition;
		ast::instruction true_action;
		ast::instruction false_action;
	public:
		implementation(ast::operation condition, ast::instruction true_action, ast::instruction false_action):
			condition(condition), true_action(true_action), false_action(false_action)
		{}
		void* operator new(size_t size) {
			return memory_pool.allocate(size);
		}
		void operator delete(void* pointer) {
			memory_pool.deallocate(pointer);
		}
	};
public:
	ifelse_i(ast::operation condition, ast::instruction true_action, ast::instruction false_action):
		impl(new implementation(condition, true_action, false_action))
	{}
private:
	static pool<sizeof(implementation)> memory_pool;
	std::shared_ptr<implementation> impl;
};

#endif /* INSTRUCTIONS_IF_H_ */
