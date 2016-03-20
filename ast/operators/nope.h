// Project: CGear
//
//  Created on: 31.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef GRAMMAR_AST_OPERATORS_NOPE_H_
#define GRAMMAR_AST_OPERATORS_NOPE_H_

#include "operator.h"

class ast::instruction::nope: public ast::instruction
{
public:
	using instance = instance_t<ast::instruction::nope>;
	void accept(ast::instruction::visitor&) const override;
};


#endif /* GRAMMAR_AST_OPERATORS_NOPE_H_ */
