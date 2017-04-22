// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef AST_TYPE_H_
#define AST_TYPE_H_

#include <memory>
#include <ast/ast.h>

class ast::type: public ast::node
{
public:
	class visitor;
	class integer;
	class name;
public:
	using ptr = std::unique_ptr<ast::type>;
public:
	virtual void accept(visitor&) = 0;
	virtual ~type() {}
};

class ast::type::visitor {
public:
	virtual void visit(ast::type::name&)    {}
	virtual void visit(ast::type::integer&) {}
	virtual ~visitor() {}
};

#endif /* AST_TYPE_H_ */
