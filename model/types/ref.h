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

class type::ref: public type
{
	friend class type::let;
	friend class type::var;
	type::info& info;
public:
	using instance = utility::instance<type::ref>;
	ref(type::info& info): info(info) {}
	ref(const ref& other): info(other.info) {}
public:
	bool operator==(const type& other) const override {
		if(auto ptr = dynamic_cast<const ref*>(&other)) {
			return ptr->info == info;
		}
		return false;
	}
	convert converting(const type& to) const override;
};

} /* namespace model */
