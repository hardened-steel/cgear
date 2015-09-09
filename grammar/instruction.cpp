// Project: CGear
//
//  Created on: 01.08.2015
//      Author: K.Pinegin
//	     email: keldgaden@gmail.com
//

#include <vector>
#include <boost/phoenix/phoenix.hpp>
#include "instruction.h"
#include "ast/operators/block.h"
#include "ast/operators/calc.h"
#include "ast/operators/if.h"
#include "ast/operators/repeat.h"
#include "ast/operators/return.h"
#include "ast/operators/variable.h"
#include "ast/operators/while.h"

class ast::instruction::nope
{
	friend ast::instruction;
protected:
	class implementation: public ast::instruction::base
	{
	public:
		void* operator new(size_t size) {
			return &snope;
		}
		void operator delete(void* pointer) {
		}
	};
public:
	nope(): impl(new implementation) {}
private:
	static implementation snope;
	std::shared_ptr<implementation> impl;
};

GInstruction::GInstruction(Lexer& lexer): GInstruction::base_type(instruction, "instruction"), operation(lexer), type(lexer)
{
	namespace qi = boost::spirit::qi;
	namespace phx = boost::phoenix;

	nope = lexer.tokens[";"][qi::_val = phx::construct<ast::instruction::nope>()];

	variable = type [qi::_a = qi::_1] >> lexer.identifier [ qi::_b = qi::_1] >
	               ( lexer.tokens[";"] [qi::_val = phx::construct<ast::instruction::variable>(qi::_a, qi::_b, phx::construct<ast::operation>())]
	               | (lexer.tokens["="] > operation > lexer.tokens[";"]) [qi::_val = phx::construct<ast::instruction::variable>(qi::_a, qi::_b, qi::_1)]
	               )
             ;
    /*
    for_i = (
           lexer.kfor
            > lexer.tokens["("]
                > (nope | variable | calc)
                > -(expression)
                > lexer.tokens[";"]
                > -(expression)
            > lexer.tokens[")"]
           > instruction
          )[qi::_val = phx::new_<st::instruction::For>(qi::_1, qi::_2, qi::_3, qi::_4)]
        ;
    */

	while_i = (
	             lexer.kwhile
	             > lexer.tokens["("]
	             > operation
	             > lexer.tokens[")"]
	             > instruction
	          ) [qi::_val = phx::construct<ast::instruction::while_i>(qi::_1, qi::_2)];

	return_i = (lexer.kreturn > operation > lexer.tokens[";"])[qi::_val = phx::construct<ast::instruction::return_i>(qi::_1)];

	calc = (operation > lexer.tokens[";"])[qi::_val = phx::construct<ast::instruction::calc>(qi::_1)];

	if_i = (
	        lexer.kif
	        > lexer.tokens["("]
	        > operation         [qi::_a = qi::_1]
	        > lexer.tokens[")"]
	        > instruction       [qi::_b = qi::_1, qi::_val = phx::construct<ast::instruction::if_i>(qi::_a, qi::_b)]
	        > -(lexer.kelse > instruction [qi::_val = phx::construct<ast::instruction::ifelse_i>(qi::_a, qi::_b, qi::_1)])
	       );

	block = (lexer.tokens["{"] > *instruction > lexer.tokens["}"]) [qi::_val = phx::construct<ast::instruction::block>(qi::_1)];

	instruction = block | if_i | return_i | while_i | variable | calc;

	variable.name("variable declaration");
	calc.name("calucate expression");
	if_i.name("if operator");
	block.name("block of instructions");
	instruction.name("instruction");

	qi::on_error<qi::fail>
	         (
	           calc
	           , std::cout
	                << phx::val("Error! Expecting ")
	                << qi::_4                               // what failed?
	                << std::endl
	         );
/*
    qi::on_success
            (
                variable
              , std::cout << phx::val("success rule variable:\n") << phx::bind(&st::print, qi::_val, 0) << std::endl
            );

    qi::on_success
            (
                calc
              , std::cout << phx::val("success rule calc:\n") << phx::bind(&st::print, qi::_val, 0) << std::endl
            );

    qi::on_success
            (
                If
              , std::cout << phx::val("success rule If:\n") << phx::bind(&st::print, qi::_val, 0) << std::endl
            );

    qi::on_success
            (
                block
              , std::cout << phx::val("success rule block:\n") << phx::bind(&st::print, qi::_val, 0) << std::endl
            );
    qi::on_success
            (
                instruction
              , std::cout << phx::val("success rule instruction:\n") << phx::bind(&st::print, qi::_val, 0) << std::endl
            );
*/
}

GInstruction::~GInstruction()
{
}

