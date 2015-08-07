#pragma once
#include "geometry.h"


class CTerrain :
	public CGeometry
{
private:
	ID3D11Buffer* mVB;
	ID3D11Buffer* mIB;

	/*ID3DX11Effect* mFX;
	ID3DX11EffectTechnique* mTech;*/
	UINT mGridIndexCount;
	//ID3DX11EffectMatrixVariable* mfxWorldViewProj;
	//ID3D11InputLayout* mInputLayout;

public:
	CTerrain(void);
	~CTerrain(void);

	virtual void Init();
	virtual void Render(CShader* pShader, const TECH_TYPE& eTech, const UINT& uPass);

	void BuildGeometryBuffers();
	void BuildFX();
	void BuildVertexLayout();
};

