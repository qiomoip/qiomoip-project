#pragma once
#include "include.h"

class CBaseMesh;

class CEntity
{
protected:
	CBaseMesh*	m_pMesh;

	//�����ǵ� ����, ��Ʈ���� ����
	//��ƼƼ Ű
	XMFLOAT3	m_vPos;
	XMFLOAT4X4	m_matWorld;
	tstring		m_strEntityKey;
	XMFLOAT3	m_LocalAxis[AT_MAX];
	XMFLOAT3	m_WorldAxis[AT_MAX];

	//���̴� Ű
	tstring	m_strShaderKey;
	TECH_TYPE	m_eTechKey;
	vector<PASS_TYPE>	m_vecPass;

	//ī�޶� Ÿ��
	CAMERA_TYPE	m_eCam;

	//�̵�, ȸ�� �ӵ���
	float		m_fSmooth;

public:
	void SetMesh(CBaseMesh* pMesh);
	void SetPos(const XMFLOAT3& vPos);
	void SetEntityKey(const tstring& strKey);

	void SetShaderInfo(const tstring& strShader, 
						const TECH_TYPE& eTech);
	void PushPass(const PASS_TYPE& ePass);

	XMFLOAT3	GetPos() const;
	XMVECTOR	GetPosXM() const;

public:
	bool Init();
	virtual void Update(float fTime);
	virtual void Input(float fTime);
	//���� �Լ������� �޽��� ������ ȣ���Ѵ�
	virtual void Render();

public:
	CEntity(void);
	~CEntity(void);
};

