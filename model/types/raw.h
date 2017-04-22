// Project: CGear
//
//  Created on: 11.12.2016
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef MODEL_TYPES_RAW_H_
#define MODEL_TYPES_RAW_H_

#include <model/type.h>
#include "info.h"

namespace model {

class type::raw: public type
{
	type::info& info;
public:
	using instance = utility::instance<type::raw>;
	raw(type::info& info): info(info) {}
	raw(const raw& other): info(other.info) {}
public:
	bool operator==(const type& other) const override {
		if(auto ptr = dynamic_cast<const raw*>(&other)) {
			return ptr->info == info;
		}
		return false;
	}
	convert converting(const type& to) const override;
};

} /* namespace model */

#endif /* MODEL_TYPES_RAW_H_ */
