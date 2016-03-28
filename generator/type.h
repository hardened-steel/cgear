// Project: CGear
//
//  Created on: 12.03.2016
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef TYPE_H_
#define TYPE_H_

#include "value.h"
#include <utility/instance.hpp>
#include <functional>

namespace generator {

class type
{
public:
	using instance = utility::instance<type>;
	struct convert
	{
		enum { impossible = -1, same, simple, difficult, custom } type;
		std::function<generator::value&(generator::value&)> functor;
		unsigned cost = 1;
	public:
		bool operator<(const convert& other) const {
			if(other.type == type) return other.cost > cost;
			return other.type > type;
		}
		bool operator==(const convert& other) const {
			return (other.type == type) && (other.cost == cost);
		}
	};
	class null;
	class info;
	class tuple;
	class raw;
	class var;
public:
	virtual bool operator==(const type& other) const = 0;
	virtual convert converting(const type& to) const = 0;
	virtual ~type() {}
};

/*class type::raw: public type
{
	type::info& info;
public:
	using instance = utility::instance<type::var>;
	raw(type::info& info): info(info) {}
	raw(const var& other): info(other.info) {}
	value::instance construct(generator::value& parameter) const {
		return value::instance{*this, info.create(parameter)};
	}
public:
	bool operator==(const type& other) const override {
		return dynamic_cast<const raw*>(&other) != nullptr;
	}
	convert converting(const type& to) const override {
		if(*this == to) return { convert::simple, [](generator::value& parameter){ return std::ref(parameter); } };
		return { convert::impossible };
	}
};*/

} /* namespace generator */

#endif /* TYPE_H_ */
