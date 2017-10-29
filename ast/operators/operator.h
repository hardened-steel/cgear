// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef OPERATOR_H_
#define OPERATOR_H_

#include <utility/instance.hpp>
#include <ast/ast.h>

class ast::instruction: public ast::node
{
public:
	class visitor;
	class variable;
	class calc;
	class if_i;
	class block;
	class nope;
public:
	using instance = utility::instance<ast::instruction, utility::copyable>;
public:
	virtual ~instruction() {}
};


class ast::instruction::nope: public ast::instruction
{
};

#endif /* OPERATOR_H_ */
