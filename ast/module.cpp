// Project: CGear
//
//  Created on: 26.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#include "module.h"
#include "visitor.h"

void ast::module::accept(ast::module::visitor& v) const {
	for(auto& statement: statements) {
		boost::apply_visitor(v, statement);
	}
}
