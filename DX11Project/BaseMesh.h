#pragma once
#include "include.h"

class CShader;

class CGeometry;

class CBaseMesh
{
protected:
	CGeometry*	m_pGeometry;

public:
	virtual void Init(const GEOMETRY_TYPE& eMesh, const INPUTLAYOUT_TYPE& eInputLayout, const LPCTSTR pFileName, tstring strTextureName)PURE;
	virtual void Render(CShader* pShader, const TECH_TYPE& eTech, const UINT& uPass)PURE;

	void SetGeometry(CGeometry* pGeometry);

public:
	CBaseMesh(void);
	virtual ~CBaseMesh(void);
};

