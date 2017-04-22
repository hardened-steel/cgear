// Project: CGear
//
//  Created on: 12.03.2016
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#ifndef VALUE_H_
#define VALUE_H_

#include <memory>
#include <utility/instance.hpp>

namespace model {

class type;
class value
{
public:
	using instance = utility::instance<value, utility::copyable>;
	class data {
	public:
		using instance = utility::instance<data, utility::copyable>;
		virtual ~data() {}
	};
	class tuple;
private:
	const type& type_;
	data::instance data_;
public:
	value(const type& type, data::instance data): type_(type), data_(std::move(data)) {}
	      data::instance& getdata()       { return data_; }
	const data::instance& getdata() const { return data_; }
	const type& gettype() const { return type_; }
	virtual ~value() {}
};

} /* namespace generator */

#endif /* VALUE_H_ */

