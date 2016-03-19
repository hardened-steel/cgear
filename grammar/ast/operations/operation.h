// Project: CGear
//
//  Created on: 01.08.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef OPERATION_H
#define OPERATION_H

#include "grammar/ast/instance.h"
#include "grammar/ast/pool.h"
#include "grammar/ast/ast.h"
#include <string>

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
	X(function_call, "()")            \

constexpr unsigned int OPERATION_COUNT() {
#define ForOperation(operation, Str) operation,
enum {
	OPERATION(ForOperation)
	OPERATION_COUNT
};
#undef ForOperation
	return OPERATION_COUNT;
}

class ast::operation: public ast::node
{
public:
	class visitor;
	class binary;
	class variable;
	class call;
	class literal;
	class code;
	using instance = instance_t<ast::operation>;
public:
	virtual void accept(ast::operation::visitor& v) const;
	virtual ~operation() {}
};

#define EnumOperation(Operation, Str) static code Operation;
class ast::operation::code
{
    int value;
    
    code(int c): value(c) {}

    const std::string& getStr() const;
public:
    OPERATION(EnumOperation)

	static constexpr const unsigned int count = OPERATION_COUNT();
    
    code(const code& other): value(other.value) {}
    code& operator = (const code& other) {
    	value = other.value;
        return *this;
    }
    bool operator == (const code& other) const { return this->value == other.value; }
    bool operator <  (const code& other) const { return this->value  < other.value; }
    operator const std::string&() const {
        return getStr();
    }
};
#undef EnumOperation

#endif // OPERATION_H
