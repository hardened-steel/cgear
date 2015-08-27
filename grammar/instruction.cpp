#include <boost/phoenix/phoenix.hpp>
#include "instruction.h"

GInstruction::GInstruction(Lexer& lexer): GInstruction::base_type(instruction, "instruction"), expression(lexer), type(lexer)
{
    namespace qi = boost::spirit::qi;
    namespace phx = boost::phoenix;

    nope = lexer.tokens[";"][qi::_val = nullptr];

    variable = type [qi::_a = qi::_1] >> lexer.identifier [ qi::_b = qi::_1] >
                   ( lexer.tokens[";"] [qi::_val = phx::new_<st::instruction::variable>(qi::_a, qi::_b)]
                   | (lexer.tokens["="] > expression > lexer.tokens[";"]) [qi::_val = phx::new_<st::instruction::variable>(qi::_a, qi::_b, qi::_1)]
                   )
             ;

    For = (
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

    While = (
             lexer.kwhile
             > lexer.tokens["("]
                 > expression
             > lexer.tokens[")"]
             > instruction
            )[qi::_val = phx::new_<st::instruction::While>(qi::_1, qi::_2)]
          ;

    Return = (lexer.kreturn > expression > lexer.tokens[";"])[qi::_val = phx::new_<st::instruction::Return>(qi::_1)];

    calc = (expression > lexer.tokens[";"])[qi::_val = phx::new_<st::instruction::calc>(qi::_1)];

    If = (lexer.kif > lexer.tokens["("] > expression > lexer.tokens[")"] > instruction > -(lexer.kelse > instruction))[qi::_val = phx::new_<st::instruction::If>(qi::_1, qi::_2, qi::_3)];

    block = (lexer.tokens["{"] > *instruction > lexer.tokens["}"]) [qi::_val = phx::new_<st::instruction::block>(qi::_1)];

    instruction = block | If | Return | While | For | variable | calc;
    
    variable.name("variable declaration");
    calc.name("calucate expression");
    If.name("if operator");
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

