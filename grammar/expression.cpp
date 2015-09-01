#include <boost/phoenix/phoenix.hpp>
#include <string>
#include "expression.h"
#include "../pool.h"

class ast::operation::binary
{
	friend ast::operation;
public:
	class implementation: public ast::operation::base
	{
		ast::operation left;
		ast::operation right;
		ast::operation::code code;
	public:
		implementation(ast::operation::code code, ast::operation left, ast::operation right): left(left), right(right), code(code) {}
		void* operator new(size_t size) {
			return memory_pool.allocate(size);
		}
		void operator delete(void* pointer) {
			memory_pool.deallocate(pointer);
		}
	};
public:
	binary(ast::operation::code code, ast::operation left, ast::operation right): impl(new implementation(code, left, right)) {}
private:
	static pool<sizeof(implementation), 1024> memory_pool;
	std::shared_ptr<implementation> impl;
};

class ast::operation::unary
{
	friend ast::operation;
public:
	class implementation: public ast::operation::base
	{
		ast::operation op;
		ast::operation::code code;
	public:
		implementation(ast::operation::code code, ast::operation op): op(op), code(code) {}
		void* operator new(size_t size) {
			return memory_pool.allocate(size);
		}
		void operator delete(void* pointer) {
			memory_pool.deallocate(pointer);
		}
	};
public:
	unary(ast::operation::code code, ast::operation op): impl(new implementation(code, op)) {}
private:
	static pool<sizeof(implementation), 1024> memory_pool;
	std::shared_ptr<implementation> impl;
};

class ast::operation::ternary
{
	friend ast::operation;
public:
	class implementation: public ast::operation::base
	{
		ast::operation true_action;
		ast::operation false_action;
		ast::operation condition;
	public:
		implementation(ast::operation condition, ast::operation true_action, ast::operation false_action): true_action(true_action), false_action(false_action), condition(condition) {}
		void* operator new(size_t size) {
			return memory_pool.allocate(size);
		}
		void operator delete(void* pointer) {
			memory_pool.deallocate(pointer);
		}
	};
public:
	ternary(ast::operation condition, ast::operation true_action, ast::operation false_action): impl(new implementation(condition, true_action, false_action)) {}
private:
	static pool<sizeof(implementation), 1024> memory_pool;
	std::shared_ptr<implementation> impl;
};

class ast::operation::var
{
friend ast::operation;
private:
	class implementation: public ast::operation::base
	{
		token::identifier id;
	public:
		implementation(token::identifier id): id(id) {}
		void* operator new(size_t size) {
			return memory_pool.allocate(size);
		}
		void operator delete(void* pointer) {
			memory_pool.deallocate(pointer);
		}
	};
public:
	var(token::identifier id): impl(new implementation(id)) {}
private:
	static pool<sizeof(implementation), 1024> memory_pool;
	std::shared_ptr<implementation> impl;
};

class ast::operation::call
{
friend ast::operation;
private:
	class implementation: public ast::operation::base
	{
		token::identifier id;
		std::vector<ast::operation> params;
	public:
		implementation(token::identifier id, const std::vector<ast::operation>& params): id(id), params(params) {}
		void* operator new(size_t size) {
			return memory_pool.allocate(size);
		}
		void operator delete(void* pointer) {
			memory_pool.deallocate(pointer);
		}
	};
public:
	call(token::identifier id, const std::vector<ast::operation>& params = {}): impl(new implementation(id, params)) {}
private:
	static pool<sizeof(implementation), 1024> memory_pool;
	std::shared_ptr<implementation> impl;
};

GExpression::GExpression(Lexer& lexer): GExpression::base_type(expression), type(lexer)
{
    namespace qi = boost::spirit::qi;
    namespace phx = boost::phoenix;

    var  = lexer.identifier[qi::_val = phx::construct<ast::operation::var>(qi::_1)];
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
                 | (lexer.ksizeof > lexer.tokens["("] > var > lexer.tokens[")"])[qi::_val = phx::construct<ast::operation::unary>(ast::operation::code::size_of, qi::_1)]
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
                 | var  [qi::_val = qi::_1]
                 ;
    
    expression.name("expression");
    var.name("variable");
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
