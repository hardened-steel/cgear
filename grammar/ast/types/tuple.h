// Project: CGear
//
//  Created on: 02.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef AST_TYPES_TUPLE_H_
#define AST_TYPES_TUPLE_H_

#include <vector>
#include "grammar/lexer/token.h"
#include "type.h"

class ast::type::tuple: public ast::type
{
public:
	class field
	{
	public:
		ast::type::instance type;
		token::identifier name;
	public:
		field(ast::type::instance type, token::identifier name): type(type), name(name) {}
		field(const field& other): type(other.type), name(other.name) {}
	};
public:
	std::vector<field> fields;
	using instance = instance_t<ast::type::tuple>;
public:
	tuple(const std::vector<field>& fields): fields(fields) {}
	tuple(std::vector<field>&& fields): fields(std::move(fields)) {}

	void accept(ast::type::visitor&) const override;
};

#endif /* AST_TYPES_TUPLE_H_ */
