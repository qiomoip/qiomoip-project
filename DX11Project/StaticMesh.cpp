#include "StaticMesh.h"
#include "Geometry.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Device.h"
#include "Shader.h"

CStaticMesh::CStaticMesh(void)
	: m_pTexture(NULL)
{
}


CStaticMesh::~CStaticMesh(void)
{
}


void CStaticMesh::Init(const GEOMETRY_TYPE& eMesh, const LPCTSTR pFileName, const LPCSTR pShaderTextureName, tstring strTextureName)
{
	//여기서 지오메트리, 텍스처 생성
	//지오메트리 로딩할 때 텍스처 네임들이 있다면
	//여기 네임 값에 넣고 텍스처 로딩
	//아니면 그냥 텍스처 로딩

	//기하 생성
	m_pGeometry = _SINGLE(CResourceManager)->CreateGeometry(eMesh, pFileName);

	if(_tcscmp(strTextureName.c_str(), L""))
	{
		m_pTexture = _SINGLE(CResourceManager)->CreateTexture(pShaderTextureName, strTextureName);
	}
}


void CStaticMesh::Render(CShader* pShader, const TECH_TYPE& eTech, const INPUTLAYOUT_TYPE& eInputLayout, const UINT& uPass)
{
	m_pTexture->SetTexture(pShader);

	pShader->GetTech(eTech)->GetPassByIndex(uPass)->Apply(0, _ICONTEXT());
	
	m_pGeometry->Render(pShader, eTech, eInputLayout, uPass);
}