// Project: CGear
//
//  Created on: 23.03.2016
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef AST_OPERATIONS_CODE_H_
#define AST_OPERATIONS_CODE_H_

#include <string>
#include "operation.h"

#define OPERATION(X)                  \
    X(assign, "=")                    \
    X(addition_and_assign, "+=")      \
    X(subtraction_and_assign, "-=")   \
    X(multiplication_and_assign, "*=")\
    X(division_and_assign, "/=")      \
    X(modulo_and_assign, "%=")        \
                                      \
    X(equal, "==")                    \
    X(not_equal, "!=")                \
                                      \
    X(addition, "+")                  \
    X(subtraction, "-")               \
                                      \
    X(multiplication, "*")            \
    X(division, "/")                  \
    X(modulo, "%")                    \

constexpr unsigned int OPERATION_COUNT() {
#define ForOperation(operation, Str) operation,
enum {
	OPERATION(ForOperation)
	OPERATION_COUNT
};
#undef ForOperation
	return OPERATION_COUNT;
}

#define EnumOperation(Operation, Str) static code Operation;
class ast::operation::code
{
    int value;
private:
    code(int c): value(c) {}
public:
    OPERATION(EnumOperation)

	static constexpr const unsigned int count = OPERATION_COUNT();
public:
    code(const code& other): value(other.value) {}
    code& operator = (const code& other) {
    	value = other.value;
        return *this;
    }
    bool operator == (const code& other) const { return this->value == other.value; }
    bool operator <  (const code& other) const { return this->value  < other.value; }
    const std::string& to_string() const;
    operator const std::string&() const {
        return to_string();
    }
};
#undef EnumOperation

#endif /* AST_OPERATIONS_CODE_H_ */
