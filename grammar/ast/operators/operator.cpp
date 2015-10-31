// Project: CGear
//
//  Created on: 03.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#include "operator.h"
#include "block.h"
#include "calc.h"
#include "if.h"
#include "repeat.h"
#include "return.h"
#include "variable.h"
#include "while.h"
#include "nope.h"

pool<sizeof(ast::instruction::block::implementation)>    ast::instruction::block::memory_pool;
pool<sizeof(ast::instruction::calc::implementation)>     ast::instruction::calc::memory_pool;
pool<sizeof(ast::instruction::if_i::implementation)>     ast::instruction::if_i::memory_pool;
pool<sizeof(ast::instruction::ifelse_i::implementation)> ast::instruction::ifelse_i::memory_pool;
pool<sizeof(ast::instruction::repeat_i::implementation)> ast::instruction::repeat_i::memory_pool;
pool<sizeof(ast::instruction::return_i::implementation)> ast::instruction::return_i::memory_pool;
pool<sizeof(ast::instruction::variable::implementation)> ast::instruction::variable::memory_pool;
pool<sizeof(ast::instruction::while_i::implementation)>  ast::instruction::while_i::memory_pool;
//pool<sizeof(ast::instruction::for_i::implementation)> ast::instruction::for_i::memory_pool;
ast::instruction::nope::implementation ast::instruction::nope::snope;

#include "visitor.h"

void ast::instruction::block::implementation::accept(ast::instruction::visitor& v) { v.visit(*this); }
void ast::instruction::calc::implementation::accept(ast::instruction::visitor& v) { v.visit(*this); }
void ast::instruction::if_i::implementation::accept(ast::instruction::visitor& v) { v.visit(*this); }
void ast::instruction::ifelse_i::implementation::accept(ast::instruction::visitor& v) { v.visit(*this); }
void ast::instruction::repeat_i::implementation::accept(ast::instruction::visitor& v) { v.visit(*this); }
void ast::instruction::return_i::implementation::accept(ast::instruction::visitor& v) { v.visit(*this); }
void ast::instruction::variable::implementation::accept(ast::instruction::visitor& v) { v.visit(*this); }
void ast::instruction::while_i::implementation::accept(ast::instruction::visitor& v) { v.visit(*this); }
void ast::instruction::nope::implementation::accept(ast::instruction::visitor& v) {}
