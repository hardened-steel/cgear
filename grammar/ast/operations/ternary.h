// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef TERNARY_H
#define TERNARY_H

#include "operation.h"

class ast::operation::ternary: public ast::operation
{
	ast::operation::instance true_action;
	ast::operation::instance false_action;
	ast::operation::instance condition;
public:
	using instance = instance_t<ast::operation::ternary>;
public:
	ternary(ast::operation::instance condition, ast::operation::instance true_action, ast::operation::instance false_action)
	: true_action(true_action), false_action(false_action), condition(condition) {}

	void accept(ast::operation::visitor&) const override;
};

#endif /* TERNARY_H */
