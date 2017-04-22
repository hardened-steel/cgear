// Project: CGear
//
//  Created on: 10.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef AST_FUNCTION_H_
#define AST_FUNCTION_H_

#include <utility/instance.hpp>
#include <ast/ast.h>
#include "../../model/context.h"

class ast::function: public ast::node
{
public:
	class visitor;
	class definition;
	class prototype;
	using instance = utility::instance<ast::function, utility::copyable>;
public:
	virtual void codegen(generator::context& context) const {}
	virtual ~function() {}
};

#endif /* AST_FUNCTION_H_ */
