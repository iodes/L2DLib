//+-----------------------------------------------------------------------------
//
//  CRendererL2D
//
//      본 클래스에서 Live2D 렌더링을 담당합니다.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "atlstr.h"
#include "Live2D.h"
#include "Live2DModelD3D.h"
#include "motion\Live2DMotion.h"
#include "motion\MotionQueueManager.h"
#include "motion\EyeBlinkMotion.h" 
#include "util/UtSystem.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#pragma warning( default : 4533 )
#define BUFFER_SIZE 1024

using std::wstring;
using std::vector;

struct CUSTOMVERTEX
{
	FLOAT x, y, z;
	DWORD color;
};

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)

#pragma region [   생성자, 소멸자   ]
//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererL2D 생성자
//
//------------------------------------------------------------------------------
CRendererL2D::CRendererL2D() :
	CRenderer(),
	m_pd3dVB(NULL)
{
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererL2D 소멸자
//
//------------------------------------------------------------------------------
CRendererL2D::~CRendererL2D()
{
	SAFE_RELEASE(m_pd3dVB);
}
#pragma endregion

#pragma region [   Initialize   ]
//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererL2D::Create
//
//  Synopsis:
//      렌더러를 생성합니다.
//
//------------------------------------------------------------------------------
HRESULT
CRendererL2D::Create(IDirect3D9 *pD3D, HWND hwnd, UINT uAdapter, CRenderer **ppRenderer)
{
	HRESULT hr = S_OK;

	CRendererL2D *pRenderer = new CRendererL2D();
	IFCOOM(pRenderer);

	IFC(pRenderer->Init(pD3D, hwnd, uAdapter));

	*ppRenderer = pRenderer;
	pRenderer = NULL;

Cleanup:
	delete pRenderer;

	return hr;
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererL2D::Init
//
//  Synopsis:
//      CRenderer::Init을 오버라이드 후 추가적인 처리를 진행합니다.
//
//------------------------------------------------------------------------------
HRESULT
CRendererL2D::Init(IDirect3D9 *pD3D, HWND hwnd, UINT uAdapter)
{
	HRESULT hr = S_OK;

	// 초기화
	IFC(CRenderer::Init(pD3D, hwnd, uAdapter));

	// 엔진 초기화
	live2d::Live2D::init();

Cleanup:
	return hr;
}
#pragma endregion

#pragma region [   Model   ]
//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererL2D::LoadModel
//
//  Synopsis:
//     Live2D 모델을 불러옵니다.
//
//------------------------------------------------------------------------------
long CRendererL2D::LoadModel(char* modelPath)
{
	m_models.push_back(live2d::Live2DModelD3D::loadModel(modelPath));
	m_modelsTexCnt.push_back(0);

	return m_models.size();
}
//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererL2D::RemoveModel
//
//  Synopsis:
//     관리중인 Live2D 모델을 삭제합니다.
//
//------------------------------------------------------------------------------
void CRendererL2D::RemoveModel(long model)
{
	delete m_models[model];
	m_models[model] = NULL;
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererL2D::SetParamFloat
//
//  Synopsis:
//     키에 해당하는 매개변수에 값을 설정합니다.
//
//------------------------------------------------------------------------------
void CRendererL2D::SetParamFloat(long model, char* key, float value)
{
	m_models[model]->setParamFloat(key, value);
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererL2D::AddToParamFloat
//
//  Synopsis:
//      키에 해당하는 매개변수에 값을 더합니다.
//
//------------------------------------------------------------------------------
void CRendererL2D::AddToParamFloat(long model, char* key, float value)
{
	m_models[model]->addToParamFloat(key, value);
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererL2D::MultParamFloat
//
//  Synopsis:
//      키에 해당하는 매개변수에 값을 곱합니다.
//
//------------------------------------------------------------------------------
void CRendererL2D::MultParamFloat(long model, char* key, float value)
{
	m_models[model]->multParamFloat(key, value);
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererL2D::GetParamFloat
//
//  Synopsis:
//      키에 해당하는 매개변수의 값을 가져옵니다.
//
//------------------------------------------------------------------------------
float CRendererL2D::GetParamFloat(long model, char* key)
{
	return m_models[model]->getParamFloat(key);
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererL2D::SetPartsOpacity
//
//  Synopsis:
//      키에 해당하는 부분의 투명도를 설정합니다.
//
//------------------------------------------------------------------------------
void CRendererL2D::SetPartsOpacity(long model, char* key, float value)
{
	m_models[model]->setPartsOpacity(key, value);
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererL2D::GetPartsOpacity
//
//  Synopsis:
//      키에 해당하는 부분의 투명도를 가져옵니다.
//
//------------------------------------------------------------------------------
float CRendererL2D::GetPartsOpacity(long model, char* key)
{
	return m_models[model]->getPartsOpacity(key);
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererL2D::SaveParam
//
//  Synopsis:
//      매개변수를 저장합니다.
//
//------------------------------------------------------------------------------
void CRendererL2D::SaveParam(long model)
{
	m_models[model]->saveParam();
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererL2D::LoadParam
//
//  Synopsis:
//      매개변수를 불러옵니다.
//
//------------------------------------------------------------------------------
void CRendererL2D::LoadParam(long model)
{
	m_models[model]->loadParam();
}

HRESULT CRendererL2D::SetTexture(long model, LPCWSTR texturePath)
{
	HRESULT hr = S_OK;

	// 텍스처 불러오기 수행
	LPDIRECT3DTEXTURE9 tex;
	if (FAILED(D3DXCreateTextureFromFileExW(m_pd3dDevice
		, texturePath
		, 0
		, 0
		, 0
		, 0
		, D3DFMT_A8R8G8B8
		, D3DPOOL_MANAGED
		, D3DX_FILTER_LINEAR
		, D3DX_FILTER_BOX
		, 0
		, NULL
		, NULL
		, &tex)))
	{
		goto Cleanup;
	}
	else
	{
		m_models[model]->setTexture(m_modelsTexCnt[model]++, tex);
	}

Cleanup:
	return hr;
}
#pragma endregion

#pragma region [   Live2D   ]
//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererL2D::BeginRender
//
//  Synopsis:
//      Live2D 렌더링을 시작합니다.
//
//------------------------------------------------------------------------------
HRESULT CRendererL2D::BeginRender(long model)
{
	HRESULT hr = S_OK;

	// 배경 설정
	IFC(m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0));
	IFC(m_pd3dDevice->BeginScene());

	// 메트릭스 설정
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	D3DXMATRIX Ortho2D;
	D3DXMATRIX Identity;

	int w, h;
	w = 800;
	h = 800;

	float modelWidth = m_models[model]->getModelImpl()->getCanvasWidth();
	float modelHeight = m_models[model]->getModelImpl()->getCanvasHeight();

	D3DXMatrixOrthoLH(&Ortho2D, modelHeight, -modelHeight *h / w, -1.0f, 1.0f);
	D3DXMatrixIdentity(&Identity);

	m_pd3dDevice->SetTransform(D3DTS_PROJECTION, &Ortho2D);
	m_pd3dDevice->SetTransform(D3DTS_WORLD, &Identity);
	m_pd3dDevice->SetTransform(D3DTS_VIEW, &Identity);

	D3DXMATRIXA16 world, scale, trans;
	m_pd3dDevice->GetTransform(D3DTS_WORLD, &world);
	D3DXMatrixTranslation(&trans, -modelWidth / 2, -modelHeight / 2, 0);
	world = trans *world;

	m_pd3dDevice->SetTransform(D3DTS_WORLD, &world);

Cleanup:
	return hr;
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererL2D::EndRender
//
//  Synopsis:
//      Live2D 렌더링을 끝냅니다.
//
//------------------------------------------------------------------------------
HRESULT CRendererL2D::EndRender(long model)
{
	HRESULT hr = S_OK;

	// 그리기 작업 수행
	m_models[model]->setDevice(m_pd3dDevice);
	m_models[model]->update();
	m_models[model]->draw();

	// 그리기 종료
	IFC(m_pd3dDevice->EndScene());
	IFC(m_pd3dDevice->Present(NULL, NULL, NULL, NULL));

Cleanup:
	return hr;
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererL2D::Dispose
//
//  Synopsis:
//      Live2D에서 확보한 모든 자원을 해제합니다.
//
//------------------------------------------------------------------------------
void CRendererL2D::Dispose()
{
	live2d::Live2D::dispose();
}
#pragma endregion