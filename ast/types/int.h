// Project: CGear
//
//  Created on: 17.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef GRAMMAR_AST_TYPES_INT_H_
#define GRAMMAR_AST_TYPES_INT_H_

#include <utility/instance.hpp>
#include <lexer/token.h>
#include "type.h"

class ast::type::integer: public ast::type
{
public:
	using instance = utility::instance<ast::type::integer, utility::copyable>;
};

#endif /* GRAMMAR_AST_TYPES_INT_H_ */
