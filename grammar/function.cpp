// Project: CGear
//
//  Created on: 01.08.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#include <boost/phoenix/phoenix.hpp>
#include "function.h"

GFunction::GFunction(Lexer& lexer): GFunction::base_type(function, "function grammar"), instruction(lexer), type(lexer)
{
	namespace qi = boost::spirit::qi;
	namespace phx = boost::phoenix;

	parameter = (type >> lexer.identifier) [qi::_val = phx::construct<st::function::parameter>(qi::_1, qi::_2)];

	prototype = type[qi::_a = qi::_1] >> (lexer.identifier >> lexer.tokens["("]
	          > (parameter % lexer.tokens[","])
	          > lexer.tokens[")"]
	          ) [qi::_val = phx::construct<st::function::prototype>(qi::_1, qi::_a, qi::_2)];

	function = prototype[qi::_a = qi::_1] >> ((lexer.tokens[";"][qi::_val = qi::_a]) | (instruction[qi::_val = phx::construct<st::function::definition>(qi::_a, qi::_1)]));

	parameter.name("function parameter");
	prototype.name("function prototype");
	function.name("function rule");

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
}

GFunction::~GFunction()
{
	//destructor
}
