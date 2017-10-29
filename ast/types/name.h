// Project: CGear
//
//  Created on: 31.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef GRAMMAR_AST_TYPES_NAME_H_
#define GRAMMAR_AST_TYPES_NAME_H_

#include <utility/instance.hpp>
#include <lexer/token.h>
#include "type.h"

class ast::type::name: public ast::type
{
	token::identifier type_name;
public:
	using instance = utility::instance<ast::type::name, utility::copyable>;
public:
	name(token::identifier type_name): type_name(type_name) {}
};

#endif /* GRAMMAR_AST_TYPES_NAME_H_ */
