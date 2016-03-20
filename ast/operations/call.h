// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef CALL_H
#define CALL_H

#include "grammar/lexer/token.h"
#include "operation.h"

class ast::operation::call: public ast::operation
{
public:
	token::identifier id;
	std::vector<ast::operation::instance> params;
public:
	using instance = instance_t<ast::operation::call>;
public:
	call(token::identifier id, const std::vector<ast::operation::instance>& params): id(id), params(params) {}
	call(token::identifier id, std::vector<ast::operation::instance>&& params = {}): id(id), params(std::move(params)) {}

	void accept(ast::operation::visitor&) const override;
};

#endif /* CALL_H */
