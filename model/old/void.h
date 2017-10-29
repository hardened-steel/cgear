// Project: CGear
//
//  Created on: 12.03.2016
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef VOID_H_
#define VOID_H_

#include <instance.hpp>

#include "../model/type.h"

namespace generator {

class type::void_t: public type
{
	bool operator==(const type& other) const override {
		return dynamic_cast<const void_t*>(&other) != nullptr;
	}
	convert converting(const type& to) const override {
		return {convert::impossible};
	}
public:
	using instance = utility::instance<void_t>;
};

} /* namespace generator */

#endif /* VOID_H_ */
