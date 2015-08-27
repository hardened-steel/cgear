#include "tree.h"
#include "context.h"

class element: public st::type::common
{
public:
    st::type type_;
    std::string index;
    virtual bool operator == (const st::type::common& other) const {
        /*
        const element* other_ptr = dynamic_cast<const element*>(&other);

        if(other_ptr == nullptr) return false;
        return type_ == other_ptr->type_;
        */
        return *(type_.get()) == other;
    }
    virtual std::string print() const {
        return type_.print();
    }
public:
    element(const st::type& t, bool left_assign, const std::string& index): st::type::common(left_assign), type_(t), index(index) {}
};

static unsigned label_index = 0;
static unsigned expression_index = 0;
std::string get_type_str(const st::type& t, bool create = false) {
    if(create) {
        if(st::type::base* type = dynamic_cast<st::type::base*>(t.get())) {
            switch(type->get_code()) {
            case st::type::base::int_:
                return "I";
            case st::type::base::real:
                return "F";
            case st::type::base::char_:
                return "C";
            case st::type::base::bool_:
                return "I";
            }
        }
        return "I";
    } else {
        if(st::type::base* type = dynamic_cast<st::type::base*>(t.get())) {
            switch(type->get_code()) {
            case st::type::base::int_:
                return "i";
            case st::type::base::real:
                return "f";
            case st::type::base::char_:
                return "c";
            case st::type::base::bool_:
                return "i";
            }
        }
    }
    if(st::type::array* array_type = dynamic_cast<st::type::array*>(t.get())) {
        if(st::type::base* type = dynamic_cast<st::type::base*>(array_type->get_array_type().get())) {
            switch(type->get_code()) {
            case st::type::base::int_:
                return "AI";
            case st::type::base::real:
                return "AF";
            case st::type::base::char_:
                return "AC";
            case st::type::base::bool_:
                return "AI";
            }
        }
    }
    if(element* element_type = dynamic_cast<element*>(t.get())) {
        if(st::type::base* type = dynamic_cast<st::type::base*>(element_type->type_.get())) {
            switch(type->get_code()) {
            case st::type::base::int_:
                return "AI";
            case st::type::base::real:
                return "AF";
            case st::type::base::char_:
                return "AC";
            case st::type::base::bool_:
                return "AI";
            }
        }
    }
}

// operation
st::type st::operation::binary::getCode(std::ostream &out, st::context &c, std::string &result) const {
    std::string operation = op;
    std::string typeStr;
    std::string left_operand("$left_operand_" + std::to_string(expression_index)), right_operand("$right_operand_" + std::to_string(expression_index));
    expression_index += 1;
    st::type left_type = left.getCode(out, c, left_operand);
    st::type right_type = right.getCode(out, c, right_operand);
    st::type return_type = right_type;

    if(op == Operation::assign) {
        if(!left_type.isAssignable()) throw std::logic_error("left operand is not assignable");
        if(element* e = dynamic_cast<element*>(right_type.get())) {
            typeStr = get_type_str(right_type);
            out << "(get" << typeStr << "," << right_operand << "," << e->index << "," << "$array_access_" + std::to_string(expression_index) << ")\n";
            out << "(rdAE" << typeStr[1] << "," << "$array_access_" + std::to_string(expression_index) << ",," << "$array_access_" + std::to_string(expression_index + 1) << "," << ")\n";
            right_operand = "$array_access_" + std::to_string(expression_index + 1);
            expression_index += 2;
            return_type = e->type_;
            return_type.setAssignable(false);
        }
        if(element* e = dynamic_cast<element*>(left_type.get())) {
            typeStr = get_type_str(left_type);
            out << "(get" << typeStr << "," << left_operand << "," << e->index << "," << "$array_access_" + std::to_string(expression_index) << ")\n";
            out << "(wrAE" << typeStr[1] << "," << "$array_access_" + std::to_string(expression_index) << "," << right_operand << "," << ")\n";
            expression_index += 1;
        } else {
            if(left_type != right_type) throw std::logic_error("different types of operands in operation \"" + operation + "\"(" + left_type.print() + " " + left_operand + "," + right_type.print() + " " + right_operand + ")");
            std::string typeStr = get_type_str(left_type);
            if((typeStr == "AC") && (get_type_str(right_type) == "AC")) {
                out << "(" << "i" << "Eq" << "," << right_operand << "," << "," << (result = left_operand) << ")\n";
            } else out << "(" << typeStr << "Eq" << "," << right_operand << "," << "," << (result = left_operand) << ")\n";
        }
        return return_type;
    }
    if(op == Operation::addition_and_assign) {
        if(!left_type.isAssignable()) throw std::logic_error("left operand is not assignable");
        if(element* e = dynamic_cast<element*>(right_type.get())) {
            typeStr = get_type_str(right_type);
            out << "(get" << typeStr << "," << right_operand << "," << e->index << "," << "$array_access_" + std::to_string(expression_index) << ")\n";
            out << "(rdAE" << typeStr[1] << "," << "$array_access_" + std::to_string(expression_index) << ",," << "$array_access_" + std::to_string(expression_index + 1) << "," << ")\n";
            right_operand = "$array_access_" + std::to_string(expression_index + 1);
            expression_index += 2;
            return_type = e->type_;
            return_type.setAssignable(false);
        }
        if(element* e = dynamic_cast<element*>(left_type.get())) {
            typeStr = get_type_str(left_type);
            out << "(get" << typeStr << "," << left_operand << "," << e->index << "," << "$array_access_" + std::to_string(expression_index) << ")\n";
            out << "(wrAE" << typeStr[1] << "," << "$array_access_" + std::to_string(expression_index) << "," << right_operand << "," << ")\n";
            expression_index += 1;
        } else {
            if(left_type != right_type) throw std::logic_error("different types of operands in operation \"" + operation + "\"(" + left_type.print() + " " + left_operand + "," + right_type.print() + " " + right_operand + ")");
            std::string typeStr = get_type_str(left_type);
            if((typeStr == "AC") && (get_type_str(right_type) == "AC")) {
                out << "(" << "ldPrm" << "," << left_operand << ")\n";
                out << "(" << "ldPrm" << "," << right_operand << ")\n";
                out << "(" << "concat" << ",,," << result << ")\n";
                out << "(" << "i" << "Eq" << "," << result << "," << "," << left_operand << ")\n";
            } else out << "(" << typeStr << "+" << "," << left_operand << "," << right_operand << "," << (result = left_operand) << ")\n";
        }
        return return_type;
    }
    if(op == Operation::division_and_assign) {
        if(!left_type.isAssignable()) throw std::logic_error("left operand is not assignable");
        if(element* e = dynamic_cast<element*>(right_type.get())) {
            typeStr = get_type_str(right_type);
            out << "(get" << typeStr << "," << right_operand << "," << e->index << "," << "$array_access_" + std::to_string(expression_index) << ")\n";
            out << "(rdAE" << typeStr[1] << "," << "$array_access_" + std::to_string(expression_index) << ",," << "$array_access_" + std::to_string(expression_index + 1) << "," << ")\n";
            right_operand = "$array_access_" + std::to_string(expression_index + 1);
            expression_index += 2;
            return_type = e->type_;
            return_type.setAssignable(false);
        }
        if(element* e = dynamic_cast<element*>(left_type.get())) {
            typeStr = get_type_str(left_type);
            out << "(get" << typeStr << "," << left_operand << "," << e->index << "," << "$array_access_" + std::to_string(expression_index) << ")\n";
            out << "(wrAE" << typeStr[1] << "," << "$array_access_" + std::to_string(expression_index) << "," << right_operand << "," << ")\n";
            expression_index += 1;
        } else {
            if(left_type != right_type) throw std::logic_error("different types of operands in operation \"" + operation + "\"(" + left_type.print() + " " + left_operand + "," + right_type.print() + " " + right_operand + ")");
            std::string typeStr = get_type_str(left_type);
            if(typeStr[0] == 'A') throw std::logic_error("array operations not support");

            out << "(" << typeStr << "/" << "," << left_operand << "," << right_operand << "," << (result = left_operand) << ")\n";
        }
        return return_type;
    }
    if(op == Operation::multiplication_and_assign) {
        if(!left_type.isAssignable()) throw std::logic_error("left operand is not assignable");
        if(element* e = dynamic_cast<element*>(right_type.get())) {
            typeStr = get_type_str(right_type);
            out << "(get" << typeStr << "," << right_operand << "," << e->index << "," << "$array_access_" + std::to_string(expression_index) << ")\n";
            out << "(rdAE" << typeStr[1] << "," << "$array_access_" + std::to_string(expression_index) << ",," << "$array_access_" + std::to_string(expression_index + 1) << "," << ")\n";
            right_operand = "$array_access_" + std::to_string(expression_index + 1);
            expression_index += 2;
            return_type = e->type_;
            return_type.setAssignable(false);
        }
        if(element* e = dynamic_cast<element*>(left_type.get())) {
            typeStr = get_type_str(left_type);
            out << "(get" << typeStr << "," << left_operand << "," << e->index << "," << "$array_access_" + std::to_string(expression_index) << ")\n";
            out << "(wrAE" << typeStr[1] << "," << "$array_access_" + std::to_string(expression_index) << "," << right_operand << "," << ")\n";
            expression_index += 1;
        } else {
            if(left_type != right_type) throw std::logic_error("different types of operands in operation \"" + operation + "\"(" + left_type.print() + " " + left_operand + "," + right_type.print() + " " + right_operand + ")");
            std::string typeStr = get_type_str(left_type);
            if(typeStr[0] == 'A') throw std::logic_error("array operations not support");

            out << "(" << typeStr << "*" << "," << left_operand << "," << right_operand << "," << (result = left_operand) << ")\n";
        }
        return return_type;
    }
    if(op == Operation::subtraction_and_assign) {
        if(!left_type.isAssignable()) throw std::logic_error("left operand is not assignable");
        if(element* e = dynamic_cast<element*>(right_type.get())) {
            typeStr = get_type_str(right_type);
            out << "(get" << typeStr << "," << right_operand << "," << e->index << "," << "$array_access_" + std::to_string(expression_index) << ")\n";
            out << "(rdAE" << typeStr[1] << "," << "$array_access_" + std::to_string(expression_index) << ",," << "$array_access_" + std::to_string(expression_index + 1) << "," << ")\n";
            right_operand = "$array_access_" + std::to_string(expression_index + 1);
            expression_index += 2;
            return_type = e->type_;
            return_type.setAssignable(false);
        }
        if(element* e = dynamic_cast<element*>(left_type.get())) {
            typeStr = get_type_str(left_type);
            out << "(get" << typeStr << "," << left_operand << "," << e->index << "," << "$array_access_" + std::to_string(expression_index) << ")\n";
            out << "(wrAE" << typeStr[1] << "," << "$array_access_" + std::to_string(expression_index) << "," << right_operand << "," << ")\n";
            expression_index += 1;
        } else {
            if(left_type != right_type) throw std::logic_error("different types of operands in operation \"" + operation + "\"(" + left_type.print() + " " + left_operand + "," + right_type.print() + " " + right_operand + ")");
            std::string typeStr = get_type_str(left_type);
            if(typeStr[0] == 'A') throw std::logic_error("array operations not support");

            out << "(" << typeStr << "-" << "," << left_operand << "," << right_operand << "," << (result = left_operand) << ")\n";
        }
        return return_type;
    }
    if(element* e = dynamic_cast<element*>(right_type.get())) {
        typeStr = get_type_str(right_type);
        out << "(get" << typeStr << "," << right_operand << "," << e->index << "," << "$array_access_" + std::to_string(expression_index) << ")\n";
        out << "(rdAE" << typeStr[1] << "," << "$array_access_" + std::to_string(expression_index) << ",," << "$array_access_" + std::to_string(expression_index + 1) << "," << ")\n";
        right_operand = "$array_access_" + std::to_string(expression_index + 1);
        expression_index += 2;
        return_type = e->type_;
        return_type.setAssignable(false);
    }
    if(element* e = dynamic_cast<element*>(left_type.get())) {
        typeStr = get_type_str(left_type);
        out << "(get" << typeStr << "," << left_operand << "," << e->index << "," << "$array_access_" + std::to_string(expression_index) << ")\n";
        out << "(rdAE" << typeStr[1] << "," << "$array_access_" + std::to_string(expression_index) << ",," << "$array_access_" + std::to_string(expression_index + 1) << "," << ")\n";
        right_operand = "$array_access_" + std::to_string(expression_index + 1);
        expression_index += 2;
    }
    if(left_type != right_type) throw std::logic_error("different types of operands in operation \"" + operation + "\"(" + left_type.print() + " " + left_operand + "," + right_type.print() + " " + right_operand + ")");
    typeStr = get_type_str(left_type);
    if(op == Operation::addition) if((typeStr == "AC") && (get_type_str(right_type) == "AC")) {
        out << "(" << "ldPrm" << "," << left_operand << ")\n";
        out << "(" << "ldPrm" << "," << right_operand << ")\n";
        out << "(" << "concat" << ",,," << result << ")\n";
        return new st::type::array(new st::type::base(st::type::base::char_, false), false);
    }
    if(typeStr[0] == 'A') throw std::logic_error("array operations not support");

    if((op == Operation::less)||(op == Operation::less_or_equal)||(op == Operation::equal)||(op == Operation::not_equal)||(op == Operation::more)||(op == Operation::more_or_equal)) return_type = new st::type::base(st::type::base::int_, false);
    if(op == Operation::modulo) if(typeStr != "i") throw std::logic_error("modulo can calc with int type only");
    out << "(" << typeStr << operation << "," << left_operand << "," << right_operand << "," << result << ")\n";
    return return_type;
}

st::type st::operation::boolLiteral::getCode(std::ostream &out, st::context &c, std::string& result) const {
    const bool& value = this->value;
    result = "&bool_literal_" + value?"true":"false";
    st::type t = new st::type::base(st::type::base::bool_, false);
    if(!c.find_name(result)) {
        c.add_name(result, t);
        out << "(" << "newI" << "," << result << "," << value << ",)\n";
    }
    return t;
}

st::type st::operation::call::getCode(std::ostream &out, st::context &c, std::string &result) const {
    const std::string& function = this->function;
    if(function == "write") {
        if(parameters.size() == 1);
        std::string str = "$string_param_" + std::to_string(expression_index++);

        st::type str_type = parameters[0].getCode(out, c, str);
        if(get_type_str(str_type) != "AC") throw std::logic_error("function write: 1 parameter must be a array of char");

        out << "(wrtCn," << str << ",,)\n";
        return new st::type::base(st::type::base::void_, false);
    }
    if(function == "read") {
        if(parameters.size() == 0);
        out << "(rdCn,,," << result << ")\n";
        return new st::type::array(new st::type::base(st::type::base::char_, false), false);
    }
    if(function == "find") {
        if(parameters.size() == 2);
        std::string substr = "$string_param_" + std::to_string(expression_index++);
        std::string str = "$string_param_" + std::to_string(expression_index++);

        st::type substr_type = parameters[1].getCode(out, c, substr);
        if(get_type_str(substr_type) != "AC") throw std::logic_error("function find: 2 parameter must be a array of char");

        st::type str_type = parameters[0].getCode(out, c, str);
        if(get_type_str(str_type) != "AC") throw std::logic_error("function find: 1 parameter must be a array of char");

        out << "(ldPrm," << str << ",,)\n";
        out << "(ldPrm," << substr << ",,)\n"; 
        out << "(fSubStr,,," << result << ")\n";
        return new st::type::base(st::type::base::int_, false);
    }
    if(function == "replace") {
        if(parameters.size() == 3);
        std::string old_substr = "$string_param_" + std::to_string(expression_index++);
        std::string new_substr = "$string_param_" + std::to_string(expression_index++);
        std::string str = "$string_param_" + std::to_string(expression_index++);

        st::type old_substr_type = parameters[1].getCode(out, c, old_substr);
        if(get_type_str(old_substr_type) != "AC") throw std::logic_error("function replace: 2 parameter must be a array of char");

        st::type new_substr_type = parameters[2].getCode(out, c, new_substr);
        if(get_type_str(new_substr_type) != "AC") throw std::logic_error("function replace: 3 parameter must be a array of char");

        st::type str_type = parameters[0].getCode(out, c, str);
        if(get_type_str(str_type) != "AC") throw std::logic_error("function replace: 1 parameter must be a array of char");

        out << "(ldPrm," << old_substr << ",,)\n";
        out << "(ldPrm," << new_substr << ",,)\n";
        out << "(ldPrm," << str << ",,)\n";
        out << "(replace,,," << result << ")\n";
        return str_type;
    }
    if(function == "substring") {
        if(parameters.size() != 3) throw std::logic_error("function substring takes 3 arguments");
        std::string str = "$string_param_" + std::to_string(expression_index++);
        std::string length = "$length_param_" + std::to_string(expression_index++);
        std::string index = "$index_param_" + std::to_string(expression_index++);

        st::type str_type = parameters[0].getCode(out, c, str);
        if(get_type_str(str_type) != "AC") throw std::logic_error("function substring: 1 parameter must be a array of char");

        st::type length_type = parameters[2].getCode(out, c, length);
        if(get_type_str(length_type) != "i") throw std::logic_error("function substring: 3 parameter must be a integer type");

        st::type index_type = parameters[1].getCode(out, c, index);
        if(get_type_str(index_type) != "i") throw std::logic_error("function substring: 2 parameter must be a integer type");

        out << "(ldPrm," << str << ",,)\n";
        out << "(ldPrm," << length << ",,)\n";
        out << "(ldPrm," << index << ",,)\n";
        out << "(substring,,," << result << ")\n";
        return new st::type::array(new st::type::base(st::type::base::char_, false), false);
    }
    throw std::logic_error("function not found");
}

void getIndex(int i, std::ostream &out, st::context &c, std::string &result) {
    const int& value = i;
    result = "&integer_literal_" + std::to_string(value);
    st::type t = new st::type::base(st::type::base::int_, false);
    if(!c.find_name(result)) {
        c.add_name(result, t);
        out << "(" << "newI" << "," << result << "," << value << ",)\n";
    }
}

st::type st::operation::intLiteral::getCode(std::ostream &out, st::context &c, std::string &result) const {
    const int& value = this->value;
    result = "&integer_literal_" + std::to_string(value);
    st::type t = new st::type::base(st::type::base::int_, false);
    if(!c.find_name(result)) {
        c.add_name(result, t);
        out << "(" << "newI" << "," << result << "," << value << ",)\n";
    }
    return t;
}

void get_one(std::ostream &out, st::context &c, std::string &result, const std::string& typeStr) {
    if(typeStr == ("i")) {
        result = "&integer_literal_" + std::to_string(1);
        st::type t = new st::type::base(st::type::base::int_, false);
        if(!c.find_name(result)) {
            c.add_name(result, t);
            out << "(" << "newI" << "," << result << "," << "1" << ",)\n";
        }
        return;
    }
    if(typeStr == ("c")) {
        result = "&char_literal_" + std::to_string(1);
        st::type t = new st::type::base(st::type::base::char_, false);
        if(!c.find_name(result)) {
            c.add_name(result, t);
            out << "(" << "newC" << "," << result << "," << "1" << ",)\n";
        }
        return;
    }
    if(typeStr == ("f")) {
        result = "&float_literal_" + std::to_string(1);
        st::type t = new st::type::base(st::type::base::real, false);
        if(!c.find_name(result)) {
            c.add_name(result, t);
            out << "(" << "newF" << "," << result << "," << "1.0" << ",)\n";
        }
        return;
    }
}

st::type st::operation::unary::getCode(std::ostream &out, st::context &c, std::string &result) const {
    if(op == Operation::size_of) {
        std::stringstream ss;
        std::string fake_result;
        std::string typeStr;
        st::type type = expr.getCode(ss, c, fake_result);
        if(element* e = dynamic_cast<element*>(type.get())) typeStr = get_type_str(e->type_);
        typeStr = get_type_str(type);
        int value = 0;
        if(typeStr == "i") value = 4;
        if(typeStr == "c") value = 1;
        if(typeStr == "f") value = 4;
        if(typeStr == "AC") {
            out << ss.str();
            out << "(" << "ldPrm" << "," << fake_result << ",," << ")\n";
            out << "(" << "length" << ",,," << result << ")\n";
            return new st::type::base(st::type::base::int_, false);
        }
        result = "&integer_literal_" + std::to_string(value);
        st::type t = new st::type::base(st::type::base::int_, false);
        if(!c.find_name(result)) {
            c.add_name(result, t);
            out << "(" << "newI" << "," << result << "," << value << ",)\n";
        }
        return t;
    }
    st::type type = expr.getCode(out, c, result);
    std::string typeStr = get_type_str(type);

    if(element* e = dynamic_cast<element*>(type.get())) {
        if(op == Operation::unary_minus) {
            out << "(get" << typeStr << "," << result << "," << e->index << "," << "$array_access_" + std::to_string(expression_index) << ")\n";
            out << "(rdAE" << typeStr[1] << "," << "$array_access_" + std::to_string(expression_index) << ",," << (result = "$array_access_" + std::to_string(expression_index + 1)) << "," << ")\n";
            out << "(" << typeStr << "-" << "," << "0" << "," << result << "," << result << ")\n";
            return e->type_;
        }
        if(op == Operation::suffix_dec) {
            std::string one;
            get_one(out, c, one, typeStr);
            if(!type.isAssignable()) throw std::logic_error("left operand is not assignable");
            out << "(get" << typeStr << "," << result << "," << e->index << "," << "$array_access_" + std::to_string(expression_index) << ")\n";
            out << "(rdAE" << typeStr[1] << "," << "$array_access_" + std::to_string(expression_index) << ",," << "$suffix_dec_" + std::to_string(expression_index) << "," << ")\n";
            out << "(rdAE" << typeStr[1] << "," << "$array_access_" + std::to_string(expression_index) << ",," << (result = "$array_index_" + std::to_string(expression_index)) << "," << ")\n";
            out << "(" << get_type_str(e->type_) << "-" << "," << result << "," << one << "," << result << ")\n";
            out << "(wrAE" << typeStr[1] << "," << "$array_access_" + std::to_string(expression_index) << "," << result << "," << ")\n";
            result = "$suffix_dec_" + std::to_string(expression_index++);
            return e->type_;
        }
        if(op == Operation::suffix_inc) {
            std::string one;
            get_one(out, c, one, typeStr);
            if(!type.isAssignable()) throw std::logic_error("left operand is not assignable");
            out << "(get" << typeStr << "," << result << "," << e->index << "," << "$array_access_" + std::to_string(expression_index) << ")\n";
            out << "(rdAE" << typeStr[1] << "," << "$array_access_" + std::to_string(expression_index) << ",," << "$suffix_inc_" + std::to_string(expression_index) << "," << ")\n";
            out << "(rdAE" << typeStr[1] << "," << "$array_access_" + std::to_string(expression_index) << ",," << (result = "$array_index_" + std::to_string(expression_index)) << "," << ")\n";
            out << "(" << get_type_str(e->type_) << "+" << "," << result << "," << one << "," << result << ")\n";
            out << "(wrAE" << typeStr[1] << "," << "$array_access_" + std::to_string(expression_index) << "," << result << "," << ")\n";
            result = "$suffix_inc_" + std::to_string(expression_index++);
            return e->type_;
        }
        if(op == Operation::prefix_dec) {
            std::string one;
            get_one(out, c, one, typeStr);
            out << "(get" << typeStr << "," << result << "," << e->index << "," << "$array_access_" + std::to_string(expression_index) << ")\n";
            out << "(rdAE" << typeStr[1] << "," << "$array_access_" + std::to_string(expression_index) << ",," << (result = "$suffix_dec_" + std::to_string(expression_index)) << "," << ")\n";
            out << "(" << get_type_str(e->type_) << "-" << "," << result << "," << one << "," << result << ")\n";
            out << "(wrAE" << typeStr[1] << "," << "$array_access_" + std::to_string(expression_index) << "," << result << "," << ")\n";
            return e->type_;
        }
        if(op == Operation::prefix_inc) {
            std::string one;
            out << "(get" << typeStr << "," << result << "," << e->index << "," << "$array_access_" + std::to_string(expression_index) << ")\n";
            out << "(rdAE" << typeStr[1] << "," << "$array_access_" + std::to_string(expression_index) << ",," << (result = "$suffix_inc_" + std::to_string(expression_index)) << "," << ")\n";
            out << "(" << get_type_str(e->type_) << "+" << "," << result << "," << one << "," << result << ")\n";
            out << "(wrAE" << typeStr[1] << "," << "$array_access_" + std::to_string(expression_index) << "," << result << "," << ")\n";
            return e->type_;
        }
        return type;
    } else {
        if(typeStr[0] == 'A') throw std::logic_error("unary operation with array of " + type.print());
        if(op == Operation::unary_minus) {
            out << "(" << typeStr << "-" << "," << "0" << "," << result << "," << result << ")\n";
            return type;
        }
        if(op == Operation::suffix_dec) {
            std::string one;
            get_one(out, c, one, typeStr);
            if(!type.isAssignable()) throw std::logic_error("left operand is not assignable");
            out << "(" << typeStr << "Eq" << "," << result << "," << "," << "$suffix_dec_" + std::to_string(expression_index) << ")\n";
            out << "(" << typeStr << "-" << "," << result << "," << one << "," << result << ")\n";
            result = "$suffix_dec_" + std::to_string(expression_index++);
            return type;
        }
        if(op == Operation::suffix_inc) {
            std::string one;
            get_one(out, c, one, typeStr);
            if(!type.isAssignable()) throw std::logic_error("left operand is not assignable");
            out << "(" << typeStr << "Eq" << "," << result << "," << "," << "$suffix_inc_" + std::to_string(expression_index) << ")\n";
            out << "(" << typeStr << "+" << "," << result << "," << one << "," << result << ")\n";
            result = "$suffix_inc_" + std::to_string(expression_index++);
            return type;
        }
        if(op == Operation::prefix_dec) {
            std::string one;
            get_one(out, c, one, typeStr);
            out << "(" << typeStr << "-" << "," << result << "," << one << "," << result << ")\n";
            return type;
        }
        if(op == Operation::prefix_inc) {
            std::string one;
            get_one(out, c, one, typeStr);
            out << "(" << typeStr << "+" << "," << result << "," << one << "," << result << ")\n";
            return type;
        }
        return type;
    }
}

st::type st::operation::realLiteral::getCode(std::ostream &out, st::context &c, std::string &result) const {
    const float& value = this->value;
    result = "&float_literal_" + std::to_string(value);
    st::type t = new st::type::base(st::type::base::real, false);
    if(!c.find_name(result)) {
        c.add_name(result, t);
        out << "(" << "newF" << "," << result << "," << value << ",)\n";
    }
    return t;
}

static unsigned array_index = 0;

st::type st::operation::stringLiteral::getCode(std::ostream &out, st::context &c, std::string &result) const {
    const std::string& value = this->value;
    std::string element = "&element_" + std::to_string(expression_index++);
    std::string index = "$index_" + std::to_string(expression_index++);
    std::string array_var = "&array_" + std::to_string(array_index++);
    st::type return_type = new st::type::array(new st::type::base(st::type::base::char_, false), false);

    out << "(new" << "AC" << "," << array_var << "," << value.size() <<",)\n";
    //out << "(new" << "C" << "," << element << "," << 0 <<",)\n";
    out << "(init" << "AC" << "," << array_var << ",\'" << value <<"\',)\n";
/*
    for(unsigned i = 0; i < value.size(); ++i) {
        out << "(getAC" << "," << array_var << "," << i << "," << index << ")\n";
        //out << "(cEq" << "," << (int)value[i] << "," << "," << element << ")\n";
        out << "(wrAEC" << "," << index << "," << element << ",)\n";
    }
*/
    result = array_var;
    return return_type;
}

st::type st::operation::ternary::getCode(std::ostream &out, st::context &c, std::string &result) const {
    std::string label("label");
    std::string condition_result = "$condition";

    label += "_" + std::to_string(label_index++);
    st::type type = condition.getCode(out, c, condition_result);
    std::string typeStr = get_type_str(type);
    if(typeStr != "i") throw std::logic_error("condition expression must be int type");
    out << "(jt,if_" + label + "," + condition_result + ",)\n";
    out << "(jmp,if_not" + label + ",,)\n";
    out << "(lbl,if_" + label + ",,)\n";
    st::type true_expr = trueAction.getCode(out, c, result);
    out << "(" << typeStr << "Eq" << "," << result << "," << "," << "$ternary_var_" + std::to_string(expression_index) << ")\n";
    out << "(jmp,end_if" + label + ",,)\n";
    out << "(lbl,if_not" + label + ",,)\n";
    st::type false_expr = falseAction.getCode(out, c, result);
    out << "(" << typeStr << "Eq" << "," << result << "," << "," << "$ternary_var_" + std::to_string(expression_index) << ")\n";
    out << "(lbl,end_if" + label + ",,)\n";
    if(true_expr != false_expr) throw std::logic_error("different types of operands in ternary operation (" + true_expr.print() + "," + false_expr.print() + ")");
    if(true_expr.isAssignable()) return false_expr;
    result = "$ternary_var_" + std::to_string(expression_index++);
    return true_expr;
}

st::type st::operation::var::getCode(std::ostream &out, st::context &c, std::string& result) const {
    const std::string& name = this->id;
    result = name;
    st::type t;
    if(c.find_name(name, &t)) return t;
    else throw std::logic_error("identifier " + name + " not declarated");
}

st::type st::operation::type_cast::getCode(std::ostream &out, st::context &c, std::string &result) const {
    std::string cast_expr = "$cast_expr_" + std::to_string(expression_index++);
    st::type type = op.getCode(out, c, cast_expr);
    std::string type_operation = get_type_str(type);
    std::string type_cast = get_type_str(type_);
    if((type_operation == "i")&&(type_cast == "f")) {
        out << "(iTf," << cast_expr <<",," << result << ")\n";
        return type_;
    }
    if((type_operation == "f")&&(type_cast == "i")) {
        out << "(fTi," << cast_expr <<",," << result << ")\n";
        return type_;
    }
    if((type_operation == "c")&&(type_cast == "i")) {
        out << "(cTi," << cast_expr <<",," << result << ")\n";
        return type_;
    }
    if((type_operation == "i")&&(type_cast == "c")) {
        out << "(iTc," << cast_expr <<",," << result << ")\n";
        return type_;
    }
    if((type_operation == "AC")&&(type_cast == "i")) {
        out << "(sTi," << cast_expr <<",," << result << ")\n";
        return type_;
    }
    if((type_operation == "i")&&(type_cast == "AC")) {
        out << "(new" << "AC" << "," << result << "," << 20 <<",)\n";
        out << "(iTs," << cast_expr <<"," << result << ",)\n";
        return type_;
    }
    if((type_operation == "f")&&(type_cast == "AC")) {
        out << "(new" << "AC" << "," << result << "," << 20 <<",)\n";
        out << "(fTs," << cast_expr <<"," << result << ",)\n";
        return type_;
    }
    throw std::logic_error("cast form " + type_operation + " to " + type_.print() + " not support");
}

st::type st::operation::index::getCode(std::ostream &out, st::context &c, std::string &result) const {
    std::string index = "$index_" + std::to_string(expression_index++);
    st::type type = i.getCode(out, c, index);
    std::string typeStr = get_type_str(type);

    if(typeStr != "i") throw std::logic_error("index must be int type");

    type = array.getCode(out, c, result);
    st::type return_type;
    if(st::type::array* array_type = dynamic_cast<st::type::array*>(type.get())) {
        type = array_type->get_array_type();
        return_type = new element(type, array_type->isAssignable(), index);
        return_type.setIndex(true);
        return return_type;
    } else throw std::logic_error("index operation can use with array type only");
}

st::type st::operation::section::getCode(std::ostream &out, st::context &c, std::string &result) const {

}

st::type st::operation::array::getCode(std::ostream &out, st::context &c, std::string &result) const {
    std::string element = "$element_" + std::to_string(expression_index++);
    std::string index_access = "$index_" + std::to_string(expression_index++);
    std::string array_var = "&array_" + std::to_string(array_index++);
    st::type type = values[0].getCode(out, c, element);
    st::type return_type = new st::type::array(type, false);

    out << "(new" << get_type_str(return_type) << "," << array_var << "," << values.size() <<",)\n";
    getIndex(0, out, c, result);
    out << "(get" << get_type_str(return_type) << "," << array_var << "," << result << "," << index_access << ")\n";
    out << "(wrAE" << get_type_str(return_type)[1] << "," << index_access << "," << element << ",)\n";
    for(unsigned i = 1; i < values.size(); ++i) {
        st::type ntype = values[i].getCode(out, c, element);
        if(ntype != type) throw std::logic_error("different types of array elements");
        getIndex(i, out, c, result);
        out << "(get" << get_type_str(return_type) << "," << array_var << "," << result << "," << index_access << ")\n";
        out << "(wrAE" << get_type_str(return_type)[1] << "," << index_access << "," << element << ",)\n";
    }
    result = array_var;
    return return_type;
}

// instruction
void st::instruction::variable::getCode(std::ostream &out, st::context &c) const {
    const std::string& name = this->name;
    if(!c.find_name(name)) {
        out << "(new" << get_type_str(type_, true) << "," << name << ",0,)\n";
        if(!init.isEmpty()) {
            std::string init_operand("$init_operand");
            st::type init_type = init.getCode(out, c, init_operand);
            std::string typeStr = get_type_str(type_);
            if(init_type != type_) throw std::logic_error("different types of operands in operation \"=\"(" + init_type.print() + "," + type_.print() + ")");
            if(typeStr[0] == 'A') out << "(" << "iEq" << "," << init_operand << "," << "," << name << ")\n";
            else out << "(" << typeStr << "Eq" << "," << init_operand << "," << "," << name << ")\n";
        }
        c.add_name(name, type_);
    } else throw std::logic_error("redefine variable " + name);
}

void st::instruction::calc::getCode(std::ostream &out, st::context &c) const {
    expression_index = 0;
    operation.getCode(out, c);
}

void st::instruction::If::getCode(std::ostream &out, st::context &c) const {
    std::string label("label");
    std::string result = "$condition";
    label += "_" + std::to_string(label_index++);

    st::type type = condition.getCode(out, c, result);
    std::string typeStr = get_type_str(type);
    if(typeStr != "i") throw std::logic_error("condition expression must be int type");
    out << "(jt,if_" + label + "," + result + ",)\n";
    out << "(jmp,if_not" + label + ",,)\n";
    out << "(lbl,if_" + label + ",,)\n";
    action.getCode(out, c);
    out << "(jmp,end_if" + label + ",,)\n";
    out << "(lbl,if_not" + label + ",,)\n";
    if(!else_action.isEmpty()) else_action.getCode(out, c);
    out << "(lbl,end_if" + label + ",,)\n";
}

void st::instruction::block::getCode(std::ostream &out, st::context &c) const {
    c.add_space();
    for(unsigned i = 0; i < instructions.size(); ++i) {
        expression_index = 0;
        instructions[i].getCode(out, c);
    }
    c.remove_space();
}

void st::instruction::While::getCode(std::ostream &out, st::context &c) const {
    std::string label("label");
    std::string result = "$condition";
    label += "_" + std::to_string(label_index++);

    out << "(lbl,continue" + label + ",,)\n";
    st::type type = condition.getCode(out, c, result);
    std::string typeStr = get_type_str(type);
    if(typeStr != "i") throw std::logic_error("condition expression must be int type");
    out << "(jt,if_" + label + "," + result + ",)\n";
    out << "(jmp,if_not" + label + ",,)\n";
    out << "(lbl,if_" + label + ",,)\n";
    action.getCode(out, c);
    out << "(jmp,continue" + label + ",,)\n";
    out << "(lbl,if_not" + label + ",,)\n";
}

void st::instruction::For::getCode(std::ostream &out, st::context &c) const {
    std::string label("label");
    std::string result = "$condition";
    label += "_" + std::to_string(label_index++);

    if(!init.isEmpty()) init.getCode(out, c);
    out << "(lbl,continue" + label + ",,)\n";
    if(condition.isEmpty()) {
        action.getCode(out, c);
        result.clear();
        if(!iterate.isEmpty()) iterate.getCode(out, c, result);
        out << "(jmp,continue" + label + ",,)\n";
    } else {
        st::type type = condition.getCode(out, c, result);
        std::string typeStr = get_type_str(type);
        if(typeStr != "i") throw std::logic_error("condition expression must be int type");
        out << "(jt,if_" + label + "," + result + ",)\n";
        out << "(jmp,if_not" + label + ",,)\n";
        out << "(lbl,if_" + label + ",,)\n";
        action.getCode(out, c);
        result.clear();
        if(!iterate.isEmpty()) iterate.getCode(out, c, result);
        out << "(jmp,continue" + label + ",,)\n";
        out << "(lbl,if_not" + label + ",,)\n";
    }
}

void st::instruction::Return::getCode(std::ostream &out, st::context &c) const {

}

// function
void st::function::getCode(std::ostream &out, st::context &c) const {
    if(const st::function::prototype* pr = boost::get<const st::function::prototype>(&f)) {
        pr->getCode(out, c);
    }
    if(const st::function::definition* def = boost::get<const st::function::definition>(&f)) {
        def->getCode(out, c);
    }
}

void st::function::parameter::getCode(std::ostream &out, st::context &c) const {

}

void st::function::prototype::getCode(std::ostream &out, st::context &c) const {
    const std::string& name = this->name;
    std::vector<st::type> params;
    for(unsigned i = 0; i < parameters.size(); ++i) params.push_back(parameters[i].get_type());
    st::type f = new st::type::function(return_type, params);
    c.add_name(name, f);

    out << "function prototype " << name << "\n";
}

void st::function::definition::getCode(std::ostream &out, st::context &c) const {
    head.getCode(out, c);
    code.getCode(out, c);
}
