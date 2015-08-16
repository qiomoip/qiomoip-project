#pragma once
#include "basemesh.h"

class CGeometry;
class CTexture;

class CStaticMesh :
	public CBaseMesh
{

	//�̰� ����ƽ ������Ʈ���� ���ڰ�����...
		//vector<tstring>	m_vecTextureName;

	//�������� ������Ʈ�� �����͸� ���� �ִ�
	//���������� ������Ʈ���� �����Ѵ�
	//������Ʈ���� ������ �� �ؽ�ó�� �ʿ��ϴٸ� �� �ؽ�ó �̸��� ������Ʈ���� �����Ѵ�
	//����� �ؽ�ó �̸� ����Ʈ�� ������ �ؽ�ó�� �����Ѵ�
	//�ؽ�ó �����ϴ� �κ��� ����������...
	//�̰� ���߿� �޽� ���� �� �ٽ� �� ��
	//���࿡ 11�� �̷��� �� �ϸ� ��¼�� ������............
private:
	CTexture*	m_pTexture;

public:
	void Init(const GEOMETRY_TYPE& eMesh, const LPCTSTR pFileName, tstring strTextureName);

	void Render(CShader* pShader, const TECH_TYPE& eTech, const INPUTLAYOUT_TYPE& eInputLayout, const UINT& uPass);

public:
	CStaticMesh(void);
	~CStaticMesh(void);
};

