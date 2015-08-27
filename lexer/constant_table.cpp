#include <boost/spirit/include/qi.hpp>
#include "constant_table.h"

token::identifier ConstantTable::createIdentifier(const token::iterator& start, const token::iterator& end) {
	return { identifierTable.emplace(start, end).first.operator->() };
}

token::intLiteral ConstantTable::createInteger(const token::iterator& start, const token::iterator& end) {
	namespace qi = boost::spirit::qi;
	namespace phx = boost::phoenix;

	const std::string literal(start, end);

	using StrIterator = std::string::const_iterator;
	using Parser = boost::spirit::qi::rule<StrIterator, token::int_type()>;
	auto convert = [this](Parser parser, StrIterator first, const StrIterator& last)->const token::int_type* {
		token::int_type value;
		boost::spirit::qi::parse(first, last, parser, value);
		return integerConstantTable.insert(std::move(value)).first.operator ->();
	};

	qi::uint_parser<unsigned, 10, 1, 1> ten;
	Parser value_parser = ten[qi::_val = qi::_1] >> *(-qi::lit('\'') >> ten[qi::_val = qi::_val * 10 + qi::_1]);
	return { convert(value_parser, literal.begin(), literal.end()) };
}

token::stringLiteral ConstantTable::createString(const token::iterator& start, const token::iterator& end) {
	return { identifierTable.emplace(start, end).first.operator->() };
}

token::stringLiteral ConstantTable::createRawString(const token::iterator& start, const token::iterator& end) {
	return { identifierTable.emplace(start, end).first.operator->() };
}

token::realLiteral ConstantTable::createReal(const token::iterator& start, const token::iterator& end) {
	namespace qi = boost::spirit::qi;
	namespace phx = boost::phoenix;

	const std::string literal(start, end);

	using StrIterator = std::string::const_iterator;
	using Parser = boost::spirit::qi::rule<StrIterator, token::real_type()>;
	auto convert = [this](Parser parser, StrIterator first, const StrIterator& last)->const token::real_type* {
		token::real_type value;
		boost::spirit::qi::parse(first, last, parser, value);
		return realConstantTable.insert(std::move(value)).first.operator ->();
	};

	Parser value_parser = qi::long_double [qi::_val = qi::_1];
	return { convert(value_parser, literal.begin(), literal.end()) };
}
