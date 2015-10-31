// Project: CGear
//
//  Created on: 10.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef FUNCTION_PROTOTYPE_H_
#define FUNCTION_PROTOTYPE_H_

#include <vector>
#include "grammar/lexer/token.h"
#include "grammar/ast/types/type.h"
#include "function.h"

class ast::function::prototype
{
	friend ast::function;
public:
	class parameter
	{
		ast::type type;
		token::identifier name;
	public:
		parameter() {}
		parameter(ast::type type, token::identifier name): type(type), name(name) {}
		parameter(const parameter& other): type(other.type), name(other.name) {}
		parameter& operator = (const parameter& other) {
			type = other.type;
			name = other.name;
			return *this;
		}
		parameter& operator = (parameter&& other) {
			type = std::move(other.type);
			name = std::move(other.name);
			return *this;
		}
	};
protected:
	class implementation: public ast::function::base
	{
		token::identifier name;
		std::vector<parameter> parameters;
		ast::type returnType;
	public:
		implementation(token::identifier name, std::vector<parameter> parameters, ast::type returnType): name(name), parameters(parameters), returnType(returnType) {}
		void accept(ast::function::visitor&) override;
		void* operator new(size_t size) {
			return memory_pool.allocate(size);
		}
		void operator delete(void* pointer) {
			memory_pool.deallocate(pointer);
		}
	};
public:
	prototype(): impl(nullptr) {}
	prototype(token::identifier name, std::vector<parameter> parameters, ast::type returnType): impl(new implementation(name, parameters, returnType)) {}
private:
	static pool<sizeof(implementation)> memory_pool;
	std::shared_ptr<implementation> impl;
};

#endif /* FUNCTION_PROTOTYPE_H_ */
