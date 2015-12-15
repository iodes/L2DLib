//+-----------------------------------------------------------------------------
//
//  CRenderer
//
//      An abstract base class that creates a device and a target render 
//      surface. Derive from this class and override Init() and Render() 
//      to do your own rendering. See CRendererL2D for an example.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRenderer ctor
//
//------------------------------------------------------------------------------
CRenderer::CRenderer() : m_pd3dDevice(NULL), m_pd3dRTS(NULL)
{
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRenderer dtor
//
//------------------------------------------------------------------------------
CRenderer::~CRenderer()
{
	SAFE_RELEASE(m_pd3dDevice);
	SAFE_RELEASE(m_pd3dRTS);
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRenderer::CheckDeviceState
//
//  Synopsis:
//      Returns the status of the device. 9Ex devices are a special case because 
//      TestCooperativeLevel() has been deprecated in 9Ex.
//
//------------------------------------------------------------------------------
HRESULT
CRenderer::CheckDeviceState()
{
	if (m_pd3dDevice)
	{
		return m_pd3dDevice->TestCooperativeLevel();
	}
	else
	{
		return D3DERR_DEVICELOST;
	}
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRenderer::CreateSurface
//
//  Synopsis:
//      Creates and sets the render target
//
//------------------------------------------------------------------------------
HRESULT
CRenderer::CreateSurface(UINT uWidth, UINT uHeight, bool fUseAlpha, UINT m_uNumSamples)
{
	HRESULT hr = S_OK;

	SAFE_RELEASE(m_pd3dRTS);

	IFC(m_pd3dDevice->CreateRenderTarget(
		uWidth,
		uHeight,
		fUseAlpha ? D3DFMT_A8R8G8B8 : D3DFMT_X8R8G8B8,
		static_cast<D3DMULTISAMPLE_TYPE>(m_uNumSamples),
		0,
		TRUE,
		&m_pd3dRTS,
		NULL
		));

	IFC(m_pd3dDevice->SetRenderTarget(0, m_pd3dRTS));

Cleanup:
	return hr;
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRenderer::Init
//
//  Synopsis:
//      Creates the device
//
//------------------------------------------------------------------------------
HRESULT
CRenderer::Init(IDirect3D9 *pD3D, HWND hwnd, UINT uAdapter, Argument argument)
{
	HRESULT hr = S_OK;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferHeight = 1;
	d3dpp.BackBufferWidth = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	assert(pD3D);

	IFC(pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,
		&d3dpp,
		&m_pd3dDevice
		));

Cleanup:
	return hr;
}