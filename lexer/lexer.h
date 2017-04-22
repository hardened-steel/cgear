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
	boost::spirit::lex::token_def<token::intLiteral> intLiteral          {R"([0-9]+)"};

#define KDecl(X) boost::spirit::lex::token_def<boost::spirit::lex::omit> k##X {#X};
	KWords(KDecl)
#undef KDecl
	//other tokens
	const token::omit& tokens = other_tokens;
	//ignore tokens
	boost::spirit::lex::token_def<> ws {R"([ \t\r\n])"}, line_comment {R"(\/\/.*?[\r\n])"};

	Lexer(class ConstantTable& table);
private:
	class ConstantTable& constants;
	token::omit other_tokens;
};

typedef Lexer::iterator_type GIterator;
typedef boost::spirit::qi::in_state_skipper<Lexer::lexer_def> GSkip;

#endif	/* LEXER_H */

