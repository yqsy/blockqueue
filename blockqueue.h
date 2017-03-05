#ifndef BLOCKQUEUE_H_
#define BLOCKQUEUE_H_

#include <queue>

class Mutex
{
public:
	Mutex();

	~Mutex();

	void Lock();

	void Unlock();
private:
	struct Internal;
	Internal* internal_;
};

class MutexLock
{
public:
	explicit MutexLock(Mutex *mu) : mu_(mu) { mu_->Lock(); }
	~MutexLock() { mu_->Unlock(); }
private:
	Mutex *const mu_;
};

class DeferUnLock
{
public:
	explicit DeferUnLock(Mutex *mu) : mu_(mu) {}
	~DeferUnLock() { mu_->Unlock(); }
private:
	Mutex *const mu_;
};

// Just event
class ConditionVariable
{
public:
	ConditionVariable();

	~ConditionVariable();

	void notify_one();

	void wait();
private:
	struct Internal;
	Internal* internal_;
};


// T will be copyed
template <typename T>
class BlockQueue
{
public:

	void Put(T value)
	{
		MutexLock lg(&mtx_);
		queue_.push(value);
		cond_.notify_one();
	}

	T Take()
	{
		for (;;)
		{
			mtx_.Lock();
			if (!queue_.empty())
				break;
			mtx_.Unlock();
			cond_.wait();
		}
		DeferUnLock dul(&mtx_);
		T rtn = queue_.front();
		queue_.pop();
		return rtn;
	}

private:
	Mutex mtx_;
	ConditionVariable cond_;
	std::queue<T>  queue_;
};


#endif
