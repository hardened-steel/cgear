// Project: CGear
//
//  Created on: 01.08.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#include <boost/phoenix/phoenix.hpp>
#include <ast/function/prototype.h>
#include <ast/function/definition.h>
#include "function.h"

class GFunction::GParameters: public boost::spirit::qi::grammar<GIterator, std::vector<ast::function::prototype::parameter>(), GSkip>
{
	boost::spirit::qi::rule<GIterator, ast::function::prototype::parameter(), GSkip> parameter;
	boost::spirit::qi::rule<GIterator, std::vector<ast::function::prototype::parameter>(), GSkip> parameters;
public:
	GParameters(Lexer& lexer, GTypeName& typeName): GParameters::base_type(parameters, "function parameters list") {
		namespace qi = boost::spirit::qi;
		namespace phx = boost::phoenix;

		parameter  = (typeName >> lexer.identifier)[qi::_val = phx::construct<ast::function::prototype::parameter>(qi::_1, qi::_2)];
		parameters = ( (lexer.tokens["("] >> lexer.tokens[")"]) [qi::_val = phx::construct<std::vector<ast::function::prototype::parameter>>()]
		             | ((lexer.tokens["("] >> (parameter % lexer.tokens[","])) > lexer.tokens[")"]) [qi::_val = qi::_1]
		             );

		parameter.name("parameter");
		parameters.name("parameters");
	}
};

class GFunction::GPrototype: public boost::spirit::qi::grammar<GIterator, ast::function::prototype::instance(), GSkip>
{
	boost::spirit::qi::rule<GIterator, ast::function::prototype::instance(), GSkip> prototype;
public:
	GPrototype(Lexer& lexer, GTypeName& typeName, GParameters& parameters): GPrototype::base_type(prototype, "function prototype") {
		namespace qi = boost::spirit::qi;
		namespace phx = boost::phoenix;

		prototype = lexer.kfunction > (lexer.identifier > parameters > lexer.tokens[":"] > typeName)[qi::_val = phx::construct<ast::function::prototype::instance>(qi::_1, qi::_2, qi::_3)];
	}
};

GFunction::GFunction(Lexer& lexer, GInstruction& instruction, GTypeName& typeName): GFunction::base_type(function, "function grammar"),
	parameters_ptr(new GParameters(lexer, typeName)), prototype_ptr(new GPrototype(lexer, typeName, *parameters_ptr))
{
	namespace qi = boost::spirit::qi;
	namespace phx = boost::phoenix;

	GPrototype& prototype = *prototype_ptr;

	function = (prototype >> lexer.tokens[";"])[qi::_val = qi::_1]
			 | (prototype >> instruction)[qi::_val = phx::construct<ast::function::definition::instance>(qi::_1, qi::_2)]
			 ;

	function.name("function rule");

	qi::on_error<qi::fail>
	    (
	        function
	      , std::cout
	            << phx::val("Error! Expecting ")
	            << qi::_4                               // what failed?
	            << std::endl
	    );

}

GFunction::~GFunction() {}
