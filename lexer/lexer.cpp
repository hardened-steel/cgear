// Project: CGear
//
//  Created on: 01.08.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix/phoenix.hpp>
#include "lexer.h"
#include "constant_table.h"

Lexer::Lexer(ConstantTable& table): constants(table)
{
	namespace phx = boost::phoenix;
	namespace lex = boost::spirit::lex;
	token::omit& token = other_tokens;

	this->self += token('(') | token(')') | token('{') | token('}') | token('[') | token(']') | token(':') | token(';') | token(',');
	this->self += token('=') | token("+=", "\\+=") | token("-=", "\\-=") | token("*=", "\\*=") | token("/=", "\\/=");
	this->self += token('+') | token('-') | token('*') | token('/') | token('%');
	this->self += token("!=", "\\!=") | token("==", "==");
#define KAdd(X) this->self += k##X;
	KWords(KAdd)
#undef KAdd
	this->self += intLiteral         [ lex::_val = phx::bind(&ConstantTable::createInteger,    &constants, lex::_start, lex::_end) ]
	            | identifier         [ lex::_val = phx::bind(&ConstantTable::createIdentifier, &constants, lex::_start, lex::_end) ]
	            ;
	this->self("WS") = ws | line_comment;
}

