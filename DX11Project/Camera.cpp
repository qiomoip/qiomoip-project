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

//������� ī�޶� ��ġ�� ��ȸ
XMVECTOR	CCamera::GetPositionXM() const
{
	return XMLoadFloat3(&m_vPosition);
}

const XMFLOAT3&	CCamera::GetPosition() const
{
	return m_vPosition;
}

//ī�޶� ���� ���� ��ȯ
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
//����ü �Ӽ� ��ȯ
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
//�þ߰��� ���� ���� ��� ũ�� ��ȯ
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
//�þ����, ������� ��ȯ
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

//����ü ����
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

//ī�޶� ��ġ, �ü�, ���� ���ͷ� ī�޶� ���� ����
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

//���� ���� ī�޶� ��ġ ����
void		CCamera::SetPosition(const float& fX, const float& fY, const float& fZ)
{
}

void		CCamera::SetPosition(const XMFLOAT3& vPos)
{
	m_vPosition = vPos;
}
//ī�޶� d��ŭ Ⱦ�̵�, ���̵�
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
//ī�޶� ȸ��
void		CCamera::Pitch(const float& fAngle)
{
	//up ���Ϳ� look ���͸� right ���Ϳ� ���� ȸ��
	XMMATRIX matRot =XMMatrixRotationAxis(XMLoadFloat3(&m_vRight), fAngle);

	XMStoreFloat3(&m_vUp, XMVector3TransformNormal(XMLoadFloat3(&m_vUp), matRot));
	XMStoreFloat3(&m_vLook, XMVector3TransformNormal(XMLoadFloat3(&m_vLook), matRot));
}

void		CCamera::RotateY(const float& fAngle)
{
	//�������͵��� ������ y�࿡ ���� ȸ���Ѵ�
	XMMATRIX matRotY = XMMatrixRotationY(fAngle);

	XMStoreFloat3(&m_vRight, XMVector3TransformNormal(XMLoadFloat3(&m_vRight), matRotY));
	XMStoreFloat3(&m_vUp, XMVector3TransformNormal(XMLoadFloat3(&m_vUp), matRotY));
	XMStoreFloat3(&m_vLook, XMVector3TransformNormal(XMLoadFloat3(&m_vLook), matRotY));
}

//�� �����Ӹ���, ī�޶� ��ġ, ���� ���� �� �� �޼��带 ȣ���� �þ� ��� �籸��
void		CCamera::UpdateViewMatrix()
{
	//ī�޶� right ����,up ����, look ���͸� ��������ȭ�Ѵ�
	//ȸ���� ���� �� �ݺ��Ǹ� ������ �����Ǳ� ������
	//���������� �ƴϸ� Ư�� �������� ������ ��ǥ�谡 �Ǿ� ������ �߻��Ѵ�

	XMVECTOR R = XMLoadFloat3(&m_vRight);
	XMVECTOR U = XMLoadFloat3(&m_vUp);
	XMVECTOR L = XMLoadFloat3(&m_vLook);
	XMVECTOR P = XMLoadFloat3(&m_vPosition);

	//�ü����͸� �������ͷ�
	XMVector3Normalize(L);

	//������ �� ���� ���͸� ����� ����ȭ�Ѵ�
	U = XMVector3Normalize(XMVector3Cross(L, R));

	//������ ������ ���͸� ���
	//up, look�� ���������̹Ƿ� ������ ����ȭ�� �ʿ�� ����
	R = XMVector3Cross(U, L);

	//�þ������ ������ ä���
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
