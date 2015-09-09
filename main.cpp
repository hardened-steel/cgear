#include <iostream>
#include <fstream>
#include <exception>
#include <sstream>

#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix/phoenix.hpp>
#include "lexer/lexer.h"
#include "syntax/tree.h"
#include "grammar/function.h"

void tokenize_and_parse(std::istream& in, std::ostream& out) {
	namespace lex = boost::spirit::lex;
	namespace phx = boost::phoenix;
	namespace qi = boost::spirit::qi;

	boost::spirit::istream_iterator f_begin(in), f_end;
	Iterator lp_begin(f_begin), lp_end(f_end);
	try {
		AttributeFactory factory;
		Lexer lexer(&factory);

		//GFunction function(lexer);
		//std::vector<st::function> functions;
		GInstruction instruction(lexer);
		st::instruction instr;

		bool res = lex::tokenize_and_phrase_parse(lp_begin, lp_end, lexer, instruction, qi::in_state("WS")[lexer.self], instr);
		if(res && lp_begin == lp_end) std::cout << std::endl; else {
			std::string rest(lp_begin, lp_end);
			std::cout << "Pasring failed, returned value: " << std::boolalpha << res << "\n" << "stopped at: \"" << rest << "\"" << std::endl;
		}
		{
			std::map<std::string, std::string> parameters;
			std::vector<std::string> contents;

			//for(int i = 0; i < functions.size(); ++i) contents.push_back(functions[i].print(1));
			contents.push_back(instr.print(1));
			json << createJSON("module", parameters, contents, 0);
		}
		{
			st::context context;
			code << "(prgStart,,,)\n";
			//for(int i = 0; i < functions.size(); ++i) functions[i].getCode(code, context);
			instr.getCode(code, context);
			code << "(prgEnd,,,)\n";
		}
		tables << "indentifiers:\n";
		for(const std::string& identifier: factory.identifier_table) {
			tables << "\t" << identifier << "\n";
		}
		tables << "integer constants:\n";
		for(const token::int_type& value: factory.integer_constant_table) {
			tables << "\t" << value << "\n";
		}
		tables << "real constants:\n";
		for(const token::real_type& value: factory.real_constant_table) {
			tables << "\t" << value << "\n";
		}
		std::cout << "success" << std::endl;
	} catch(std::exception& e) {
		std::string rest(lp_begin, lp_end);
		std::cout << "Pasring failed: " << e.what() << "\n" << "stopped at: \"" << rest << "\"" << std::endl;
	}
}

int main(int argc, char* argv[]) {
	namespace lex = boost::spirit::lex;
	namespace phx = boost::phoenix;
	namespace qi = boost::spirit::qi;

	for(int i = 1; i < argc; ++i) {
		std::ifstream in(argv[i]);
		std::ifstream out(argv[i]);
		in.unsetf(std::ios::skipws);
		tokenize_and_parse(in, out);
	}
}

