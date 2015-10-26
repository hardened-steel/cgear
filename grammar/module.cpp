// Project: CGear
//
//  Created on: 03.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#include <boost/phoenix/phoenix.hpp>
#include "module.h"

GModule::GModule(Lexer& lexer): GModule::base_type(module, "module"),
	type(lexer), typeName(lexer), expression(lexer, typeName), instruction(lexer, expression, type), function(lexer, instruction, type, typeName)
{
	namespace qi = boost::spirit::qi;
	namespace phx = boost::phoenix;

	module = (*function)[qi::_val = qi::_1];
}
