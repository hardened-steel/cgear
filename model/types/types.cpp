// Project: CGear
//
//  Created on: 11.12.2016
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#include <model/value.h>
#include "raw.h"
#include "var.h"
#include "ref.h"
#include "let.h"

namespace model {

type::convert type::raw::converting(const type& to) const {
	if(*this == to) return { 0, [](value& parameter){ return std::ref(parameter); } };
	return type::convert();
}

type::convert type::var::converting(const type& to) const {
	if(*this == to) return { 0, [](value& parameter){ return std::ref(parameter); } };
	if(auto ptr = dynamic_cast<const ref*>(&to)) {
		if(ptr->info == info) {
			return { 1, [&](value& parameter)->value::instance { return {to, parameter.getdata() }; } };
		}
	}
	if(auto ptr = dynamic_cast<const let*>(&to)) {
		if(ptr->info == info) {
			return { 1, [&](value& parameter)->value::instance { return {to, parameter.getdata() }; } };
		}
	}
	return type::convert();
}

type::convert type::ref::converting(const type& to) const {
	if(*this == to) return { 0, [](value& parameter){ return std::ref(parameter); } };
	if(auto ptr = dynamic_cast<const let*>(&to)) {
		if(ptr->info == info) {
			return { 1, [&](value& parameter)->value::instance { return {to, parameter.getdata() }; } };
		}
	}
	return type::convert();
}

type::convert type::let::converting(const type& to) const {
	if(*this == to) return { 0, [](value& parameter){ return std::ref(parameter); } };
	return type::convert();
}

} /* namespace model */
