#ifndef GTYPE_H
#define GTYPE_H

#include <memory>
#include <boost/spirit/include/qi.hpp>
#include "../lexer/lexer.h"
#include "../syntax/tree.h"

class ast::type: public ast
{
public:
	class base;
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
	type(const std::shared_ptr<base>& impl): impl(impl) {}
	type(std::shared_ptr<base>&& impl): impl(std::move(impl)) {}
	type& operator=(const std::shared_ptr<base>& impl) {
		this->impl = impl;
		return *this;
	}
	type& operator=(std::shared_ptr<base>&& impl) {
		this->impl = std::move(impl);
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
