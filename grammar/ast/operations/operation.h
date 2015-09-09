// Project: CGear
//
//  Created on: 01.08.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef OPERATION_H
#define OPERATION_H

#include "../pool.h"
#include "../ast.h"
#include <string>
#include <memory>

#define OPERATION(X) \
	X(assign, "=")\
	X(addition_and_assign, "+=")\
	X(subtraction_and_assign, "-=")\
	X(multiplication_and_assign, "*=")\
	X(division_and_assign, "/=")\
	X(modulo_and_assign, "%=")\
	\
	X(ternary, "?")\
	\
	X(equal, "==")\
	X(not_equal, "!=")\
	\
	X(less, "<")\
	X(less_or_equal, "<=")\
	X(more, ">")\
	X(more_or_equal, ">=")\
	\
	X(addition, "+")\
	X(subtraction, "-")\
	\
	X(multiplication, "*")\
	X(division, "/")\
	X(modulo, "%")\
	\
	X(unary_plus, "+")\
	X(unary_minus,"-")\
	X(prefix_inc, "++")\
	X(prefix_dec, "--")\
	X(size_of,"sizeof")\
	\
	X(suffix_inc, "++")\
	X(suffix_dec, "++")\
	X(function_call, "()")

constexpr unsigned int OPERATION_COUNT() {
#define ForOperation(operation, Str) operation,
enum {
	OPERATION(ForOperation)
	OPERATION_COUNT
};
#undef ForOperation
	return OPERATION_COUNT;
}

class ast::operation: public ast
{
public:
	class base
	{
	public:
		virtual ~base() {}
	};
	class unary;
	class binary;
	class ternary;
	class type_cast;
	class variable;
	class index;
	class section;
	class call;
	class array;
	class literal;
	class code;
public:
	operation(): impl(nullptr) {}
	operation(operation&& other): impl(std::move(other.impl)) {}
	operation(const operation& other): impl(other.impl) {}
	template<typename T> operation(T&& other): impl(std::move(other.impl)) {}
	template<typename T> operation(const T& other): impl(other.impl) {}
	template<typename T> operation& operator=(T&& other) {
		this->impl = std::move(other.impl);
		return *this;
	}
	template<typename T> operation& operator=(const T& other) {
		this->impl = other.impl;
		return *this;
	}
private:
	std::shared_ptr<base> impl;
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
