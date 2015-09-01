#ifndef GTYPE_H
#define GTYPE_H

#include <memory>
#include <map>
#include <boost/spirit/include/qi.hpp>
#include "../lexer/lexer.h"
#include "../syntax/tree.h"

class ast::type: public ast
{
public:
	class base
	{
	public:
		virtual ~base() {}
	};
	class t_bool;
	class t_int;
	class t_real;
	class t_void;
	class array;
	class pointer;
	class t_class;
	class t_struct;
public:
	type(): impl(nullptr) {}
	type(type&& other): impl(std::move(other.impl)) {}
	type(const type& other): impl(other.impl) {}
	template<typename T> type(T&& other): impl(std::move(other.impl)) {}
	template<typename T> type(const T& other): impl(other.impl) {}
	template<typename T> type& operator=(T&& other) {
		this->impl = std::move(other.impl);
		return *this;
	}
	template<typename T> type& operator=(const T& other) {
		this->impl = other.impl;
		return *this;
	}
private:
	std::shared_ptr<base> impl;
};

class GType : public boost::spirit::qi::grammar<GIterator, ast::type(), GSkip>
{
	boost::spirit::qi::rule<GIterator, ast::type(), GSkip> type;
public:
	GType(Lexer& lexer);
};

#endif // GTYPE_H
