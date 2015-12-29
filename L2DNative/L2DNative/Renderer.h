#pragma once

class CRenderer
{
public:
	virtual ~CRenderer();

	HRESULT CheckDeviceState();
	HRESULT CreateSurface(UINT uWidth, UINT uHeight, bool fUseAlpha, UINT m_uNumSamples);

	virtual long LoadModel(char* modelPath) = 0;
	virtual void RemoveModel(long hModel) = 0;
	virtual void SetParamFloatInt(long hModel, int key, float value) = 0;
	virtual void SetParamFloatString(long hModel, char* key, float value) = 0;
	virtual void AddToParamFloat(long hModel, char* key, float value) = 0;
	virtual void MultParamFloat(long hModel, char* key, float value) = 0;
	virtual float GetParamFloatInt(long hModel, int key) = 0;
	virtual float GetParamFloatString(long hModel, char* key) = 0;
	virtual void SetPartsOpacityInt(long hModel, int key, float value) = 0;
	virtual void SetPartsOpacityString(long hModel, char* key, float value) = 0;
	virtual float GetPartsOpacityInt(long hModel, int key) = 0;
	virtual float GetPartsOpacityString(long hModel, char* key) = 0;
	virtual int GetParamIndex(long hModel, char* key) = 0;
	virtual int GetPartsDataIndex(long hModel, char* key) = 0;
	virtual void SaveParam(long hModel) = 0;
	virtual void LoadParam(long hModel) = 0;
	virtual HRESULT SetTexture(long hModel, LPCWSTR texturePath) = 0;

	virtual long LoadMotion(char* motionPath) = 0;
	virtual void SetFadeIn(long hMotion, int msec) = 0;
	virtual void SetFadeOut(long hMotion, int msec) = 0;
	virtual void SetLoop(long hMotion, bool loop) = 0;
	virtual void StartMotion(long hMotion) = 0;
	virtual void UpdateMotion(long hModel) = 0;
	
	virtual void EyeBlinkUpdate(long hModel) = 0;

	virtual long CreatePhysics() = 0;
	virtual void PhysicsSetup(long physicsHandler, float baseLengthM, float airRegistance, float mass) = 0;
	virtual void PhysicsAddSrcParam(long physicsHandler, const char* srcType, const char* paramID, float scale, float weight) = 0;
	virtual void PhysicsAddTargetParam(long phsyicsHandler, const char* targetType, const char* paramID, float scale, float weight) = 0;
	virtual void PhysicsUpdate(long physicsHandler, long hModel, INT64 time) = 0;

	virtual long CreateExpression() = 0;
	virtual void StartExpression(long expressionHandler) = 0;
	virtual void ExpressionSetFadeIn(long expressionHandler, int FadeInMSec) = 0;
	virtual void ExpressionSetFadeOut(long expressionHandler, int FadeOutMSec) = 0;
	virtual void ExpressionAddParam(long expressionHandler, char* paramID, char* calc, float value, float defaultValue) = 0;
	virtual void ExpressionAddParamV09(long expressionHandler, char* paramID, float value, float defaultValue) = 0;

	virtual INT64 GetUserTimeMSec() = 0;
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