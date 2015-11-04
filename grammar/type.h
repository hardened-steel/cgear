// Project: CGear
//
//  Created on: 01.08.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef GTYPE_H
#define GTYPE_H

#include <memory>
#include <map>
#include <boost/spirit/include/qi.hpp>
#include "lexer/lexer.h"
#include "ast/types/type.h"

class GType: public boost::spirit::qi::grammar<GIterator, ast::type::instance(), GSkip>
{
	boost::spirit::qi::rule<GIterator, ast::type::instance(), GSkip> type;
public:
	GType(Lexer& lexer);
};

class GTypeName: public boost::spirit::qi::grammar<GIterator, ast::type::instance(), GSkip>
{
	boost::spirit::qi::rule<GIterator, ast::type::instance(), GSkip> type;
public:
	GTypeName(Lexer& lexer);
};

#endif // GTYPE_H
