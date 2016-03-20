// Project: CGear
//
//  Created on: 01.08.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef LEXER_CONSTANT_TABLE_H_
#define LEXER_CONSTANT_TABLE_H_

#include <set>
#include "token.h"

class ConstantTable
{
	std::set<std::string> identifierTable;
	std::set<token::int_type> integerConstantTable;
	std::set<token::real_type> realConstantTable;
public:
	token::identifier createIdentifier(const token::iterator& start, const token::iterator& end);
	token::intLiteral createInteger(const token::iterator& start, const token::iterator& end);
	token::stringLiteral createString(const token::iterator& start, const token::iterator& end);
	token::stringLiteral createRawString(const token::iterator& start, const token::iterator& end);
	token::realLiteral createReal(const token::iterator& start, const token::iterator& end);
};

#endif /* LEXER_CONSTANT_TABLE_H_ */
