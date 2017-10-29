// Project: CGear
//
//  Created on: 12.03.2016
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#pragma once

#include <map>
#include <model/overload.h>
#include <model/type.h>
#include <model/value.h>

namespace model {

class type::info
{
	std::string name;
	overload constructors;
	std::map<std::string, type::instance> fields;
	std::map<std::string, overload>       operations;
	std::function<void(value&)> destructor = [](value&){};
public:
	info(const std::string& id): name(id) {}
	void operator+=(overload::function&& creator) {
		constructors += std::move(creator);
	}
public:
	value::instance create(value& parameter) const {
		return constructors.call(parameter);
	}
	value::instance call(const std::string& operation, value& object, value& parameter) const;
	bool operator==(const info& other) const;
	void destroy(value& object) const {
		destructor(object);
	}
};

} /* namespace model */

