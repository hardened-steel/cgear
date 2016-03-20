// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef OPERATOR_H_
#define OPERATOR_H_

#include "grammar/ast/operations/operation.h"
#include "grammar/ast/pool.h"
#include "grammar/ast/ast.h"
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
	using instance = instance_t<ast::instruction>;
public:
	virtual void accept(ast::instruction::visitor& v) const;
	virtual ~instruction() {}
};

#endif /* OPERATOR_H_ */
