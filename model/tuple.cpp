// Project: CGear
//
//  Created on: 11.12.2016
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#include <list>
#include "tuple.h"

namespace model {

bool type::tuple::operator==(const type& other) const {
	if(auto ptr = dynamic_cast<const type::tuple*>(&other)) {
		return ptr->types == types;
	}
	return false;
}

type::convert type::tuple::converting(const type& to) const {
	if(auto other = dynamic_cast<const type::tuple*>(&to)) {
		if(other->types.size() == types.size()) {
			unsigned cost = 0;
			std::list<type::convert::function> coverts;
			for(size_t i = 0; i < types.size(); ++i) {
				type::convert iconvert = types[i]->converting(other->types[i]);
				if(iconvert) {
					cost += iconvert.cost();
					coverts.emplace_back(iconvert.func());
				} else {
					return type::convert();
				}
			}
			return type::convert (
				cost,
				[=](value& v)->value::instance {
					auto& itv = dynamic_cast<value::tuple&>(v);

					std::vector<value::instance> values;
					values.reserve(coverts.size());

					size_t i = 0;
					for(auto& iconvert: coverts) {
						values.emplace_back(iconvert(itv[i++]));
					}
					utility::instance<value::tuple> otv(std::move(values));
					return {*this, std::move(otv)};
				}
			);
		}
	}
	return type::convert();
}

} /* namespace model */
