#include "ShaderManager.h"
//#include "SkyShader.h"
#include "DefaultShader.h"

CShaderManager::CShaderManager(void)
{
}


CShaderManager::~CShaderManager(void)
{
	Clear();
}

HRESULT CShaderManager::CreateShader(const SHADER_TYPE& eShader, const LPCTSTR pFileName)
{
	CShader* pShader = FindShader(eShader);

	if(pShader)
	{
		return S_OK;
	}

	switch(eShader)
	{
	case SHADER_DEFAULT:
		pShader = new CDefaultShader;
		break;
	default:
		break;
	}
	
	
	if(FAILED(pShader->Init(pFileName)))
	{
		return E_FAIL;
	}

	m_mapShader.insert(map<SHADER_TYPE, CShader*>::value_type(eShader, pShader));

	return S_OK;
}

CShader* CShaderManager::FindShader(const SHADER_TYPE& eShader)
{
	map<SHADER_TYPE, CShader*>::iterator iter = m_mapShader.find(eShader);

	if(iter == m_mapShader.end())
		return NULL;

	return iter->second;
}

void CShaderManager::Clear()
{
	Safe_Delete_Map(m_mapShader);
}