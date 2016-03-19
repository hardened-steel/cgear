// Project: CGear
//
//  Created on: 01.08.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#include <boost/phoenix/phoenix.hpp>
//#include "ast/types/name.h"
//#include "ast/types/tuple.h"
#include "ast/types/int.h"
#include "type.h"

GType::GType(Lexer& lexer, GTypeName& typeName): GType::base_type(type, "type") {
	namespace qi = boost::spirit::qi;
	namespace phx = boost::phoenix;

    type = typeName[qi::_val = qi::_1]
		 //| lexer.identifier[qi::_val = phx::construct<ast::type::name::instance>(qi::_1)]
         ;

}

GTypeName::GTypeName(Lexer& lexer): GTypeName::base_type(type, "type identifier") {
	namespace qi = boost::spirit::qi;
	namespace phx = boost::phoenix;

	type = lexer.kint[qi::_val = phx::construct<ast::type::t_int::instance>()]
		 //| lexer.identifier[qi::_val = phx::construct<ast::type::name::instance>(qi::_1)]
		 ;
}
