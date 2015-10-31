// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef TERNARY_H
#define TERNARY_H

#include "operation.h"

class ast::operation::ternary
{
	friend ast::operation;
protected:
	class implementation: public ast::operation::base
	{
		ast::operation true_action;
		ast::operation false_action;
		ast::operation condition;
	public:
		implementation(ast::operation condition, ast::operation true_action, ast::operation false_action):
			true_action(true_action), false_action(false_action), condition(condition)
		{}
		void accept(ast::operation::visitor&) override;
		void* operator new(size_t size) {
			return memory_pool.allocate(size);
		}
		void operator delete(void* pointer) {
			memory_pool.deallocate(pointer);
		}
	};
public:
	ternary(ast::operation condition, ast::operation true_action, ast::operation false_action): impl(new implementation(condition, true_action, false_action)) {}
private:
	static pool<sizeof(implementation)> memory_pool;
	std::shared_ptr<implementation> impl;
};

#endif /* TERNARY_H */
