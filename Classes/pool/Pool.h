
#ifndef __SPRITE_POOL_H_
#define __SPRITE_POOL_H_

#include <list>

template <class T> class Pool
{
public:
	Pool() { }

public:
	void returnObject(T* obj) {
		_pool.push_back(obj);
	}
	
	T* getOne() {
		if (_pool.empty()) {
			return new T;
		}
		T* first = _pool.front();
		_pool.pop_front();
		return first;
	}

	void destroy() {
		typename std::list<T*>::iterator it;
		for (it = _pool.begin(); it != _pool.end(); ++it) {
			delete *it;
		}
	}

protected:
	std::list<T*> _pool;
};

#endif
