#pragma once
#include "app.h"

class CClientApp :
	public CApp
{
private:
	
public:
	bool Init(const int& iWidth, const int& iHeight);
	void Update(float fTime);
	void Input();
	void Render();
	void Clear();

	void OnResize();

public:
	CClientApp(HINSTANCE hInstance);
	~CClientApp(void);
};

