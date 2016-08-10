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

namespace generator {

class type;
class value
{
public:
	using instance = utility::instance<value>;
	class data {
	public:
		using instance = utility::instance<data>;
		virtual ~data() {}
	};
	class null;
	class tuple;
	class var;
private:
	const type& type_;
	data::instance data_;
public:
	value(const type& type, data::instance&& data): type_(type), data_(std::move(data)) {}
	data& getdata() { return data_.get(); }
	data const& getdata() const { return data_.get(); }
	const type& gettype() const { return type_; }
	virtual ~value() {}
};

} /* namespace generator */

#endif /* VALUE_H_ */

