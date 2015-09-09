// Project: CGear
//
//  Created on: 01.08.2015
//      Author: K.Pinegin
//	     email: keldgaden@gmail.com
//

#include <boost/phoenix/phoenix.hpp>
#include "ast/operations/binary.h"
#include "ast/operations/unary.h"
#include "ast/operations/ternary.h"
#include "ast/operations/call.h"
#include "ast/operations/variable.h"
#include "expression.h"

GExpression::GExpression(Lexer& lexer): GExpression::base_type(expression), type(lexer)
{
	namespace qi = boost::spirit::qi;
	namespace phx = boost::phoenix;

	variable  = lexer.identifier[qi::_val = phx::construct<ast::operation::variable>(qi::_1)];
	call = lexer.identifier[qi::_a = qi::_1] >>
	     ( (lexer.tokens["("] >> lexer.tokens[")"])                                   [qi::_val = phx::construct<ast::operation::call>(qi::_a)]
	     | (lexer.tokens["("] >> expression % lexer.tokens[","] > lexer.tokens[")"] ) [qi::_val = phx::construct<ast::operation::call>(qi::_a, qi::_1)]
	     );
	expression = operation[0]  [qi::_val = qi::_1];
	operation[0] = (operation[1] >> lexer.tokens["=" ] > expression)[qi::_val = phx::construct<ast::operation::binary>(ast::operation::code::assign,                    qi::_1, qi::_2)]
	             | (operation[1] >> lexer.tokens["+="] > expression)[qi::_val = phx::construct<ast::operation::binary>(ast::operation::code::addition_and_assign,       qi::_1, qi::_2)]
	             | (operation[1] >> lexer.tokens["-="] > expression)[qi::_val = phx::construct<ast::operation::binary>(ast::operation::code::subtraction_and_assign,    qi::_1, qi::_2)]
	             | (operation[1] >> lexer.tokens["*="] > expression)[qi::_val = phx::construct<ast::operation::binary>(ast::operation::code::multiplication_and_assign, qi::_1, qi::_2)]
	             | (operation[1] >> lexer.tokens["/="] > expression)[qi::_val = phx::construct<ast::operation::binary>(ast::operation::code::division_and_assign,       qi::_1, qi::_2)]
	             | (operation[1])[qi::_val = qi::_1]
	             ;
	operation[1] = (operation[2] >> lexer.tokens["?"] > expression > lexer.tokens[":"] > expression)[qi::_val = phx::construct<ast::operation::ternary>(qi::_1, qi::_2, qi::_3)]
	             | (operation[2])[qi::_val = qi::_1]
	             ;
	operation[2] = operation[3][qi::_val = qi::_1] >>
	             *( (lexer.tokens["=="] > operation[3])[qi::_val = phx::construct<ast::operation::binary>(ast::operation::code::equal,     qi::_val, qi::_1)]
	              | (lexer.tokens["!="] > operation[3])[qi::_val = phx::construct<ast::operation::binary>(ast::operation::code::not_equal, qi::_val, qi::_1)]
	             );
	operation[3] = operation[4][qi::_val = qi::_1] >>
	             *( (lexer.tokens["<" ] > operation[4])[qi::_val = phx::construct<ast::operation::binary>(ast::operation::code::less,          qi::_val, qi::_1)]
	              | (lexer.tokens["<="] > operation[4])[qi::_val = phx::construct<ast::operation::binary>(ast::operation::code::less_or_equal, qi::_val, qi::_1)]
	              | (lexer.tokens[">" ] > operation[4])[qi::_val = phx::construct<ast::operation::binary>(ast::operation::code::more,          qi::_val, qi::_1)]
	              | (lexer.tokens[">="] > operation[4])[qi::_val = phx::construct<ast::operation::binary>(ast::operation::code::more_or_equal, qi::_val, qi::_1)]
	             );
	operation[4] = operation[5][qi::_val = qi::_1] >>
	             *( (lexer.tokens["+"] > operation[5])[qi::_val = phx::construct<ast::operation::binary>(ast::operation::code::addition,    qi::_val, qi::_1)]
	              | (lexer.tokens["-"] > operation[5])[qi::_val = phx::construct<ast::operation::binary>(ast::operation::code::subtraction, qi::_val, qi::_1)]
	             );
	operation[5] = operation[6][qi::_val = qi::_1] >>
	             *( (lexer.tokens["*"] > operation[6])[qi::_val = phx::construct<ast::operation::binary>(ast::operation::code::multiplication, qi::_val, qi::_1)]
	              | (lexer.tokens["/"] > operation[6])[qi::_val = phx::construct<ast::operation::binary>(ast::operation::code::division,       qi::_val, qi::_1)]
	              | (lexer.tokens["%"] > operation[6])[qi::_val = phx::construct<ast::operation::binary>(ast::operation::code::modulo,         qi::_val, qi::_1)]
	             );
	operation[6] = (lexer.tokens["++"] > operation[7])[qi::_val = phx::construct<ast::operation::unary>(ast::operation::code::prefix_inc,  qi::_1)]
	             | (lexer.tokens["--"] > operation[7])[qi::_val = phx::construct<ast::operation::unary>(ast::operation::code::prefix_dec,  qi::_1)]
	             | (lexer.tokens["+" ] > operation[7])[qi::_val = phx::construct<ast::operation::unary>(ast::operation::code::unary_plus,  qi::_1)]
	             | (lexer.tokens["-" ] > operation[7])[qi::_val = phx::construct<ast::operation::unary>(ast::operation::code::unary_minus, qi::_1)]
	             | (lexer.ksizeof > lexer.tokens["("] > variable > lexer.tokens[")"])[qi::_val = phx::construct<ast::operation::unary>(ast::operation::code::size_of, qi::_1)]
	             //| (lexer.tokens["("] >> type > lexer.tokens[")"] > operation[7])[qi::_val = phx::construct<ast::operation::type_cast>(qi::_1, qi::_2)]
	             | (operation[7])[qi::_val = qi::_1]
	             ;
	operation[7] = operation[8][qi::_val = qi::_1] >>
	             *( (lexer.tokens["++"]) [qi::_val = phx::construct<ast::operation::unary>(ast::operation::code::suffix_inc, qi::_val)]
	              | (lexer.tokens["--"]) [qi::_val = phx::construct<ast::operation::unary>(ast::operation::code::suffix_dec, qi::_val)]
	              //| (lexer.tokens["["] >> expression >> lexer.tokens["]"])[qi::_val = phx::construct<ast::operation::index>(qi::_val, qi::_1)]
	              //| (lexer.tokens["["] > expression > lexer.tokens[":"] > expression > lexer.tokens["]"])[qi::_val = phx::construct<ast::operation::section>(qi::_val, qi::_1, qi::_2)]
	             );
	operation[8] = (lexer.tokens["("] > expression > lexer.tokens[")"]) [qi::_val = qi::_1]
	             //| (lexer.tokens["{"] > (expression % lexer.tokens[","]) > lexer.tokens["}"]) [qi::_val = phx::construct<ast::operation::array>(qi::_1)]
	             //| lexer.ktrue         [qi::_val = phx::construct<ast::operation::literal>(true)]
	             //| lexer.kfalse        [qi::_val = phx::construct<ast::operation::literal>(false)]
	             //| lexer.intLiteral    [qi::_val = phx::construct<ast::operation::literal>(qi::_1)]
	             //| lexer.realLiteral   [qi::_val = phx::construct<ast::operation::literal>(qi::_1)]
	             //| lexer.stringLiteral [qi::_val = phx::construct<ast::operation::literal>(qi::_1)]
	             | call [qi::_val = qi::_1]
	             | variable  [qi::_val = qi::_1]
	             ;
    
	expression.name("expression");
	variable.name("variable");
	call.name("call function");
/*
    qi::on_success
            (
                expression
              , std::cout << phx::val("success rule expression:\n") << phx::bind(&st::print, qi::_val, 0) << std::endl
            );
    qi::on_success
            (
                var
              , std::cout << phx::val("success rule var:\n") << phx::bind(&st::print, qi::_val, 0) << std::endl
            );
    qi::on_success
            (
                call
              , std::cout << phx::val("success rule call:\n") << phx::bind(&st::print, qi::_val, 0) << std::endl
            );
*/
}

GExpression::~GExpression()
{
}
