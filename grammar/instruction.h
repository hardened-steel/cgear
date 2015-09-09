// Project: CGear
//
//  Created on: 01.08.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <boost/spirit/include/qi.hpp>

#include "ast/operators/operator.h"
#include "expression.h"
#include "lexer/lexer.h"
#include "type.h"

class GInstruction: public boost::spirit::qi::grammar<GIterator, ast::instruction(), GSkip>
{
	boost::spirit::qi::rule<GIterator, ast::instruction(), GSkip> instruction;
	boost::spirit::qi::rule<GIterator, ast::instruction(), boost::spirit::locals<ast::type, token::identifier>, GSkip> variable;
	boost::spirit::qi::rule<GIterator, ast::instruction(), GSkip> calc;
	boost::spirit::qi::rule<GIterator, ast::instruction(), boost::spirit::locals<ast::operation, ast::instruction>, GSkip> if_i;
	boost::spirit::qi::rule<GIterator, ast::instruction(), GSkip> while_i;
	boost::spirit::qi::rule<GIterator, ast::instruction(), GSkip> for_i;
	boost::spirit::qi::rule<GIterator, ast::instruction(), GSkip> repeat_i;
	boost::spirit::qi::rule<GIterator, ast::instruction(), GSkip> try_catch_i;
	boost::spirit::qi::rule<GIterator, ast::instruction(), GSkip> switch_i;
	boost::spirit::qi::rule<GIterator, ast::instruction(), GSkip> return_i;
	boost::spirit::qi::rule<GIterator, ast::instruction(), GSkip> block;
	boost::spirit::qi::rule<GIterator, ast::instruction(), GSkip> nope;

	GExpression operation;
	GType type;
public:
	GInstruction(Lexer& lexer);
	~GInstruction();
};

#endif // INSTRUCTION_H
