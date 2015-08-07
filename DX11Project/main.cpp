#include "ClientApp.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
				   PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	
	//_CrtSetBreakAlloc( 139 ); 

	CClientApp theApp(hInstance);
	
	if( !theApp.Init(800, 600) )
		return 0;
	
	return theApp.Run();
}