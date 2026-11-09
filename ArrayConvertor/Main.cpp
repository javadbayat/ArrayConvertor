#include "ArrayConvertor.h"
#include <new>

#ifdef _WIN64
	#pragma comment(lib, "libstation.x64.lib")
#else
	#pragma comment(lib, "libstation.x86.lib")
#endif

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG ulReason, LPVOID pvReserved)
{
	return TRUE;
}

STDAPI StationGetObject(LPUNKNOWN *ppStation)
{
	try
	{
		(*ppStation = new CArrayConvertor)->AddRef();
	}
	catch (std::bad_alloc &)
	{
		return E_OUTOFMEMORY;
	}

	return S_OK;
}