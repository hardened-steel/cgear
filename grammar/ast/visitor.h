// Project: CGear
//
//  Created on: 30.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef GRAMMAR_AST_VISITOR_H_
#define GRAMMAR_AST_VISITOR_H_

#include <boost/variant.hpp>
#include "ast.h"

class ast::visitor: public boost::static_visitor<void>
{
public:
	class base
	{
	public:
		virtual void visit(const ast::function&) = 0;
		virtual void visit(const ast::type&) = 0;
	};
private:
	ast::visitor::base* impl;
public:
	visitor(ast::visitor::base& impl): impl(&impl) {}

	void operator()(ast::function&) const;
	template <typename T>
	void operator()(T& operand) const {
		impl->visit(operand);
	}
};

#endif /* GRAMMAR_AST_VISITOR_H_ */
