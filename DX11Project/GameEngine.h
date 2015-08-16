#pragma once
#include "Singleton.h"

class CEntity;

class CGameEngine
	: public CSingleton<CGameEngine>
{
	friend CSingleton;

public:
	HRESULT Init();
	HRESULT CreateEntity();
	HRESULT CreateCamera();
	HRESULT CreateShader();
	HRESULT CreateLight();

	void Input();
	void Update(float fTime);
	void Render();
	void Clear();

private:
	list<CEntity*>	m_listRender;

private:
	CGameEngine(void);
	~CGameEngine(void);
};

