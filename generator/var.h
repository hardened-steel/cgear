// Project: CGear
//
//  Created on: 12.03.2016
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef VAR_H_
#define VAR_H_

#include <generator/overload.h>
#include "type.h"
#include "value.h"
#include "info.h"

namespace generator {

class type::var: public type
{
	type::info& info;
public:
	using instance = utility::instance<type::var>;
	var(type::info& info): info(info) {}
	var(const var& other): info(other.info) {}
	value::instance construct(generator::value& parameter) const {
		return value::instance{*this, info.create(parameter)};
	}
public:
	bool operator==(const type& other) const override {
		return dynamic_cast<const var*>(&other) != nullptr;
	}
	convert converting(const type& to) const override {
		if(*this == to) return { convert::same, [](generator::value& parameter){ return std::ref(parameter); } };
		return { convert::impossible };
	}
};

} /* namespace generator */

#endif /* VAR_H_ */
