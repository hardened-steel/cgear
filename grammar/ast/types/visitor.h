// Project: CGear
//
//  Created on: 31.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef GRAMMAR_AST_TYPES_VISITOR_H_
#define GRAMMAR_AST_TYPES_VISITOR_H_

#include "type.h"
//#include "name.h"
#include "int.h"
//#include "tuple.h"

class ast::type::visitor
{
public:
	virtual void visit(const ast::type::t_int&) = 0;
	//virtual void visit(const ast::type::tuple&) = 0;
	//virtual void visit(const ast::type::name&) = 0;
	virtual ~visitor() {}
};

#endif /* GRAMMAR_AST_TYPES_VISITOR_H_ */
