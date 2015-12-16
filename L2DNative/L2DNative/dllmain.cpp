#include "stdafx.h"

#pragma region [   DLL   ]
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
#pragma endregion

#pragma region [   Manager   ]
static CRendererManager *pManager = NULL;

static HRESULT EnsureRendererManager()
{
	return pManager ? S_OK : CRendererManager::Create(&pManager);
}
#pragma endregion

#pragma region [   DirectX Extern   ]
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

extern "C" HRESULT WINAPI Destroy()
{
	HRESULT hr = S_OK;

	delete pManager;
	pManager = NULL;

Cleanup:
	return hr;
}
#pragma endregion

#pragma region [   Model Extern   ]
extern "C" HRESULT WINAPI LoadModel(char* modelPath, long* ret)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	*ret = pManager->LoadModel(modelPath);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI RemoveModel(long hModel)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	pManager->RemoveModel(hModel);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI SetParamFloat(long hModel, char* key, float value)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	pManager->SetParamFloat(hModel, key, value);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI GetParamFloat(long hModel, char* key, float* ret)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	*ret = pManager->GetParamFloat(hModel, key);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI MultParamFloat(long hModel, char* key, float value)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	pManager->MultParamFloat(hModel, key, value);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI AddToParamFloat(long hModel, char* key, float value)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	pManager->AddToParamFloat(hModel, key, value);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI SetPartsOpacity(long hModel, char* key, float value)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	pManager->SetPartsOpacity(hModel, key, value);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI GetPartsOpacity(long hModel, char* key, float* ret)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	*ret = pManager->GetPartsOpacity(hModel, key);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI SaveParam(long hModel)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	pManager->SaveParam(hModel);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI LoadParam(long hModel)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	pManager->LoadParam(hModel);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI SetTexture(long hModel, LPCWSTR texturePath)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	pManager->SetTexture(hModel, texturePath);

Cleanup:
	return hr;
}
#pragma endregion

#pragma region [   Motion   ]
extern "C" HRESULT WINAPI LoadMotion(char* motionPath, long* ret)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	*ret = pManager->LoadMotion(motionPath);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI SetFadeIn(long hMotion, int msec)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	pManager->SetFadeIn(hMotion, msec);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI SetFadeOut(long hMotion, int msec)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	pManager->SetFadeOut(hMotion, msec);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI SetLoop(long hMotion, bool loop)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	pManager->SetLoop(hMotion, loop);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI StartMotion(long hMotion)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	pManager->StartMotion(hMotion);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI UpdateParam(long hModel)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	pManager->UpdateParam(hModel);

Cleanup:
	return hr;
}
#pragma endregion

#pragma region [   Live2D Extern   ]
extern "C" HRESULT WINAPI BeginRender(long hModel)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	return pManager->BeginRender(hModel);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI EndRender(long hModel)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	return pManager->EndRender(hModel);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI Dispose()
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	pManager->Dispose();

Cleanup:
	return hr;
}

#pragma endregion