// Project: CGear
//
//  Created on: 31.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef GRAMMAR_AST_TYPES_VISITOR_H_
#define GRAMMAR_AST_TYPES_VISITOR_H_

#include "type.h"

class ast::type::visitor
{
public:
	virtual void visit(ast::type::t_int::implementation&) = 0;
	virtual void visit(ast::type::tuple::implementation&) = 0;
	virtual void visit(ast::type::name::implementation&) = 0;
};

#endif /* GRAMMAR_AST_TYPES_VISITOR_H_ */
