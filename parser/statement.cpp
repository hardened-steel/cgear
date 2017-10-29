// Project: CGear
//
//  Created on: 23.04.2017
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#include <boost/phoenix/phoenix.hpp>
#include <ast/statement/function.h>
#include <ast/statement/variable.h>
#include <ast/statement/type.h>
#include "statement.h"

GStatement::GStatement(Lexer& lexer, GFunction& gfunction, GExpression& gexpression, GType& gtype)
: GStatement::base_type(statement, "statement")
{
	namespace qi = boost::spirit::qi;
	namespace phx = boost::phoenix;

	function = gfunction [qi::_val = phx::construct<ast::statement::function::instance>(qi::_1)];
	type     = gtype     [qi::_val = phx::construct<ast::statement::type::instance>(qi::_1)    ];
	variable = (
	             (gtype >> lexer.identifier >> lexer.tokens["="] >> gexpression) [qi::_val = phx::construct<ast::statement::variable>(qi::_1, qi::_2, qi::_3)]
	           | (gtype >> lexer.identifier >> lexer.tokens[";"]) [qi::_val = phx::construct<ast::statement::variable>(qi::_1, qi::_2)]
	           );
	statement = function | variable | type;
}

GStatement::~GStatement()
{
}
