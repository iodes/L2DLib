#pragma once
#include "Argument.h"

class CRenderer
{
public:
	virtual ~CRenderer();

	HRESULT CheckDeviceState();
	HRESULT CreateSurface(UINT uWidth, UINT uHeight, bool fUseAlpha, UINT m_uNumSamples);

	virtual void SetParamFloat(char* key, float value) = 0;
	virtual void AddToParamFloat(char* key, float value) = 0;
	virtual void MultParamFloat(char* key, float value) = 0;
	virtual float GetParamFloat(char* key) = 0;
	virtual void SetPartsOpacity(char* key, float value) = 0;
	virtual float GetPartsOpacity(char* key) = 0;
	virtual void SaveParam() = 0;
	virtual void LoadParam() = 0;

	virtual HRESULT BeginRender() = 0;
	virtual HRESULT EndRender() = 0;

	virtual void Dispose() = 0;

	IDirect3DSurface9 *GetSurfaceNoRef() { return m_pd3dRTS; }

protected:
	CRenderer();

	virtual HRESULT Init(IDirect3D9 *pD3D, HWND hwnd, UINT uAdapter, Argument argument);

	IDirect3DDevice9   *m_pd3dDevice;
	IDirect3DSurface9 *m_pd3dRTS;

};