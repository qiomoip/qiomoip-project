#pragma once
#include "app.h"

class CClientApp :
	public CApp
{
private:
	
public:
	bool Init(const int& iWidth, const int& iHeight);
	void Update(float fTime);
	void Input(float fTime);
	void Render();
	void Clear();

	virtual void OnMouseDown(WPARAM btnState, int x, int y);
	virtual void OnMouseUp(WPARAM btnState, int x, int y)  ;
	virtual void OnMouseMove(WPARAM btnState, int x, int y);
	void OnResize();

public:
	CClientApp(HINSTANCE hInstance);
	~CClientApp(void);
};

