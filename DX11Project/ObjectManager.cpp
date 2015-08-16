#include "ObjectManager.h"
#include "ResourceManager.h"
#include "Entity.h"
#include "Player.h"
#include "Zombie.h"

CObjectManager::CObjectManager(void)
{
}


CObjectManager::~CObjectManager(void)
{
	Clear();
}

CEntity* CObjectManager::CreateObject(const RENDER_TYPE& eRender, const ENTITY_TYPE& eEntity, 
									  const MESH_TYPE& eMesh, const GEOMETRY_TYPE& eGeo, const INPUTLAYOUT_TYPE& eInputLayout,
									  const tstring& strEntityKey,
									  const tstring& strTextureName, const LPCTSTR pFileName)
{

	CEntity* pEntity = FindObject(strEntityKey);
	if(pEntity)
		return pEntity;
	switch(eEntity)
	{
	case ET_NONE:
	case ET_BOX:
	case ET_TERRAIN:
	case ET_SKULL:
	case ET_WAVES:
	case ET_ENVIRONMENT:
		pEntity = new CEntity;
		break;
	case ET_PLAYER:
		pEntity = new CPlayer;
		break;
	case ET_ZOMBIE:
		pEntity = new CZombie;
		break;
	default :
		//잘못 된 enum값.
		return NULL;
	break;
	}

	//렌더러 생성
	if(eRender != RT_NONE)
	{
		//CreateResource(MT_BOX, pFileName);
		//여기서 생성된 렌더러를 엔티티에 넣음
		//pEntity->SetMesh();

		CBaseMesh* pMesh = _SINGLE(CResourceManager)->CreateRenderer(
			eMesh, eGeo, pFileName, strTextureName);
		pEntity->SetMesh(pMesh);
	}

	if(!pEntity->Init())
	{
		return NULL;
	}

	pEntity->SetEntityKey(strEntityKey);
	pEntity->SetInputLayout(eInputLayout);

	m_mapObject.insert(map<tstring, CEntity*>::value_type(strEntityKey, pEntity));

	return pEntity;
}

CEntity* CObjectManager::FindObject(const tstring& strKey)
{
	map<tstring, CEntity*>::iterator iter = m_mapObject.find(strKey);

	if(iter == m_mapObject.end())
		return NULL;
	return iter->second;
}

void CObjectManager::DeleteObject(const tstring& strKey)
{
	map<tstring, CEntity*>::iterator iter = m_mapObject.find(strKey);

	if(iter == m_mapObject.end())
		return;

	Safe_Delete(iter->second);
	m_mapObject.erase(iter);
}

void CObjectManager::Input()
{
	map<tstring, CEntity*>::iterator iter = m_mapObject.begin();

	for(; iter != m_mapObject.end(); ++iter)
	{
		iter->second->Input();
	}
}

void CObjectManager::Update(float fTime)
{
	map<tstring, CEntity*>::iterator iter = m_mapObject.begin();

	for(; iter != m_mapObject.end(); ++iter)
	{
		iter->second->Update(fTime);
	}
}

void CObjectManager::Clear()
{
	m_listRender.clear();
	map<tstring, CEntity*>::iterator iter = m_mapObject.begin();

	for(; iter != m_mapObject.end(); ++iter)
	{
		Safe_Delete(iter->second);
	}
	m_mapObject.clear();
}

map<tstring, CEntity*> CObjectManager::GetMapObject()
{
	return m_mapObject;
}