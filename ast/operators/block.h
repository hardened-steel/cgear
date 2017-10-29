// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef INSTRUCTIONS_BLOCK_H_
#define INSTRUCTIONS_BLOCK_H_

#include <vector>
#include <utility/instance.hpp>
#include "operator.h"

class ast::instruction::block: public ast::instruction
{
	std::vector<ast::instruction::instance> instructions;
public:
	using instance = utility::instance<ast::instruction::block, utility::copyable>;
public:
	block(const block&) = default;
	block(block&&) = default;
	block(const std::vector<ast::instruction::instance>& instructions): instructions(instructions) {}
	block(std::vector<ast::instruction::instance>&& instructions): instructions(std::move(instructions)) {}
};

#endif /* INSTRUCTIONS_BLOCK_H_ */
