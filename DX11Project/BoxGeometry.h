#pragma once
#include "Geometry.h"


class CBoxGeometry :
	public CGeometry
{
private:
	ID3D11Buffer*	m_pVB;
	ID3D11Buffer*	m_pIB;

public:
	void Init();
	void CreateVertexBuffer();
	void CreateIndexBuffer();
	void CaculateNormal();

	void Render(CShader* pShader, const TECH_TYPE& eTech, const UINT& uPass);

	void Clear();

public:
	CBoxGeometry(void);
	~CBoxGeometry(void);
};

