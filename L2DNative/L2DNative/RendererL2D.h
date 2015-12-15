#pragma once
#include "Argument.h"
#include "Live2D.h"
#include "Live2DModelD3D.h"
#include "motion\Live2DMotion.h"
#include "motion\MotionQueueManager.h"
#include "motion\EyeBlinkMotion.h" 
#include <vector>

using std::vector;

class CRendererL2D : public CRenderer
{
public:
	static HRESULT Create(IDirect3D9 *pD3D, HWND hwnd, UINT uAdapter, CRenderer **ppRenderer);
	~CRendererL2D();

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

protected:
	HRESULT Init(IDirect3D9 *pD3D, HWND hwnd, UINT uAdapter);

private:
	vector<live2d::Live2DModelD3D*> m_models;
	vector<long> m_modelsTexCnt;

	CRendererL2D();
	IDirect3DVertexBuffer9 *m_pd3dVB;
};