// Project: CGear
//
//  Created on: 01.08.2015
//      Author: K.Pinegin
//	     email: keldgaden@gmail.com
//

#ifndef LEXER_TOKEN_H_
#define LEXER_TOKEN_H_

#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/support_istream_iterator.hpp>
#include <boost/spirit/include/support_line_pos_iterator.hpp>
#include <string>
#include <map>

struct token
{
	using iterator = boost::spirit::line_pos_iterator<boost::spirit::istream_iterator>;
	template<class T> class attribute
	{
		const T* pointer;
	public:
		attribute(): pointer(nullptr) {}
		attribute(const T* ptr): pointer(ptr) {}
		attribute(const attribute& other): pointer(other.pointer) {}
		attribute& operator = (const attribute& other) {
			pointer = other.pointer;
			return *this;
		}
		operator const T&() const { return *pointer; }
	};
	using real_type = long double;
	using int_type = unsigned long long int;
	class identifier: public attribute<std::string>     { public: using attribute<std::string>::attribute; };
	class charLiteral: public attribute<std::string>    { public: using attribute<std::string>::attribute; };
	class stringLiteral: public attribute<std::string>  { public: using attribute<std::string>::attribute; };
	using realLiteral = attribute<real_type>;
	using intLiteral = attribute<int_type>;
	typedef boost::spirit::lex::lexertl::token
	<
	    iterator, boost::mpl::vector
	    <
	        identifier,
	        charLiteral,
	        stringLiteral,
	        realLiteral,
	        intLiteral
	    >,
	    boost::mpl::true_
	> type;

	class omit
	{
		std::map<std::string, boost::spirit::lex::token_def<boost::spirit::lex::omit>> tokens;
	public:
		boost::spirit::lex::token_def<boost::spirit::lex::omit>& operator()(std::string&& tok, std::string&& regex) {
			return tokens[tok] = boost::spirit::lex::token_def<boost::spirit::lex::omit>(regex);
		}

		boost::spirit::lex::token_def<boost::spirit::lex::omit>& operator()(char tok) {
			std::string regex = "\\";
			std::string token(1, tok);
			regex += token;
			return tokens[token] = boost::spirit::lex::token_def<boost::spirit::lex::omit>(regex);
		}

		const boost::spirit::lex::token_def<boost::spirit::lex::omit>& operator[](const std::string& tok) const {
			return tokens.at(tok);
		}
	};
};

namespace boost { namespace spirit { namespace traits {
    template <typename Iterator, typename T> struct assign_to_attribute_from_iterators<T, Iterator>
    {
        static void call(Iterator const& first, Iterator const& last, T& attr) {
        }
    };
}}}

#endif /* LEXER_TOKEN_H_ */
