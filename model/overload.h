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

#include "type.h"
#include "value.h"

namespace model {

class overload
{
	/*template<class Functor, class Tuple, std::size_t... Index> class caster
	{
	public:
		static auto call(Functor functor, value& parameter) {
			value::tuple& parameters = dynamic_cast<value::tuple&>(parameter);
			return functor(dynamic_cast<typename std::tuple_element<Index, Tuple>::type>(parameters[Index].getdata())...);
		}
	};*/
public:
	class function
	{
		friend overload;
		const model::type& type;
		std::function<value::instance(value&)> functor;
	public:
		/*template<class ...TArgs> function(const model::type& type, std::function<model::value::instance(TArgs...)> functor): type(type) {
			this->functor = [=](value& parameter) {
				using Functor = std::function<model::value::instance(TArgs...)>;
				using Tuple   = std::tuple<TArgs...>;
				return caster<Functor, Tuple, std::index_sequence_for<TArgs...>{}>::call(functor, parameter);
			};
		}*/
		function(const model::type& type, std::function<value::instance(value&)> functor): type(type), functor(std::move(functor)) {}
		value::instance operator()(value& parameter) const { return functor(parameter); }
	};
public:
	value::instance call(value& parameter) const;
	void operator+=(function&& f) {
		functions.push_back(std::move(f));
	}
private:
	std::list<function> functions;
};

} /* namespace model */

#endif /* OVERLOAD_H_ */
