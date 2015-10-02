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
	this->self += token("++", "\\+\\+") | token("--", "\\-\\-");
	this->self += token('+') | token('-') | token('*') | token('/') | token('%');
	this->self += token('|') | token('&');
	this->self += token('?') | token('<') | token('>') | token("<=", "<=") | token(">=", ">=");
	this->self += token("!=", "\\!=") | token("==", "==");
	this->self += kbool | kelse | kfor | kif | kint | kreal | kreturn | karray | kvoid | kwhile | ktrue | kfalse | kchar | ksizeof | kconst;
	this->self += kfunction;
	this->self += realLiteral        [ lex::_val = phx::bind(&ConstantTable::createReal,       &constants, lex::_start, lex::_end) ]
	            | intLiteral         [ lex::_val = phx::bind(&ConstantTable::createInteger,    &constants, lex::_start, lex::_end) ]
	            | identifier         [ lex::_val = phx::bind(&ConstantTable::createIdentifier, &constants, lex::_start, lex::_end) ]
	            | stringLiteral      [ lex::_val = phx::bind(&ConstantTable::createString,     &constants, lex::_start, lex::_end) ]
	            | rawStringLiteral   [ lex::_val = phx::bind(&ConstantTable::createRawString,  &constants, lex::_start, lex::_end) ]
	            ;
	this->self("WS") = ws | line_comment | block_comment;
}

