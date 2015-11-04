// Project: CGear
//
//  Created on: 01.08.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#include "operation.h"

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

const std::string& ast::operation::code::getStr() const {
    return operation_str[this->value - 1];
}

#include "visitor.h"

void ast::operation::unary::accept(ast::operation::visitor& v) { v.visit(*this); }
void ast::operation::binary::accept(ast::operation::visitor& v) { v.visit(*this); }
void ast::operation::ternary::accept(ast::operation::visitor& v) { v.visit(*this); }
//void ast::operation::type_cast::accept(ast::operation::visitor& v) { v.visit(*this); }
void ast::operation::variable::accept(ast::operation::visitor& v) { v.visit(*this); }
//void ast::operation::index::accept(ast::operation::visitor& v) { v.visit(*this); }
//void ast::operation::section::accept(ast::operation::visitor& v) { v.visit(*this); }
void ast::operation::call::accept(ast::operation::visitor& v) { v.visit(*this); }
//void ast::operation::array::accept(ast::operation::visitor& v) { v.visit(*this); }
void ast::operation::literal::accept(ast::operation::visitor& v) { v.visit(*this); }
