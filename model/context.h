// Project: CGear
//
//  Created on: 31.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef CONTEXT_H
#define CONTEXT_H

#include <map>
#include <string>
#include <algorithm>
#include <ast/operations/code.h>
#include "../model/info.h"
#include "../process/overload.h"
#include "../process/overload.h"
#include "../process/value.h"

namespace generator {

class context
{
public:
	using operation = typename overload<value&>::function;
	class global;
	class local;
protected:
	std::map<std::string, type::info> types;
	std::map<std::string, value::instance> identifiers;
public:
    virtual ~context() {}

    virtual void add(const std::string& name, value::instance value);
    virtual void add(const std::string& name, type::info type);

    virtual type::info& gettype(const std::string& name);
    virtual value& getvalue(const std::string& name);

	virtual void add(const ast::operation::code& code, operation&& functor) = 0;
	virtual overload<value&>& getoperation(const ast::operation::code& code) = 0;
};

class context::local: public context
{
	context& parent;
public:
	local(context& parent): parent(parent) {}
    ~local() {}

    type::info& gettype(const std::string& name) override;
    value& getvalue(const std::string& name)     override;

	void add(const ast::operation::code& code, operation&& functor)  override { parent.add(code, std::move(functor)); }
	overload<value&>& getoperation(const ast::operation::code& code) override { return parent.getoperation(code);     }
};

class context::global: public context
{
protected:
	std::map<ast::operation::code, overload<value&>> operations;
public:
	void add(const ast::operation::code& code, operation&& functor) override;
	overload<value&>& getoperation(const ast::operation::code& code) override;
};

} /* namespace generator */

#endif // CONTEXT_H

