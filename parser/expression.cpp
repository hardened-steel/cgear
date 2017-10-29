// Project: CGear
//
//  Created on: 01.08.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#include <boost/phoenix/phoenix.hpp>
#include <ast/operations/binary.h>
#include <ast/operations/call.h>
#include <ast/operations/variable.h>
#include <ast/operations/literal.h>
#include "expression.h"

GExpression::GExpression(Lexer& lexer, GTypeName& type): GExpression::base_type(expression)
{
	namespace qi = boost::spirit::qi;
	namespace phx = boost::phoenix;

	variable  = lexer.identifier[qi::_val = phx::construct<ast::operation::variable::instance>(qi::_1)];

	call = lexer.identifier[qi::_a = qi::_1] >>
	     ( (lexer.tokens["("] >> lexer.tokens[")"])                                    [qi::_val = phx::construct<ast::operation::call::instance>(qi::_a)]
	     | ((lexer.tokens["("] >> expression % lexer.tokens[","]) > lexer.tokens[")"]) [qi::_val = phx::construct<ast::operation::call::instance>(qi::_a, qi::_1)]
	     );

	expression = operation[0]  [qi::_val = qi::_1];
	operation[0] = ((operation[1] >> lexer.tokens["=" ]) > expression)[qi::_val = phx::construct<ast::operation::binary::instance>(ast::operation::code::assign,                    qi::_1, qi::_2)]
	             | ((operation[1] >> lexer.tokens["+="]) > expression)[qi::_val = phx::construct<ast::operation::binary::instance>(ast::operation::code::addition_and_assign,       qi::_1, qi::_2)]
	             | ((operation[1] >> lexer.tokens["-="]) > expression)[qi::_val = phx::construct<ast::operation::binary::instance>(ast::operation::code::subtraction_and_assign,    qi::_1, qi::_2)]
	             | ((operation[1] >> lexer.tokens["*="]) > expression)[qi::_val = phx::construct<ast::operation::binary::instance>(ast::operation::code::multiplication_and_assign, qi::_1, qi::_2)]
	             | ((operation[1] >> lexer.tokens["/="]) > expression)[qi::_val = phx::construct<ast::operation::binary::instance>(ast::operation::code::division_and_assign,       qi::_1, qi::_2)]
	             | (operation[1])[qi::_val = std::move(qi::_1)]
	             ;
	/*
	operation[1] = (operation[2] >> lexer.tokens["?"] > expression > lexer.tokens[":"] > expression)[qi::_val = phx::construct<ast::operation::ternary::instance>(qi::_1, qi::_2, qi::_3)]
	             | (operation[2])[qi::_val = qi::_1]
	             ;
	             */
	operation[1] = operation[2][qi::_val = qi::_1];
	operation[2] = operation[3][qi::_val = qi::_1] >>
	             *( (lexer.tokens["=="] > operation[3])[qi::_val = phx::construct<ast::operation::binary::instance>(ast::operation::code::equal,     qi::_val, qi::_1)]
	              | (lexer.tokens["!="] > operation[3])[qi::_val = phx::construct<ast::operation::binary::instance>(ast::operation::code::not_equal, qi::_val, qi::_1)]
	             );
	/*
	operation[3] = operation[4][qi::_val = qi::_1] >>
	             *( (lexer.tokens["<" ] > operation[4])[qi::_val = phx::construct<ast::operation::binary::instance>(ast::operation::code::less,          qi::_val, qi::_1)]
	              | (lexer.tokens["<="] > operation[4])[qi::_val = phx::construct<ast::operation::binary::instance>(ast::operation::code::less_or_equal, qi::_val, qi::_1)]
	              | (lexer.tokens[">" ] > operation[4])[qi::_val = phx::construct<ast::operation::binary::instance>(ast::operation::code::more,          qi::_val, qi::_1)]
	              | (lexer.tokens[">="] > operation[4])[qi::_val = phx::construct<ast::operation::binary::instance>(ast::operation::code::more_or_equal, qi::_val, qi::_1)]
	             );
	             */
	operation[3] = operation[4][qi::_val = qi::_1];
	operation[4] = operation[5][qi::_val = qi::_1] >>
	             *( (lexer.tokens["+"] > operation[5])[qi::_val = phx::construct<ast::operation::binary::instance>(ast::operation::code::addition,    qi::_val, qi::_1)]
	              | (lexer.tokens["-"] > operation[5])[qi::_val = phx::construct<ast::operation::binary::instance>(ast::operation::code::subtraction, qi::_val, qi::_1)]
	             );
	operation[5] = operation[6][qi::_val = qi::_1] >>
	             *( (lexer.tokens["*"] > operation[6])[qi::_val = phx::construct<ast::operation::binary::instance>(ast::operation::code::multiplication, qi::_val, qi::_1)]
	              | (lexer.tokens["/"] > operation[6])[qi::_val = phx::construct<ast::operation::binary::instance>(ast::operation::code::division,       qi::_val, qi::_1)]
	              | (lexer.tokens["%"] > operation[6])[qi::_val = phx::construct<ast::operation::binary::instance>(ast::operation::code::modulo,         qi::_val, qi::_1)]
	             );
	/*
	operation[6] = (lexer.tokens["++"] > operation[7])[qi::_val = phx::construct<ast::operation::unary::instance>(ast::operation::code::prefix_inc,  qi::_1)]
	             | (lexer.tokens["--"] > operation[7])[qi::_val = phx::construct<ast::operation::unary::instance>(ast::operation::code::prefix_dec,  qi::_1)]
	             | (lexer.tokens["+" ] > operation[7])[qi::_val = phx::construct<ast::operation::unary::instance>(ast::operation::code::unary_plus,  qi::_1)]
	             | (lexer.tokens["-" ] > operation[7])[qi::_val = phx::construct<ast::operation::unary::instance>(ast::operation::code::unary_minus, qi::_1)]
	             | (lexer.ksizeof > lexer.tokens["("] > variable > lexer.tokens[")"])[qi::_val = phx::construct<ast::operation::unary::instance>(ast::operation::code::size_of, qi::_1)]
	             //| (lexer.tokens["("] >> type > lexer.tokens[")"] > operation[7])[qi::_val = phx::construct<ast::operation::type_cast::instance>(qi::_1, qi::_2)]
	             | (operation[7])[qi::_val = qi::_1]
	             ;
	             */
	/*
	operation[7] = operation[8][qi::_val = qi::_1] >>
	             *( (lexer.tokens["++"]) [qi::_val = phx::construct<ast::operation::unary::instance>(ast::operation::code::suffix_inc, qi::_val)]
	              | (lexer.tokens["--"]) [qi::_val = phx::construct<ast::operation::unary::instance>(ast::operation::code::suffix_dec, qi::_val)]
	              //| (lexer.tokens["["] >> expression >> lexer.tokens["]"])[qi::_val = phx::construct<ast::operation::index::instance>(qi::_val, qi::_1)]
	              //| (lexer.tokens["["] > expression > lexer.tokens[":"] > expression > lexer.tokens["]"])[qi::_val = phx::construct<ast::operation::section::instance>(qi::_val, qi::_1, qi::_2)]
	             );
	             */
	operation[6] = operation[8][qi::_val = qi::_1];
	operation[8] = (lexer.tokens["("] > expression > lexer.tokens[")"]) [qi::_val = qi::_1]
	             //| (lexer.tokens["{"] > (expression % lexer.tokens[","]) > lexer.tokens["}"]) [qi::_val = phx::construct<ast::operation::array::instance>(qi::_1)]
	             | lexer.ktrue         [qi::_val = phx::construct<ast::operation::literal::instance>(true)]
	             | lexer.kfalse        [qi::_val = phx::construct<ast::operation::literal::instance>(false)]
	             | lexer.intLiteral    [qi::_val = phx::construct<ast::operation::literal::instance>(qi::_1)]
	             //| lexer.realLiteral   [qi::_val = phx::construct<ast::operation::literal::instance>(qi::_1)]
	             //| lexer.stringLiteral [qi::_val = phx::construct<ast::operation::literal::instance>(qi::_1)]
	             | call [qi::_val = qi::_1]
	             | variable  [qi::_val = qi::_1]
	             ;

	expression.name("expression");
	variable.name("variable");
	call.name("call function");
}

GExpression::~GExpression()
{
}
