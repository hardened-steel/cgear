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

namespace generator {
	class context;
	class value;
}

class ast::operation: public ast::node
{
public:
	class visitor;
	class binary;
	class variable;
	class call;
	class literal;
	class code;
	using instance = utility::instance<ast::operation, utility::copyable>;
public:
	virtual generator::value& codegen(generator::context& context) const { throw "error"; }
	virtual ~operation() {}
};

#endif // OPERATION_H
