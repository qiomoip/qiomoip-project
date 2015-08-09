#pragma once
#include "include.h"
class CTimer;
class CMainWnd;

class CApp
{
protected:
	HINSTANCE		m_hInst;		//응용 프로그램의 인스턴스 핸들
	//HWND			m_hMainWnd;		//주 창 핸들
	bool			m_bAppPaused;	//앱이 일시정지된 상태인가
	bool			m_bMinimized;	//최소화된 상태인가
	bool			m_bMaximized;	//최대화된 상태인가
	bool			m_bResizing;	//사용자가 크기 조정용 테두리를 끌고 있는 상태인가
	CTimer*			m_pMainTimer;	//경과시간과 게임 전체 시간을 측정하는 데 쓰인다
	CMainWnd*		m_pMainWnd;		//윈도우 창 관리
protected:
	//app의 생성자에서 기본값들로 초기화되는 변수들
	//창 크기
	int					m_iClientWidth;
	int					m_iClientHeight;

public:
	HINSTANCE GetAppInst() const;
	HWND GetMainWnd() const;
	float GetAspectRatio() const;


	int Run();

	// 프레임워크 메서드
	//파생 클라이언트 클래스는 이 메서드를 자신의 요구에 맞게 재정의한다

	virtual bool Init(const int& iWidth, const int& iHeight);
	virtual void Update(float fTime)PURE;
	virtual void Input(float fTime)PURE;
	virtual void Render()PURE;
	virtual void Clear()PURE;
	virtual LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	// Convenience overrides for handling mouse input.
	virtual void OnMouseDown(WPARAM btnState, int x, int y){ }
	virtual void OnMouseUp(WPARAM btnState, int x, int y)  { }
	virtual void OnMouseMove(WPARAM btnState, int x, int y){ }
	virtual void OnResize();

	static LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
public:
	CApp(void);
	CApp(HINSTANCE hInst);
	virtual ~CApp(void);
};

