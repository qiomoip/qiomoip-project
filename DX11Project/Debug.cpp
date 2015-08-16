#include "Debug.h"


CDebug::CDebug(void) :
	m_hwnd(NULL),
	m_hwndList(NULL)
{
	memset(&m_WndInfo, 0, sizeof(RECT) );
	memset(&m_WndClass, 0, sizeof(WNDCLASS) );
}


CDebug::~CDebug(void)
{
	Clear();
}

void CDebug::Init()
{	
	
	m_WndClass.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	m_WndClass.lpfnWndProc		= (WNDPROC)CDebug::WndProcZFLog;
	m_WndClass.cbClsExtra		= 0;							// No Extra Window Data
	m_WndClass.cbWndExtra		= 0;							// No Extra Window Data
	m_WndClass.hInstance		= GetModuleHandle( NULL );
	m_WndClass.hIcon			= LoadIcon(NULL, IDI_WINLOGO);	// Load The Default Icon
	m_WndClass.hCursor			= LoadCursor(NULL, IDC_ARROW);	// Load The Arrow Pointer
	m_WndClass.hbrBackground	= (HBRUSH)GetStockObject( WHITE_BRUSH) ;
	m_WndClass.lpszMenuName		= NULL;
	//hwnd의 CreateWindow와 같은 이름이어야 한다. 
	m_WndClass.lpszClassName	= _T("LogWindow");

	RegisterClass(&m_WndClass);

	m_WndInfo.right = ZF_LOG_WINDOW_CX;
	m_WndInfo.bottom = ZF_LOG_WINDOW_CY;
	m_WndInfo.left = GetSystemMetrics( SM_CXFULLSCREEN ) - m_WndInfo.right;
	m_WndInfo.top = 0;

	
}
//로그 창 생성
void CDebug::CreateLogWindow()
{
	RECT rc;
	m_hwnd = CreateWindow( m_WndClass.lpszClassName, _T("WINDOW"), WS_POPUP | WS_CAPTION, 
		m_WndInfo.left, m_WndInfo.top, m_WndInfo.right, m_WndInfo.bottom,
		NULL, NULL, GetModuleHandle( NULL ), NULL );
	
	GetClientRect( m_hwnd, &rc );
	m_hwndList = CreateWindow( _T("LISTBOX"), _T(""), WS_CHILD | WS_VSCROLL, 0, 0, 
		rc.right, rc.bottom, m_hwnd, NULL, GetModuleHandle( NULL ), NULL );
	ShowWindow( m_hwnd, SW_SHOW );
	ShowWindow( m_hwndList, SW_SHOW );
}


void CDebug::Clear()
{
	DestroyWindow( m_hwnd );
}


LRESULT CALLBACK CDebug::WndProcZFLog( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	return DefWindowProc( hwnd, uMsg, wParam, lParam );
}

void CDebug::AddLog(LPTSTR log, ...)
{
	TCHAR buf[1024];

	_vstprintf(buf, log, (char*)(&log+1) ); 

	SendMessage( m_hwndList, LB_ADDSTRING, 0, (LPARAM) buf );
	UINT32 n = SendMessage( m_hwndList, LB_GETCOUNT, 0, 0L ) - 1;
	SendMessage( m_hwndList, LB_SETCURSEL, (WPARAM)n, 0L );
}