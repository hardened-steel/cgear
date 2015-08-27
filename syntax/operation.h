#ifndef OPERATION_H
#define OPERATION_H

#include <string>

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

#define EnumOperation(Operation, Str) static operation Operation;
class operation
{
    int code;
    
    operation(int c): code(c) {}

    const std::string& getStr() const;
public:
    OPERATION(EnumOperation)

	static const unsigned int count;
    
    operation(const operation& other): code(other.code) {}
    operation& operator = (const operation& other) {
        code = other.code;
        return *this;
    }
    bool operator == (const operation& other) const { return this->code == other.code; }
    bool operator <  (const operation& other) const { return this->code  < other.code; }
    operator const std::string&() const {
        return getStr();
    }
};
#undef EnumOperation

#endif // OPERATION_H
