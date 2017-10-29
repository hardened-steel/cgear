// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef CALL_H
#define CALL_H

#include <lexer/token.h>
#include "operation.h"

class ast::operation::call: public ast::operation
{
	token::identifier id;
	std::vector<ast::operation::instance> params;
public:
	using instance = utility::instance<ast::operation::call, utility::copyable>;
public:
	call(const call&) = default;
	call(call&&) = default;
	call(token::identifier id, const std::vector<ast::operation::instance>& params): id(std::move(id)), params(params) {}
	call(token::identifier id, std::vector<ast::operation::instance>&& params = {}): id(std::move(id)), params(std::move(params)) {}
};

#endif /* CALL_H */
