// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef TYPE_H_
#define TYPE_H_

#include "grammar/ast/instance.h"
#include "grammar/ast/pool.h"
#include "grammar/ast/ast.h"
#include <memory>

class ast::type: public ast::node
{
public:
	class visitor;
	class t_bool;
	class t_int;
	class t_real;
	class t_void;
	class array;
	class pointer;
	class tuple;
	class t_class;
	class t_struct;
	class name;
public:
	using instance = instance_t<ast::type>;
public:
	virtual void accept(ast::type::visitor& v) const;
	virtual ~type() {}
};

#endif /* TYPE_H_ */
