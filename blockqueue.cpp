#include "blockqueue.h"

#include <windows.h>

struct Mutex::Internal
{
	CRITICAL_SECTION mutex;
};

Mutex::Mutex() :
	internal_(new Internal)
{
	InitializeCriticalSection(&internal_->mutex);
}

Mutex::~Mutex()
{
	DeleteCriticalSection(&internal_->mutex);
	delete internal_;
}

void Mutex::Lock()
{
	EnterCriticalSection(&internal_->mutex);
}

void Mutex::Unlock()
{
	LeaveCriticalSection(&internal_->mutex);
}

struct ConditionVariable::Internal
{
	HANDLE event;
};

ConditionVariable::ConditionVariable() :
	internal_(new Internal)
{
	internal_->event = CreateEvent(NULL, FALSE, FALSE, NULL);

}

ConditionVariable::~ConditionVariable()
{
	delete internal_;
}

void ConditionVariable::notify_one()
{
	SetEvent(internal_->event);
}

void ConditionVariable::wait()
{
	WaitForSingleObject(internal_->event, INFINITE);
}
