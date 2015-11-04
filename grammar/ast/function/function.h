// Project: CGear
//
//  Created on: 10.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef AST_FUNCTION_H_
#define AST_FUNCTION_H_

#include "grammar/ast/instance.h"
#include "grammar/ast/pool.h"
#include "grammar/ast/ast.h"

class ast::function: public ast::node
{
public:
	class visitor;
	class definition;
	class prototype;
	using instance = instance_t<ast::function>;
public:
	virtual void accept(ast::function::visitor& v);
	virtual ~function() {}
};

#endif /* AST_FUNCTION_H_ */
