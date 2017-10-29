// Project: CGear
//
//  Created on: 23.04.2017
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef PARSER_STATEMENT_H_
#define PARSER_STATEMENT_H_

#include <boost/spirit/include/qi.hpp>
#include <ast/statement/statement.h>
#include <lexer/lexer.h>
#include "expression.h"
#include "function.h"
#include "type.h"

class GStatement: public boost::spirit::qi::grammar<GIterator, ast::statement::instance(), GSkip>
{
	boost::spirit::qi::rule<GIterator, ast::statement::instance(), GSkip> statement;
	boost::spirit::qi::rule<GIterator, ast::statement::instance(), GSkip> function;
	boost::spirit::qi::rule<GIterator, ast::statement::instance(), GSkip> variable;
	boost::spirit::qi::rule<GIterator, ast::statement::instance(), GSkip> type;
public:
	GStatement(Lexer& lexer, GFunction& function, GExpression& expression, GType& type);
	~GStatement();
};

#endif /* PARSER_STATEMENT_H_ */
