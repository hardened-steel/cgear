// Project: CGear
//
//  Created on: 31.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef GRAMMAR_AST_OPERATORS_NOPE_H_
#define GRAMMAR_AST_OPERATORS_NOPE_H_

#include "operator.h"

class ast::instruction::nope
{
	friend ast::instruction;
protected:
	class implementation: public ast::instruction::base
	{
	public:
		void accept(ast::instruction::visitor&) override;
		void* operator new(size_t size) {
			return &snope;
		}
		void operator delete(void* pointer) {
		}
	};
public:
	nope(): impl(new implementation) {}
private:
	static implementation snope;
	std::shared_ptr<implementation> impl;
};


#endif /* GRAMMAR_AST_OPERATORS_NOPE_H_ */
