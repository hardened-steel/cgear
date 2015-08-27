#ifndef FUNCTION_H
#define FUNCTION_H

#include "head.hpp"
#include "instruction.h"

class GFunction: public boost::spirit::qi::grammar<GIterator, boost::spirit::locals<st::function::prototype>, st::function(), GSkip>
{
    boost::spirit::qi::rule<GIterator, boost::spirit::locals<st::function::prototype>, st::function(), GSkip> function;
    boost::spirit::qi::rule<GIterator, st::function::parameter(), GSkip> parameter;
    boost::spirit::qi::rule<GIterator, boost::spirit::locals<st::type>, st::function::prototype(), GSkip> prototype;

    GInstruction instruction;
    GType type;
public:
    GFunction(Lexer& lexer);
    ~GFunction();
};

#endif // FUNCTION_H