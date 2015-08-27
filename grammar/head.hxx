#ifndef HEAD_HXX
#define HEAD_HXX

#include <boost/spirit/include/phoenix.hpp>
/*
class IHandler
{
public:
    virtual void onError(GIterator& begin, GIterator end, GIterator where, boost::spirit::info const& what) const = 0;
    virtual void onSuccess(st& base, GIterator first, GIterator last) const = 0;
};

class WHandler
{
    IHandler& handler;
public:
    WHandler(IHandler& handler): handler(handler) {}
    void operator()(GIterator& b, GIterator e, GIterator where, boost::spirit::info const& what) const { handler.onError(b, e, where, what); }
    void operator()(st& base, GIterator first, GIterator last) const { handler.onSuccess(base, first, last); }
};

using Handler = boost::phoenix::function<WHandler>;
*/
#endif // HEAD_HXX
