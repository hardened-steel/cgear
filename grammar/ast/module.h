// Project: CGear
//
//  Created on: 03.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef AST_MODULE_H
#define AST_MODULE_H

#include <boost/variant.hpp>
#include "ast.h"
#include "function/function.h"
#include "types/type.h"

class ast::module
{
public:
	using statement = boost::variant<ast::function::instance, ast::type::instance>;
	std::vector<statement> statements;
public:
	class visitor;
public:
	module() {}
	module(const std::vector<statement>& statements): statements(statements) {}
	module(std::vector<statement>&& statements): statements(std::move(statements)) {}

	void accept(ast::module::visitor&) const;
};

#endif /* AST_MODULE_H */
