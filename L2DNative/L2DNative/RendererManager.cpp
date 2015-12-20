//+-----------------------------------------------------------------------------
//
//  CRendererManager
//
//      Manages the list of CRenderers. Managed code pinvokes into this class
//      and this class forwards to the appropriate CRenderer.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#pragma region [   DirectX   ]
const static TCHAR szAppName[] = TEXT("L2DNative");
typedef HRESULT(WINAPI *DIRECT3DCREATE9EXFUNCTION)(UINT SDKVersion, IDirect3D9Ex**);

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererManager 생성자
//
//------------------------------------------------------------------------------
CRendererManager::CRendererManager()
	:
	m_pD3D(NULL),
	m_pD3DEx(NULL),
	m_cAdapters(0),
	m_hwnd(NULL),
	m_pCurrentRenderer(NULL),
	m_rgRenderers(NULL),
	m_uWidth(1024),
	m_uHeight(1024),
	m_uNumSamples(0),
	m_fUseAlpha(false),
	m_fSurfaceSettingsChanged(true)
{

}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererManager 소멸자
//
//------------------------------------------------------------------------------
CRendererManager::~CRendererManager()
{
	DestroyResources();

	if (m_hwnd)
	{
		DestroyWindow(m_hwnd);
		UnregisterClass(szAppName, NULL);
	}
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererManager::Create
//
//  Synopsis:
//      Creates the manager
//
//------------------------------------------------------------------------------
HRESULT
CRendererManager::Create(CRendererManager **ppManager)
{
	HRESULT hr = S_OK;

	*ppManager = new CRendererManager();
	IFCOOM(*ppManager);

Cleanup:
	return hr;
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererManager::EnsureRenderers
//
//  Synopsis:
//      Makes sure the CRenderer objects exist
//
//------------------------------------------------------------------------------
HRESULT
CRendererManager::EnsureRenderers()
{
	HRESULT hr = S_OK;

	if (!m_rgRenderers)
	{
		IFC(EnsureHWND());

		assert(m_cAdapters);
		m_rgRenderers = new CRenderer*[m_cAdapters];
		IFCOOM(m_rgRenderers);
		ZeroMemory(m_rgRenderers, m_cAdapters * sizeof(m_rgRenderers[0]));

		for (UINT i = 0; i < m_cAdapters; ++i)
		{
			IFC(CRendererL2D::Create(m_pD3D, m_hwnd, i, &m_rgRenderers[i]));
		}

		// Default to the default adapter 
		m_pCurrentRenderer = m_rgRenderers[0];
	}

Cleanup:
	return hr;
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererManager::EnsureHWND
//
//  Synopsis:
//      Makes sure an HWND exists if we need it
//
//------------------------------------------------------------------------------
HRESULT
CRendererManager::EnsureHWND()
{
	HRESULT hr = S_OK;

	if (!m_hwnd)
	{
		WNDCLASS wndclass;

		wndclass.style = CS_HREDRAW | CS_VREDRAW;
		wndclass.lpfnWndProc = DefWindowProc;
		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;
		wndclass.hInstance = NULL;
		wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wndclass.lpszMenuName = NULL;
		wndclass.lpszClassName = szAppName;

		if (!RegisterClass(&wndclass))
		{
			IFC(E_FAIL);
		}

		m_hwnd = CreateWindow(szAppName,
			TEXT("L2DNative"),
			WS_OVERLAPPEDWINDOW,
			0,
			0,
			0,
			0,
			NULL,
			NULL,
			NULL,
			NULL);
	}

Cleanup:
	return hr;
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererManager::EnsureD3DObjects
//
//  Synopsis:
//      Makes sure the D3D objects exist
//
//------------------------------------------------------------------------------
HRESULT
CRendererManager::EnsureD3DObjects()
{
	HRESULT hr = S_OK;

	HMODULE hD3D = NULL;
	if (!m_pD3D)
	{
		m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
		if (!m_pD3D)
		{
			IFC(E_FAIL);
		}

		m_cAdapters = m_pD3D->GetAdapterCount();
	}

Cleanup:
	if (hD3D)
	{
		FreeLibrary(hD3D);
	}

	return hr;
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererManager::CleanupInvalidDevices
//
//  Synopsis:
//      Checks to see if any devices are bad and if so, deletes all resources
//
//      We could delete resources and wait for D3DERR_DEVICENOTRESET and reset
//      the devices, but if the device is lost because of an adapter order 
//      change then our existing D3D objects would have stale adapter 
//      information. We'll delete everything to be safe rather than sorry.
//
//------------------------------------------------------------------------------
void
CRendererManager::CleanupInvalidDevices()
{
	for (UINT i = 0; i < m_cAdapters; ++i)
	{
		if (FAILED(m_rgRenderers[i]->CheckDeviceState()))
		{
			DestroyResources();
			break;
		}
	}
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererManager::GetBackBufferNoRef
//
//  Synopsis:
//      Returns the surface of the current renderer without adding a reference
//
//      This can return NULL if we're in a bad device state.
//
//------------------------------------------------------------------------------
HRESULT
CRendererManager::GetBackBufferNoRef(IDirect3DSurface9 **ppSurface)
{
	HRESULT hr = S_OK;

	// Make sure we at least return NULL
	*ppSurface = NULL;

	CleanupInvalidDevices();

	IFC(EnsureD3DObjects());

	//
	// Even if we never render to another adapter, this sample creates devices
	// and resources on each one. This is a potential waste of video memory,
	// but it guarantees that we won't have any problems (e.g. out of video
	// memory) when switching to render on another adapter. In your own code
	// you may choose to delay creation but you'll need to handle the issues
	// that come with it.
	//

	IFC(EnsureRenderers());

	if (m_fSurfaceSettingsChanged)
	{
		if (FAILED(TestSurfaceSettings()))
		{
			IFC(E_FAIL);
		}

		for (UINT i = 0; i < m_cAdapters; ++i)
		{
			IFC(m_rgRenderers[i]->CreateSurface(m_uWidth, m_uHeight, m_fUseAlpha, m_uNumSamples));
		}

		m_fSurfaceSettingsChanged = false;
	}

	if (m_pCurrentRenderer)
	{
		*ppSurface = m_pCurrentRenderer->GetSurfaceNoRef();
	}

Cleanup:
	// If we failed because of a bad device, ignore the failure for now and 
	// we'll clean up and try again next time.
	if (hr == D3DERR_DEVICELOST)
	{
		hr = S_OK;
	}

	return hr;
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererManager::TestSurfaceSettings
//
//  Synopsis:
//      Checks to see if our current surface settings are allowed on all
//      adapters.
//
//------------------------------------------------------------------------------
HRESULT
CRendererManager::TestSurfaceSettings()
{
	HRESULT hr = S_OK;

	D3DFORMAT fmt = m_fUseAlpha ? D3DFMT_A8R8G8B8 : D3DFMT_X8R8G8B8;

	// 
	// We test all adapters because because we potentially use all adapters.
	// But even if this sample only rendered to the default adapter, you
	// should check all adapters because WPF may move your surface to
	// another adapter for you!
	//

	for (UINT i = 0; i < m_cAdapters; ++i)
	{
		// Can we get HW rendering?
		IFC(m_pD3D->CheckDeviceType(
			i,
			D3DDEVTYPE_HAL,
			D3DFMT_X8R8G8B8,
			fmt,
			TRUE
			));

		// Is the format okay?
		IFC(m_pD3D->CheckDeviceFormat(
			i,
			D3DDEVTYPE_HAL,
			D3DFMT_X8R8G8B8,
			D3DUSAGE_RENDERTARGET | D3DUSAGE_DYNAMIC, // We'll use dynamic when on XP
			D3DRTYPE_SURFACE,
			fmt
			));

		// D3DImage only allows multisampling on 9Ex devices. If we can't 
		// multisample, overwrite the desired number of samples with 0.
		if (m_pD3DEx && m_uNumSamples > 1)
		{
			assert(m_uNumSamples <= 16);

			if (FAILED(m_pD3D->CheckDeviceMultiSampleType(
				i,
				D3DDEVTYPE_HAL,
				fmt,
				TRUE,
				static_cast<D3DMULTISAMPLE_TYPE>(m_uNumSamples),
				NULL
				)))
			{
				m_uNumSamples = 0;
			}
		}
		else
		{
			m_uNumSamples = 0;
		}
	}

Cleanup:
	return hr;
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererManager::DestroyResources
//
//  Synopsis:
//      Delete all D3D resources
//
//------------------------------------------------------------------------------
void
CRendererManager::DestroyResources()
{
	SAFE_RELEASE(m_pD3D);
	SAFE_RELEASE(m_pD3DEx);

	for (UINT i = 0; i < m_cAdapters; ++i)
	{
		delete m_rgRenderers[i];
	}
	delete[] m_rgRenderers;
	m_rgRenderers = NULL;

	m_pCurrentRenderer = NULL;
	m_cAdapters = 0;

	m_fSurfaceSettingsChanged = true;
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererManager::SetSize
//
//  Synopsis:
//      Update the size of the surface. Next render will create a new surface.
//
//------------------------------------------------------------------------------
void
CRendererManager::SetSize(UINT uWidth, UINT uHeight)
{
	if (uWidth != m_uWidth || uHeight != m_uHeight)
	{
		m_uWidth = uWidth;
		m_uHeight = uHeight;
		m_fSurfaceSettingsChanged = true;
	}
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererManager::SetAlpha
//
//  Synopsis:
//      Update the format of the surface. Next render will create a new surface.
//
//------------------------------------------------------------------------------
void
CRendererManager::SetAlpha(bool fUseAlpha)
{
	if (fUseAlpha != m_fUseAlpha)
	{
		m_fUseAlpha = fUseAlpha;
		m_fSurfaceSettingsChanged = true;
	}
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererManager::SetNumDesiredSamples
//
//  Synopsis:
//      Update the MSAA settings of the surface. Next render will create a 
//      new surface.
//
//------------------------------------------------------------------------------
void
CRendererManager::SetNumDesiredSamples(UINT uNumSamples)
{
	if (m_uNumSamples != uNumSamples)
	{
		m_uNumSamples = uNumSamples;
		m_fSurfaceSettingsChanged = true;
	}
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererManager::SetAdapter
//
//  Synopsis:
//      Update the current renderer. Next render will use the new renderer.
//
//------------------------------------------------------------------------------
void
CRendererManager::SetAdapter(POINT screenSpacePoint)
{
	CleanupInvalidDevices();

	//
	// After CleanupInvalidDevices, we may not have any D3D objects. Rather than
	// recreate them here, ignore the adapter update and wait for render to recreate.
	//

	if (m_pD3D && m_rgRenderers)
	{
		HMONITOR hMon = MonitorFromPoint(screenSpacePoint, MONITOR_DEFAULTTONULL);

		for (UINT i = 0; i < m_cAdapters; ++i)
		{
			if (hMon == m_pD3D->GetAdapterMonitor(i))
			{
				m_pCurrentRenderer = m_rgRenderers[i];
				break;
			}
		}
	}
}
#pragma endregion

#pragma region [   Model   ]
//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererManager::LoadModel
//
//  Synopsis:
//     Live2D 모델을 불러옵니다.
//
//------------------------------------------------------------------------------
long
CRendererManager::LoadModel(char* modelPath)
{
	return m_pCurrentRenderer ? m_pCurrentRenderer->LoadModel(modelPath) : 0;
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererManager::RemoveModel
//
//  Synopsis:
//     관리중인 Live2D 모델을 삭제합니다.
//
//------------------------------------------------------------------------------
void
CRendererManager::RemoveModel(long hModel)
{
	if (m_pCurrentRenderer)
		m_pCurrentRenderer->RemoveModel(hModel);
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererManager::SetParamFloat
//
//  Synopsis:
//     키에 해당하는 매개변수에 값을 설정합니다.
//
//------------------------------------------------------------------------------
void CRendererManager::SetParamFloatInt(long hModel, int key, float value)
{
	if (m_pCurrentRenderer)
		m_pCurrentRenderer->SetParamFloatInt(hModel, key, value);
}
void CRendererManager::SetParamFloatString(long hModel, char* key, float value)
{
	if (m_pCurrentRenderer)
		m_pCurrentRenderer->SetParamFloatString(hModel, key, value);
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererManager::AddToParamFloat
//
//  Synopsis:
//      키에 해당하는 매개변수에 값을 더합니다.
//
//------------------------------------------------------------------------------
void CRendererManager::AddToParamFloat(long hModel, char* key, float value)
{
	if (m_pCurrentRenderer)
		m_pCurrentRenderer->AddToParamFloat(hModel, key, value);
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererManager::MultParamFloat
//
//  Synopsis:
//      키에 해당하는 매개변수에 값을 곱합니다.
//
//------------------------------------------------------------------------------
void CRendererManager::MultParamFloat(long hModel, char* key, float value)
{
	if (m_pCurrentRenderer)
		m_pCurrentRenderer->MultParamFloat(hModel, key, value);
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererManager::GetParamFloat
//
//  Synopsis:
//      키에 해당하는 매개변수의 값을 가져옵니다.
//
//------------------------------------------------------------------------------
float CRendererManager::GetParamFloatInt(long hModel, int key)
{
	if (m_pCurrentRenderer)
		return m_pCurrentRenderer->GetParamFloatInt(hModel, key);

	return NULL;
}
float CRendererManager::GetParamFloatString(long hModel, char* key)
{
	if (m_pCurrentRenderer)
		return m_pCurrentRenderer->GetParamFloatString(hModel, key);

	return NULL;
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererManager::SetPartsOpacity
//
//  Synopsis:
//      키에 해당하는 부분의 투명도를 설정합니다.
//
//------------------------------------------------------------------------------
void CRendererManager::SetPartsOpacityInt(long hModel, int key, float value)
{
	if (m_pCurrentRenderer)
		m_pCurrentRenderer->SetPartsOpacityInt(hModel, key, value);
}
void CRendererManager::SetPartsOpacityString(long hModel, char* key, float value)
{
	if (m_pCurrentRenderer)
		m_pCurrentRenderer->SetPartsOpacityString(hModel, key, value);
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererManager::GetPartsOpacity
//
//  Synopsis:
//      키에 해당하는 부분의 투명도를 가져옵니다.
//
//------------------------------------------------------------------------------
float CRendererManager::GetPartsOpacityInt(long hModel, int key)
{
	if (m_pCurrentRenderer)
		return m_pCurrentRenderer->GetPartsOpacityInt(hModel, key);

	return NULL;
}
float CRendererManager::GetPartsOpacityString(long hModel, char* key)
{
	if (m_pCurrentRenderer)
		return m_pCurrentRenderer->GetPartsOpacityString(hModel, key);

	return NULL;
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererManager::GetParamIndex
//
//  Synopsis:
//      키에 해당하는 매개변수의 인덱스를 가져옵니다.
//
//------------------------------------------------------------------------------
int CRendererManager::GetParamIndex(long hModel, char* key)
{
	if (m_pCurrentRenderer)
		return m_pCurrentRenderer->GetParamIndex(hModel, key);

	return NULL;
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererManager::GetPartsDataIndex
//
//  Synopsis:
//      키에 해당하는 파츠의 인덱스를 가져옵니다.
//
//------------------------------------------------------------------------------
int CRendererManager::GetPartsDataIndex(long hModel, char* key)
{
	if (m_pCurrentRenderer)
		return m_pCurrentRenderer->GetPartsDataIndex(hModel, key);

	return NULL;
}


//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererManager::SaveParam
//
//  Synopsis:
//      매개변수를 저장합니다.
//
//------------------------------------------------------------------------------
void CRendererManager::SaveParam(long hModel)
{
	if (m_pCurrentRenderer)
		m_pCurrentRenderer->SaveParam(hModel);
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererManager::LoadParam
//
//  Synopsis:
//      매개변수를 불러옵니다.
//
//------------------------------------------------------------------------------
void CRendererManager::LoadParam(long hModel)
{
	if (m_pCurrentRenderer)
		m_pCurrentRenderer->LoadParam(hModel);
}

HRESULT CRendererManager::SetTexture(long hModel, LPCWSTR texturePath)
{
	return m_pCurrentRenderer ? m_pCurrentRenderer->SetTexture(hModel, texturePath) : S_OK;
}

#pragma endregion

#pragma region [   Motion   ]
long CRendererManager::LoadMotion(char* motionPath)
{
	return (m_pCurrentRenderer) ? m_pCurrentRenderer->LoadMotion(motionPath) : 0;
}

void CRendererManager::SetFadeIn(long hMotion, int msec)
{
	if (m_pCurrentRenderer)
		m_pCurrentRenderer->SetFadeIn(hMotion, msec);
}

void CRendererManager::SetFadeOut(long hMotion, int msec)
{
	if (m_pCurrentRenderer)
		m_pCurrentRenderer->SetFadeOut(hMotion, msec);
}

void CRendererManager::SetLoop(long hMotion, bool loop)
{
	if (m_pCurrentRenderer)
		m_pCurrentRenderer->SetLoop(hMotion, loop);
}

void CRendererManager::StartMotion(long hMotion)
{
	if (m_pCurrentRenderer)
		m_pCurrentRenderer->StartMotion(hMotion);
}

void CRendererManager::UpdateMotion(long hModel)
{
	if (m_pCurrentRenderer)
		m_pCurrentRenderer->UpdateMotion(hModel);
}
#pragma endregion

#pragma region [   Eye Blink   ]
void CRendererManager::EyeBlinkUpdate(long hModel)
{
	if (m_pCurrentRenderer)
		m_pCurrentRenderer->EyeBlinkUpdate(hModel);
}
#pragma endregion

#pragma region [   Physics   ]
long CRendererManager::CreatePhysics()
{
	return m_pCurrentRenderer ? m_pCurrentRenderer->CreatePhysics() : 0;
}
void CRendererManager::PhysicsSetup(long physicsHandler, float baseLengthM, float airRegistance, float mass)
{
	if (m_pCurrentRenderer)
		m_pCurrentRenderer->PhysicsSetup(physicsHandler, baseLengthM, airRegistance, mass);
}
void CRendererManager::PhysicsAddSrcParam(long physicsHandler, const char* srcType, const char * paramID, float scale, float weight)
{
	if (m_pCurrentRenderer)
		m_pCurrentRenderer->PhysicsAddSrcParam(physicsHandler, srcType, paramID, scale, weight);
}
void CRendererManager::PhysicsAddTargetParam(long physicsHandler, const char* targetType, const char * paramID, float scale, float weight)
{
	if (m_pCurrentRenderer)
		m_pCurrentRenderer->PhysicsAddTargetParam(physicsHandler, targetType, paramID, scale, weight);
}
void CRendererManager::PhysicsUpdate(long physicsHandler, long hModel, long long time)
{
	if (m_pCurrentRenderer)
		m_pCurrentRenderer->PhysicsUpdate(physicsHandler, hModel, time);
}
#pragma endregion

#pragma region [   Live2D   ]
INT64 CRendererManager::GetUserTimeMSec()
{
	return m_pCurrentRenderer ? m_pCurrentRenderer->GetUserTimeMSec() : 0;
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererManager::BeginRender
//
//  Synopsis:
//      렌더링 시작 작업을 수행합니다.
//
//------------------------------------------------------------------------------
HRESULT
CRendererManager::BeginRender(long hModel)
{
	return m_pCurrentRenderer ? m_pCurrentRenderer->BeginRender(hModel) : S_OK;
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererManager::EndRender
//
//  Synopsis:
//      렌더링 종료 작업을 수행합니다.
//
//------------------------------------------------------------------------------
HRESULT
CRendererManager::EndRender(long hModel)
{
	return m_pCurrentRenderer ? m_pCurrentRenderer->EndRender(hModel) : S_OK;
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererManager::Dispose
//
//  Synopsis:
//     Live2D에서 확보한 모든 자원을 해제합니다.
//
//------------------------------------------------------------------------------
void
CRendererManager::Dispose()
{
	if(m_pCurrentRenderer) m_pCurrentRenderer->Dispose();
}
#pragma endregion