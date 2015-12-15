#pragma once
#include "Argument.h"

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
	void SetArgument(Argument argument);

	void SetParamFloat(char* key, float value);
	void AddToParamFloat(char* key, float value);
	void MultParamFloat(char* key, float value);
	float GetParamFloat(char* key);
	void SetPartsOpacity(char* key, float value);
	float GetPartsOpacity(char* key);
	void SaveParam();
	void LoadParam();

	HRESULT GetBackBufferNoRef(IDirect3DSurface9 **ppSurface);

	HRESULT BeginRender();
	HRESULT EndRender();

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
	Argument m_Argument;
};