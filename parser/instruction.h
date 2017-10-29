// Project: CGear
//
//  Created on: 01.08.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <boost/spirit/include/qi.hpp>
#include <ast/operators/operator.h>
#include <lexer/lexer.h>
#include "expression.h"
#include "type.h"

class GInstruction: public boost::spirit::qi::grammar<GIterator, ast::instruction::instance(), GSkip>
{
	boost::spirit::qi::rule<GIterator, ast::instruction::instance(), GSkip> instruction;
	boost::spirit::qi::rule<GIterator, ast::instruction::instance(), GSkip> calc;
	boost::spirit::qi::rule<GIterator, ast::instruction::instance(), GSkip> block;
	boost::spirit::qi::rule<GIterator, ast::instruction::instance(), GSkip> nope;
public:
	GInstruction(Lexer& lexer, GExpression& operation, GType& type);
	~GInstruction();
};

#endif // INSTRUCTION_H
