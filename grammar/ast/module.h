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
#include "visitor.h"

class ast::module
{
	using statement = boost::variant<ast::function, ast::type>;
	std::vector<statement> statements;
public:
	module() {}
	module(const std::vector<statement>& statements): statements(statements) {}
	module(std::vector<statement>&& statements): statements(std::move(statements)) {}

	void accept(const ast::visitor&) const;
};

#endif /* AST_MODULE_H */
