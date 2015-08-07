#include "ResourceManager.h"
#include "StaticMesh.h"
#include "BoxGeometry.h"
#include "Texture.h"

CResourceManager::CResourceManager(void)
{

}


CResourceManager::~CResourceManager(void)
{
	Clear();
}

CBaseMesh*	CResourceManager::CreateRenderer(const MESH_TYPE& eRender, const GEOMETRY_TYPE& eMesh, const INPUTLAYOUT_TYPE& eInputLayout, const LPCTSTR pFileName, tstring strTextureName)
{
	//
	CBaseMesh* pMesh = NULL;
	switch(eRender)
	{
	case MT_STATIC:
		pMesh = new CStaticMesh;
		break;
	default:
		break;
	}

	pMesh->Init(eMesh, eInputLayout, pFileName, strTextureName);

	return pMesh;

}

CGeometry* CResourceManager::CreateGeometry(const GEOMETRY_TYPE& eGeo, const INPUTLAYOUT_TYPE& eInputLayout, const LPCTSTR pFileName)
{
	map<GEOMETRY_TYPE, CGeometry*>::iterator iter = m_mapMesh.find(eGeo);

	if(iter != m_mapMesh.end())
	{
		return iter->second;
	}

	CGeometry* pGeometry = NULL;

	//없으면 메쉬를 새로 만듦
	switch(eGeo)
	{
	case GT_STATIC:
		break;
	case GT_BOX:
		pGeometry = new CBoxGeometry;
		break;
	}

	pGeometry->Init();
	pGeometry->SetInputLayout(eInputLayout);

	m_mapMesh.insert(map<GEOMETRY_TYPE, CGeometry*>::value_type(eGeo, pGeometry));

	return pGeometry;
}

CTexture* CResourceManager::CreateTexture(tstring strTextureName)
{
	CTexture* pTexture = new CTexture;
	TCHAR szFileName[MAX_PATH] = {0};
	_tcscpy(szFileName, strTextureName.c_str());

	TCHAR szTypeName[MAX_PATH] = {0};

	//타입 이름
	int i = strTextureName.size() -1;
	int iCnt = 0;
	while(i >= 0)
	{
		//szTypeName[strTextureName.size() - 1 - i] = szFileName[i];
		
		++iCnt;
		--i;
		if(szFileName[i] == '.')
		{
			break;
		}
	}

	for(int i = 0; i < iCnt; ++i)
	{
		szTypeName[iCnt - i] = szFileName[strTextureName.size() - 1 - i];
	}
	szTypeName[0] = '.';
	pTexture->CreateTexture(szFileName, szTypeName);
	return pTexture;
}

void CResourceManager::Clear()
{
	Safe_Delete_Map(m_mapMesh);
	Safe_Delete_Map(m_mapTexture);
}