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
	void RemoveModel(long model);
	void SetParamFloat(long model, char* key, float value);
	void AddToParamFloat(long model, char* key, float value);
	void MultParamFloat(long model, char* key, float value);
	float GetParamFloat(long model, char* key);
	void SetPartsOpacity(long model, char* key, float value);
	float GetPartsOpacity(long model, char* key);
	void SaveParam(long model);
	void LoadParam(long model);

	HRESULT SetTexture(long model, LPCWSTR texturePath);

	HRESULT BeginRender(long model);
	HRESULT EndRender(long model);
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