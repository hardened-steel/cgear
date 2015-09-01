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
