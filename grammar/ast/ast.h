// Project: CGear
//
//  Created on: 01.08.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef AST_H_
#define AST_H_

#include "grammar/lexer/token.h"
#include "instance.h"

class ast
{
public:
	class module;
	class visitor;

	class function;
	class instruction;
	class operation;
	class type;
	class node
	{
	public:
		using instance = instance_t<node>;
	public:
		token::iterator begin, end;
	};
};

#endif /* AST_H_ */
