#pragma once
#include <iostream>

class Singletone
{
private:
	static Singletone* m_hThis;
protected:
	Singletone()
	{

	}

	virtual ~Singletone()
	{

	}
public:
	static Singletone* GetInstance()
	{
		if (m_hThis == NULL)
			m_hThis = new Singletone;

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