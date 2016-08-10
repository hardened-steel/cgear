// Project: CGear
//
//  Created on: 12.03.2016
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#include "null.h"

namespace generator {

type::null value::null::null_t;
value::data value::null::null_d;
null_t null;

value::null::null(): value(null_t, null_d) {}

} /* namespace generator */
