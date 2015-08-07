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
	//���⼭ ������Ʈ��, �ؽ�ó ����
	//������Ʈ�� �ε��� �� �ؽ�ó ���ӵ��� �ִٸ�
	//���� ���� ���� �ְ� �ؽ�ó �ε�
	//�ƴϸ� �׳� �ؽ�ó �ε�

	//���� ����
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