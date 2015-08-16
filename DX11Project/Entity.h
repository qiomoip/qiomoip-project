#pragma once
#include "include.h"

class CBaseMesh;

class CEntity
{
protected:
	CBaseMesh*	m_pMesh;

	//포지션등 벡터, 매트릭스 정보
	//엔티티 키
	XMFLOAT3	m_vPos;
	XMFLOAT4X4	m_matWorld;
	XMFLOAT4X4	m_matScale;
	tstring		m_strEntityKey;
	XMFLOAT3	m_LocalAxis[AT_MAX];
	XMFLOAT3	m_WorldAxis[AT_MAX];
	XMFLOAT3	m_vScale;

	//쉐이더 키
	//tstring	m_strShaderKey;
	SHADER_TYPE m_eShader;
	TECH_TYPE	m_eTechKey;
	vector<PASS_TYPE>	m_vecPass;
	INPUTLAYOUT_TYPE	m_eInputLayout;

	//카메라 타입
	CAMERA_TYPE	m_eCam;

	//이동, 회전 속도값
	float		m_fSmooth;

public:
	void SetMesh(CBaseMesh* pMesh);
	void SetPos(const XMFLOAT3& vPos);
	void SetScale(const XMFLOAT3& vScale);
	void SetScale(const float& sx, const float& sy, const float& sz);
	void SetEntityKey(const tstring& strKey);

	void SetShaderInfo(const SHADER_TYPE& eShader, 
						const TECH_TYPE& eTech);
	void PushPass(const PASS_TYPE& ePass);

	void SetInputLayout(const INPUTLAYOUT_TYPE& eInputLayout);

	XMFLOAT3	GetPos() const;
	XMVECTOR	GetPosXM() const;

public:
	bool Init();
	virtual void Update(float fTime);
	virtual void Input(float fTime);
	//렌더 함수에서는 메쉬의 렌더를 호출한다
	virtual void Render();

public:
	CEntity(void);
	~CEntity(void);
};

