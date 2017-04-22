// Project: CGear
//
//  Created on: 21.03.2016
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef MODEL_TUPLE_H_
#define MODEL_TUPLE_H_

#include <vector>
#include <utility/instance.hpp>

#include "type.h"
#include "value.h"

namespace model {

class type::tuple: public type
{
	std::vector<type::instance> types;
public:
	tuple(std::vector<type::instance> types): types(std::move(types)) {}
	bool operator==(const type& other) const override;
	convert converting(const type& to) const override;
	type& operator[](size_t index) {
		return types.at(index);
	}
	const type& operator[](size_t index) const {
		return types.at(index);
	}
};

class value::tuple: public value::data
{
	std::vector<value::instance> values;
public:
	tuple(std::vector<value::instance>&& values): values(std::move(values)) {}
	value& operator[](size_t index) {
		return values.at(index);
	}
	const value& operator[](size_t index) const {
		return values.at(index);
	}
};

} /* namespace model */

#endif /* MODEL_TUPLE_H_ */
