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
