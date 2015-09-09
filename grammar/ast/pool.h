// Project: CGear
//
//  Created on: 01.08.2015
//      Author: K.Pinegin
//	     email: keldgaden@gmail.com
//

#ifndef POOL_H_
#define POOL_H_

template<unsigned size, unsigned capacity> class pool
{
	void *pointers[capacity];
	unsigned int top;
public:
	static_assert(size > 0, "size must be greater than zero");

	pool() {
		for(top = 0; top < capacity; ++top) {
			pointers[top] = ::operator new(size);
		}
	}
	void* allocate(const size_t nsize) {
		if((nsize > size) || (top == 0)) return ::operator new(nsize);
		return pointers[--top];
	}
	void deallocate(void* pointer) {
		if(top == capacity) ::operator delete(pointer);
		else pointers[top++] = pointer;
	}
	~pool() {
		while(top) ::operator delete(pointers[--top]);
	}
};

#endif /* POOL_H_ */
