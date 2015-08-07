#pragma once
#include "include.h"

class CShader;

class CGeometry
{
protected:
	XMFLOAT3	m_vPos;
	INPUTLAYOUT_TYPE	m_eInputLayout;

public:
	virtual void Init()PURE;
	void SetPos(const XMFLOAT3& vPos);
	virtual void Render(CShader* pShader, const TECH_TYPE& eTech, const UINT& uPass)PURE;
	void SetInputLayout(const INPUTLAYOUT_TYPE& eInput);
public:
	CGeometry(void);
	virtual ~CGeometry(void);
};

