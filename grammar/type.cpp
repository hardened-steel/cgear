// Project: CGear
//
//  Created on: 01.08.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#include <boost/phoenix/phoenix.hpp>
#include "ast/types/tuple.h"
#include "ast/types/int.h"
#include "type.h"

class type_name
{
	friend ast::type;
protected:
	class implementation: public ast::type::base
	{
		token::identifier name;
	public:
		implementation(token::identifier name): name(name) {}
		void* operator new(size_t size) {
			return memory_pool.allocate(size);
		}
		void operator delete(void* pointer) {
			memory_pool.deallocate(pointer);
		}
	};
public:
	type_name(token::identifier name): impl(new implementation(name)) {}
private:
	static pool<sizeof(implementation)> memory_pool;
	std::shared_ptr<implementation> impl;
};

pool<sizeof(type_name::implementation)> type_name::memory_pool;

GType::GType(Lexer& lexer): GType::base_type(type, "type") {
	namespace qi = boost::spirit::qi;
	namespace phx = boost::phoenix;

    type = /*( lexer.kbool   [qi::_val = phx::new_<ast::type::t_bool>()]
           | */lexer.kint    [qi::_val = phx::construct<ast::type::t_int>()]
           /*| lexer.kreal   [qi::_val = phx::new_<ast::type::base>(ast::type::base::real , true)]
           | lexer.kchar   [qi::_val = phx::new_<ast::type::base>(ast::type::base::char_, true)]
           | lexer.kvoid   [qi::_val = phx::new_<ast::type::base>(ast::type::base::void_, true)]
           | (lexer.karray > lexer.tokens["<"] > type > lexer.tokens[">"]) [qi::_val = phx::new_<ast::type::array>(qi::_1, true)]
           )
           |
           lexer.kconst >>
           ( lexer.kbool   [qi::_val = phx::new_<st::type::base>(ast::type::base::bool_, false)]
           | lexer.kint    [qi::_val = phx::new_<st::type::base>(ast::type::base::int_ , false)]
           | lexer.kreal   [qi::_val = phx::new_<st::type::base>(ast::type::base::real , false)]
           | lexer.kchar   [qi::_val = phx::new_<st::type::base>(ast::type::base::char_, false)]
           | lexer.kvoid   [qi::_val = phx::new_<st::type::base>(ast::type::base::void_, false)]
           | (lexer.karray > lexer.tokens["<"] > type > lexer.tokens[">"]) [qi::_val = phx::new_<ast::type::array>(qi::_1, false)]
           )*/
		   | lexer.identifier[qi::_val = phx::construct<type_name>(qi::_1)]
         ;

}

GTypeName::GTypeName(Lexer& lexer): GTypeName::base_type(type, "type identifier") {
	namespace qi = boost::spirit::qi;
	namespace phx = boost::phoenix;

	type = lexer.kint      [qi::_val = phx::construct<ast::type::t_int>()]
		 | lexer.identifier[qi::_val = phx::construct<type_name>(qi::_1)]
		 ;
}
