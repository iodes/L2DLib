#pragma once

class CRenderer;

class CRendererManager
{
public:
	static HRESULT Create(CRendererManager **ppManager);
	~CRendererManager();

	void SetSize(UINT uWidth, UINT uHeight);
	void SetAlpha(bool fUseAlpha);
	void SetNumDesiredSamples(UINT uNumSamples);
	void SetAdapter(POINT screenSpacePoint);
	HRESULT GetBackBufferNoRef(IDirect3DSurface9 **ppSurface);

	long LoadModel(char* modelPath);
	void RemoveModel(long hModel);
	void SetParamFloat(long hModel, char* key, float value);
	void AddToParamFloat(long hModel, char* key, float value);
	void MultParamFloat(long hModel, char* key, float value);
	float GetParamFloat(long hModel, char* key);
	void SetPartsOpacity(long hModel, char* key, float value);
	float GetPartsOpacity(long hModel, char* key);
	void SaveParam(long hModel);
	void LoadParam(long hModel);
	HRESULT SetTexture(long hModel, LPCWSTR texturePath);

	long LoadMotion(char* motionPath);
	void SetFadeIn(long hMotion, int msec);
	void SetFadeOut(long hMotion, int msec);
	void SetLoop(long hMotion, bool loop);

	HRESULT BeginRender(long hModel);
	HRESULT EndRender(long hModel);
	void Dispose();

private:
	CRendererManager();

	void CleanupInvalidDevices();
	HRESULT EnsureRenderers();
	HRESULT EnsureHWND();
	HRESULT EnsureD3DObjects();
	HRESULT TestSurfaceSettings();
	void DestroyResources();

	IDirect3D9    *m_pD3D;
	IDirect3D9Ex  *m_pD3DEx;

	UINT m_cAdapters;
	CRenderer **m_rgRenderers;
	CRenderer *m_pCurrentRenderer;

	HWND m_hwnd;

	UINT m_uWidth;
	UINT m_uHeight;
	UINT m_uNumSamples;
	bool m_fUseAlpha;
	bool m_fSurfaceSettingsChanged;
};