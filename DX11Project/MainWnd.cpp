#include "MainWnd.h"
#include "App.h"


CMainWnd::CMainWnd(void)
	: m_iClientWidth(0)
	, m_iClientHeight(0)
	, m_strMainWndCaption(L"Express")
	, m_hMainWnd(NULL)
	, m_hInst(NULL)
{
}


CMainWnd::~CMainWnd(void)
{
}

const HWND& CMainWnd::GetMainWnd() const
{
	return m_hMainWnd;
}

float CMainWnd::GetAspectRatio() const
{
	return  static_cast<float>(m_iClientWidth) / m_iClientHeight;
}

std::tstring CMainWnd::GetCaption() const
{
	return m_strMainWndCaption;
}

const int&		CMainWnd::GetClientWidth() const
{
	return m_iClientWidth;
}

const int&		CMainWnd::GetClientHeight() const
{
	return m_iClientHeight;
}

bool CMainWnd::Init(const int& iWidth, const int& iHeight)
{
	m_iClientWidth = iWidth;
	m_iClientHeight = iHeight;

	WNDCLASS wc;
	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = CApp::MainWndProc; 
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = m_hInst;
	wc.hIcon         = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.lpszMenuName  = 0;
	wc.lpszClassName = L"D3DWndClassName";

	if( !RegisterClass(&wc) )
	{
		MessageBox(0, L"RegisterClass Failed.", 0, 0);
		return false;
	}

	// Compute window rectangle dimensions based on requested client area dimensions.
	RECT R = { 0, 0, m_iClientWidth, m_iClientHeight };
	AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	int width  = R.right - R.left;
	int height = R.bottom - R.top;

	m_hMainWnd = CreateWindow(L"D3DWndClassName", m_strMainWndCaption.c_str(), 
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, m_hInst, 0); 
	if( !m_hMainWnd )
	{
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		return false;
	}

	ShowWindow(m_hMainWnd, SW_SHOW);
	UpdateWindow(m_hMainWnd);

	return true;
}

void CMainWnd::SetSize(const int& iWidth, const int& iHeight)
{
	m_iClientHeight = iHeight;
	m_iClientWidth = iWidth;
}