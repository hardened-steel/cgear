// Project: CGear
//
//  Created on: 11.12.2016
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#pragma once

#include <model/type.h>
#include "info.h"

namespace model {

class type::let: public type
{
	friend class type::var;
	friend class type::ref;
	type::info& info;
public:
	using instance = utility::instance<type::let>;
	let(type::info& info): info(info) {}
	let(const let& other): info(other.info) {}
public:
	bool operator==(const type& other) const override {
		if(auto ptr = dynamic_cast<const let*>(&other)) {
			return ptr->info == info;
		}
		return false;
	}
	convert converting(const type& to) const override;
};

} /* namespace model */

