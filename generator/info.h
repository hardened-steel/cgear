// Project: CGear
//
//  Created on: 12.03.2016
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef INFO_H_
#define INFO_H_

#include <map>
#include <ast/operations/code.h>
#include <generator/overload.h>
#include "type.h"
#include "value.h"

namespace generator {

class type::info
{
	friend class var;
private:
	overload<value::data::instance> constructors;
	std::map<std::string, type::info> fields;
	std::map<ast::operation::code, overload<value&>> operations;
	std::function<void(generator::value&)> destructor = [](generator::value&){};
public:
	using constructor = typename overload<value::data::instance>::function;
	void operator+=(constructor&& creator) {
		constructors += std::move(creator);
	}
private:
	value::data::instance create(generator::value& parameter) const {
		return constructors.call(parameter);
	}
	value& call(ast::operation::code& code, generator::value& parameter) {
		return operations[code].call(parameter);
	}
	void destroy(generator::value& object) const {
		destructor(object);
	}
};

} /* namespace generator */

#endif /* INFO_H_ */
