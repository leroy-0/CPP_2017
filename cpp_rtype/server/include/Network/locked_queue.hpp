#pragma once
#include <mutex>
#include <queue>
#include <list>

template<typename _T> class	locked_queue
{
private:
	std::mutex				mutex;
	std::queue<_T>			queue;

public:
	void					push(_T value)
	{
		mutex.lock();
		queue.push(value);
		mutex.unlock();
	};

	_T						pop()
	{
		_T					value;

		mutex.lock();
		std::swap(value, queue.front());
		queue.pop();
		mutex.unlock();
		return value;
	};

	bool			empty() {
		bool		result;

		mutex.lock();
		result = queue.empty();
		mutex.unlock();
		return result;
	}
};