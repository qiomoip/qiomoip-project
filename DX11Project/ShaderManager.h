#pragma once
#include "Singleton.h"

class CShader;

class CShaderManager
	: public CSingleton<CShaderManager>
{
	friend CSingleton;
private:
	map<SHADER_TYPE, CShader*>	m_mapShader;

public:
	HRESULT CreateShader(const SHADER_TYPE& eShader, const LPCTSTR pFileName);
	CShader* FindShader(const SHADER_TYPE& eShader);

	void Clear();

private:
	CShaderManager(void);
	~CShaderManager(void);
};

