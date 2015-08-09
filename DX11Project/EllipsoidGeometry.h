#pragma once
#include "geometry.h"

class GeometryGenerator;

class CEllipsoidGeometry :
	public CGeometry
{
private:
	void Init();
	void CreateVertexBuffer();
	void CreateIndexBuffer();
	void CaculateNormal();

	void Render(CShader* pShader, const TECH_TYPE& eTech, const UINT& uPass);

	void Clear();

public:
	CEllipsoidGeometry(void);
	~CEllipsoidGeometry(void);
};

