// Project: CGear
//
//  Created on: 31.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef GRAMMAR_AST_OPERATORS_NOPE_H_
#define GRAMMAR_AST_OPERATORS_NOPE_H_

#include <utility/instance.hpp>
#include "operator.h"

class ast::instruction::nope: public ast::instruction
{
public:
	using instance = utility::instance<ast::instruction::nope, utility::copyable>;
	void codegen(generator::context& context) const override {}
};


#endif /* GRAMMAR_AST_OPERATORS_NOPE_H_ */
