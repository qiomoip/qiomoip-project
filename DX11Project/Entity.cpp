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
	, m_strShaderKey(L"")
	, m_eTechKey(DST_NONE)
	, m_eCam(CAM_PERSPECTIVE)
	, m_fSmooth(10.0f)
{
	m_vecPass.reserve(5);
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

void CEntity::SetShaderInfo(const tstring& strShader,
							const TECH_TYPE& eTech)
{
	m_strShaderKey = strShader;
	m_eTechKey = eTech;
}


void CEntity::PushPass(const PASS_TYPE& ePass)
{
	m_vecPass.push_back(ePass);
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

	return true;
}

void CEntity::Update(float fTime)
{
	//여기서 월드행렬 설정
	//월드행렬 만들기

	UINT uSize1 = sizeof(XMFLOAT3);
	memcpy(&m_matWorld._41, &m_vPos, sizeof(XMFLOAT3));

}

void CEntity::Input(float fTime)
{
	
}


void CEntity::Render()
{
	CShader* pShader = _SINGLE(CShaderManager)->FindShader(m_strShaderKey);
	ID3DX11EffectMatrixVariable* fxWVP = pShader->GetMatrix("matWVP");
	ID3DX11EffectMatrixVariable* fxWorld = pShader->GetMatrix("matWorld");

	//matWorldInvTranspose
	ID3DX11EffectMatrixVariable* fxIWorldInvTranspose = pShader->GetMatrix("matWorldInvTranspose");

	XMMATRIX matWorld = XMLoadFloat4x4(&m_matWorld);

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
		m_pMesh->Render(pShader, m_eTechKey, m_vecPass[i]);
	}


}