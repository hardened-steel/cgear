// Project: CGear
//
//  Created on: 12.03.2016
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef NULL_H_
#define NULL_H_

#include "../model/type.h"
#include "../process/value.h"

namespace generator {

class type::null: public type
{
	bool operator==(const type& other) const override {
		return dynamic_cast<const null*>(&other) != nullptr;
	}
	convert converting(const type& to) const override {
		if(*this == to) return {convert::same, [](generator::value& parameter) { return std::ref(parameter); }};
		return {convert::impossible};
	}
};

class value::null: public value, public value::data
{
	static type::null null_t;
	static value::data null_d;
public:
	null();
};

class null_t: public type::null, public value::null {};
extern null_t null;

} /* namespace generator */

#endif /* NULL_H_ */
