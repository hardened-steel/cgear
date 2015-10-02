// Project: CGear
//
//  Created on: 02.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef AST_TYPES_TUPLE_H_
#define AST_TYPES_TUPLE_H_

#include <vector>
#include "../../lexer/token.h"
#include "type.h"

class ast::type::tuple
{
	friend ast::type;
public:
	class field
	{
		ast::type type;
		token::identifier name;
	public:
		field(ast::type type, token::identifier name): type(type), name(name) {}
		field(const field& other): type(other.type), name(other.name) {}
	};
protected:
	class implementation: public ast::type::base
	{
		std::vector<field> fields;
	public:
		implementation(const std::vector<field>& fields): fields(fields) {}
		implementation(std::vector<field>&& fields): fields(std::move(fields)) {}
		void* operator new(size_t size) {
			return memory_pool.allocate(size);
		}
		void operator delete(void* pointer) {
			memory_pool.deallocate(pointer);
		}
	};
public:
	tuple(): impl(nullptr) {}
	tuple(const std::vector<field>& fields): impl(new implementation(fields)) {}
	tuple(std::vector<field>&& fields): impl(new implementation(std::move(fields))) {}
private:
	static pool<sizeof(implementation), 1024> memory_pool;
	std::shared_ptr<implementation> impl;
};

#endif /* AST_TYPES_TUPLE_H_ */
