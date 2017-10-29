// Project: CGear
//
//  Created on: 26.03.2016
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef AST_STATEMENT_H_
#define AST_STATEMENT_H_

#include <utility/instance.hpp>
#include <ast/operations/operation.h>
#include <ast/types/type.h>
#include <ast/ast.h>

class ast::statement: public ast::node
{
public:
	class variable;
	class type;
	class function;
public:
	using instance = utility::instance<ast::statement, utility::copyable>;
};

#endif /* AST_STATEMENT_H_ */
