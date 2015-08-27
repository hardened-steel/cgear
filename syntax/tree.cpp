#include <map>
#include "tree.h"

std::string createJSON(std::string name, std::map<std::string, std::string>& parameters, std::vector<std::string>& contents, unsigned seek) {
    std::string space(seek * 2, ' ');
    std::string json;
    json += space + "{\n";
    json += space + " \"name\" : \"" + name + "\"";
    for(auto& i: parameters) {
        json += ",\n" + space + " \"" + i.first + "\" : \"" + i.second + "\"";
    }
    if(!contents.empty()) {
        json += ",\n" + space + " \"children\":\n";
        json += space + " [\n";
        for(unsigned i = 0; i < contents.size() - 1; ++i) {
            json += contents[i] + space + "  ,\n";
        }
        json += contents[contents.size() - 1];
        json += space + " ]\n";
    } else json += "\n";
    json += space + "}\n";

    return json;
}

std::string st::type::base::print() const {
    switch(code) {
    case void_: return "void";
    case int_ : return "int";
    case real : return "real";
    case bool_: return "bool";
    case char_: return "char";
    }
    return "";
}

std::string st::type::array::print() const {
    return "array<" + base_type.print() + ">";
}

// operations
std::string st::operation::print(unsigned seek) const {
    std::map<std::string, std::string> parameters;
    std::vector<std::string> contents;

    if(op) {
        return op->print(seek);
    } else {
        return createJSON("operation", parameters, contents, seek);
    }
}

std::string st::operation::var::print(unsigned seek) const {
    std::map<std::string, std::string> parameters;
    std::vector<std::string> contents;

    const std::string& id = this->id;
    return createJSON("var " + id, parameters, contents, seek);
}

std::string st::operation::binary::print(unsigned seek) const {
    std::map<std::string, std::string> parameters;
    std::vector<std::string> contents;

    contents.push_back(left.print(seek + 1));
    contents.push_back(right.print(seek + 1));
    const std::string& str = op;
    return createJSON("binary " + str, parameters, contents, seek);
}

std::string st::operation::unary::print(unsigned seek) const {
    std::map<std::string, std::string> parameters;
    std::vector<std::string> contents;

    contents.push_back(expr.print(seek + 1));
    const std::string& str = op;
    return createJSON("unary " + str, parameters, contents, seek);
}

std::string st::operation::call::print(unsigned seek) const {
    std::map<std::string, std::string> parameters;
    std::vector<std::string> contents;

    for(unsigned i = 0; i < this->parameters.size(); ++i) contents.push_back(this->parameters[i].print(seek + 1));
    return createJSON("call", parameters, contents, seek);
}

std::string st::operation::ternary::print(unsigned seek) const {
    std::map<std::string, std::string> parameters;
    std::vector<std::string> contents;

    contents.push_back(condition.print(seek + 1));
    contents.push_back(trueAction.print(seek + 1));
    contents.push_back(falseAction.print(seek + 1));
    return createJSON("ternanry ?", parameters, contents, seek);
}

std::string st::operation::intLiteral::print(unsigned seek) const {
    std::map<std::string, std::string> parameters;
    std::vector<std::string> contents;

    parameters["value"] = std::to_string(value);
    return createJSON("literal int", parameters, contents, seek);
}

std::string st::operation::realLiteral::print(unsigned seek) const {
    std::map<std::string, std::string> parameters;
    std::vector<std::string> contents;

    parameters["value"] = std::to_string(value);
    return createJSON("literal real", parameters, contents, seek);
}

std::string st::operation::boolLiteral::print(unsigned seek) const {
    std::map<std::string, std::string> parameters;
    std::vector<std::string> contents;

    parameters["value"] = value?"true":"false";
    return createJSON("literal bool", parameters, contents, seek);
}

std::string st::operation::stringLiteral::print(unsigned seek) const {
    std::map<std::string, std::string> parameters;
    std::vector<std::string> contents;

    parameters["value"] = value;
    return createJSON("literal string", parameters, contents, seek);
}

std::string st::operation::type_cast::print(unsigned seek) const {
    std::map<std::string, std::string> parameters;
    std::vector<std::string> contents;

    contents.push_back(op.print(seek + 1));
    parameters["type to cast"] = type_.print();
    return createJSON("type cast", parameters, contents, seek);
}

std::string st::operation::index::print(unsigned seek) const {
    std::map<std::string, std::string> parameters;
    std::vector<std::string> contents;

    contents.push_back(array.print(seek + 1));
    contents.push_back(i.print(seek + 1));
    return createJSON("operation []", parameters, contents, seek);
}

std::string st::operation::section::print(unsigned seek) const {
    std::map<std::string, std::string> parameters;
    std::vector<std::string> contents;

    contents.push_back(array.print(seek + 1));
    contents.push_back(first.print(seek + 1));
    contents.push_back(last.print(seek + 1));
    return createJSON("operation [:]", parameters, contents, seek);
}

std::string st::operation::array::print(unsigned seek) const {
    std::map<std::string, std::string> parameters;
    std::vector<std::string> contents;

    for(unsigned i = 0; i < values.size(); ++i) contents.push_back(values[i].print(seek + 1));
    return createJSON("array of", parameters, contents, seek);
}

// instructions
std::string st::instruction::print(unsigned seek) const {
    std::map<std::string, std::string> parameters;
    std::vector<std::string> contents;

    if(instr) {
        return instr->print(seek);
    } else {
        return createJSON("instruction", parameters, contents, seek);
    }
}

std::string st::instruction::block::print(unsigned seek) const {
    std::map<std::string, std::string> parameters;
    std::vector<std::string> contents;

    for(unsigned i = 0; i < instructions.size(); ++i) contents.push_back(instructions[i].print(seek + 1));
    return createJSON("block", parameters, contents, seek);
}

std::string st::instruction::calc::print(unsigned seek) const {
    std::map<std::string, std::string> parameters;
    std::vector<std::string> contents;

    contents.push_back(operation.print(seek + 1));
    return createJSON("calc", parameters, contents, seek);
}

std::string st::instruction::If::print(unsigned seek) const {
    std::map<std::string, std::string> parameters;
    std::vector<std::string> contents;

    contents.push_back(condition.print(seek + 1));
    contents.push_back(action.print(seek + 1));
    if(!else_action.isEmpty()) contents.push_back(else_action.print(seek + 1));
    return createJSON("if", parameters, contents, seek);
}

std::string st::instruction::variable::print(unsigned seek) const {
    std::map<std::string, std::string> parameters;
    std::vector<std::string> contents;

    parameters["type code"] = type_.print();
    parameters["id"] = name;
    if(!init.isEmpty()) contents.push_back(init.print(seek + 1));
    return createJSON("local variable", parameters, contents, seek);
}

std::string st::instruction::For::print(unsigned seek) const {
    std::map<std::string, std::string> parameters;
    std::vector<std::string> contents;

    if(!init.isEmpty()) contents.push_back(init.print(seek + 1));
    if(!condition.isEmpty()) contents.push_back(condition.print(seek + 1));
    if(!iterate.isEmpty()) contents.push_back(iterate.print(seek + 1));
    contents.push_back(action.print(seek + 1));
    return createJSON("for", parameters, contents, seek);
}

std::string st::instruction::While::print(unsigned seek) const {
    std::map<std::string, std::string> parameters;
    std::vector<std::string> contents;

    contents.push_back(condition.print(seek + 1));
    contents.push_back(action.print(seek + 1));
    return createJSON("while", parameters, contents, seek);
}

std::string st::instruction::Return::print(unsigned seek) const {
    std::map<std::string, std::string> parameters;
    std::vector<std::string> contents;

    contents.push_back(operation.print(seek + 1));
    return createJSON("return", parameters, contents, seek);
}

class function_visitor : public boost::static_visitor<std::string>
{
    unsigned seek;
public:
    function_visitor(unsigned seek): seek(seek) {}
    std::string operator()(const st::function::definition & def) const
    {
        return def.print(seek);
    }

    std::string operator()(const st::function::prototype & pr) const
    {
        return pr.print(seek);
    }
};

std::string st::function::print(unsigned seek) const {
    return boost::apply_visitor(function_visitor(seek), f);
}

std::string st::function::definition::print(unsigned seek) const {
    std::map<std::string, std::string> parameters;
    std::vector<std::string> contents;

    contents.push_back(head.print(seek + 1));
    contents.push_back(code.print(seek + 1));
    return createJSON("function define", parameters, contents, seek);
}

std::string st::function::prototype::print(unsigned seek) const {
    std::map<std::string, std::string> parameters;
    std::vector<std::string> contents;

    parameters["return type code"] = return_type.print();
    parameters["id"] = name;
    for(unsigned i = 0; i < this->parameters.size(); ++i) contents.push_back(this->parameters[i].print(seek + 1));
    return createJSON("function prototype", parameters, contents, seek);
}

std::string st::function::parameter::print(unsigned seek) const {
    std::map<std::string, std::string> parameters;
    std::vector<std::string> contents;

    parameters["type code"] = type_.print();
    parameters["id"] = name;
    return createJSON("function parameter", parameters, contents, seek);
}
