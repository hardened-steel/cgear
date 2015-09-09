#ifndef HEAD_HPP
#define HEAD_HPP

#include <boost/spirit/include/qi.hpp>
#include "../syntax/tree.h"

typedef boost::spirit::qi::in_state_skipper<Lexer::lexer_def> GSkip;

#endif // HEAD_HPP
