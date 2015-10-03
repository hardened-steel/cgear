// Project: CGear
//
//  Created on: 01.08.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef GRAMMAR_FUNCTION_H_
#define GRAMMAR_FUNCTION_H_

#include <boost/spirit/include/qi.hpp>
#include "lexer/lexer.h"
#include "ast/function/function.h"
#include "ast/function/prototype.h"
#include "instruction.h"

class GFunction: public boost::spirit::qi::grammar<GIterator, boost::spirit::locals<ast::function::prototype>, ast::function(), GSkip>
{
	boost::spirit::qi::rule<GIterator, boost::spirit::locals<ast::function::prototype>, ast::function(), GSkip> function;
	boost::spirit::qi::rule<GIterator, ast::function::prototype(), GSkip> prototype;

	GInstruction& instruction;
	GTypeName& typeName;
public:
	GFunction(Lexer& lexer, GInstruction& instruction, GTypeName& typeName);
	~GFunction();
};

#endif // GRAMMAR_FUNCTION_H_
