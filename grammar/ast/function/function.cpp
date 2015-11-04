// Project: CGear
//
//  Created on: 03.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#include "function.h"
#include "prototype.h"
#include "definition.h"
#include "visitor.h"

void ast::function::prototype::accept(ast::function::visitor& v) { v.visit(*this); }
void ast::function::definition::accept(ast::function::visitor& v) { v.visit(*this); }
