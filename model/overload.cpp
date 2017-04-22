// Project: CGear
//
//  Created on: 12.03.2016
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#include "overload.h"

namespace model {

value::instance overload::call(value& parameter) const {
	using convert = std::tuple<type::convert, const overload::function&>;
	const type& type = parameter.gettype();
	std::vector<convert> overloads;

	overloads.reserve(functions.size());
	for(auto& function: functions) {
		type::convert convert_info = type.converting(function.type);
		if(convert_info) {
			overloads.emplace_back(std::move(convert_info), function);
		}
	}
	if(overloads.empty()) throw "void functor";
	auto it = std::min_element (
		overloads.cbegin(),
		overloads.cend(),
		[](const convert& a, const convert& b) {
			const type::convert& cost_a = std::get<type::convert>(a);
			const type::convert& cost_b = std::get<type::convert>(b);
			if(cost_a == cost_b) throw "call is ambiguous";
			return cost_a < cost_b;
		}
	);
	auto& functor   = std::get<const overload::function&>(*it);
	auto& convertor = std::get<type::convert>(*it);
	return functor(convertor(parameter));
}

} /* namespace model */
