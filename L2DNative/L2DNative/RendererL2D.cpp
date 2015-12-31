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
#include "physics\PhysicsHair.h"
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
	m_motionManager = new live2d::MotionQueueManager();
	m_expressionManager = new live2d::MotionQueueManager();
	m_eyeBlink = new live2d::EyeBlinkMotion();

Cleanup:
	return hr;
}
#pragma endregion

#pragma region [   Model   ]
//+------------------------------------------
Model* CRendererL2D::GetModel(long hModel)
{
	return m_models[hModel - 1];
}

long CRendererL2D::AddModel(Model* model)
{
	m_models.push_back(model);

	vector<Texture> textureVector;
	m_textures.push_back(textureVector);

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
void CRendererL2D::RemoveModel(long hModel)
{
	Model* model = GetModel(hModel);

	long textureCount = GetTextureCount(hModel);

	for (int i = 0; i < textureCount; i++)
	{
		model->releaseModelTextureNo(i);
	}

	for (Texture texture : m_textures[hModel - 1])
	{
		texture->Release();
	}

	delete model;
}

void CRendererL2D::AddTexture(long hModel, Texture texture)
{
	m_textures[hModel - 1].push_back(texture);
}

long CRendererL2D::GetTextureCount(long hModel)
{
	return m_textures[hModel - 1].size();
}

//------------------------------------------------------------------------------
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
	Model* model = Model::loadModel(modelPath);
	long hModel = AddModel(model);

	return hModel;
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
void CRendererL2D::SetParamFloatInt(long hModel, int key, float value)
{
	Model* model = GetModel(hModel);
	model->setParamFloat(key, value);
}
void CRendererL2D::SetParamFloatString(long hModel, char* key, float value)
{
	Model* model = GetModel(hModel);
	model->setParamFloat(key, value);
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
void CRendererL2D::AddToParamFloat(long hModel, char* key, float value)
{
	Model* model = GetModel(hModel);
	model->addToParamFloat(key, value);
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
void CRendererL2D::MultParamFloat(long hModel, char* key, float value)
{
	Model* model = GetModel(hModel);
	model->multParamFloat(key, value);
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
float CRendererL2D::GetParamFloatInt(long hModel, int key)
{
	Model* model = GetModel(hModel);
	return model->getParamFloat(key);
}
float CRendererL2D::GetParamFloatString(long hModel, char* key)
{
	Model* model = GetModel(hModel);
	return model->getParamFloat(key);
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
void CRendererL2D::SetPartsOpacityInt(long hModel, int key, float value)
{
	Model* model = GetModel(hModel);
	model->setPartsOpacity(key, value);
}
void CRendererL2D::SetPartsOpacityString(long hModel, char* key, float value)
{
	Model* model = GetModel(hModel);
	model->setPartsOpacity(key, value);
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
float CRendererL2D::GetPartsOpacityInt(long hModel, int key)
{
	Model* model = GetModel(hModel);
	return model->getPartsOpacity(key);
}
float CRendererL2D::GetPartsOpacityString(long hModel, char* key)
{
	 Model* model = GetModel(hModel);
	 return model->getPartsOpacity(key);
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererL2D::GetParamIndex
//
//  Synopsis:
//      키에 해당하는 매개변수의 인덱스를 가져옵니다.
//
//------------------------------------------------------------------------------
int CRendererL2D::GetParamIndex(long hModel, char* key)
{
	Model* model = GetModel(hModel);
	return model->getParamIndex(key);
}

//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererL2D::GetPartsDataIndex
//
//  Synopsis:
//      키에 해당하는 파츠의 인덱스를 가져옵니다.
//
//------------------------------------------------------------------------------
int CRendererL2D::GetPartsDataIndex(long hModel, char* key)
{
	Model* model = GetModel(hModel);
	return model->getPartsDataIndex(key);
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
void CRendererL2D::SaveParam(long hModel)
{
	Model* model = GetModel(hModel);
	model->saveParam();
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
void CRendererL2D::LoadParam(long hModel)
{
	Model* model = GetModel(hModel);
	model->loadParam();
}

HRESULT CRendererL2D::SetTexture(long hModel, LPCWSTR texturePath)
{
	HRESULT hr = S_OK;
	// 텍스처 불러오기 수행

	Texture texture;
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
		, &texture)))
	{
		goto Cleanup;
	}
	else
	{
		Model* model = GetModel(hModel);
		long textureCount = GetTextureCount(hModel);
		model->setTexture(textureCount, texture);
		AddTexture(hModel, texture);
	}

Cleanup:
	return hr;
}
#pragma endregion

#pragma region [   Motion   ]
Motion* CRendererL2D::GetMotion(long hMotion)
{
	return m_motions[hMotion - 1];
}

long CRendererL2D::AddMotion(Motion* motion)
{
	m_motions.push_back(motion);

	return m_motions.size();
}

void CRendererL2D::RemoveMotion(long hMotion)
{
	Motion* motion = GetMotion(hMotion);
	delete motion;
}

long CRendererL2D::LoadMotion(char* motionPath)
{
	Motion* motion = Motion::loadMotion(motionPath);
	long hMotion = AddMotion(motion);
	return hMotion;
}

void CRendererL2D::SetFadeIn(long hMotion, int msec)
{
	Motion* motion = GetMotion(hMotion);
	motion->setFadeIn(msec);
}

void CRendererL2D::SetFadeOut(long hMotion, int msec)
{
	Motion* motion = GetMotion(hMotion);
	motion->setFadeIn(msec);
}

void CRendererL2D::SetLoop(long hMotion, bool loop)
{
	Motion* motion = GetMotion(hMotion);
	motion->setLoop(loop);
}

void CRendererL2D::StartMotion(long hMotion)
{
	Motion* motion = GetMotion(hMotion);
	m_motionManager->startMotion(motion, false);
}

void CRendererL2D::UpdateMotion(long hModel)
{
	Model* model = GetModel(hModel);
	m_motionManager->updateParam(model);
}
#pragma endregion

#pragma region [   Eye Blink   ]
void CRendererL2D::EyeBlinkUpdate(long hModel)
{
	Model* model = GetModel(hModel);
	m_eyeBlink->setParam(model);
}
#pragma endregion

#pragma region [   Physics   ]
live2d::PhysicsHair* CRendererL2D::GetPhysics(long physicsHandler)
{
	return m_physics[physicsHandler - 1];
}
long CRendererL2D::AddPhysics(live2d::PhysicsHair* physics)
{
	m_physics.push_back(physics);
	return m_physics.size();
}
long CRendererL2D::CreatePhysics()
{
	live2d::PhysicsHair* physics = new live2d::PhysicsHair();
	long physicsHandler = AddPhysics(physics);
	return physicsHandler;
}
void CRendererL2D::PhysicsSetup(long physicsHandler, float baseLengthM, float airRegistance, float mass)
{
	live2d::PhysicsHair* physics = GetPhysics(physicsHandler);
	physics->setup(baseLengthM, airRegistance, mass);
}
void CRendererL2D::PhysicsAddSrcParam(long physicsHandler, const char* srcType, const char* paramID, float scale, float weight)
{
	live2d::PhysicsHair* physics = GetPhysics(physicsHandler);
	live2d::PhysicsHair::Src type = live2d::PhysicsHair::SRC_TO_X;

	if (strcmp(srcType, "x") == 0)
	{
		type = live2d::PhysicsHair::SRC_TO_X;
	}
	else if (strcmp(srcType, "y") == 0)
	{
		type = live2d::PhysicsHair::SRC_TO_Y;
	}
	else if (strcmp(srcType, "angle") == 0)
	{
		type = live2d::PhysicsHair::SRC_TO_G_ANGLE;
	}
	else
	{
		live2d::UtDebug::error("live2d", "Invalid parameter:PhysicsHair.Src");
	}

	physics->addSrcParam(type, paramID, scale, weight);
}
void CRendererL2D::PhysicsAddTargetParam(long physicsHandler, const char* targetType, const char* paramID, float scale, float weight)
{
	live2d::PhysicsHair* physics = GetPhysics(physicsHandler);
	live2d::PhysicsHair::Target type = live2d::PhysicsHair::TARGET_FROM_ANGLE;

	if (strcmp(targetType, "angle") == 0)
	{
		type = live2d::PhysicsHair::TARGET_FROM_ANGLE;
	}
	else if (strcmp(targetType, "angle_v") == 0)
	{
		type = live2d::PhysicsHair::TARGET_FROM_ANGLE_V;
	}
	else
	{
		live2d::UtDebug::error("live2d", "Invalid parameter:PhysicsHair.Target");
	}

	physics->addTargetParam(type, paramID, scale, weight);
}
void CRendererL2D::PhysicsUpdate(long physicsHandler, long hModel, INT64 time)
{
	live2d::PhysicsHair* physics = GetPhysics(physicsHandler);

	Model* model = GetModel(hModel);
	physics->update(model, time);
}
#pragma endregion

#pragma region [   Expression   ]
live2d::framework::L2DExpressionMotion* CRendererL2D::GetExpression(long expressionHandler)
{
	return m_expression[expressionHandler - 1];
}

long CRendererL2D::AddExpression(live2d::framework::L2DExpressionMotion* expression)
{
	m_expression.push_back(expression);

	return m_expression.size();
}

long CRendererL2D::CreateExpression()
{
	live2d::framework::L2DExpressionMotion* expression = new live2d::framework::L2DExpressionMotion();
	long expressionHandler = AddExpression(expression);

	return expressionHandler;
}

void CRendererL2D::StartExpression(long expressionHandler)
{
	live2d::framework::L2DExpressionMotion* expression = GetExpression(expressionHandler);
	m_expressionManager->startMotion(expression, false);
}

void CRendererL2D::ExpressionSetFadeIn(long expressionHandler, int FadeInMSec)
{
	live2d::framework::L2DExpressionMotion* expression = GetExpression(expressionHandler);
	expression->setFadeIn(FadeInMSec);
}

void CRendererL2D::ExpressionSetFadeOut(long expressionHandler, int FadeOutMSec)
{
	live2d::framework::L2DExpressionMotion* expression = GetExpression(expressionHandler);
	expression->setFadeOut(FadeOutMSec);
}

void CRendererL2D::ExpressionAddParam(long expressionHandler, char* paramID, char* calc, float value, float defaultValue)
{
	live2d::framework::L2DExpressionMotion* expression = GetExpression(expressionHandler);
	expression->addParam(paramID, calc, value, defaultValue);
}

void CRendererL2D::ExpressionAddParamV09(long expressionHandler, char* paramID, float value, float defaultValue)
{
	live2d::framework::L2DExpressionMotion* expression = GetExpression(expressionHandler);
	expression->addParamV09(paramID, value, defaultValue);
}

void CRendererL2D::UpdateExpression(long hModel)
{
	Model* model = GetModel(hModel);
	m_expressionManager->updateParam(model);
}
#pragma endregion

#pragma region [   Live2D   ]
INT64 CRendererL2D::GetUserTimeMSec()
{
	return live2d::UtSystem::getUserTimeMSec();
}
//+-----------------------------------------------------------------------------
//
//  Member:
//      CRendererL2D::BeginRender
//
//  Synopsis:
//      Live2D 렌더링을 시작합니다.
//
//------------------------------------------------------------------------------
HRESULT CRendererL2D::BeginRender(long hModel)
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
	Model* model = GetModel(hModel);
	float modelWidth = model->getModelImpl()->getCanvasWidth();
	float modelHeight = model->getModelImpl()->getCanvasHeight();

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
HRESULT CRendererL2D::EndRender(long hModel)
{
	HRESULT hr = S_OK;

	// 그리기 작업 수행
	Model* model = GetModel(hModel);
	model->setDevice(m_pd3dDevice);
	model->update();
	model->draw();

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