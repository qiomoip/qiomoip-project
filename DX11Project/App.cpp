#include "App.h"
#include "Timer.h"
#include "Device.h"
#include "MainWnd.h"
#include "Debug.h"

CApp* g_pApp = NULL;

CApp::CApp()
{
}

CApp::CApp(HINSTANCE hInst)
	: m_hInst(hInst),		
	m_bAppPaused(false),	
	m_bMinimized(false),	
	m_bMaximized(false),	
	m_bResizing(false),	
	m_pMainTimer(NULL),
	m_iClientWidth(800),
	m_iClientHeight(600)
{
	g_pApp = this;
}


CApp::~CApp(void)
{
	Safe_Delete(m_pMainTimer);
	_SINGLE(CMainWnd)->DestroyInstance();
	_SINGLE(CDevice)->DestroyInstance();
}


LRESULT CALLBACK
	CApp::MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Forward hwnd on because we can get messages (e.g., WM_CREATE)
	// before CreateWindow returns, and thus before mhMainWnd is valid.
	return g_pApp->MsgProc(hwnd, msg, wParam, lParam);
}


HINSTANCE CApp::GetAppInst() const
{
	return m_hInst;
}


int CApp::Run()
{
	MSG msg = {0};
 
	m_pMainTimer->Reset();

	while(msg.message != WM_QUIT)
	{
		// If there are Window messages then process them.
		if(PeekMessage( &msg, 0, 0, 0, PM_REMOVE ))
		{
            TranslateMessage( &msg );
            DispatchMessage( &msg );
		}
		// Otherwise, do animation/game stuff.
		else
        {	
			m_pMainTimer->Tick();

			if( !m_bAppPaused )
			{
				m_pMainTimer->CalculateFrameStats(m_pMainWnd->GetCaption(), m_pMainWnd->GetMainWnd());
				Input();
				Update(m_pMainTimer->GetDeltaTime());	
				Render();
			}
			else
			{
				Sleep(100);
			}
        }
    }

	return (int)msg.wParam;
}

bool CApp::Init(const int& iWidth, const int& iHeight)
{
	#ifdef _DEBUG || DEBUG
	_SINGLE(CDebug)->Init();
	_SINGLE(CDebug)->CreateLogWindow();
#endif

	m_iClientWidth = iWidth;
	m_iClientHeight = iHeight;

	m_pMainTimer = new CTimer;

	m_pMainTimer->Init();

	m_pMainWnd = _SINGLE(CMainWnd);


	if(!m_pMainWnd->Init(m_iClientWidth, m_iClientHeight))
		return false;

	if(!_SINGLE(CDevice)->Init(m_pMainWnd->GetMainWnd(), m_iClientWidth, m_iClientHeight))
		return false;

	return true;
}

LRESULT CApp::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
		// WM_ACTIVATE is sent when the window is activated or deactivated.  
		// We pause the game when the window is deactivated and unpause it 
		// when it becomes active.  
	case WM_ACTIVATE:
		if( LOWORD(wParam) == WA_INACTIVE )
		{
			m_bAppPaused = true;
			m_pMainTimer->Stop();
		}
		else
		{
			m_bAppPaused = false;
			m_pMainTimer->Restart();
		}
		return 0;

		// WM_SIZE is sent when the user resizes the window.  
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
		}
		break;
	case WM_SIZE:
		// Save the new client area dimensions.
		m_iClientWidth  = LOWORD(lParam);
		m_iClientHeight = HIWORD(lParam);
		if(_DEVICE() )
		{
			if( wParam == SIZE_MINIMIZED )
			{
				m_bAppPaused = true;
				m_bMinimized = true;
				m_bMaximized = false;
			}
			else if( wParam == SIZE_MAXIMIZED )
			{
				m_bAppPaused = false;
				m_bMinimized = false;
				m_bMaximized = true;

				OnResize();
			}
			else if( wParam == SIZE_RESTORED )
			{

				// Restoring from minimized state?
				if( m_bMinimized )
				{
					m_bAppPaused = false;
					m_bMinimized = false;

					OnResize();
				}

				// Restoring from maximized state?
				else if( m_bMinimized )
				{
					m_bAppPaused = false;
					m_bMaximized = false;

					OnResize();
				}
				else if( m_bResizing )
				{
					// If user is dragging the resize bars, we do not resize 
					// the buffers here because as the user continuously 
					// drags the resize bars, a stream of WM_SIZE messages are
					// sent to the window, and it would be pointless (and slow)
					// to resize for each WM_SIZE message received from dragging
					// the resize bars.  So instead, we reset after the user is 
					// done resizing the window and releases the resize bars, which 
					// sends a WM_EXITSIZEMOVE message.
				}
				else // API call such as SetWindowPos or mSwapChain->SetFullscreenState.
				{
					OnResize();
				}
			}
		}
		return 0;

		// WM_EXITSIZEMOVE is sent when the user grabs the resize bars.
	case WM_ENTERSIZEMOVE:
		m_bAppPaused = true;
		m_bResizing  = true;
		m_pMainTimer->Stop();
		return 0;

		// WM_EXITSIZEMOVE is sent when the user releases the resize bars.
		// Here we reset everything based on the new window dimensions.
	case WM_EXITSIZEMOVE:
		m_bAppPaused = false;
		m_bResizing  = false;
		m_pMainTimer->Restart();
		_SINGLE(CDevice)->OnResize(m_iClientWidth, m_iClientHeight);
		return 0;

		// WM_DESTROY is sent when the window is being destroyed.
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

		// The WM_MENUCHAR message is sent when a menu is active and the user presses 
		// a key that does not correspond to any mnemonic or accelerator key. 
	case WM_MENUCHAR:
		// Don't beep when we alt-enter.
		return MAKELRESULT(0, MNC_CLOSE);

		// Catch this message so to prevent the window from becoming too small.
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200; 
		return 0;

	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
		OnMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
		OnMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_MOUSEMOVE:
		OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void CApp::OnResize()
{
	_SINGLE(CDevice)->OnResize(m_iClientWidth, m_iClientHeight);
	m_pMainWnd->SetSize(m_iClientWidth, m_iClientHeight);
}