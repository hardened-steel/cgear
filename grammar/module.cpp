// Project: CGear
//
//  Created on: 03.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#include <boost/phoenix/phoenix.hpp>
#include "type.h"
#include "function.h"
#include "instruction.h"
#include "expression.h"
#include "module.h"

class GModule::implementation
{
public:
	GType type;
	GTypeName typeName;
	GExpression expression;
	GInstruction instruction;
	GFunction function;
public:
	implementation(Lexer& lexer):
		type(lexer), typeName(lexer), expression(lexer, typeName), instruction(lexer, expression, type), function(lexer, instruction, typeName)
	{}
};

GModule::GModule(Lexer& lexer): GModule::base_type(module, "module"), impl(new GModule::implementation(lexer))
{
	namespace qi = boost::spirit::qi;
	namespace phx = boost::phoenix;

	GType& type               = impl->type;
	GFunction& function       = impl->function;

	module = (*(function | type))[qi::_val = qi::_1];
}

GModule::~GModule() {

}
