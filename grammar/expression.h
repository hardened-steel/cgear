#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "type.h"

class ast::operation: public ast
{
public:
	class base
	{
	public:
		virtual ~base() {}
	};
	class unary;
	class binary;
	class ternary;
	class type_cast;
	class var;
	class index;
	class section;
	class array;

	operation(): impl(nullptr) {}
	operation(const std::shared_ptr<base>& impl): impl(impl) {}
	operation(std::shared_ptr<base>&& impl): impl(std::move(impl)) {}
	operation& operator=(const std::shared_ptr<base>& impl) {
		this->impl = impl;
		return *this;
	}
	operation& operator=(std::shared_ptr<base>&& impl) {
		this->impl = std::move(impl);
		return *this;
	}
private:
	std::shared_ptr<base> impl;
};

class GExpression: public boost::spirit::qi::grammar<GIterator, ast::operation(), GSkip>
{
    static const unsigned operationNum = 9;
    boost::spirit::qi::rule<GIterator, ast::operation(), GSkip> expression;
    boost::spirit::qi::rule<GIterator, ast::operation(), GSkip> var;
    //boost::spirit::qi::rule<GIterator, ast::operation(), boost::spirit::locals<ast::identifier>, GSkip> call;
    boost::spirit::qi::rule<GIterator, ast::operation(), GSkip> operation[operationNum];

    //GType type;
public:
    GExpression(Lexer& lexer);
    ~GExpression();
};

#endif // EXPRESSION_H
