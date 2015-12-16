#pragma once
#include "Argument.h"

class CRenderer
{
public:
	virtual ~CRenderer();

	HRESULT CheckDeviceState();
	HRESULT CreateSurface(UINT uWidth, UINT uHeight, bool fUseAlpha, UINT m_uNumSamples);

	virtual long LoadModel(char* modelPath) = 0;
	virtual void RemoveModel(long model) = 0;
	virtual void SetParamFloat(long model, char* key, float value) = 0;
	virtual void AddToParamFloat(long model, char* key, float value) = 0;
	virtual void MultParamFloat(long model, char* key, float value) = 0;
	virtual float GetParamFloat(long model, char* key) = 0;
	virtual void SetPartsOpacity(long model, char* key, float value) = 0;
	virtual float GetPartsOpacity(long model, char* key) = 0;
	virtual void SaveParam(long model) = 0;
	virtual void LoadParam(long model) = 0;
	virtual HRESULT SetTexture(long model, LPCWSTR texturePath) = 0;

	virtual long LoadMotion(char* motionPath) = 0;

	virtual HRESULT BeginRender(long model) = 0;
	virtual HRESULT EndRender(long model) = 0;

	virtual void Dispose() = 0;

	IDirect3DSurface9 *GetSurfaceNoRef() { return m_pd3dRTS; }

protected:
	CRenderer();

	virtual HRESULT Init(IDirect3D9 *pD3D, HWND hwnd, UINT uAdapter);

	IDirect3DDevice9   *m_pd3dDevice;
	IDirect3DSurface9 *m_pd3dRTS;

};