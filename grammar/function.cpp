// Project: CGear
//
//  Created on: 01.08.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#include <boost/phoenix/phoenix.hpp>
#include "function.h"
#include "ast/function/prototype.h"
#include "ast/function/definition.h"

GFunction::GFunction(Lexer& lexer, GInstruction& instruction, GTypeName& typeName): GFunction::base_type(function, "function grammar"),
	instruction(instruction), typeName(typeName)
{
	namespace qi = boost::spirit::qi;
	namespace phx = boost::phoenix;

	boost::spirit::qi::rule<GIterator, ast::function::prototype::parameter(), GSkip> parameter = (typeName >> lexer.identifier)[qi::_val = phx::construct<ast::function::prototype::parameter>(qi::_1, qi::_2)];
	boost::spirit::qi::rule<GIterator, std::vector<ast::function::prototype::parameter>(), GSkip> parameters;
	parameters = ( (lexer.tokens["("] >> lexer.tokens[")"])
	             | (lexer.tokens["("] >> parameter % lexer.tokens[","] > lexer.tokens[")"]) [qi::_val = qi::_1]
	             );

	prototype = lexer.kfunction > (lexer.identifier > parameters > lexer.tokens[":"] > typeName)[qi::_val = phx::construct<ast::function::prototype>(qi::_1, qi::_2, qi::_3)];
	function = prototype[qi::_a = qi::_1] >> ((lexer.tokens[";"][qi::_val = qi::_a]) | (instruction[qi::_val = phx::construct<ast::function::definition>(qi::_a, qi::_1)]));

	prototype.name("function prototype");
	function.name("function rule");

	/*
	qi::on_error<qi::fail>
	    (
	        prototype
	      , std::cout
	            << phx::val("Error! Expecting ")
	            << qi::_4                               // what failed?
	             << std::endl
	    );
	qi::on_error<qi::fail>
	    (
	        function
	      , std::cout
	            << phx::val("Error! Expecting ")
	            << qi::_4                               // what failed?
	            << std::endl
	    );
	*/
}

GFunction::~GFunction()
{
	//destructor
}
