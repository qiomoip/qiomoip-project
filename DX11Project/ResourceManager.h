#pragma once
#include "Singleton.h"

class CGeometry;
class CTexture;
class CBaseMesh;

class CResourceManager
	: public CSingleton<CResourceManager>
{
	friend CSingleton;

private:
	map<GEOMETRY_TYPE, CGeometry*>	m_mapMesh;
	map<tstring, CTexture*>	m_mapTexture;

public:
	CBaseMesh* CreateRenderer(const MESH_TYPE& eMesh, const GEOMETRY_TYPE& eGeo, const LPCTSTR pFileName, const LPCSTR pShaderTextureName, tstring strTextureName = L"");
	CGeometry* CreateGeometry(const GEOMETRY_TYPE& eGeo, const LPCTSTR pFileName);
	CTexture* CreateTexture(const LPCSTR pShaderTextureName, tstring strTextureName);
	void Clear();

private:
	CResourceManager(void);
	~CResourceManager(void);
};

