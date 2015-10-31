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

#include "binary.h"
#include "call.h"
#include "ternary.h"
#include "unary.h"
#include "variable.h"
#include "literal.h"

pool<sizeof(ast::operation::binary::implementation)>   ast::operation::binary::memory_pool;
pool<sizeof(ast::operation::call::implementation)>     ast::operation::call::memory_pool;
pool<sizeof(ast::operation::ternary::implementation)>  ast::operation::ternary::memory_pool;
pool<sizeof(ast::operation::unary::implementation)>    ast::operation::unary::memory_pool;
pool<sizeof(ast::operation::variable::implementation)> ast::operation::variable::memory_pool;
pool<sizeof(ast::operation::literal::implementation)>  ast::operation::literal::memory_pool;

#include "visitor.h"

void ast::operation::unary::implementation::accept(ast::operation::visitor& v) { v.visit(*this); }
void ast::operation::binary::implementation::accept(ast::operation::visitor& v) { v.visit(*this); }
void ast::operation::ternary::implementation::accept(ast::operation::visitor& v) { v.visit(*this); }
//void ast::operation::type_cast::implementation::accept(ast::operation::visitor& v) { v.visit(*this); }
void ast::operation::variable::implementation::accept(ast::operation::visitor& v) { v.visit(*this); }
//void ast::operation::index::implementation::accept(ast::operation::visitor& v) { v.visit(*this); }
//void ast::operation::section::implementation::accept(ast::operation::visitor& v) { v.visit(*this); }
void ast::operation::call::implementation::accept(ast::operation::visitor& v) { v.visit(*this); }
//void ast::operation::array::implementation::accept(ast::operation::visitor& v) { v.visit(*this); }
void ast::operation::literal::implementation::accept(ast::operation::visitor& v) { v.visit(*this); }
