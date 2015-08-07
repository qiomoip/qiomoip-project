#pragma once
#include "Singleton.h"

class CShader;

class CShaderManager
	: public CSingleton<CShaderManager>
{
	friend CSingleton;
private:
	map<tstring, CShader*>	m_mapShader;

public:
	HRESULT CreateShader(const tstring& strShaderKey, const LPCTSTR pFileName);
	CShader* FindShader(const tstring& strShaderKey);

	void Clear();

private:
	CShaderManager(void);
	~CShaderManager(void);
};

