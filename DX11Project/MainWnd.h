#pragma once
#include "singleton.h"

class CMainWnd
	: public CSingleton<CMainWnd>
{
	friend CSingleton;
private:
	int					m_iClientWidth;
	int					m_iClientHeight;
	std::tstring		m_strMainWndCaption;	//창의 제목
	HWND			m_hMainWnd;		//주 창 핸들
	HINSTANCE		m_hInst;		//응용 프로그램의 인스턴스 핸들

public:
	const HWND& GetMainWnd() const;
	float GetAspectRatio() const;
	std::tstring GetCaption() const;
	const int&		GetClientWidth() const;
	const int&		GetClientHeight() const;

	bool Init(const int& iWidth, const int& iHeight);
	void SetSize(const int& iWidth, const int& iHeight);

private:
	CMainWnd(void);
	~CMainWnd(void);
};

