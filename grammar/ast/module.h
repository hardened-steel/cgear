// Project: CGear
//
//  Created on: 03.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef AST_MODULE_H
#define AST_MODULE_H

#include "ast.h"

class ast::module
{
	std::vector<ast::function> functions;
public:
	module() {}
	module(const std::vector<ast::function>& functions): functions(functions) {}
	module(std::vector<ast::function>&& functions): functions(std::move(functions)) {}
	void process();
};

#endif /* AST_MODULE_H */
