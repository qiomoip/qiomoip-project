#include "GameEngine.h"
#include "Device.h"
#include "ObjectManager.h"
#include "Entity.h"

#include "ShaderManager.h"
#include "Shader.h"

#include "CameraManager.h"
#include "Camera.h"

#include "MainWnd.h"

#include "KeyManager.h"

#include "ResourceManager.h"
#include "Math.h"


#ifdef _DEBUG || DEBUG
#include "Debug.h"
#endif
CGameEngine::CGameEngine(void)
{
}


CGameEngine::~CGameEngine(void)
{
	Clear();
}

HRESULT CGameEngine::Init()
{
	_SINGLE(CKeyManager)->Initialize();

	if(FAILED(CreateEntity()))
	{
		return E_FAIL;
	}
	if(FAILED(CreateCamera()))
	{
		return E_FAIL;
	}
	if(FAILED(CreateShader()))
	{
		return E_FAIL;
	}
	if(FAILED(CreateLight()))
	{
		return E_FAIL;
	}


	return S_OK;
}


HRESULT CGameEngine::CreateEntity()
{
	/*CEntity* pEntity = _SINGLE(CObjectManager)->CreateObject(
		RT_ENTITY, ET_BOX, MT_STATIC, GT_BOX, IT_DEFAULT_DEFAULT_LIGHT,
		L"Player", L"Resource\\Texture\\WoodCrate02.dds");*/

	CEntity* pEntity = _SINGLE(CObjectManager)->CreateObject(
		RT_ENTITY, ET_PLAYER, MT_STATIC, GT_BOX, IT_DEFAULT_DEFAULT_LIGHT,
		L"Player", L"Resource\\Texture\\FireAnim\\Fire%d.png");

	if(!pEntity)
	{
		return false;
	}

	pEntity->SetShaderInfo(SHADER_DEFAULT, DST_DEFAULT);
	pEntity->PushPass(DEFAULT_SKTREFLECT);
	
	m_listRender.push_back(pEntity);


	CEntity* pZombie = _SINGLE(CObjectManager)->CreateObject(
		RT_ENTITY, ET_ZOMBIE, MT_STATIC, GT_BOX, IT_DEFAULT_DEFAULT_LIGHT,
		L"Zombie", L"Resource\\Texture\\WoodCrate01.dds");

	if(!pZombie)
	{
		return false;
	}
	pZombie->SetPos(XMFLOAT3(3.f, 0.f, -3.f) );
	pZombie->SetShaderInfo(SHADER_DEFAULT, DST_DEFAULT);
	pZombie->PushPass(DEFAULT_SKTREFLECT);
	
	m_listRender.push_back(pZombie);


	CEntity* pTerrain = _SINGLE(CObjectManager)->CreateObject(
		RT_ENTITY, ET_TERRAIN, MT_STATIC, GT_TERRAIN, IT_DEFAULT_DEFAULT_LIGHT,
		L"Terrain", _T("Resource\\Texture\\grass.dds") );

	if(!pTerrain)
	{
		return false;
	}

	pTerrain->SetShaderInfo(SHADER_DEFAULT, DST_DEFAULT);
	pTerrain->PushPass(DEFAULT_LIGHT);
	
	m_listRender.push_back(pTerrain);

	CEntity* pSkySphere = _SINGLE(CObjectManager)->CreateObject(
		RT_ENVIRONMENT, ET_ENVIRONMENT, MT_STATIC, GT_SPHERE, IT_DEFAULT_DEFAULT_LIGHT,
		L"Environment", _T("Resource\\Texture\\snowcube1024.dds"), "g_texCube" ); 

	if(!pSkySphere)
	{
		return false;
	}

	pSkySphere->SetScale(500.f, 500.f, 500.f);

	pSkySphere->SetShaderInfo(SHADER_DEFAULT, DST_DEFAULT);
	pSkySphere->PushPass((PASS_TYPE)2);
	
	m_listRender.push_back(pSkySphere);

	return true;
}

HRESULT CGameEngine::CreateCamera()
{
	CCamera* pCamera = _SINGLE(CCameraManager)->CreateCamera(L"MainCamera");

	if(!pCamera)
		return E_FAIL;

	pCamera->SetPosition(XMFLOAT3(0.f, 3.f, -3.f));
	pCamera->SetLens(
		(float)_SINGLE(CMainWnd)->GetClientWidth(), 
		(float)_SINGLE(CMainWnd)->GetClientHeight(), 
		PI * 0.25f,	_SINGLE(CMainWnd)->GetAspectRatio(), 
		1.f, 1000.f);
	pCamera->LookAt(XMFLOAT3(0.f, 3.f, -30.f), XMFLOAT3(0.f, 0.f, 0.f), XMFLOAT3(0.f, 1.f, 0.f));
	pCamera->SetLookObject(_SINGLE(CObjectManager)->FindObject(L"Player"));

	_SINGLE(CCameraManager)->SetCurrentCamera(pCamera);

	//테스트용 서브 카메라 생성
#if defined(DEBUG) | defined(_DEBUG)
	CCamera* pSubCamera = _SINGLE(CCameraManager)->CreateCamera(L"SubCamera");
	if(!pSubCamera )
		return E_FAIL;

	pSubCamera ->SetPosition(XMFLOAT3(0.f, 10.f, -10.f) );
	pSubCamera ->SetLens(
		(float)_SINGLE(CMainWnd)->GetClientWidth(), 
		(float)_SINGLE(CMainWnd)->GetClientHeight(), 
		PI * 0.25f,	_SINGLE(CMainWnd)->GetAspectRatio(), 
		1.f, 1000.f);
	pSubCamera ->LookAt(XMFLOAT3(0.f, 10.f, -10.f), XMFLOAT3(0.f, 0.f, 0.f), XMFLOAT3(0.f, 1.f, 0.f));
#endif

	return S_OK;
}

HRESULT CGameEngine::CreateShader()
{
	//쉐이더를 만듬미다
	_SINGLE(CShaderManager)->CreateShader(SHADER_DEFAULT, L"DefaultShader.fx");

	/*
	ID3DX11EffectScalarVariable* FogStart =  _SINGLE(CShaderManager)->FindShader(
		_T("DefaultShader") )->GetScalar("gFogStart");
	ID3DX11EffectScalarVariable* FogRange = _SINGLE(CShaderManager)->FindShader(
		_T("DefaultShader") )->GetScalar("gFogRange");
	ID3DX11EffectVectorVariable* FogColor = _SINGLE(CShaderManager)->FindShader(
		_T("DefaultShader") )->GetVector("gFogColor");
	XMVECTORF32 Silver    = {0.75f, 0.75f, 0.75f, 1.0f};
	FogColor->SetFloatVector(reinterpret_cast<const float*>(&Silver) );
	FogStart->SetFloat(50.f); 
	FogRange->SetFloat(50.f); */
	
	return true;
}

HRESULT CGameEngine::CreateLight()
{
	DIRECTIONALLIGHT DirLight;

	DirLight.vDir = _SINGLE(CCameraManager)->GetCurCamera()->GetLook();
	DirLight.vDiffuse = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	DirLight.vAmbient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	DirLight.vSpecular = DirLight.vAmbient;

	

	POINTLIGHT PointLight;
	PointLight.vPos = XMFLOAT3(-3.f, 3.f, -2.f);
	PointLight.vAmbient  = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	PointLight.vDiffuse  = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
	PointLight.vSpecular = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
	PointLight.vAtt      = XMFLOAT3(0.0f, 0.f, 1.0f);
	PointLight.fRange = 5.f;

	SPOTLIGHT SpotLight;
	//SpotLight.fRange = 10.f;
	SpotLight.vPos = XMFLOAT3(3.f, 3.f, -2.f);
	SpotLight.vDiffuse = XMFLOAT4(0.f, 1.f, 0.f, 1.f);
	SpotLight.vAmbient = SpotLight.vDiffuse;
	SpotLight.vSpecular = XMFLOAT4(1.f, 1.f, 1.f, 1.f);
	SpotLight.vAtt = XMFLOAT3(0.f, 0.f, 1.f);
	SpotLight.fRange = 1000.f;
	SpotLight.vDir = XMFLOAT3(0.f, -1.f, 0.f);
	SpotLight.fSpot = 80.f;


	MATERIAL Material;

	Material.vDiffuse = XMFLOAT4(1.f, 1.f, 1.f, 1.0f);
	Material.vAmbient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	Material.vSpecular = Material.vAmbient;
	Material.vReflect = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.f);

	CShader* pShader = _SINGLE(CShaderManager)->FindShader(SHADER_DEFAULT);

	pShader->GetValue("gDirLight")->SetRawValue(&DirLight, 0, sizeof(DirLight));
	pShader->GetValue("gPointLight")->SetRawValue(&PointLight, 0, sizeof(PointLight));;
	//pShader->GetValue("gSpotLight")->SetRawValue(&SpotLight, 0, sizeof(SpotLight));
	pShader->GetValue("material")->SetRawValue(&Material, 0, sizeof(Material));;

	XMFLOAT3 vEye = _SINGLE(CCameraManager)->GetCurCamera()->GetPosition();

	pShader->GetVector("gEyePosW")->SetRawValue(&vEye, 0, sizeof(XMFLOAT3));

	return S_OK;
}

void CGameEngine::Input()
{
	_SINGLE(CKeyManager)->SetKeyState();
	_SINGLE(CObjectManager)->Input();
	_SINGLE(CCameraManager)->Input();

}

void CGameEngine::Update(float fTime)
{
	_SINGLE(CKeyManager)->SetKeyState();
	_SINGLE(CCameraManager)->Update(fTime);
	_SINGLE(CObjectManager)->Update(fTime);

}

void CGameEngine::Render()
{
	_SINGLE(CDevice)->BeginRender();
	//if(m_pFX && m_pTech)
	//{
	//	_ICONTEXT()->IASetInputLayout(m_pInputLayout);
	//	_ICONTEXT()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//	for(vector<CGeometry*>::iterator iter = m_vecMesh.begin();
	//		iter != m_vecMesh.end(); ++iter)
	//	{
	//		(*iter)->Render(m_pFX, m_pTech, fAspect);
	//	}
	//}

	_ICONTEXT()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//오브젝트 매니저 렌더  호출
	//렌더 전에 inputlayout 설정
	list<CEntity*>::iterator iter = m_listRender.begin();

	for(; iter != m_listRender.end(); ++iter)
	{
		(*iter)->Render();
	}

	_SINGLE(CDevice)->EndRender();

}

void CGameEngine::Clear()
{
	_SINGLE(CMath)->DestroyInstance();
	_SINGLE(CKeyManager)->DestroyInstance();
	_SINGLE(CResourceManager)->DestroyInstance();
	_SINGLE(CObjectManager)->DestroyInstance();
	_SINGLE(CShaderManager)->DestroyInstance();
	_SINGLE(CCameraManager)->DestroyInstance();

#ifdef _DEBUG || DEBUG
	_SINGLE(CDebug)->DestroyInstance();
#endif
}