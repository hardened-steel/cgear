// Project: CGear
//
//  Created on: 14 февр. 2016 г.
//      Author: motorhead
//

#ifndef PROCESS_TYPE_H_
#define PROCESS_TYPE_H_

#include <map>
#include <list>

class type
{
	std::multimap<ast::operation::code, std::list<type>> operations;
	std::multimap<token::identifier, std::list<type>> methods;
};

#endif /* PROCESS_TYPE_H_ */
