#include "Camera.h"
#include "Entity.h"

#include "KeyManager.h"

CCamera::CCamera(void)
	: m_fNearZ(1.f)
	, m_fFarZ(1000.f)
	, m_fAspect(800 / 600)
	, m_fFovY(0.25f * PI)
	, m_fNearWindowHeight(0.f)
	, m_fFarWindowHeight(0.f)
	, m_eCam(CAM_PERSPECTIVE)
	, m_pLookObject(NULL)
	, m_vDest(XMFLOAT3(0.f, 20.f, 0.f))
	, m_fSmooth(10.f)
{
}


CCamera::~CCamera(void)
{
}

void CCamera::Init()
{
	memset(&m_vPosition, 0, sizeof(XMFLOAT3));
	memset(&m_vRight, 0, sizeof(XMFLOAT3));
	memset(&m_vUp, 0, sizeof(XMFLOAT3));
	memset(&m_vLook, 0, sizeof(XMFLOAT3));
	m_vRight.x = 1.f;
	m_vUp.y = 1.f;
	m_vLook.z = 1.f;

	memset(m_tCam, 0, sizeof(CAMERA) * CAM_MAX);
}


void		CCamera::Update()
{
	if(m_pLookObject)
	{
		FollowObject();
	}

	UpdateViewMatrix();
}

void		CCamera::Input(float fTime)
{
	const KEYINFO* pKey = NULL;
	
	pKey = _SINGLE(CKeyManager)->GetKey(KEY_W);
	if(pKey)
	{
		if(pKey->bDown || pKey->bPush)
		{
			XMVECTOR	vPos = XMLoadFloat3(&m_vPosition);
			XMVECTOR	vWorldX = XMLoadFloat3(&m_vLook);

			vPos += vWorldX * fTime * m_fSmooth;

			XMStoreFloat3(&m_vPosition, vPos);
		}
	}

	pKey = _SINGLE(CKeyManager)->GetKey(KEY_S);
	if(pKey)
	{
		if(pKey->bDown || pKey->bPush)
		{
			XMVECTOR	vPos = XMLoadFloat3(&m_vPosition);
			XMVECTOR	vWorldX = XMLoadFloat3(&m_vLook);

			vPos += vWorldX * (-1.f) * fTime * m_fSmooth;

			XMStoreFloat3(&m_vPosition, vPos);
		}
	}

	pKey = _SINGLE(CKeyManager)->GetKey(KEY_D);
	if(pKey)
	{
		if(pKey->bDown || pKey->bPush)
		{
			XMVECTOR	vPos = XMLoadFloat3(&m_vPosition);
			XMVECTOR	vWorldX = XMLoadFloat3(&m_vRight);

			vPos += vWorldX * fTime * m_fSmooth;

			XMStoreFloat3(&m_vPosition, vPos);
		}
	}

	pKey = _SINGLE(CKeyManager)->GetKey(KEY_A);
	if(pKey)
	{
		if(pKey->bDown || pKey->bPush)
		{
			XMVECTOR	vPos = XMLoadFloat3(&m_vPosition);
			XMVECTOR	vWorldX = XMLoadFloat3(&m_vRight);

			vPos += vWorldX * (-1.f) * fTime * m_fSmooth;

			XMStoreFloat3(&m_vPosition, vPos);
		}
	}

	pKey = _SINGLE(CKeyManager)->GetKey(KEY_C);
	if(pKey)
	{
		if(pKey->bDown || pKey->bPush)
		{
			XMVECTOR	vPos = XMLoadFloat3(&m_vPosition);
			XMVECTOR	vWorldX = XMLoadFloat3(&m_vUp);

			vPos += vWorldX * fTime * m_fSmooth;

			XMStoreFloat3(&m_vPosition, vPos);
		}
	}

	pKey = _SINGLE(CKeyManager)->GetKey(KEY_Z);
	if(pKey)
	{
		if(pKey->bDown || pKey->bPush)
		{
			XMVECTOR	vPos = XMLoadFloat3(&m_vPosition);
			XMVECTOR	vWorldX = XMLoadFloat3(&m_vUp);

			vPos += vWorldX * (-1.f) * fTime * m_fSmooth;

			XMStoreFloat3(&m_vPosition, vPos);
		}
	}

	pKey = _SINGLE(CKeyManager)->GetKey(KEY_VKHOME);
	if(pKey)
	{
		if(pKey->bDown || pKey->bPush)
		{
			Pitch( (-1.f) * fTime * XM_PI * 0.5f );
		}
	}

	pKey = _SINGLE(CKeyManager)->GetKey(KEY_VKEND);
	if(pKey)
	{
		if(pKey->bDown || pKey->bPush)
		{
			Pitch( (1.f) * fTime * XM_PI * 0.5f );
		}
	}

	pKey = _SINGLE(CKeyManager)->GetKey(KEY_VKPGDN);
	if(pKey)
	{
		if(pKey->bDown || pKey->bPush)
		{
			RotateY( (1.f) * fTime * XM_PI * 0.5f );
		}
	}

	pKey = _SINGLE(CKeyManager)->GetKey(KEY_VKDEL);
	if(pKey)
	{
		if(pKey->bDown || pKey->bPush)
		{
			RotateY( (-1.f) * fTime * XM_PI * 0.5f );
		}
	}
}

//세계공간 카메라 위치를 조회
XMVECTOR	CCamera::GetPositionXM() const
{
	return XMLoadFloat3(&m_vPosition);
}

const XMFLOAT3&	CCamera::GetPosition() const
{
	return m_vPosition;
}

//카메라 기저 벡터 반환
XMVECTOR	CCamera::GetRightXM() const
{
	return XMLoadFloat3(&m_vRight);
}

XMVECTOR	CCamera::GetUpXM() const
{
	return XMLoadFloat3(&m_vUp);
}

XMVECTOR	CCamera::GetLookXM() const
{
	return	XMLoadFloat3(&m_vLook);
}

const XMFLOAT3&	CCamera::GetRight() const
{
	return m_vRight;
}

const XMFLOAT3&	CCamera::GetUp() const
{
	return m_vUp;
}

const XMFLOAT3&	CCamera::GetLook() const
{
	return m_vLook;
}
//절두체 속성 반환
const float&		CCamera::GetNearZ() const
{
	return m_fNearZ;
}

const float&		CCamera::GetFarZ() const
{
	return m_fFarZ;
}

const float&		CCamera::GetAspect() const
{
	return m_fAspect;
}

const float&		CCamera::GetFovY() const
{
	return	m_fFovY;
}

const float&		CCamera::GetFovX() const
{
	float halfWidth = 0.5f*GetNearWindowWidth();
	return 2.0f*atan(halfWidth / m_fNearZ);
}
//시야공간 기준 원근 평면 크기 반환
float		CCamera::GetNearWindowWidth() const
{
	return m_fAspect * m_fNearWindowHeight;
}

float		CCamera::GetFarWindowWidth() const
{
	return m_fAspect * m_fFarWindowHeight;
}

const float&		CCamera::GetNearWindowHeight() const
{
	return m_fNearWindowHeight;
}

const float&		CCamera::GetFarWindowHeight() const
{
	return m_fFarWindowHeight;
}
//시야행렬, 투영행렬 반환
XMMATRIX	CCamera::GetView(const CAMERA_TYPE& eCam ) const
{
	return XMLoadFloat4x4(&m_tCam[eCam].matView);
}

XMMATRIX	CCamera::GetProj(const CAMERA_TYPE& eCam ) const
{
	return XMLoadFloat4x4(&m_tCam[eCam].matProj);
}

XMMATRIX	CCamera::GetViewProj(const CAMERA_TYPE& eCam ) const
{
	return XMMatrixMultiply(XMLoadFloat4x4(&m_tCam[eCam].matView), XMLoadFloat4x4(&m_tCam[eCam].matProj));
}

void		CCamera::SetCameraType(const CAMERA_TYPE& eCam)
{
	m_eCam = eCam;
}

//절두체 설정
void		CCamera::SetLens(const float& fWidth, const float& fHeight, const float& fFovY, const float& fAspect, const float& fZn, const float& fZf)
{
	m_fFovY = fFovY;
	m_fAspect = fAspect;
	m_fNearZ = fZn;
	m_fFarZ = fZf;

	m_fNearWindowHeight = 2.f * m_fNearZ * tanf(0.5f * m_fFovY);
	m_fFarWindowHeight = 2.f * m_fFarZ * tanf(0.5f * m_fFovY);

	XMMATRIX p = XMMatrixPerspectiveFovLH(m_fFovY, m_fAspect, m_fNearZ, m_fFarZ);
	XMStoreFloat4x4(&m_tCam[CAM_PERSPECTIVE].matProj, p);

	XMMATRIX o = XMMatrixOrthographicLH(fWidth, fHeight, m_fNearZ, m_fFarZ);
	XMStoreFloat4x4(&m_tCam[CAM_ORTHOGONAL].matProj, o);

	XMMATRIX I = XMMatrixIdentity();
	XMStoreFloat4x4(&m_tCam[CAM_ORTHOGONAL].matView, I);
}

//카메라 위치, 시선, 상향 벡터로 카메라 공간 설정
void		CCamera::LookAt(const FXMVECTOR& vPos, const FXMVECTOR& vTarget, const FXMVECTOR& vWorldUp)
{
	XMVECTOR L = XMVector3Normalize(XMVectorSubtract(vTarget, vPos));
	XMVECTOR R = XMVector3Normalize(XMVector3Cross(vWorldUp, L));
	XMVECTOR U = XMVector3Cross(L, R);

	XMStoreFloat3(&m_vPosition, vPos);
	XMStoreFloat3(&m_vLook, L);
	XMStoreFloat3(&m_vRight, R);
	XMStoreFloat3(&m_vUp, U);
}

void		CCamera::LookAt(const XMFLOAT3& vPos, const XMFLOAT3& vTarget, const XMFLOAT3& vUp)
{
	XMVECTOR P = XMLoadFloat3(&vPos);
	XMVECTOR T = XMLoadFloat3(&vTarget);
	XMVECTOR U = XMLoadFloat3(&vUp);

	LookAt(P, T, U);
}

//세계 공간 카메라 위치 설정
void		CCamera::SetPosition(const float& fX, const float& fY, const float& fZ)
{
}

void		CCamera::SetPosition(const XMFLOAT3& vPos)
{
	m_vPosition = vPos;
}
//카메라 d만큼 횡이동, 축이동
void		CCamera::Strafe(const float& fDist)
{

	XMVECTOR s = XMVectorReplicate(fDist);	//s == (fDist, fDist, fDist);
	XMVECTOR r = XMLoadFloat3(&m_vRight);
	XMVECTOR p = XMLoadFloat3(&m_vPosition);

	XMStoreFloat3(&m_vPosition, XMVectorMultiplyAdd(s, r, p));
}

void		CCamera::Walk(const float& fDist)
{
	//m_vPosition += fDist * m_vLook;
	XMVECTOR s = XMVectorReplicate(fDist);	//s == (fDist, fDist, fDist);
	XMVECTOR l = XMLoadFloat3(&m_vLook);
	XMVECTOR p = XMLoadFloat3(&m_vPosition);

	XMStoreFloat3(&m_vPosition, XMVectorMultiplyAdd(s, l, p));
}
//카메라 회전
void		CCamera::Pitch(const float& fAngle)
{
	//up 벡터와 look 벡터를 right 벡터에 대해 회전
	XMMATRIX matRot =XMMatrixRotationAxis(XMLoadFloat3(&m_vRight), fAngle);

	XMStoreFloat3(&m_vUp, XMVector3TransformNormal(XMLoadFloat3(&m_vUp), matRot));
	XMStoreFloat3(&m_vLook, XMVector3TransformNormal(XMLoadFloat3(&m_vLook), matRot));
}

void		CCamera::RotateY(const float& fAngle)
{
	//기저벡터들을 세계의 y축에 대해 회전한다
	XMMATRIX matRotY = XMMatrixRotationY(fAngle);

	XMStoreFloat3(&m_vRight, XMVector3TransformNormal(XMLoadFloat3(&m_vRight), matRotY));
	XMStoreFloat3(&m_vUp, XMVector3TransformNormal(XMLoadFloat3(&m_vUp), matRotY));
	XMStoreFloat3(&m_vLook, XMVector3TransformNormal(XMLoadFloat3(&m_vLook), matRotY));
}

//매 프레임마다, 카메라 위치, 방향 수정 후 이 메서드를 호출해 시야 행렬 재구축
void		CCamera::UpdateViewMatrix()
{
	//카메라 right 벡터,up 벡터, look 벡터를 정규직교화한다
	//회전이 여러 번 반복되면 오차가 누적되기 때문에
	//정규직교가 아니면 특정 방향으로 기울어진 좌표계가 되어 문제가 발생한다

	XMVECTOR R = XMLoadFloat3(&m_vRight);
	XMVECTOR U = XMLoadFloat3(&m_vUp);
	XMVECTOR L = XMLoadFloat3(&m_vLook);
	XMVECTOR P = XMLoadFloat3(&m_vPosition);

	//시선벡터를 단위벡터로
	XMVector3Normalize(L);

	//보정된 새 상향 벡터를 계산해 정규화한다
	U = XMVector3Normalize(XMVector3Cross(L, R));

	//보정된 오른쪽 벡터를 계산
	//up, look이 정규직교이므로 외적을 정규화할 필요는 없다
	R = XMVector3Cross(U, L);

	//시야행렬의 성분을 채운다
	float x = -XMVectorGetX(XMVector3Dot(P, R));
	float y = -XMVectorGetX(XMVector3Dot(P, U));
	float z = -XMVectorGetX(XMVector3Dot(P, L));

	XMStoreFloat3(&m_vRight, R);
	XMStoreFloat3(&m_vUp, U);
	XMStoreFloat3(&m_vLook, L);

	m_tCam[CAM_PERSPECTIVE].matView(0, 0) = m_vRight.x;
	m_tCam[CAM_PERSPECTIVE].matView(1, 0) = m_vRight.y;
	m_tCam[CAM_PERSPECTIVE].matView(2, 0) = m_vRight.z;
	m_tCam[CAM_PERSPECTIVE].matView(3, 0) = x;

	m_tCam[CAM_PERSPECTIVE].matView(0, 1) = m_vUp.x;
	m_tCam[CAM_PERSPECTIVE].matView(1, 1) = m_vUp.y;
	m_tCam[CAM_PERSPECTIVE].matView(2, 1) = m_vUp.z;
	m_tCam[CAM_PERSPECTIVE].matView(3, 1) = y;

	m_tCam[CAM_PERSPECTIVE].matView(0, 2) = m_vLook.x;
	m_tCam[CAM_PERSPECTIVE].matView(1, 2) = m_vLook.y;
	m_tCam[CAM_PERSPECTIVE].matView(2, 2) = m_vLook.z;
	m_tCam[CAM_PERSPECTIVE].matView(3, 2) = z;

	m_tCam[CAM_PERSPECTIVE].matView(0, 3) = 0.f;
	m_tCam[CAM_PERSPECTIVE].matView(1, 3) = 0.f;
	m_tCam[CAM_PERSPECTIVE].matView(2, 3) = 0.f;
	m_tCam[CAM_PERSPECTIVE].matView(3, 3) = 1.f;
}

void		CCamera::FollowObject()
{
	XMVECTOR vObjectPos = m_pLookObject->GetPosXM();
	
	XMVECTOR vPos = vObjectPos + XMLoadFloat3(&m_vDest);

	XMStoreFloat3(&m_vPosition, vPos);
}

void CCamera::SetLookObject(CEntity* pEntity)
{
	m_pLookObject = pEntity;

	XMVECTOR vObjectPos = pEntity->GetPosXM();

	XMVECTOR vPos = vObjectPos + XMLoadFloat3(&m_vDest);

	XMVECTOR vWorldUp = XMLoadFloat3(&m_vUp);

	LookAt(vPos, vObjectPos, vWorldUp);
}
