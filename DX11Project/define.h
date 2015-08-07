#pragma once

using namespace DirectX;
using namespace DirectX::PackedVector;

#if defined(DEBUG) | defined(_DEBUG)
#ifndef HR
#define HR(x)									\
	{									\
		HRESULT hr = (x);						\
		if(FAILED(hr))							\
		{								\
			LPWSTR output;                                    	\
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |		\
				FORMAT_MESSAGE_IGNORE_INSERTS 	 |		\
				FORMAT_MESSAGE_ALLOCATE_BUFFER,			\
				NULL,						\
				hr,						\
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),	\
				(LPTSTR) &output,				\
				0,						\
				NULL);					        \
			MessageBox(NULL, output, L"Error", MB_OK);		\
		}								\
	}
#endif
#else
	#ifndef HR
	#define HR(x) (x)
	#endif
#endif 

#define _SINGLE(x)	x::GetInstance()
#define _DEVICE()		_SINGLE(CDevice)->GetDevice()
#define _ICONTEXT()		_SINGLE(CDevice)->GetContext()

XMGLOBALCONST XMVECTORF32 COLOR_WHITE     = {1.0f, 1.0f, 1.0f, 1.0f};
XMGLOBALCONST XMVECTORF32 COLOR_BLACK     = {0.0f, 0.0f, 0.0f, 1.0f};
XMGLOBALCONST XMVECTORF32 COLOR_RED       = {1.0f, 0.0f, 0.0f, 1.0f};
XMGLOBALCONST XMVECTORF32 COLOR_GREEN     = {0.0f, 1.0f, 0.0f, 1.0f};
XMGLOBALCONST XMVECTORF32 COLOR_BLUE      = {0.0f, 0.0f, 1.0f, 1.0f};
XMGLOBALCONST XMVECTORF32 COLOR_YELLOW    = {1.0f, 1.0f, 0.0f, 1.0f};
XMGLOBALCONST XMVECTORF32 COLOR_CYAN      = {0.0f, 1.0f, 1.0f, 1.0f};
XMGLOBALCONST XMVECTORF32 COLOR_MAGENTA   = {1.0f, 0.0f, 1.0f, 1.0f};

XMGLOBALCONST XMVECTORF32 COLOR_SILVER    = {0.75f, 0.75f, 0.75f, 1.0f};
XMGLOBALCONST XMVECTORF32 COLOR_LIGHTSTEELBLUE = {0.69f, 0.77f, 0.87f, 1.0f};

 namespace std { typedef basic_string<TCHAR> tstring; } 

 const float PI       = 3.1415926535f;
