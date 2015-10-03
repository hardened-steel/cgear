// Project: CGear
//
//  Created on: 03.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef GRAMMAR_MODULE_H
#define GRAMMAR_MODULE_H

#include <boost/spirit/include/qi.hpp>
#include "ast/module.h"
#include "type.h"
#include "function.h"
#include "instruction.h"
#include "expression.h"

class GModule: public boost::spirit::qi::grammar<GIterator, ast::module(), GSkip>
{
	boost::spirit::qi::rule<GIterator, ast::module(), GSkip> module;

	GType type;
	GTypeName typeName;
	GExpression expression;
	GInstruction instruction;
	GFunction function;
public:
	GModule(Lexer& lexer);
};

#endif /* GRAMMAR_MODULE_H */
