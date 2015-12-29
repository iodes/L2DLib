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
	void SetParamFloatInt(long hModel, int key, float value);
	void SetParamFloatString(long hModel, char* key, float value);
	void AddToParamFloat(long hModel, char* key, float value);
	void MultParamFloat(long hModel, char* key, float value);
	float GetParamFloatInt(long hModel, int key);
	float GetParamFloatString(long hModel, char* key);
	void SetPartsOpacityInt(long hModel, int key, float value);
	void SetPartsOpacityString(long hModel, char* key, float value);
	float GetPartsOpacityInt(long hModel, int key);
	float GetPartsOpacityString(long hModel, char* key);
	int GetParamIndex(long hModel, char* key);
	int GetPartsDataIndex(long hModel, char* key);
	void SaveParam(long hModel);
	void LoadParam(long hModel);
	HRESULT SetTexture(long hModel, LPCWSTR texturePath);

	long LoadMotion(char* motionPath);
	void SetFadeIn(long hMotion, int msec);
	void SetFadeOut(long hMotion, int msec);
	void SetLoop(long hMotion, bool loop);
	void StartMotion(long hMotion);
	void UpdateMotion(long hModel);

	void EyeBlinkUpdate(long hModel);

	long CreatePhysics();
	void PhysicsSetup(long physicsHandler, float baseLengthM, float airRegistance, float mass);
	void PhysicsAddSrcParam(long physicsHandler, const char* srcType, const char * paramID, float scale, float weight);
	void PhysicsAddTargetParam(long phsyicsHandler, const char* targetType, const char* paramID, float scale, float weight);
	void PhysicsUpdate(long physicsHandler, long hModel, INT64 time);
	
	long CreateExpression();
	void StartExpression(long expressionHandler);
	void ExpressionSetFadeIn(long expressionHandler, int FadeInMSec);
	void ExpressionSetFadeOut(long expressionHandler, int FadeOutMSec);
	void ExpressionAddParam(long expressionHandler, char* paramID, char* calc, float value, float defaultValue);
	void ExpressionAddParamV09(long expressionHandler, char* paramID, float value, float defaultValue);

	INT64 GetUserTimeMSec();
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