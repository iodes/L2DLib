#pragma once
#include "Argument.h"

class CRendererL2D : public CRenderer
{
public:
	static HRESULT Create(IDirect3D9 *pD3D, HWND hwnd, UINT uAdapter, Argument argument, CRenderer **ppRenderer);
	~CRendererL2D();

	void SetParamFloat(char* key, float value);
	void AddToParamFloat(char* key, float value);
	void MultParamFloat(char* key, float value);
	float GetParamFloat(char* key);
	void SetPartsOpacity(char* key, float value);
	float GetPartsOpacity(char* key);
	void SaveParam();
	void LoadParam();

	HRESULT BeginRender();
	HRESULT EndRender();

protected:
	HRESULT Init(IDirect3D9 *pD3D, HWND hwnd, UINT uAdapter, Argument argument);

private:
	CRendererL2D();
	IDirect3DVertexBuffer9 *m_pd3dVB;
};