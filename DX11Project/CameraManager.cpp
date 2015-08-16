#include "CameraManager.h"
#include "KeyManager.h"
#include "Camera.h"


CCameraManager::CCameraManager(void)
	: m_pCurCamera(NULL)
{
}


CCameraManager::~CCameraManager(void)
{
	Clear();
}

CCamera* CCameraManager::CreateCamera(const tstring& strKey)
{
	CCamera* pCamera = new CCamera;

	pCamera->Init();

	m_mapCamera.insert(map<tstring, CCamera*>::value_type(strKey, pCamera));

	return pCamera;
}

CCamera* CCameraManager::FindCamera(const tstring& strKey)
{
	map<tstring, CCamera*>::iterator iter = m_mapCamera.find(strKey);

	if(iter == m_mapCamera.end())
		return NULL;

	return iter->second;
}

void CCameraManager::SetCurrentCamera(CCamera* pCamera)
{
	m_pCurCamera = pCamera;
}

void CCameraManager::SetCurrentCamera(const tstring& strKey)
{
	CCamera* pCamera = FindCamera(strKey);

	m_pCurCamera = pCamera;
}

const CCamera* CCameraManager::GetCurCamera() const
{
	return m_pCurCamera;
}

void CCameraManager::SetLens(const float& fWidth, const float& fHeight, const float& fFovY, const float& fAspect, const float& fZn, const float& fZf)
{
	if(!m_pCurCamera)
		return;

	m_pCurCamera->SetLens(fWidth, fHeight, fFovY, fAspect, fZn, fZf);
}

void CCameraManager::Update(float fTime)
{
	if(!m_pCurCamera)
		return;

	m_pCurCamera->Update(fTime);
}

void CCameraManager::Input()
{
#if defined(DEBUG) | defined(_DEBUG)
	//테스트용 서브 카메라 전환.(메인 카메라로 시작하는 것을 전제.)
	const KEYINFO* pKey = NULL;
	pKey = _SINGLE(CKeyManager)->GetKey(KEY_VKSPACE);
	if(pKey)
	{
		if(/*pKey->bDown ||*/ pKey->bPush)
		{
			static bool isMainCam = true;

			if( isMainCam == true)
			{
				SetCurrentCamera( _T("SubCamera") );
				isMainCam = false;
			}
			else 
			{
				SetCurrentCamera( _T("MainCamera") );
				isMainCam = true;
			}
		}
	}
#endif

	if(!m_pCurCamera)
		return;
	m_pCurCamera->Input();
}

void CCameraManager::Clear()
{
	map<tstring, CCamera*>::iterator iter = m_mapCamera.begin();

	for(; iter != m_mapCamera.end(); ++iter)
	{
		Safe_Delete(iter->second);
	}
	m_mapCamera.clear();
}

