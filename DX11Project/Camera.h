#pragma once
#include "include.h"

class CEntity;

class CCamera
{
private:
	//view 좌표 구성	(
	XMFLOAT3	m_vPosition;	//카메라 위치		(원점)
	XMFLOAT3	m_vRight;	//카메라 우향 벡터	(x)
	XMFLOAT3	m_vUp;		//카메라 상향 벡터	(y)
	XMFLOAT3	m_vLook;		//카메라 시선 벡터	(z)

	//절두체 속성
	float		m_fNearZ;
	float		m_fFarZ;
	float		m_fAspect;
	float		m_fFovY;
	float		m_fNearWindowHeight;
	float		m_fFarWindowHeight;

	//시야행렬, 투영행렬
	CAMERA		m_tCam[CAM_MAX];

	CAMERA_TYPE	m_eCam;

	CEntity*	m_pLookObject;

	XMFLOAT3	m_vDest;

	//카메라이동, 회전 속도 값.
	float		m_fSmooth;

public:
	virtual void		Init();
	virtual void		Update();
	virtual void		Input(float fTime);

	//세계공간 카메라 위치를 조회
	XMVECTOR			GetPositionXM() const;
	const XMFLOAT3&		GetPosition() const;

	//카메라 기저 벡터 반환
	XMVECTOR			GetRightXM() const;
	XMVECTOR			GetUpXM() const;
	XMVECTOR			GetLookXM() const;
	const XMFLOAT3&		GetRight() const;
	const XMFLOAT3&		GetUp() const;
	const XMFLOAT3&		GetLook() const;

	//절두체 속성 반환
	const float&		GetNearZ() const;
	const float&		GetFarZ() const;
	const float&		GetAspect() const;
	const float&		GetFovY() const;
	const float&		GetFovX() const;

	//시야공간 기준 원근 평면 크기 반환
	float		GetNearWindowWidth() const;			//근평면 절두체 너비
	float		GetFarWindowWidth() const;			//원평면 절두체 너비
	const float&		GetNearWindowHeight() const;//근평면 절두체 높이
	const float&		GetFarWindowHeight() const;	//원평면 절두체 높이

	//시야행렬, 투영행렬 반환
	XMMATRIX	GetView(const CAMERA_TYPE& eCam = CAM_PERSPECTIVE) const;
	XMMATRIX	GetProj(const CAMERA_TYPE& eCam = CAM_PERSPECTIVE) const;
	XMMATRIX	GetViewProj(const CAMERA_TYPE& eCam = CAM_PERSPECTIVE) const;

	//카메라 타입 설정
	void		SetCameraType(const CAMERA_TYPE& eCam);
	//절두체 설정
	void		SetLens(const float& fWidth, const float& fHeight, const float& fFovY, const float& fAspect, const float& fZn, const float& fZf);

	//카메라 위치, 시선, 상향 벡터로 카메라 공간 설정
	void		LookAt(const FXMVECTOR& vPos, const FXMVECTOR& vTarget, const FXMVECTOR& vWorldUp);
	void		LookAt(const XMFLOAT3& vPos, const XMFLOAT3& vTarget, const XMFLOAT3& vUp);

	//세계 공간 카메라 위치 설정
	void		SetPosition(const float& fX, const float& fY, const float& fZ);
	void		SetPosition(const XMFLOAT3& vPos);

	//카메라 d만큼 횡이동, 축이동
	void		Strafe(const float& fDist);
	void		Walk(const float& fDist);

	//카메라 회전
	//X축 회전
	void		Pitch(const float& fAngle);
	//Y축 회전
	void		RotateY(const float& fAngle);

	//매 프레임마다, 카메라 위치, 방향 수정 후 이 메서드를 호출해 시야 행렬 재구축
	void		UpdateViewMatrix();

	void		FollowObject();

	void		SetLookObject(CEntity* pEntity);	

public:
	CCamera(void);
	virtual ~CCamera(void);
};

