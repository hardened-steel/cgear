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

class type::var: public type
{
	friend class type::ref;
	friend class type::let;
	type::info& info;
public:
	using instance = utility::instance<type::var>;
	var(type::info& info): info(info) {}
	var(const var& other): info(other.info) {}
public:
	bool operator==(const type& other) const override {
		if(auto ptr = dynamic_cast<const var*>(&other)) {
			return ptr->info == info;
		}
		return false;
	}
	convert converting(const type& to) const override;
};

} /* namespace model */
