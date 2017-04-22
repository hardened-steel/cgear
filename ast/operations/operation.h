// Project: CGear
//
//  Created on: 01.08.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef OPERATION_H
#define OPERATION_H

#include <ast/ast.h>
#include <memory>

class ast::operation: public ast::node
{
public:
	class visitor;
	class binary;
	class variable;
	class literal;

	class code;
	using ptr = std::unique_ptr<ast::operation>;
public:
	virtual void accept(visitor&) = 0;
	virtual ~operation() {}
};

class ast::operation::visitor
{
public:
	virtual void visit(ast::operation::binary&)   {}
	virtual void visit(ast::operation::variable&) {}
	virtual void visit(ast::operation::literal&)  {}
	virtual ~visitor() {}
};

#endif // OPERATION_H
