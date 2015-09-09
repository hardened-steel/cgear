// Project: CGear
//
//  Created on: 01.08.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef LEXER_H
#define	LEXER_H

#include "token.h"

class Lexer: public boost::spirit::lex::lexer<boost::spirit::lex::lexertl::actor_lexer<token::type>>
{
public:
	boost::spirit::lex::token_def<token::identifier> identifier          {"[a-zA-Z_][a-zA-Z0-9_]*"};
	boost::spirit::lex::token_def<token::stringLiteral> stringLiteral    {R"_(\"(\\.|[^\"\\\n])*\")_"};
	boost::spirit::lex::token_def<token::stringLiteral> rawStringLiteral {R"_(R\".{0,3}\()_"};
	boost::spirit::lex::token_def<token::intLiteral> charLiteral         {R"_('(\\.|[^'\\\n])*')_"};
	boost::spirit::lex::token_def<token::realLiteral> realLiteral        {R"([0-9]*\.[0-9]+([eE][-+]?[0-9]+)?)"};
	boost::spirit::lex::token_def<token::intLiteral> intLiteral          {R"([0-9]+)"};

	//bool
	boost::spirit::lex::token_def<boost::spirit::lex::omit> ktrue        {"true"};
	boost::spirit::lex::token_def<boost::spirit::lex::omit> kfalse       {"false"};
	//key words
	boost::spirit::lex::token_def<boost::spirit::lex::omit> kconst       {"const"};
	boost::spirit::lex::token_def<boost::spirit::lex::omit> kreturn      {"return"};
	boost::spirit::lex::token_def<boost::spirit::lex::omit> kwhile       {"while"};
	boost::spirit::lex::token_def<boost::spirit::lex::omit> kfor         {"for"};
	boost::spirit::lex::token_def<boost::spirit::lex::omit> kif          {"if"};
	boost::spirit::lex::token_def<boost::spirit::lex::omit> kelse        {"else"};
	boost::spirit::lex::token_def<boost::spirit::lex::omit> ksizeof      {"sizeof"};
	//types
	boost::spirit::lex::token_def<boost::spirit::lex::omit> kint         {"int"};
	boost::spirit::lex::token_def<boost::spirit::lex::omit> kreal        {"real"};
	boost::spirit::lex::token_def<boost::spirit::lex::omit> kvoid        {"void"};
	boost::spirit::lex::token_def<boost::spirit::lex::omit> kbool        {"bool"};
	boost::spirit::lex::token_def<boost::spirit::lex::omit> kchar        {"char"};
	boost::spirit::lex::token_def<boost::spirit::lex::omit> karray       {"array"};
	//other tokens
	const token::omit& tokens = other_tokens;
	//ignore tokens
	boost::spirit::lex::token_def<> ws {R"([ \t\r\n])"}, line_comment {R"(\/\/.*?[\r\n])"}, block_comment {R"(\/\*.*?\*\/)"};

	Lexer(class ConstantTable& table);
private:
	class ConstantTable& constants;
	token::omit other_tokens;
};

typedef Lexer::iterator_type GIterator;
typedef boost::spirit::qi::in_state_skipper<Lexer::lexer_def> GSkip;

#endif	/* LEXER_H */

