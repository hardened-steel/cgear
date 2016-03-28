// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef BINARY_H
#define BINARY_H

#include <utility/instance.hpp>
#include "operation.h"
#include "code.h"

class ast::operation::binary: public ast::operation
{
	ast::operation::instance left;
	ast::operation::instance right;
	ast::operation::code code;
public:
	using instance = utility::instance<ast::operation::binary, utility::copyable>;
public:
	binary(const binary&) = default;
	binary(binary&&) = default;
	binary(ast::operation::code code, ast::operation::instance left, ast::operation::instance right)
	: left(std::move(left)), right(std::move(right)), code(std::move(code)) {}
	generator::value& codegen(generator::context& context) const override;
};

#endif /* BINARY_H */
