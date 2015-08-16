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
	//���⼭ ������Ʈ��, �ؽ�ó ����
	//������Ʈ�� �ε��� �� �ؽ�ó ���ӵ��� �ִٸ�
	//���� ���� ���� �ְ� �ؽ�ó �ε�
	//�ƴϸ� �׳� �ؽ�ó �ε�

	//���� ����
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