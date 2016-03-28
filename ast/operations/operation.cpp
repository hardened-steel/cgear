// Project: CGear
//
//  Created on: 01.08.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#include "code.h"

#define ForOperation(operation, Str) operation,
enum numeration
{
	null = 0,
    OPERATION(ForOperation)
};

#define EnumOperation(Operation, Str) ast::operation::code ast::operation::code::Operation = numeration::Operation;
OPERATION(EnumOperation)
#undef EnumOperation

#define EnumOperation(Operation, Str) Str,
const std::string operation_str[] = { OPERATION(EnumOperation) };
#undef EnumOperation

const std::string& ast::operation::code::to_string() const {
    return operation_str[this->value - 1];
}

#include "variable.h"
#include "binary.h"
#include "call.h"

generator::value& ast::operation::variable::codegen(generator::context& context) const {

}

generator::value& ast::operation::binary::codegen(generator::context& context) const {

}

generator::value& ast::operation::call::codegen(generator::context& context) const {

}
