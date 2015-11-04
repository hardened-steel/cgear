// Project: CGear
//
//  Created on: 01.08.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <boost/spirit/include/qi.hpp>
#include "lexer/lexer.h"
#include "ast/operators/operator.h"
#include "expression.h"
#include "type.h"

class GInstruction: public boost::spirit::qi::grammar<GIterator, ast::instruction::instance(), GSkip>
{
	boost::spirit::qi::rule<GIterator, ast::instruction::instance(), GSkip> instruction;
	boost::spirit::qi::rule<GIterator, ast::instruction::instance(), boost::spirit::locals<ast::type::instance, token::identifier>, GSkip> variable;
	boost::spirit::qi::rule<GIterator, ast::instruction::instance(), GSkip> calc;
	boost::spirit::qi::rule<GIterator, ast::instruction::instance(), boost::spirit::locals<ast::operation::instance, ast::instruction::instance>, GSkip> if_i;
	boost::spirit::qi::rule<GIterator, ast::instruction::instance(), GSkip> while_i;
	boost::spirit::qi::rule<GIterator, ast::instruction::instance(), GSkip> for_i;
	boost::spirit::qi::rule<GIterator, ast::instruction::instance(), GSkip> repeat_i;
	boost::spirit::qi::rule<GIterator, ast::instruction::instance(), GSkip> try_catch_i;
	boost::spirit::qi::rule<GIterator, ast::instruction::instance(), GSkip> switch_i;
	boost::spirit::qi::rule<GIterator, ast::instruction::instance(), GSkip> return_i;
	boost::spirit::qi::rule<GIterator, ast::instruction::instance(), GSkip> block;
	boost::spirit::qi::rule<GIterator, ast::instruction::instance(), GSkip> nope;

	GExpression& operation;
	GType& type;
public:
	GInstruction(Lexer& lexer, GExpression& operation, GType& type);
	~GInstruction();
};

#endif // INSTRUCTION_H
