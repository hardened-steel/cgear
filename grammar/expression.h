#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <type_traits>
#include "../syntax/operation.h"
#include "type.h"

class GExpression: public boost::spirit::qi::grammar<GIterator, ast::operation(), GSkip>
{
    boost::spirit::qi::rule<GIterator, ast::operation(), GSkip> expression;
    boost::spirit::qi::rule<GIterator, ast::operation(), GSkip> var;
    boost::spirit::qi::rule<GIterator, ast::operation(), boost::spirit::locals<token::identifier>, GSkip> call;
    boost::spirit::qi::rule<GIterator, ast::operation(), GSkip> operation[9];

    GType type;
public:
    GExpression(Lexer& lexer);
    ~GExpression();
};

#endif // EXPRESSION_H
