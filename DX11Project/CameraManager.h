#pragma once
#include "singleton.h"

class CCamera;

class CCameraManager
	: public CSingleton<CCameraManager>
{
	friend CSingleton;

private:
	map<tstring, CCamera*>	m_mapCamera;
	CCamera*				m_pCurCamera;

public:
	CCamera* CreateCamera(const tstring& strKey);
	CCamera* FindCamera(const tstring& strKey);
	
	void SetCurrentCamera(CCamera* pCamera);
	void SetCurrentCamera(const tstring& strKey);

	const CCamera* GetCurCamera() const;

	void SetLens(const float& fWidth, const float& fHeight, const float& fFovY, const float& fAspect, const float& fZn, const float& fZf);

	void Update(float fTime);
	void Input(float fTime);
	void Clear();

private:
	CCameraManager(void);
	~CCameraManager(void);
};

