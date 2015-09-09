// Project: CGear
//
//  Created on: 01.08.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#include <boost/phoenix/phoenix.hpp>
#include "../syntax/operation.h"
#include "execinfo.h"
#include "type.h"

class ast::type::t_bool: public ast::type::base
{
public:

};

GTypeName::GTypeName(Lexer& lexer): GTypeName::base_type(type, "type") {
	namespace qi = boost::spirit::qi;
	namespace phx = boost::phoenix;
}

GType::GType(Lexer& lexer): GType::base_type(type, "type") {
	namespace qi = boost::spirit::qi;
	namespace phx = boost::phoenix;
/*
    type = ( lexer.kbool   [qi::_val = phx::new_<ast::type::t_bool>()]
           | lexer.kint    [qi::_val = phx::new_<ast::type::base>(ast::type::base::int_ , true)]
           | lexer.kreal   [qi::_val = phx::new_<ast::type::base>(ast::type::base::real , true)]
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
           )
         ;
*/
}

