// Project: CGear
//
//  Created on: 01.08.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef GRAMMAR_FUNCTION_H_
#define GRAMMAR_FUNCTION_H_

#include <boost/spirit/include/qi.hpp>
#include <ast/function/function.h>
#include <lexer/lexer.h>
#include "instruction.h"

class GFunction: public boost::spirit::qi::grammar<GIterator, ast::function::instance(), GSkip>
{
	boost::spirit::qi::rule<GIterator, ast::function::instance(), GSkip> function;
protected:
	class GParameters;
	class GPrototype;
public:
	GFunction(Lexer& lexer, GInstruction& instruction, GTypeName& typeName);
	~GFunction();
private:
	std::unique_ptr<GParameters> parameters_ptr;
	std::unique_ptr<GPrototype>  prototype_ptr;
};

#endif // GRAMMAR_FUNCTION_H_
