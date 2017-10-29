// Project: CGear
//
//  Created on: 01.08.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef OPERATION_H
#define OPERATION_H

#include <utility/instance.hpp>
#include <ast/ast.h>

class ast::operation: public ast::node
{
public:
	class visitor;
	class binary;
	class variable;
	class literal;
	class call;

	class code;
	using instance = utility::instance<ast::operation, utility::copyable>;
public:
	virtual ~operation() {}
};


#endif // OPERATION_H
