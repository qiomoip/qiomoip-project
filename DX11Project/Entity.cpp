#include "Entity.h"
#include "BaseMesh.h"
#include "ShaderManager.h"
#include "Shader.h"
#include "CameraManager.h"
#include "Camera.h"

#include "MainWnd.h"

#include "KeyManager.h"

#include "Math.h"

CEntity::CEntity(void)
	: m_pMesh(NULL)
	, m_strEntityKey(L"")
	, m_eShader(SHADER_NONE)
	, m_eTechKey(DST_NONE)
	, m_eCam(CAM_PERSPECTIVE)
	
	, m_eInputLayout(IT_DEFAULT_DEFAULT_COLOR)
	, m_vScale(1.f, 1.f, 1.f)
{
	m_vecPass.reserve(5);
	memset(&m_tInputInfo, 0, sizeof(INPUTINFO) );
}


CEntity::~CEntity(void)
{
	Safe_Delete(m_pMesh);
}

void CEntity::SetMesh(CBaseMesh* pMesh)
{
	m_pMesh = pMesh;
}

void CEntity::SetPos(const XMFLOAT3& vPos)
{
	m_vPos = vPos;
}

void CEntity::SetScale(const XMFLOAT3& vScale)
{
	m_vScale = vScale;
}

	void CEntity::SetScale(const float& sx, const float& sy, const float& sz)
	{
		m_vScale = XMFLOAT3(sx, sy, sz);
	}

void CEntity::SetShaderInfo(const SHADER_TYPE& eShader,
							const TECH_TYPE& eTech)
{
	m_eShader = eShader;
	m_eTechKey = eTech;
}


void CEntity::PushPass(const PASS_TYPE& ePass)
{
	m_vecPass.push_back(ePass);
}

void CEntity::SetInputLayout(const INPUTLAYOUT_TYPE& eInputLayout)
{
	m_eInputLayout = eInputLayout;
}


XMFLOAT3	CEntity::GetPos() const
{
	return m_vPos;
}

XMVECTOR	CEntity::GetPosXM() const
{
	return XMLoadFloat3(&m_vPos);
}

void CEntity::SetEntityKey(const tstring& strKey)
{
	m_strEntityKey = strKey;
}

bool CEntity::Init()
{
	memset(&m_vPos, 0, sizeof(XMFLOAT3));

	XMMATRIX I= XMMatrixIdentity();
	XMStoreFloat4x4(&m_matWorld, I);

	memset(m_LocalAxis,0, sizeof(XMFLOAT3) * AT_MAX);
	m_LocalAxis[AT_X].x = 1.f;
	m_LocalAxis[AT_Y].y = 1.f;
	m_LocalAxis[AT_Z].z = 1.f;

	memcpy(m_WorldAxis, m_LocalAxis, sizeof(XMFLOAT3) * AT_MAX);
	
	m_tInputInfo.fMoveSpeed = 10.f;
	m_tInputInfo.fRotateSpeed = XM_PI;
	return true;
}

void CEntity::Update(float fTime)
{
	//여기서 월드행렬 설정
	//월드행렬 만들기
	UINT uSize1 = sizeof(XMFLOAT3);
	memcpy(&m_matWorld._41, &m_vPos, sizeof(XMFLOAT3));

	XMMATRIX matScale = XMMatrixScalingFromVector(XMLoadFloat3(&m_vScale));
	XMStoreFloat4x4(&m_matScale, matScale);
}

void CEntity::Input()
{	
}

void CEntity::Render()
{
	CShader* pShader = _SINGLE(CShaderManager)->FindShader(m_eShader);
	ID3DX11EffectMatrixVariable* fxWVP = pShader->GetMatrix("matWVP");
	ID3DX11EffectMatrixVariable* fxWorld = pShader->GetMatrix("matWorld");

	//matWorldInvTranspose
	ID3DX11EffectMatrixVariable* fxIWorldInvTranspose = pShader->GetMatrix("matWorldInvTranspose");

	XMMATRIX matWorld = XMLoadFloat4x4(&m_matScale) * XMLoadFloat4x4(&m_matWorld);

	XMMATRIX matInvTranspose =_SINGLE(CMath)->GetInverseTranspose(matWorld);

	const CCamera* pCurCam = _SINGLE(CCameraManager)->GetCurCamera();
	XMMATRIX matView =	pCurCam->GetView(m_eCam);
	XMMATRIX matProj = pCurCam->GetProj(m_eCam);

	XMMATRIX matWVP = matWorld * matView * matProj;

	fxWVP->SetMatrix(reinterpret_cast<float*>(&matWVP));
	fxWorld->SetMatrix(reinterpret_cast<float*>(&matWorld));
	fxIWorldInvTranspose->SetMatrix(reinterpret_cast<float*>(&matInvTranspose));

	for(int i = 0; i < m_vecPass.size(); ++i)
	{
		m_pMesh->Render(pShader, m_eTechKey, m_eInputLayout, m_vecPass[i]);
	}
}
