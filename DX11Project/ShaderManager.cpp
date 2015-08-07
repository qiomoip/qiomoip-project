#include "ShaderManager.h"
#include "Shader.h"

CShaderManager::CShaderManager(void)
{
}


CShaderManager::~CShaderManager(void)
{
	Clear();
}

HRESULT CShaderManager::CreateShader(const tstring& strShaderKey, const LPCTSTR pFileName)
{
	CShader* pShader = FindShader(strShaderKey);

	if(pShader)
	{
		return S_OK;
	}

	pShader = new CShader;
	
	if(FAILED(pShader->Init(pFileName)))
	{
		return E_FAIL;
	}

	m_mapShader.insert(map<tstring, CShader*>::value_type(strShaderKey, pShader));

	return S_OK;
}

CShader* CShaderManager::FindShader(const tstring& strShaderKey)
{
	map<tstring, CShader*>::iterator iter = m_mapShader.find(strShaderKey);

	if(iter == m_mapShader.end())
		return NULL;

	return iter->second;
}

void CShaderManager::Clear()
{
	Safe_Delete_Map(m_mapShader);
}