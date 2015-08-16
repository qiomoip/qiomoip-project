#pragma once
#include "geometry.h"


class CTerrain :
	public CGeometry
{
private:
	ID3D11Buffer* mVB;
	ID3D11Buffer* mIB;

	UINT mGridIndexCount;
public:
	CTerrain(void);
	~CTerrain(void);

	virtual void Init();
	virtual void Render(CShader* pShader, const TECH_TYPE& eTech, const INPUTLAYOUT_TYPE& eInputLayout, const UINT& uPass);

	void BuildGeometryBuffers();
};

