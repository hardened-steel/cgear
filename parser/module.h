// Project: CGear
//
//  Created on: 03.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef GRAMMAR_MODULE_H
#define GRAMMAR_MODULE_H

#include <memory>
#include <boost/spirit/include/qi.hpp>
#include <ast/module.h>

class GModule: public boost::spirit::qi::grammar<GIterator, ast::module(), GSkip>
{
	class implementation;
private:
	boost::spirit::qi::rule<GIterator, ast::module(), GSkip> module;
	std::unique_ptr<implementation> impl;
public:
	GModule(Lexer& lexer);
	~GModule();
};

#endif /* GRAMMAR_MODULE_H */
