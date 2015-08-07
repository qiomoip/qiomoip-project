#pragma once
#include "singleton.h"

class CMainWnd
	: public CSingleton<CMainWnd>
{
	friend CSingleton;
private:
	int					m_iClientWidth;
	int					m_iClientHeight;
	std::tstring		m_strMainWndCaption;	//â�� ����
	HWND			m_hMainWnd;		//�� â �ڵ�
	HINSTANCE		m_hInst;		//���� ���α׷��� �ν��Ͻ� �ڵ�

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

