// Project: CGear
//
//  Created on: 03.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#include <boost/phoenix/phoenix.hpp>
#include "statement.h"
#include "type.h"
#include "function.h"
#include "instruction.h"
#include "expression.h"
#include "module.h"

class GModule::implementation
{
public:
	GTypeName typeName;
	GType type;
	GExpression expression;
	GInstruction instruction;
	GFunction function;
	GStatement statement;
public:
	implementation(Lexer& lexer)
	: typeName(lexer), type(lexer, typeName), expression(lexer, typeName)
	, instruction(lexer, expression, type), function(lexer, instruction, typeName)
	, statement(lexer, function, expression, type)
	{}
};

GModule::GModule(Lexer& lexer): GModule::base_type(module, "module"), impl(new GModule::implementation(lexer))
{
	namespace qi = boost::spirit::qi;
	namespace phx = boost::phoenix;

	module = (*(impl->statement))[qi::_val = qi::_1];
}

GModule::~GModule() {

}
