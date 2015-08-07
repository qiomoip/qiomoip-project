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
	CEntity* pEntity = _SINGLE(CObjectManager)->CreateObject(
		RT_ENTITY, ET_BOX, MT_STATIC, GT_BOX, IT_DEFAULT_DEFAULT_LIGHT,
		L"Player", L"Resource\\Texture\\WoodCrate02.dds");

	if(!pEntity)
	{
		return false;
	}

	pEntity->SetShaderInfo(L"DefaultShader", DST_DEFAULT);
	pEntity->PushPass(DEFAULT_LIGHT);
	
	m_listRender.push_back(pEntity);


	//CEntity* pTerrain = _SINGLE(CObjectManager)->CreateObject(
	//	RT_ENTITY, ET_TERRAIN, MT_STATIC, GT_TERRAIN, IT_DEFAULT_DEFAULT_COLOR,
	//	L"Terrain");

	//if(!pTerrain)
	//{
	//	return false;
	//}

	//pTerrain->SetShaderInfo(L"DefaultShader", DST_DEFAULT);
	//pTerrain->PushPass(DEFAULT_COLOR);
	//
	//m_listRender.push_back(pTerrain);

	return true;
}

HRESULT CGameEngine::CreateCamera()
{
	CCamera* pCamera = _SINGLE(CCameraManager)->CreateCamera(L"MainCamera");

	if(!pCamera)
		return E_FAIL;

	pCamera->SetPosition(XMFLOAT3(0.f, 3.f, -3.f));
	pCamera->SetLens(_SINGLE(CMainWnd)->GetClientWidth(), _SINGLE(CMainWnd)->GetClientHeight(), PI * 0.25f,
		_SINGLE(CMainWnd)->GetAspectRatio(), 1.f, 1000.f);
	pCamera->LookAt(XMFLOAT3(0.f, 3.f, -30.f), XMFLOAT3(0.f, 0.f, 0.f), XMFLOAT3(0.f, 1.f, 0.f));
	//pCamera->SetLookObject(_SINGLE(CObjectManager)->FindObject(L"Player"));

	_SINGLE(CCameraManager)->SetCurrentCamera(pCamera);

	return S_OK;
}

HRESULT CGameEngine::CreateShader()
{
	//쉐이더를 만듬미다
	_SINGLE(CShaderManager)->CreateShader(L"DefaultShader", L"DefaultShader.fx");

	return true;
}

HRESULT CGameEngine::CreateLight()
{
	DIRECTIONALLIGHT DirLight;

	DirLight.vDir = _SINGLE(CCameraManager)->GetCurCamera()->GetLook();
	DirLight.vDiffuse = XMFLOAT4(1.f, 1.f, 1.f, 1.0f);
	DirLight.vAmbient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	DirLight.vSpecular = DirLight.vDiffuse;

	

	//POINTLIGHT PointLight;
	//PointLight.vPos = XMFLOAT3(0.f, 0.f, -2.f);
	//PointLight.vDiffuse = XMFLOAT4(0.f, 1.f, 0.f, 1.f);
	//PointLight.vAmbient = PointLight.vDiffuse;
	//PointLight.vSpecular = PointLight.vDiffuse;
	//PointLight.vAtt = XMFLOAT3(0.f, 1.f, 0.f);
	//PointLight.fRange = 2.f;


	MATERIAL Material;

	Material.vDiffuse = XMFLOAT4(1.f, 1.f, 1.f, 1.0f);
	Material.vAmbient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	Material.vSpecular = Material.vAmbient;

	CShader* pShader = _SINGLE(CShaderManager)->FindShader(L"DefaultShader");

	pShader->GetValue("gDirLight")->SetRawValue(&DirLight, 0, sizeof(DirLight));
	//pShader->GetValue("gPointLight")->SetRawValue(&PointLight, 0, sizeof(PointLight));;
	pShader->GetValue("material")->SetRawValue(&Material, 0, sizeof(Material));;

	XMFLOAT3 vEye = _SINGLE(CCameraManager)->GetCurCamera()->GetPosition();

	pShader->GetVector("gEyePosW")->SetRawValue(&vEye, 0, sizeof(XMFLOAT3));

	return S_OK;
}

void CGameEngine::Input()
{
	_SINGLE(CKeyManager)->SetKeyState();
	_SINGLE(CObjectManager)->Input();
}

void CGameEngine::Update(const float& fTime)
{
	_SINGLE(CKeyManager)->SetKeyState();
	_SINGLE(CCameraManager)->Update();
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

}