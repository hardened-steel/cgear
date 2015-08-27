#include "operation.h"

#define ForOperation(operation, Str) operation,
enum numeration
{
	null = 0,
    OPERATION(ForOperation)
	OPERATION_COUNT
};

const unsigned int operation::count = OPERATION_COUNT;

#define EnumOperation(Operation, Str) operation operation::Operation = numeration::Operation;
OPERATION(EnumOperation)
#undef EnumOperation

#define EnumOperation(Operation, Str) Str,
const std::string operation_str[] = { OPERATION(EnumOperation) };
#undef EnumOperation

const std::string& operation::getStr() const {
    return operation_str[this->code - 1];
}
