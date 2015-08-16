#include "ResourceManager.h"
#include "StaticMesh.h"
#include "BoxGeometry.h"
#include "Texture.h"
#include "Terrain.h"
#include "SphereGeometry.h"

CResourceManager::CResourceManager(void)
{

}


CResourceManager::~CResourceManager(void)
{
	Clear();
}

CBaseMesh*	CResourceManager::CreateRenderer(const MESH_TYPE& eRender, const GEOMETRY_TYPE& eMesh, const LPCTSTR pFileName, const LPCSTR pShaderTextureName, tstring strTextureName)
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

	pMesh->Init(eMesh, pFileName, pShaderTextureName, strTextureName);

	return pMesh;

}

CGeometry* CResourceManager::CreateGeometry(const GEOMETRY_TYPE& eGeo, const LPCTSTR pFileName)
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
	case GT_TERRAIN:
		pGeometry = new CTerrain;
		break;
	case GT_SPHERE:
		pGeometry = new CSphereGeometry;
		break;
	}

	pGeometry->Init();
	//pGeometry->SetInputLayout(eInputLayout);

	m_mapMesh.insert(map<GEOMETRY_TYPE, CGeometry*>::value_type(eGeo, pGeometry));

	return pGeometry;
}

CTexture* CResourceManager::CreateTexture(const LPCSTR pShaderTextureName, tstring strTextureName)
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

	//%d가 있는
	TCHAR szMulti[10] = {0};

	_tcscpy(szMulti, &szFileName[strTextureName.size() - iCnt - 1 - 2]);

	//%d가 있는 텍스쳐
	TCHAR szName[10] = {0};
	_tcscpy(szName, L"%d");
	_tcscat(szName, szTypeName);
	if(_tcscmp(szName, szMulti) == 0)
	{
		memset(&szFileName[strTextureName.size() - iCnt - 1 - 2], 0, sizeof(TCHAR) * (iCnt + 3));
		pTexture->CreateTexture(szFileName, szTypeName, true);
	}

	//없음
	else
	{
		pTexture->CreateTexture(szFileName, szTypeName, false);
	}

	pTexture->SetShaderTextureName(pShaderTextureName);

	m_mapTexture.insert(map<tstring, CTexture*>::value_type(strTextureName, pTexture));
	return pTexture;
}

void CResourceManager::Clear()
{
	Safe_Delete_Map(m_mapMesh);
	Safe_Delete_Map(m_mapTexture);
}