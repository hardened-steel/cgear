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

class ast::instruction::block: public ast::instruction
{
	std::vector<ast::instruction::instance> instructions;
public:
	using instance = instance_t<ast::instruction::block>;
public:
	block(const std::vector<ast::instruction::instance>& instructions): instructions(instructions) {}
	block(std::vector<ast::instruction::instance>&& instructions): instructions(std::move(instructions)) {}

	void accept(ast::instruction::visitor&) const override;
};

#endif /* INSTRUCTIONS_BLOCK_H_ */
