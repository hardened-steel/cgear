// Project: CGear
//
//  Created on: 30.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef GRAMMAR_AST_OPERATORS_VISITOR_H_
#define GRAMMAR_AST_OPERATORS_VISITOR_H_

#include "operator.h"

class ast::instruction::visitor
{
public:
	virtual void visit(ast::instruction::calc::implementation&) = 0;
	virtual void visit(ast::instruction::if_i::implementation&) = 0;
	virtual void visit(ast::instruction::ifelse_i::implementation&) = 0;
	virtual void visit(ast::instruction::while_i::implementation&) = 0;
	//virtual void visit(ast::instruction::for_i::implementation&) = 0;
	virtual void visit(ast::instruction::repeat_i::implementation&) = 0;
	//virtual void visit(ast::instruction::try_catch_i::implementation&) = 0;
	//virtual void visit(ast::instruction::switch_i::implementation&) = 0;
	virtual void visit(ast::instruction::return_i::implementation&) = 0;
	virtual void visit(ast::instruction::block::implementation&) = 0;
	virtual void visit(ast::instruction::variable::implementation&) = 0;
};

#endif /* GRAMMAR_AST_OPERATORS_VISITOR_H_ */
