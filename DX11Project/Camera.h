#pragma once
#include "include.h"

class CEntity;

class CCamera
{
private:
	//view ��ǥ ����	(
	XMFLOAT3	m_vPosition;	//ī�޶� ��ġ		(����)
	XMFLOAT3	m_vRight;	//ī�޶� ���� ����	(x)
	XMFLOAT3	m_vUp;		//ī�޶� ���� ����	(y)
	XMFLOAT3	m_vLook;		//ī�޶� �ü� ����	(z)

	//����ü �Ӽ�
	float		m_fNearZ;
	float		m_fFarZ;
	float		m_fAspect;
	float		m_fFovY;
	float		m_fNearWindowHeight;
	float		m_fFarWindowHeight;

	//�þ����, �������
	CAMERA		m_tCam[CAM_MAX];

	CAMERA_TYPE	m_eCam;

	CEntity*	m_pLookObject;

	XMFLOAT3	m_vDest;

	//ī�޶��̵�, ȸ�� �ӵ� ��.
	float		m_fSmooth;

public:
	virtual void		Init();
	virtual void		Update();
	virtual void		Input(float fTime);

	//������� ī�޶� ��ġ�� ��ȸ
	XMVECTOR			GetPositionXM() const;
	const XMFLOAT3&		GetPosition() const;

	//ī�޶� ���� ���� ��ȯ
	XMVECTOR			GetRightXM() const;
	XMVECTOR			GetUpXM() const;
	XMVECTOR			GetLookXM() const;
	const XMFLOAT3&		GetRight() const;
	const XMFLOAT3&		GetUp() const;
	const XMFLOAT3&		GetLook() const;

	//����ü �Ӽ� ��ȯ
	const float&		GetNearZ() const;
	const float&		GetFarZ() const;
	const float&		GetAspect() const;
	const float&		GetFovY() const;
	const float&		GetFovX() const;

	//�þ߰��� ���� ���� ��� ũ�� ��ȯ
	float		GetNearWindowWidth() const;			//����� ����ü �ʺ�
	float		GetFarWindowWidth() const;			//����� ����ü �ʺ�
	const float&		GetNearWindowHeight() const;//����� ����ü ����
	const float&		GetFarWindowHeight() const;	//����� ����ü ����

	//�þ����, ������� ��ȯ
	XMMATRIX	GetView(const CAMERA_TYPE& eCam = CAM_PERSPECTIVE) const;
	XMMATRIX	GetProj(const CAMERA_TYPE& eCam = CAM_PERSPECTIVE) const;
	XMMATRIX	GetViewProj(const CAMERA_TYPE& eCam = CAM_PERSPECTIVE) const;

	//ī�޶� Ÿ�� ����
	void		SetCameraType(const CAMERA_TYPE& eCam);
	//����ü ����
	void		SetLens(const float& fWidth, const float& fHeight, const float& fFovY, const float& fAspect, const float& fZn, const float& fZf);

	//ī�޶� ��ġ, �ü�, ���� ���ͷ� ī�޶� ���� ����
	void		LookAt(const FXMVECTOR& vPos, const FXMVECTOR& vTarget, const FXMVECTOR& vWorldUp);
	void		LookAt(const XMFLOAT3& vPos, const XMFLOAT3& vTarget, const XMFLOAT3& vUp);

	//���� ���� ī�޶� ��ġ ����
	void		SetPosition(const float& fX, const float& fY, const float& fZ);
	void		SetPosition(const XMFLOAT3& vPos);

	//ī�޶� d��ŭ Ⱦ�̵�, ���̵�
	void		Strafe(const float& fDist);
	void		Walk(const float& fDist);

	//ī�޶� ȸ��
	//X�� ȸ��
	void		Pitch(const float& fAngle);
	//Y�� ȸ��
	void		RotateY(const float& fAngle);

	//�� �����Ӹ���, ī�޶� ��ġ, ���� ���� �� �� �޼��带 ȣ���� �þ� ��� �籸��
	void		UpdateViewMatrix();

	void		FollowObject();

	void		SetLookObject(CEntity* pEntity);	

public:
	CCamera(void);
	virtual ~CCamera(void);
};

