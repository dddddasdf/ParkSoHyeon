#pragma once
#include <iostream>


template <typename T>
class Singletone
{
private:
	static T* m_hThis;
protected:
	Singletone()
	{

	}

	virtual ~Singletone()
	{

	}
public:
	static T* GetInstance()
	{
		if (m_hThis == NULL)
			m_hThis = new T;

		return m_hThis;
	}

	static void DestoryThis()
	{
		if (m_hThis)
		{
			delete m_hThis;
			m_hThis = NULL;
		}
	}
};