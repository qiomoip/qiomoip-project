#pragma once
#include "singleton.h"

#define ZF_LOG_WINDOW_CX 300
#define ZF_LOG_WINDOW_CY 800

class CDebug :
	public CSingleton<CDebug>
{
private:
	HWND		m_hwnd;
	HWND		m_hwndList;
	
	RECT		m_WndInfo;
	WNDCLASS	m_WndClass;

public:
	CDebug(void);
	~CDebug(void);

	void Init();
	//로그 창 생성
	void CreateLogWindow();
	
	void Clear();
		
	static LRESULT CALLBACK CDebug::WndProcZFLog( 
		HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

	void AddLog(LPTSTR log, ...);
};

