// Project: CGear
//
//  Created on: 30.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef GRAMMAR_AST_VISITOR_H_
#define GRAMMAR_AST_VISITOR_H_

#include <boost/variant.hpp>
#include "module.h"

class ast::module::visitor: public boost::static_visitor<void>
{
public:
	virtual void visit(const ast::function::instance&) = 0;
	virtual void visit(const ast::type::instance&) = 0;
public:
	virtual ~visitor() {}

	template <typename T> void operator()(const T& operand) {
		visit(operand);
	}
};

#endif /* GRAMMAR_AST_VISITOR_H_ */
