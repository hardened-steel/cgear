#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "head.hpp"
#include "expression.h"
#include "type.h"

class GInstruction: public boost::spirit::qi::grammar<GIterator, st::instruction(), GSkip>
{
    boost::spirit::qi::rule<GIterator, st::instruction(), GSkip> instruction;
    boost::spirit::qi::rule<GIterator, st::instruction(), boost::spirit::locals<st::type, token::identifier>, GSkip> variable;
    boost::spirit::qi::rule<GIterator, st::instruction(), GSkip> calc;
    boost::spirit::qi::rule<GIterator, st::instruction(), GSkip> If;
    boost::spirit::qi::rule<GIterator, st::instruction(), GSkip> block;
    boost::spirit::qi::rule<GIterator, st::instruction(), GSkip> For;
    boost::spirit::qi::rule<GIterator, st::instruction(), GSkip> While;
    boost::spirit::qi::rule<GIterator, st::instruction(), GSkip> Return;
    boost::spirit::qi::rule<GIterator, st::instruction(), GSkip> nope;

    GExpression expression;
    GType type;
public:
    GInstruction(Lexer& lexer);
    ~GInstruction();
};

#endif // INSTRUCTION_H
