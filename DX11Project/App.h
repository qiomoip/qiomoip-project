#pragma once
#include "include.h"
class CTimer;
class CMainWnd;

class CApp
{
protected:
	HINSTANCE		m_hInst;		//���� ���α׷��� �ν��Ͻ� �ڵ�
	//HWND			m_hMainWnd;		//�� â �ڵ�
	bool			m_bAppPaused;	//���� �Ͻ������� �����ΰ�
	bool			m_bMinimized;	//�ּ�ȭ�� �����ΰ�
	bool			m_bMaximized;	//�ִ�ȭ�� �����ΰ�
	bool			m_bResizing;	//����ڰ� ũ�� ������ �׵θ��� ���� �ִ� �����ΰ�
	CTimer*			m_pMainTimer;	//����ð��� ���� ��ü �ð��� �����ϴ� �� ���δ�
	CMainWnd*		m_pMainWnd;		//������ â ����
protected:
	//app�� �����ڿ��� �⺻����� �ʱ�ȭ�Ǵ� ������
	//â ũ��
	int					m_iClientWidth;
	int					m_iClientHeight;

public:
	HINSTANCE GetAppInst() const;
	HWND GetMainWnd() const;
	float GetAspectRatio() const;


	int Run();

	// �����ӿ�ũ �޼���
	//�Ļ� Ŭ���̾�Ʈ Ŭ������ �� �޼��带 �ڽ��� �䱸�� �°� �������Ѵ�

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

