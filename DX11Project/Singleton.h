#pragma once
#include "include.h"

template <typename T>
class CSingleton
{
protected:
	static T*	m_pInstance;

public:
	static T* GetInstance()
	{
		if(!m_pInstance)
			m_pInstance = new T;
		return m_pInstance;
	}

	static void DestroyInstance()
	{
		if(m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = NULL;
		}
	}

protected:
	CSingleton(void){};
	~CSingleton(void){};
};

template<typename T>
T*	CSingleton<T>::m_pInstance = NULL;
