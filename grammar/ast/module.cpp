// Project: CGear
//
//  Created on: 26.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#include "module.h"

void ast::module::accept(const ast::visitor& v) const {
	for(auto& statement: statements) {
		boost::apply_visitor(v, statement);
	}
}
