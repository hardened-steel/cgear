// Project: CGear
//
//  Created on: 31.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#include "context.h"

#include "grammar/ast/function/function.h"
#include "grammar/ast/function/prototype.h"
#include "grammar/ast/function/definition.h"
#include "grammar/ast/function/visitor.h"

#include "grammar/ast/operators/operator.h"
#include "grammar/ast/operators/block.h"
#include "grammar/ast/operators/calc.h"
#include "grammar/ast/operators/if.h"
#include "grammar/ast/operators/repeat.h"
#include "grammar/ast/operators/return.h"
#include "grammar/ast/operators/variable.h"
#include "grammar/ast/operators/while.h"
#include "grammar/ast/operators/nope.h"
#include "grammar/ast/operators/visitor.h"

#include "grammar/ast/operations/operation.h"
#include "grammar/ast/operations/binary.h"
#include "grammar/ast/operations/call.h"
#include "grammar/ast/operations/ternary.h"
#include "grammar/ast/operations/unary.h"
#include "grammar/ast/operations/variable.h"
#include "grammar/ast/operations/literal.h"
#include "grammar/ast/operations/visitor.h"

#include "grammar/ast/types/type.h"
#include "grammar/ast/types/name.h"
#include "grammar/ast/types/int.h"
#include "grammar/ast/types/tuple.h"
#include "grammar/ast/types/visitor.h"

#include "grammar/ast/module.h"
#include "grammar/ast/visitor.h"

#include <iostream>

/*
class visitor: public ast::function::visitor, public ast::visitor::base
{
public:
	void visit(ast::function::prototype&) override {
		std::cout << "prototype" << std::endl;
	}
	void visit(ast::function::definition&) override {
		std::cout << "definition" << std::endl;
	}
	void visit(const ast::function& f) override {
		std::cout << "function" << std::endl;
		f.accept(*this);
	}
	void visit(const ast::type&) override {
		std::cout << "type" << std::endl;
	}
};
*/
void visit_all(ast::module m) {
	//visitor v;
	//m.accept(ast::visitor(v));
}
