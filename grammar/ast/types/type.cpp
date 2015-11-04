// Project: CGear
//
//  Created on: 31.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#include "visitor.h"

void ast::type::t_int::accept(ast::type::visitor& v) { v.visit(*this); }
void ast::type::tuple::accept(ast::type::visitor& v) { v.visit(*this); }
void ast::type::name::accept(ast::type::visitor& v) { v.visit(*this); }
