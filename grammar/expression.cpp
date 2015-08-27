#include <boost/phoenix/phoenix.hpp>
#include <string>
#include "expression.h"
#include "../pool.h"

class ast::operation::binary
{
public:
	enum {
		assign, addition_and_assign, subtraction_and_assign, multiplication_and_assign, division_and_assign, modulo_and_assign,
		equal, not_equal,
		less, less_or_equal, more, more_or_equal,
		addition, subtraction,
		multiplication, division, modulo,
	};
	class implementation: public ast::operation::base
	{
		ast::operation left;
		ast::operation right;
		int code;
	public:
		implementation(ast::operation left, int code, ast::operation right): left(left), code(code), right(right) {}
		void* operator new(size_t size) {
			return memory_pool.allocate(size);
		}
		void operator delete(void* pointer) {
			memory_pool.deallocate(pointer);
		}
	};
	operator ast::operation() const {
		std::shared_ptr<base> ptr = impl;
		return ptr;
	}
private:
	static pool<sizeof(implementation), 1024> memory_pool;
	std::shared_ptr<implementation> impl;
};

GExpression::GExpression(Lexer& lexer): GExpression::base_type(expression)//, type(lexer)
{
    namespace qi = boost::spirit::qi;
    namespace phx = boost::phoenix;

    ast::operation::binary b;
    ast::operation operation = ast::operation::binary();
    //var = lexer.identifier[qi::_val = phx::new_<ast::operation::var>(qi::_1)];
    /*
    call = lexer.identifier[qi::_a = qi::_1] >> lexer.tokens["("] >
            ( (lexer.tokens[")"])                                   [qi::_val = phx::new_<st::operation::call>(qi::_a)]
            | (expression % lexer.tokens[","] > lexer.tokens[")"] ) [qi::_val = phx::new_<st::operation::call>(qi::_a, qi::_1)]
            );
    */
    /*
    expression = operation[0]  [qi::_val = qi::_1];
    operation[0] = (operation[1] >> lexer.tokens["="]  > expression)[qi::_val = phx::new_<ast::operation::binary>(Operation::assign, qi::_1, qi::_2)]
                 | (operation[1] >> lexer.tokens["+="] > expression)[qi::_val = phx::new_<ast::operation::binary>(Operation::addition_and_assign, qi::_1, qi::_2)]
                 | (operation[1] >> lexer.tokens["-="] > expression)[qi::_val = phx::new_<ast::operation::binary>(Operation::subtraction_and_assign, qi::_1, qi::_2)]
                 | (operation[1] >> lexer.tokens["*="] > expression)[qi::_val = phx::new_<ast::operation::binary>(Operation::multiplication_and_assign, qi::_1, qi::_2)]
                 | (operation[1] >> lexer.tokens["/="] > expression)[qi::_val = phx::new_<ast::operation::binary>(Operation::division_and_assign, qi::_1, qi::_2)]
                 | (operation[1])[qi::_val = qi::_1]
                 ;
    operation[1] = (operation[2] >> lexer.tokens["?"] > expression > lexer.tokens[":"] > expression)[qi::_val = phx::new_<ast::operation::ternary>(qi::_1, qi::_2, qi::_3)]
                 | (operation[2])[qi::_val = qi::_1]
                 ;
    operation[2] = operation[3][qi::_val = qi::_1] >>
                 *( (lexer.tokens["=="] > operation[3])[qi::_val = phx::new_<ast::operation::binary>(Operation::equal, qi::_val, qi::_1)]
                  | (lexer.tokens["!="] > operation[3])[qi::_val = phx::new_<ast::operation::binary>(Operation::not_equal, qi::_val, qi::_1)]
                 );
    operation[3] = operation[4][qi::_val = qi::_1] >>
                 *( (lexer.tokens["<"]  > operation[4])[qi::_val = phx::new_<ast::operation::binary>(Operation::less, qi::_val, qi::_1)]
                  | (lexer.tokens["<="] > operation[4])[qi::_val = phx::new_<ast::operation::binary>(Operation::less_or_equal, qi::_val, qi::_1)]
                  | (lexer.tokens[">"]  > operation[4])[qi::_val = phx::new_<ast::operation::binary>(Operation::more, qi::_val, qi::_1)]
                  | (lexer.tokens[">="] > operation[4])[qi::_val = phx::new_<ast::operation::binary>(Operation::more_or_equal, qi::_val, qi::_1)]
                 );
    operation[4] = operation[5][qi::_val = qi::_1] >>
                 *( (lexer.tokens["+"] > operation[5])[qi::_val = phx::new_<ast::operation::binary>(Operation::addition, qi::_val, qi::_1)]
                  | (lexer.tokens["-"] > operation[5])[qi::_val = phx::new_<ast::operation::binary>(Operation::subtraction, qi::_val, qi::_1)]
                 );
    operation[5] = operation[6][qi::_val = qi::_1] >>
                 *( (lexer.tokens["*"] > operation[6])[qi::_val = phx::new_<ast::operation::binary>(Operation::multiplication, qi::_val, qi::_1)]
                  | (lexer.tokens["/"] > operation[6])[qi::_val = phx::new_<ast::operation::binary>(Operation::division, qi::_val, qi::_1)]
                  | (lexer.tokens["%"] > operation[6])[qi::_val = phx::new_<ast::operation::binary>(Operation::modulo, qi::_val, qi::_1)]
                 );
    operation[6] = (lexer.tokens["++"] > operation[7])[qi::_val = phx::new_<ast::operation::unary>(Operation::prefix_inc, qi::_1)]
                 | (lexer.tokens["--"] > operation[7])[qi::_val = phx::new_<ast::operation::unary>(Operation::prefix_dec, qi::_1)]
                 | (lexer.tokens["+"] > operation[7])[qi::_val = phx::new_<ast::operation::unary>(Operation::unary_plus, qi::_1)]
                 | (lexer.tokens["-"] > operation[7])[qi::_val = phx::new_<ast::operation::unary>(Operation::unary_minus, qi::_1)]
                 | (lexer.ksizeof > lexer.tokens["("] > var > lexer.tokens[")"])[qi::_val = phx::new_<ast::operation::unary>(Operation::size_of, qi::_1)]
                 | (lexer.tokens["("] >> type > lexer.tokens[")"] > operation[7])[qi::_val = phx::new_<ast::operation::type_cast>(qi::_1, qi::_2)]
                 | (operation[7])[qi::_val = qi::_1]
                 ;
    operation[7] = operation[8][qi::_val = qi::_1] >>
                 *( (lexer.tokens["++"]) [qi::_val = phx::new_<ast::operation::unary>(Operation::suffix_inc, qi::_val)]
                  | (lexer.tokens["--"]) [qi::_val = phx::new_<ast::operation::unary>(Operation::suffix_dec, qi::_val)]
                  | (lexer.tokens["["] >> expression >> lexer.tokens["]"])[qi::_val = phx::new_<ast::operation::index>(qi::_val, qi::_1)]
                  | (lexer.tokens["["] > expression > lexer.tokens[":"] > expression > lexer.tokens["]"])[qi::_val = phx::new_<ast::operation::section>(qi::_val, qi::_1, qi::_2)]
                 );
    operation[8] = (lexer.tokens["("] > expression > lexer.tokens[")"]) [qi::_val = qi::_1]
                 | (lexer.tokens["{"] > (expression % lexer.tokens[","]) > lexer.tokens["}"]) [qi::_val = phx::new_<ast::operation::array>(qi::_1)]
               //  | lexer.ktrue         [qi::_val = phx::new_<ast::operation::boolLiteral>(true)]
               //  | lexer.kfalse        [qi::_val = phx::new_<ast::operation::boolLiteral>(false)]
               //  | lexer.intLiteral    [qi::_val = phx::new_<ast::operation::intLiteral>(qi::_1)]
               //  | lexer.realLiteral   [qi::_val = phx::new_<ast::operation::realLiteral>(qi::_1)]
               //  | lexer.stringLiteral [qi::_val = phx::new_<ast::operation::stringLiteral>(qi::_1)]
                 //| call [qi::_val = qi::_1]
                 | var  [qi::_val = qi::_1]
                 ;
    
    expression.name("expression");
    var.name("variable");
    //call.name("call function");
     */
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
