// Project: CGear
//
//  Created on: 01.08.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef AST_H_
#define AST_H_

#include <memory>
#include <lexer/token.h>

class ast
{
public:
	class module;
	class visitor;

	class statement;
	class function;
	class instruction;
	class operation;
	class type;
	class node
	{
	public:
		using ptr = std::unique_ptr<node>;
	public:
		token::iterator begin, end;
	};
};

#endif /* AST_H_ */
