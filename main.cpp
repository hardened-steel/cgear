#include <iostream>
#include <fstream>
#include <exception>
#include <sstream>

#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix/phoenix.hpp>
#include "grammar/lexer/lexer.h"
#include "grammar/lexer/constant_table.h"
#include "grammar/function.h"

void parse_file(std::istream& in, std::ostream& out) {
	namespace lex = boost::spirit::lex;
	namespace phx = boost::phoenix;
	namespace qi = boost::spirit::qi;

	boost::spirit::istream_iterator f_begin(in), f_end;
	token::iterator lp_start(f_begin), lp_begin(f_begin), lp_end(f_end);
	try {
		ConstantTable table;
		Lexer lexer(table);

		//GFunction function(lexer);
		//std::vector<st::function> functions;
		GType type(lexer);
		GTypeName typeName(lexer);
		GExpression expression(lexer, typeName);
		GInstruction instruction(lexer, expression, type);
		GFunction gfunction(lexer, instruction, typeName);
		ast::function function;

		bool res = lex::tokenize_and_phrase_parse(lp_begin, lp_end, lexer, gfunction, qi::in_state("WS")[lexer.self]);
		if(res && lp_begin == lp_end) {
			std::cout << "successed" << std::endl;
		} else {
			std::string rest(lp_begin, lp_end);
			std::cout << "Parsed: \"" << std::string(lp_start, lp_begin) << "\"" << std::endl;
			std::cout << "Pasring failed, returned value: " << std::boolalpha << res << "\n" << "stopped at: \"" << rest << "\"" << std::endl;
		}
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
		std::ofstream out(argv[i] + std::string(".out"));
		in.unsetf(std::ios::skipws);
		std::cout << "parse file \"" << argv[i] << "\":" << std::endl;
		parse_file(in, out);
	}
}

