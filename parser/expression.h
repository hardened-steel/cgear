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

class GExpression: public boost::spirit::qi::grammar<GIterator, ast::operation::instance(), GSkip>
{
	boost::spirit::qi::rule<GIterator, ast::operation::instance(), GSkip> expression;
	boost::spirit::qi::rule<GIterator, ast::operation::instance(), GSkip> variable;
	boost::spirit::qi::rule<GIterator, ast::operation::instance(), boost::spirit::locals<token::identifier>, GSkip> call;
	boost::spirit::qi::rule<GIterator, ast::operation::instance(), GSkip> operation[9];
public:
	GExpression(Lexer& lexer, GTypeName& type);
	~GExpression();
};

#endif // EXPRESSION_H
