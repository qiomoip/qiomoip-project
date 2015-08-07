#include "ClientApp.h"
#include "Device.h"
#include "MainWnd.h"
#include "Timer.h"
#include "GameEngine.h"

#include "CameraManager.h"

CClientApp::CClientApp(HINSTANCE hInstance)
	:CApp(hInstance)
{
}


CClientApp::~CClientApp(void)
{
	Clear();

}

bool CClientApp::Init(const int& iWidth, const int& iHeight)
{
	if(!CApp::Init(iWidth, iHeight))
		return false;

	_SINGLE(CGameEngine)->Init();

	return true;
}


void CClientApp::Update(float fTime)
{
	_SINGLE(CGameEngine)->Update(fTime);
}

void CClientApp::Input()
{
	_SINGLE(CGameEngine)->Input();
}

void CClientApp::Render()
{
	_SINGLE(CGameEngine)->Render();
}

void CClientApp::OnResize()
{
	CApp::OnResize();
	
	//ī�޶� ���� ��� ī�޶��� ���� ��� ����
	_SINGLE(CCameraManager)->SetLens(m_pMainWnd->GetClientWidth(), m_pMainWnd->GetClientHeight(),
		PI * 0.25f, m_pMainWnd->GetAspectRatio(), 1.f, 1000.f);
}

void CClientApp::Clear()
{
	_SINGLE(CGameEngine)->DestroyInstance();
}