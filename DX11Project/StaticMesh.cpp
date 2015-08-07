#include "StaticMesh.h"
#include "Geometry.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Device.h"
#include "Shader.h"

CStaticMesh::CStaticMesh(void)
{
}


CStaticMesh::~CStaticMesh(void)
{
}


void CStaticMesh::Init(const GEOMETRY_TYPE& eMesh, const INPUTLAYOUT_TYPE& eInputLayout, const LPCTSTR pFileName, tstring strTextureName)
{
	//여기서 지오메트리, 텍스처 생성
	//지오메트리 로딩할 때 텍스처 네임들이 있다면
	//여기 네임 값에 넣고 텍스처 로딩
	//아니면 그냥 텍스처 로딩

	//기하 생성
	m_pGeometry = _SINGLE(CResourceManager)->CreateGeometry(eMesh, eInputLayout, pFileName);

	if(_tcscmp(strTextureName.c_str(), L""))
	{
		m_vecTexture.push_back(_SINGLE(CResourceManager)->CreateTexture(strTextureName));
	}
}

void CStaticMesh::PushTexture(CTexture* pTexture)
{
	m_vecTexture.push_back(pTexture);
}

void CStaticMesh::Render(CShader* pShader, const TECH_TYPE& eTech, const UINT& uPass)
{
	for(vector<CTexture*>::iterator iter = m_vecTexture.begin();
		iter != m_vecTexture.end(); ++iter)
	{
		(*iter)->SetTexture(pShader);
	}

	pShader->GetTech(eTech)->GetPassByIndex(uPass)->Apply(0, _ICONTEXT());
	
	m_pGeometry->Render(pShader, eTech, uPass);
}