#pragma once
#include "Geometry.h"
#include "GeometryGenerator.h"

class CBoxGeometry :
	public CGeometry
{
private:
	ID3D11Buffer*	m_pVB;
	ID3D11Buffer*	m_pIB;

public:
	void Init();
	void CreateVertexBuffer(GeometryGenerator::MeshData& box);
	void CreateIndexBuffer(GeometryGenerator::MeshData& box);
	//void CaculateNormal();

	void Render(CShader* pShader, const TECH_TYPE& eTech, const UINT& uPass);

	void Clear();

public:
	CBoxGeometry(void);
	~CBoxGeometry(void);
};

