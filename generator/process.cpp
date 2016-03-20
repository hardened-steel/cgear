#include "grammar/ast/instance.h"

#include <vector>
#include <unordered_map>
#include <tuple>
#include <typeindex>
#include <functional>

class generator
{
public:
	class type;
	class value;
	class expression;
};

class generator::type
{
public:
	class tuple;
	using instance = instance_t<generator::type>;
	virtual bool operator==(const generator::type& other) const = 0;
	virtual size_t hash() const = 0;
	virtual ~type() {}
public:
	bool operator!=(const generator::type& other) const {
		return !(*this == other);
	}
};

class generator::type::tuple: public generator::type
{
	using vector_t = std::vector<generator::type::instance>;
	vector_t types;
public:
	using instance = instance_t<generator::type::tuple>;
	tuple(vector_t types): types(types) {}
	bool operator==(const generator::type& other) const override {
		if(const tuple* other_tuple = dynamic_cast<const generator::type::tuple*>(&other)) {
			auto count = other_tuple->types.size();
			if(types.size() != count) return false;
			for(auto i = vector_t::size_type(0); i < count; ++i) {
				if(types[i] != other_tuple->types[i]) return false;
			}
			return true;
		}
		return false;
	}
	generator::type::instance& operator[](size_t index) {
		return types[index];
	}
	size_t hash() const override {
		size_t value = 0;
		for(auto& t: types) {
			value += t->hash();
		}
		return value;
	}
};

class generator::value
{
public:
	class tuple;
	using instance = instance_t<generator::value>;
	virtual generator::type::instance get_type() const = 0;
	virtual ~value() {}
};

class generator::value::tuple: public generator::value
{
	using vector_v = std::vector<generator::value::instance>;
	vector_v values;
public:
	using instance = instance_t<generator::value::tuple>;
	tuple(vector_v values): values(values) {}
	generator::type::instance get_type() const override {
		std::vector<generator::type::instance> types;
		for(auto& v: values) {
			types.push_back(v->get_type());
		}
		return generator::type::tuple::instance{std::move(types)};
	}
	generator::value::instance& operator[](size_t index) {
		return values[index];
	}
	size_t size() const { return values.size(); }
};

class generator::expression
{
public:
	using instance = instance_t<generator::expression>;
	generator::type::instance type;
	virtual generator::value::instance calculate(generator::value::instance&) = 0;
	virtual ~expression() {}
};

class signature
{
	std::string name;
	generator::type::instance parameters;
public:
	struct hash {
		size_t operator()(const signature& s) const {
			size_t h1 = std::hash<std::string>()(s.name);
			size_t h2 = s.parameters->hash();
			return h1 ^ h2;
		}
	};
public:
	signature(const std::string& name, generator::type::instance parameters)
	: name(name), parameters(parameters) {}
	bool operator==(const signature& other) const {
		if(name != other.name) return false;
		if(parameters != other.parameters) return false;
		return true;
	}
};

class context
{
	using map_t = std::unordered_map<signature, generator::expression::instance, signature::hash>;
	using insert_t = map_t::value_type;
	map_t functions;
public:
	void operator+=(insert_t function) {
		functions.insert(function);
	}

	template<class T1, class T2>
	static insert_t create(const std::string& name, std::function<generator::value::instance(instance_t<T1>, instance_t<T2>)> function) {
		class expression: public generator::expression
		{
			std::function<generator::value::instance(instance_t<T1>, instance_t<T2>)> function;
		public:
			using instance = instance_t<expression>;
			expression(std::function<generator::value::instance(instance_t<T1>, instance_t<T2>)>&& function): function(std::move(function)) {}
			generator::value::instance calculate(generator::value::instance& value) override {
				generator::value::tuple::instance values = instance_static_cast<generator::value::tuple>(value);
				return function(instance_static_cast<T1>(values->operator[](0)), instance_static_cast<T2>(values->operator[](1)));
			}
		};
		return insert_t{signature{name, generator::type::tuple::instance(T1::type, T2::type)}, expression::instance(std::move(function))};
	}
};

void process() {

}
