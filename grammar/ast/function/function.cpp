// Project: CGear
//
//  Created on: 03.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#include "function.h"
#include "prototype.h"
#include "definition.h"

pool<sizeof(ast::function::prototype::implementation)>  ast::function::prototype::memory_pool;
pool<sizeof(ast::function::definition::implementation)> ast::function::definition::memory_pool;

#include "visitor.h"

void ast::function::prototype::implementation::accept(ast::function::visitor& v) { v.visit(*this); }
void ast::function::definition::implementation::accept(ast::function::visitor& v) { v.visit(*this); }
