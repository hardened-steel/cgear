// Project: CGear
//
//  Created on: 26.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#include <boost/variant.hpp>
#include "module.h"

void ast::module::codegen() {
	class visitor : public boost::static_visitor<void>
	{
		mutable generator::context context;
	public:
	    void operator()(ast::function::instance& function) const {
	    	function->codegen(context);
	    }
	    void operator()(ast::type::instance& type) const {
	    }
	};
	for(auto& i: statements) {
		boost::apply_visitor(visitor(), i);
	}
}
