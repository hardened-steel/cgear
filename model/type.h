// Project: CGear
//
//  Created on: 12.03.2016
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#pragma once

#include <utility/instance.hpp>
#include <map>
#include <functional>
#include "value.h"

namespace model {

class type
{
public:
	using instance = utility::instance<type>;
	class convert
	{
	public:
		using function = std::function<value::instance(value&)>;
	public:
		convert() = default;
		convert(unsigned cost, function functor): cost_(cost), functor(functor) {}
		bool operator<(const convert& other) const {
			return cost_ < other.cost_;
		}
		bool operator==(const convert& other) const {
			return other.cost_ == cost_;
		}
		operator bool() const { return cost_ > 0; }
		unsigned cost() const { return cost_;     }
		function func() const { return functor;   }
		value::instance operator()(value& v) const { return functor(v); }
	private:
		unsigned cost_ = 0;
		function functor = [](value&)->value::instance { throw "bad convert"; };
	};
	class info;
	class tuple;
	class raw;
	class var;
	class ref;
	class let;
public:
	virtual bool operator==(const type& other) const = 0;
	virtual convert converting(const type& to) const = 0;
	virtual ~type() {}
};

} /* namespace model */

