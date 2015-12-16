#pragma once
#include "Live2D.h"
#include "Live2DModelD3D.h"
#include "motion\Live2DMotion.h"
#include "motion\MotionQueueManager.h"
#include "motion\EyeBlinkMotion.h" 
#include <vector>

using std::vector;

typedef live2d::Live2DModelD3D Model;
typedef live2d::Live2DMotion Motion;
typedef LPDIRECT3DTEXTURE9 Texture;

class CRendererL2D : public CRenderer
{
public:
	static HRESULT Create(IDirect3D9 *pD3D, HWND hwnd, UINT uAdapter, CRenderer **ppRenderer);
	~CRendererL2D();

	long AddModel(Model* model);
	Model* GetModel(long hModel);
	void RemoveModel(long hModel);

	void AddTexture(long hModel, Texture texture);
	long GetTextureCount(long hModel);

	long LoadModel(char* modelPath);
	void SetParamFloat(long hModel, char* key, float value);
	void AddToParamFloat(long hModel, char* key, float value);
	void MultParamFloat(long hModel, char* key, float value);
	float GetParamFloat(long hModel, char* key);
	void SetPartsOpacity(long hModel, char* key, float value);
	float GetPartsOpacity(long hModel, char* key);
	void SaveParam(long hModel);
	void LoadParam(long hModel);
	HRESULT SetTexture(long hModel, LPCWSTR texturePath);

	long AddMotion(Motion* motion);
	Motion* GetMotion(long hMotion);
	void RemoveMotion(long hMotion);

	long LoadMotion(char* motionPath);
	void SetFadeIn(long hMotion, int msec);
	void SetFadeOut(long hMotion, int msec);
	void SetLoop(long hMotion, bool loop);

	void StartMotion(long hMotion);
	void UpdateMotion(long hModel);

	void EyeBlinkUpdate(long hModel);

	HRESULT BeginRender(long hModel);
	HRESULT EndRender(long hModel);
	void Dispose();

protected:
	HRESULT Init(IDirect3D9 *pD3D, HWND hwnd, UINT uAdapter);

private:

#pragma region [   HandleVectors   ]
	vector<Model*> m_models;
	vector<vector<Texture>> m_textures;
	vector<Motion*> m_motions;
#pragma endregion

	live2d::MotionQueueManager* m_motionManager;
	live2d::EyeBlinkMotion* m_eyeBlink;

	CRendererL2D();
	IDirect3DVertexBuffer9 *m_pd3dVB;
};