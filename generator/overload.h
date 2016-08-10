// Project: CGear
//
//  Created on: 12.03.2016
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef OVERLOAD_H_
#define OVERLOAD_H_

#include <algorithm>
#include <utility>
#include <vector>
#include <tuple>
#include <list>

#include <utility/instance.hpp>
#include "value.h"
#include "type.h"
#include "null.h"
#include "tuple.h"

namespace generator {

template<class T> class overload
{
	template<class Functor, class Tuple, std::size_t... Index> class caster
	{
	public:
		static auto call(Functor functor, value& parameter) {
			value::tuple& parameters = dynamic_cast<value::tuple&>(parameter);
			return functor(dynamic_cast<typename std::tuple_element<Index, Tuple>::type>(parameters[Index].getdata())...);
		}
	};
public:
	class function
	{
		friend overload;
		const generator::type& type;
		std::function<T(generator::value&)> functor;
	public:
		template<class ...TArgs> function(const generator::type& type, std::function<T(TArgs...)> functor): type(type) {
			this->functor = [=](value& parameter) {
				using Functor = std::function<T(TArgs...)>;
				using Tuple   = std::tuple<TArgs...>;
				return caster<Functor, Tuple, std::index_sequence_for<TArgs...>{}>::call(functor, parameter);
			};
		}
		function(const generator::type& type, std::function<T(generator::value&)> functor): type(type), functor(std::move(functor)) {}
		T operator()(generator::value& parameter) const { return functor(parameter); }
	};
public:
	T call(generator::value& parameter) const;
	void operator+=(function&& f) {
		functions.push_back(std::move(f));
	}
private:
	std::list<function> functions;
};

template<class T> T overload<T>::call(generator::value& parameter) const {
	using convert = std::tuple<type::convert, const function&>;
	const generator::type& type = parameter.gettype();
	std::vector<convert> overloads;

	overloads.reserve(functions.size());
	for(auto& function: functions) {
		type::convert convert_info = type.converting(function.type);
		if(convert_info.cost != type::convert::impossible) {
			overloads.emplace_back(std::move(convert_info), function);
		}
	}
	if(overloads.empty()) throw "void functor";
	auto it = std::min_element(overloads.cbegin(), overloads.cend(), [](const convert& a, const convert& b) {
		const type::convert& cost_a = std::get<type::convert>(a);
		const type::convert& cost_b = std::get<type::convert>(b);
		if(cost_a == cost_b) throw "call is ambiguous";
		return cost_a < cost_b;
	});
	auto& functor   = std::get<const function&>(*it);
	auto& convertor = std::get<type::convert>(*it);
	return functor(convertor.functor(parameter));
}

} /* namespace generator */

#endif /* OVERLOAD_H_ */
