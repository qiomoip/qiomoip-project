#pragma once
#include "include.h"

class CShader;

class CGeometry
{
protected:
	XMFLOAT3	m_vPos;

public:
	virtual void Init()PURE;
	void SetPos(const XMFLOAT3& vPos);
	virtual void Render(CShader* pShader, const TECH_TYPE& eTech, const INPUTLAYOUT_TYPE& eInputLayout, const UINT& uPass)PURE;
public:
	CGeometry(void);
	virtual ~CGeometry(void);
};

