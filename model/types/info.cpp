// Project: CGear
//
//  Created on: 12.03.2016
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#include "info.h"

namespace model {

value::instance type::info::call(const std::string& operation, value& object, value& parameter) const {
	auto it = operations.find(operation);
	if(it != operations.end()) {
		const overload &functions = it->second;
		return functions.call(parameter);
	}
	throw "no method name";
}

bool type::info::operator==(const type::info& other) const {
	return name == other.name;
}

} /* namespace model */
