// Project: CGear
//
//  Created on: 30.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef GRAMMAR_AST_OPERATORS_VISITOR_H_
#define GRAMMAR_AST_OPERATORS_VISITOR_H_

#include "block.h"
#include "calc.h"
#include "if.h"
#include "repeat.h"
#include "return.h"
#include "variable.h"
#include "while.h"
#include "nope.h"

class ast::instruction::visitor
{
public:
	virtual void visit(const ast::instruction::calc&) = 0;
	virtual void visit(const ast::instruction::if_i&) = 0;
	virtual void visit(const ast::instruction::ifelse_i&) = 0;
	virtual void visit(const ast::instruction::while_i&) = 0;
	//virtual void visit(const ast::instruction::for_i&) = 0;
	virtual void visit(const ast::instruction::repeat_i&) = 0;
	//virtual void visit(const ast::instruction::try_catch_i&) = 0;
	//virtual void visit(const ast::instruction::switch_i&) = 0;
	virtual void visit(const ast::instruction::return_i&) = 0;
	virtual void visit(const ast::instruction::block&) = 0;
	virtual void visit(const ast::instruction::variable&) = 0;
	virtual ~visitor() {}
};

#endif /* GRAMMAR_AST_OPERATORS_VISITOR_H_ */
