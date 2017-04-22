// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef OPERATOR_H_
#define OPERATOR_H_

#include <ast/ast.h>
#include <memory>
#include "../../process/context.h"

class ast::instruction: public ast::node
{
public:
	class visitor;
	class variable;
	class calc;
	class if_i;
	class block;
	class nope;
public:
	using ptr = std::unique_ptr<ast::instruction>;
public:
	virtual void accept(visitor&) = 0;
	virtual ~instruction() {}
};

class ast::instruction::visitor
{
public:
	virtual void visit(ast::instruction::if_i&)     {}
	virtual void visit(ast::instruction::block&)    {}
	virtual void visit(ast::instruction::calc&)     {}
	virtual void visit(ast::instruction::variable&) {}
	virtual ~visitor() {}
};

class ast::instruction::nope: public ast::instruction
{
	void accept(visitor&) override {}
};

#endif /* OPERATOR_H_ */
