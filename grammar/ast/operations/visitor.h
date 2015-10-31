// Project: CGear
//
//  Created on: 31.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef GRAMMAR_AST_OPERATIONS_VISITOR_H_
#define GRAMMAR_AST_OPERATIONS_VISITOR_H_

#include "operation.h"

class ast::operation::visitor
{
public:
	virtual void visit(ast::operation::unary::implementation&) = 0;
	virtual void visit(ast::operation::binary::implementation&) = 0;
	virtual void visit(ast::operation::ternary::implementation&) = 0;
	//virtual void visit(ast::operation::type_cast::implementation&) = 0;
	virtual void visit(ast::operation::variable::implementation&) = 0;
	//virtual void visit(ast::operation::index::implementation&) = 0;
	//virtual void visit(ast::operation::section::implementation&) = 0;
	virtual void visit(ast::operation::call::implementation&) = 0;
	//virtual void visit(ast::operation::array::implementation&) = 0;
	virtual void visit(ast::operation::literal::implementation&) = 0;
	virtual ~visitor() = 0;
};

#endif /* GRAMMAR_AST_OPERATIONS_VISITOR_H_ */
