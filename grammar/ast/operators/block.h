// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef INSTRUCTIONS_BLOCK_H_
#define INSTRUCTIONS_BLOCK_H_

#include <vector>
#include "operator.h"

class ast::instruction::block
{
	friend ast::instruction;
public:
	class implementation: public ast::instruction::base
	{
		std::vector<ast::instruction> instructions;
	public:
		implementation(const std::vector<ast::instruction>& instructions): instructions(instructions) {}
		implementation(std::vector<ast::instruction>&& instructions): instructions(std::move(instructions)) {}
		void accept(ast::instruction::visitor&) override;
		void* operator new(size_t size) {
			return memory_pool.allocate(size);
		}
		void operator delete(void* pointer) {
			memory_pool.deallocate(pointer);
		}
	};
public:
	block(const std::vector<ast::instruction>& instructions): impl(new implementation(instructions)) {}
	block(std::vector<ast::instruction>&& instructions): impl(new implementation(std::move(instructions))) {}
private:
	static pool<sizeof(implementation)> memory_pool;
	std::shared_ptr<implementation> impl;
};

#endif /* INSTRUCTIONS_BLOCK_H_ */
