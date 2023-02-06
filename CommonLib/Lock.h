#pragma once
#include<Windows.h>
class CLock
{
public:
	CLock()
	{
		InitializeCriticalSection(&m_cs);
	}

	~CLock()
	{
		DeleteCriticalSection(&m_cs);
	}

	void Lock()
	{
		EnterCriticalSection(&m_cs);
	}

	void Unlock()
	{
		LeaveCriticalSection(&m_cs);
	}
private:
	CRITICAL_SECTION    m_cs;
};

class AutoLock
{
public:
	AutoLock()
	{
		m_lock.Lock();
	}
	~AutoLock()
	{
		m_lock.Unlock();
	}
private:
	CLock   m_lock;
private:
	AutoLock(const AutoLock& lock);
	AutoLock& operator=(const AutoLock& lock);
};
