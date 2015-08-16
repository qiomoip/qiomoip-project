#pragma once
#include "Singleton.h"

class CEntity;

class CObjectManager
	: public CSingleton<CObjectManager>
{
	friend CSingleton;
private:
	map<tstring, CEntity*>	m_mapObject;
	list<CEntity*>			m_listRender;

public:
	CEntity* CreateObject(const RENDER_TYPE& eRender, const ENTITY_TYPE& eEntity, 
		const MESH_TYPE& eMesh, const GEOMETRY_TYPE& eGeo, const INPUTLAYOUT_TYPE& eInputLayout,
		const tstring& strEntityKey, const tstring& strTextureName = L"", const LPCSTR pTextureName = "g_texDiffuseMap", const LPCTSTR pFileName = NULL);
	CEntity* FindObject(const tstring& strKey);
	void DeleteObject(const tstring& strKey);
	void Input();
	void Update(float fTime);
	void Clear();

	map<tstring, CEntity*> GetMapObject();
private:
	CObjectManager(void);
	~CObjectManager(void);
};

