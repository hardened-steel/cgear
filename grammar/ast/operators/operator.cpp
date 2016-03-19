// Project: CGear
//
//  Created on: 03.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#include "visitor.h"

void ast::instruction::block::accept(ast::instruction::visitor& v) const { v.visit(*this); }
void ast::instruction::calc::accept(ast::instruction::visitor& v) const { v.visit(*this); }
void ast::instruction::if_i::accept(ast::instruction::visitor& v) const { v.visit(*this); }
void ast::instruction::ifelse_i::accept(ast::instruction::visitor& v) const { v.visit(*this); }
//void ast::instruction::repeat_i::accept(ast::instruction::visitor& v) const { v.visit(*this); }
void ast::instruction::return_i::accept(ast::instruction::visitor& v) const { v.visit(*this); }
void ast::instruction::variable::accept(ast::instruction::visitor& v) const { v.visit(*this); }
void ast::instruction::while_i::accept(ast::instruction::visitor& v) const { v.visit(*this); }
void ast::instruction::nope::accept(ast::instruction::visitor& v) const {}
void ast::instruction::accept(ast::instruction::visitor& v) const {}
