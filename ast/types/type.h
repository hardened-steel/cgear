// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef AST_TYPE_H_
#define AST_TYPE_H_

#include <memory>
#include <utility/instance.hpp>
#include <ast/ast.h>

class ast::type: public ast::node
{
public:
	class visitor;
	class boolean;
	class integer;
	class real;
	class void_t;
	class array;
	class pointer;
	class tuple;
	class user;
	class name;
public:
	using instance = utility::instance<ast::type, utility::copyable>;
public:
	virtual ~type() {}
};

#endif /* AST_TYPE_H_ */
