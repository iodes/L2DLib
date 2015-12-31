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

extern "C" HRESULT WINAPI SetParamFloatInt(long hModel, int key, float value)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	pManager->SetParamFloatInt(hModel, key, value);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI SetParamFloatString(long hModel, char* key, float value)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	pManager->SetParamFloatString(hModel, key, value);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI GetParamFloatInt(long hModel, int key, float* ret)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	*ret = pManager->GetParamFloatInt(hModel, key);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI GetParamFloatString(long hModel, char* key, float* ret)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	*ret = pManager->GetParamFloatString(hModel, key);

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

extern "C" HRESULT WINAPI SetPartsOpacityInt(long hModel, int key, float value)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	pManager->SetPartsOpacityInt(hModel, key, value);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI SetPartsOpacityString(long hModel, char* key, float value)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	pManager->SetPartsOpacityString(hModel, key, value);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI GetPartsOpacityInt(long hModel, int key, float* ret)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	*ret = pManager->GetPartsOpacityInt(hModel, key);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI GetPartsOpacityString(long hModel, char* key, float* ret)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	*ret = pManager->GetPartsOpacityString(hModel, key);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI GetParamIndex(long hModel, char* key, int* ret)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	*ret = pManager->GetParamIndex(hModel, key);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI GetPartsDataIndex(long hModel, char* key, int* ret)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	*ret = pManager->GetPartsDataIndex(hModel, key);

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

extern "C" HRESULT WINAPI UpdateMotion(long hModel)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	pManager->UpdateMotion(hModel);

Cleanup:
	return hr;
}
#pragma endregion

#pragma region [   Eye Blink   ]
extern "C" HRESULT WINAPI EyeBlinkUpdate(long hModel)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	pManager->EyeBlinkUpdate(hModel);

Cleanup:
	return hr;
}
#pragma endregion

#pragma region [   Physics   ]
extern "C" HRESULT WINAPI CreatePhysics(long* ret)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	*ret = pManager->CreatePhysics();

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI PhysicsSetup(long physicsHandler, float baseLengthM, float airRegistance, float mass)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	pManager->PhysicsSetup(physicsHandler, baseLengthM, airRegistance, mass);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI PhysicsAddSrcParam(long physicsHandler, const char* srcType, const char * paramID, float scale, float weight)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	pManager->PhysicsAddSrcParam(physicsHandler, srcType, paramID, scale, weight);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI PhysicsAddTargetParam(long physicsHandler, const char* targetType, const char * paramID, float scale, float weight)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	pManager->PhysicsAddTargetParam(physicsHandler, targetType, paramID, scale, weight);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI PhysicsUpdate(long physicsHandler, long hModel, INT64 time)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	pManager->PhysicsUpdate(physicsHandler, hModel, time);

Cleanup:
	return hr;
}
#pragma endregion

#pragma region [   Expression   ]
extern "C" HRESULT WINAPI CreateExpression(long* ret)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	*ret = pManager->CreateExpression();

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI StartExpression(long expressionHandler)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	pManager->StartExpression(expressionHandler);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI ExpressionSetFadeIn(long expressionHandler, int FadeInMSec)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	pManager->ExpressionSetFadeIn(expressionHandler, FadeInMSec);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI ExpressionSetFadeOut(long expressionHandler, int FadeOutMSec)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	pManager->ExpressionSetFadeOut(expressionHandler, FadeOutMSec);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI ExpressionAddParam(long expressionHandler, char* paramID, char* calc, float value, float defaultValue)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	pManager->ExpressionAddParam(expressionHandler, paramID, calc, value, defaultValue);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI ExpressionAddParamV09(long expressionHandler, char* paramID, float value, float defaultValue)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	pManager->ExpressionAddParamV09(expressionHandler, paramID, value, defaultValue);

Cleanup:
	return hr;
}

extern "C" HRESULT WINAPI UpdateExpression(long hModel)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	pManager->UpdateExpression(hModel);

Cleanup:
	return hr;
}
#pragma endregion

#pragma region [   Live2D Extern   ]
extern "C" HRESULT WINAPI GetUserTimeMSec(INT64* ret)
{
	HRESULT hr = S_OK;
	IFC(EnsureRendererManager());

	*ret = pManager->GetUserTimeMSec();

Cleanup:
	return hr;
}

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