// Project: CGear
//
//  Created on: 26.03.2016
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#include "../model/context.h"

namespace generator {

//context
void context::add(const std::string& name, value::instance value) {
	auto item = std::make_pair(name, std::move(value));
	identifiers.insert(std::move(item));
}

void context::add(const std::string& name, type::info type) {
	auto item = std::make_pair(name, std::move(type));
	types.insert(std::move(item));
}

type::info& context::gettype(const std::string& name) {
	auto it = types.find(name);
	if(it == types.end()) throw "not found";
	return it->second;
}

value& context::getvalue(const std::string& name) {
	auto it = identifiers.find(name);
	if(it == identifiers.end()) throw "not found";
	return it->second;
}

//local
type::info& context::local::gettype(const std::string& name) {
	auto it = types.find(name);
	if(it == types.end()) return parent.gettype(name);
	return it->second;
}

value& context::local::getvalue(const std::string& name) {
	auto it = identifiers.find(name);
	if(it == identifiers.end()) return parent.getvalue(name);
	return it->second;
}

//global
void context::global::add(const ast::operation::code& code, operation&& functor) {
	overload<value&>& operation = operations[code];
	operation += std::move(functor);
}

overload<value&>& context::global::getoperation(const ast::operation::code& code) {
	return operations[code];
}

} /* namespace generator */
