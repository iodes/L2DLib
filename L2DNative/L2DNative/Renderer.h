#pragma once

class CRenderer
{
public:
	virtual ~CRenderer();

	HRESULT CheckDeviceState();
	HRESULT CreateSurface(UINT uWidth, UINT uHeight, bool fUseAlpha, UINT m_uNumSamples);

	virtual long LoadModel(char* modelPath) = 0;
	virtual void RemoveModel(long hModel) = 0;
	virtual void SetParamFloat(long hModel, char* key, float value) = 0;
	virtual void AddToParamFloat(long hModel, char* key, float value) = 0;
	virtual void MultParamFloat(long hModel, char* key, float value) = 0;
	virtual float GetParamFloat(long hModel, char* key) = 0;
	virtual void SetPartsOpacity(long hModel, char* key, float value) = 0;
	virtual float GetPartsOpacity(long hModel, char* key) = 0;
	virtual void SaveParam(long hModel) = 0;
	virtual void LoadParam(long hModel) = 0;
	virtual HRESULT SetTexture(long hModel, LPCWSTR texturePath) = 0;

	virtual long LoadMotion(char* motionPath) = 0;
	virtual void SetFadeIn(long hMotion, int msec) = 0;
	virtual void SetFadeOut(long hMotion, int msec) = 0;
	virtual void SetLoop(long hMotion, bool loop) = 0;
	virtual void StartMotion(long hMotion) = 0;
	virtual void UpdateParam(long hModel) = 0;

	virtual HRESULT BeginRender(long hModel) = 0;
	virtual HRESULT EndRender(long hModel) = 0;

	virtual void Dispose() = 0;

	IDirect3DSurface9 *GetSurfaceNoRef() { return m_pd3dRTS; }

protected:
	CRenderer();

	virtual HRESULT Init(IDirect3D9 *pD3D, HWND hwnd, UINT uAdapter);

	IDirect3DDevice9   *m_pd3dDevice;
	IDirect3DSurface9 *m_pd3dRTS;

};