// Project: CGear
//
//  Created on: 09.09.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef CALL_H_
#define CALL_H_

#include "../../lexer/token.h"
#include "operation.h"

class ast::operation::call
{
	friend ast::operation;
protected:
	class implementation: public ast::operation::base
	{
		token::identifier id;
		std::vector<ast::operation> params;
	public:
		implementation(token::identifier id, const std::vector<ast::operation>& params): id(id), params(params) {}
		implementation(token::identifier id, std::vector<ast::operation>&& params): id(id), params(std::move(params)) {}
		void* operator new(size_t size) {
			return memory_pool.allocate(size);
		}
		void operator delete(void* pointer) {
			memory_pool.deallocate(pointer);
		}
	};
public:
	call(token::identifier id, const std::vector<ast::operation>& params): impl(new implementation(id, params)) {}
	call(token::identifier id, std::vector<ast::operation>&& params = {}): impl(new implementation(id, std::move(params))) {}
private:
	static pool<sizeof(implementation), 1024> memory_pool;
	std::shared_ptr<implementation> impl;
};

#endif /* CALL_H_ */
