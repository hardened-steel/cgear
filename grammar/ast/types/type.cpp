// Project: CGear
//
//  Created on: 31.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#include "type.h"
#include "name.h"
#include "int.h"
#include "tuple.h"

pool<sizeof(ast::type::t_int::implementation)>  ast::type::t_int::memory_pool;
pool<sizeof(ast::type::tuple::implementation)> ast::type::tuple::memory_pool;
pool<sizeof(ast::type::name::implementation)> ast::type::name::memory_pool;

#include "visitor.h"

void ast::type::t_int::implementation::accept(ast::type::visitor& v) { v.visit(*this); }
void ast::type::tuple::implementation::accept(ast::type::visitor& v) { v.visit(*this); }
void ast::type::name::implementation::accept(ast::type::visitor& v) { v.visit(*this); }
