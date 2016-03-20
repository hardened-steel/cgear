// Project: CGear
//
//  Created on: 01.08.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
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
#include "ast/operators/nope.h"


template<class Iterator>
std::string print(Iterator start, Iterator end) {
	return std::string(start, end);
}

class WHandler
{
public:
    void operator()(ast::instruction::instance& node, GIterator& first, const GIterator& last) const {
    	auto begin = boost::get<boost::iterator_range<token::iterator>>(first->value()).begin();
    	auto end   = boost::get<boost::iterator_range<token::iterator>>(last->value()).end();

    	//node->begin = begin;
    	//node->end = end;
    }
};

boost::phoenix::function<WHandler> Handler;

GInstruction::GInstruction(Lexer& lexer, GExpression& operation, GType& type): GInstruction::base_type(instruction, "instruction")
{
	namespace qi = boost::spirit::qi;
	namespace phx = boost::phoenix;

	nope = lexer.tokens[";"][qi::_val = phx::construct<ast::instruction::nope>()];

	variable = type [qi::_a = qi::_1] >> lexer.identifier [ qi::_b = qi::_1] >
	               ( lexer.tokens[";"] [qi::_val = phx::construct<ast::instruction::variable::instance>(qi::_a, qi::_b, phx::construct<ast::operation::instance>())]
	               | (lexer.tokens["="] > operation > lexer.tokens[";"]) [qi::_val = phx::construct<ast::instruction::variable::instance>(qi::_a, qi::_b, qi::_1)]
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
          )[qi::_val = phx::new_<st::instruction::for_i::instance>(qi::_1, qi::_2, qi::_3, qi::_4)]
        ;
    */

	while_i = (
	             lexer.kwhile
	             > lexer.tokens["("]
	             > operation
	             > lexer.tokens[")"]
	             > instruction
	          ) [qi::_val = phx::construct<ast::instruction::while_i::instance>(qi::_1, qi::_2)];

	return_i = (lexer.kreturn > operation > lexer.tokens[";"])[qi::_val = phx::construct<ast::instruction::return_i::instance>(qi::_1)];

	calc = (operation > lexer.tokens[";"])[qi::_val = phx::construct<ast::instruction::calc::instance>(qi::_1)];

	if_i = (
	        lexer.kif
	        > lexer.tokens["("]
	        > operation         [qi::_a = qi::_1]
	        > lexer.tokens[")"]
	        > instruction       [qi::_b = qi::_1, qi::_val = phx::construct<ast::instruction::if_i::instance>(qi::_a, qi::_b)]
	        > -(lexer.kelse > instruction [qi::_val = phx::construct<ast::instruction::ifelse_i::instance>(qi::_a, qi::_b, qi::_1)])
	       );

	block = (lexer.tokens["{"] > *instruction > lexer.tokens["}"]) [qi::_val = phx::construct<ast::instruction::block::instance>(qi::_1)];

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

    qi::on_success(block, Handler(qi::_val, qi::_1, qi::_3));
}

GInstruction::~GInstruction()
{
}

