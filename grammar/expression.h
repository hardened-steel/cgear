// Project: CGear
//
//  Created on: 01.08.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <boost/spirit/include/qi.hpp>
#include "ast/operations/operation.h"
#include "lexer/lexer.h"
#include "type.h"

class GExpression: public boost::spirit::qi::grammar<GIterator, ast::operation(), GSkip>
{
	boost::spirit::qi::rule<GIterator, ast::operation(), GSkip> expression;
	boost::spirit::qi::rule<GIterator, ast::operation(), GSkip> variable;
	boost::spirit::qi::rule<GIterator, ast::operation(), boost::spirit::locals<token::identifier>, GSkip> call;
	boost::spirit::qi::rule<GIterator, ast::operation(), GSkip> operation[9];

	GTypeName type;
public:
	GExpression(Lexer& lexer);
	~GExpression();
};

#endif // EXPRESSION_H
