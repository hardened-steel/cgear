// Project: CGear
//
//  Created on: 31.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef GRAMMAR_AST_FUNCTION_VISITOR_H_
#define GRAMMAR_AST_FUNCTION_VISITOR_H_

#include "function.h"

class ast::function::visitor
{
public:
	virtual void visit(ast::function::prototype::implementation&) = 0;
	virtual void visit(ast::function::definition::implementation&) = 0;
};

#endif /* GRAMMAR_AST_FUNCTION_VISITOR_H_ */
