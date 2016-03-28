// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef OPERATOR_H_
#define OPERATOR_H_

#include <utility/instance.hpp>
#include <generator/context.h>
#include <ast/ast.h>
#include <memory>

class ast::instruction: public ast::node
{
public:
	class visitor;
	class variable;
	class calc;
	class if_i;
	class ifelse_i;
	class while_i;
	class for_i;
	class repeat_i;
	class try_catch_i;
	class switch_i;
	class return_i;
	class block;
	class nope;
public:
	using instance = utility::instance<ast::instruction, utility::copyable>;
public:
	virtual void codegen(generator::context& context) const {}
	virtual ~instruction() {}
};

#endif /* OPERATOR_H_ */
