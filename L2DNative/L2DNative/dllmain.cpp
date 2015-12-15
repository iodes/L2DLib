#include "stdafx.h"

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

static CRendererManager *pManager = NULL;

static HRESULT EnsureRendererManager()
{
	return pManager ? S_OK : CRendererManager::Create(&pManager);
}

extern "C" HRESULT WINAPI SetSize(UINT uWidth, UINT uHeight)
{
	HRESULT hr = S_OK;

	IFC(EnsureRendererManager());

	pManager->SetSize(uWidth, uHeight);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI SetAlpha(BOOL fUseAlpha)
{
	HRESULT hr = S_OK;

	IFC(EnsureRendererManager());

	pManager->SetAlpha(!!fUseAlpha);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI SetNumDesiredSamples(UINT uNumSamples)
{
	HRESULT hr = S_OK;

	IFC(EnsureRendererManager());

	pManager->SetNumDesiredSamples(uNumSamples);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI SetAdapter(POINT screenSpacePoint)
{
	HRESULT hr = S_OK;

	IFC(EnsureRendererManager());

	pManager->SetAdapter(screenSpacePoint);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI GetBackBufferNoRef(IDirect3DSurface9 **ppSurface)
{
	HRESULT hr = S_OK;

	IFC(EnsureRendererManager());

	IFC(pManager->GetBackBufferNoRef(ppSurface));

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI SetArgument(Argument argument)
{
	HRESULT hr = S_OK;

	IFC(EnsureRendererManager());

	pManager->SetArgument(argument);

Cleanup:
	return hr;
}

extern "C" void WINAPI SetParamFloat(char* key, float value)
{
	pManager->SetParamFloat(key, value);
}

extern "C" void WINAPI AddToParamFloat(char* key, float value)
{
	pManager->AddToParamFloat(key, value);
}

extern "C" void WINAPI MultParamFloat(char* key, float value)
{
	pManager->MultParamFloat(key, value);
}

extern "C" float WINAPI GetParamFloat(char* key)
{
	return pManager->GetParamFloat(key);
}

extern "C" void WINAPI SetPartsOpacity(char* key, float value)
{
	pManager->SetPartsOpacity(key, value);
}

extern "C" float WINAPI GetPartsOpacity(char* key)
{
	return pManager->GetPartsOpacity(key);
}

extern "C" void WINAPI SaveParam()
{
	pManager->SaveParam();
}
extern "C" void WINAPI LoadParam()
{
	pManager->LoadParam();
}

extern "C" HRESULT WINAPI BeginRender()
{
	assert(pManager);

	return pManager->BeginRender();
}

extern "C" HRESULT WINAPI EndRender()
{
	assert(pManager);

	return pManager->EndRender();
}

extern "C" void WINAPI Destroy()
{
	delete pManager;
	pManager = NULL;
}