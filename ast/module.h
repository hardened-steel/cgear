// Project: CGear
//
//  Created on: 03.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef AST_MODULE_H
#define AST_MODULE_H

#include <utility/instance.hpp>
#include <boost/variant.hpp>
#include "statement/statement.h"

class ast::module
{
	std::vector<ast::statement::instance> statements;
public:
	module() {}
	module(const std::vector<ast::statement::instance>& statements): statements(statements) {}
	module(std::vector<ast::statement::instance>&& statements): statements(std::move(statements)) {}
	void codegen();
};

#endif /* AST_MODULE_H */
