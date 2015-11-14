// Project: CGear
//
//  Created on: 31.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef CONTEXT_H
#define CONTEXT_H

#include <list>
#include <map>
#include <string>
#include <algorithm>
#include "grammar/ast/types/type.h"

class context
{
	std::multimap<std::string, ast::type::instance> identifiers;
public:
    context() {}
    ~context() {}

    void add_name(const std::string& name, ast::type type) {
        identifiers.insert(std::pair<std::string, ast::type::instance>(name, type));
    }

    bool find_name(const std::string& name, const ast::type::instance& type) {
		//auto begin = identifiers.find(name);
		//auto end   = identifiers.end();
		//return end != std::find_if(begin, end, [&](const auto& it) { return it.second == type; });
    	return true;
    }

    bool find_name(const std::string& name) {
        return false;
		auto begin = identifiers.find(name);
		auto end   = identifiers.end();
		return begin != end;
    }
};

#endif // CONTEXT_H

