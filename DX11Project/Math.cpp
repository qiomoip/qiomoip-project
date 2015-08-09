#include "Math.h"


CMath::CMath(void)
{
}


CMath::~CMath(void)
{
}

XMMATRIX	CMath::GetInverseTranspose(CXMMATRIX mat)
{
	XMMATRIX matT = mat;
	matT.r[3] = XMVectorSet(0.f, 0.f, 0.f, 1.f);

	XMVECTOR	det = XMMatrixDeterminant(matT);

	return XMMatrixTranspose(XMMatrixInverse(&det, matT));
}

CXMVECTOR	CMath::CaculateNormal(FXMVECTOR vPos1, FXMVECTOR vPos2, FXMVECTOR vPos3)
{
	XMVECTOR e0 = vPos2 - vPos1;
	XMVECTOR e1 = vPos3 - vPos1;
	e0 = XMVector3Normalize(e0);
	e1 = XMVector3Normalize(e1);
	XMVECTOR vCross = XMVector3Cross(e0, e1);
	vCross = XMVector3Normalize(vCross);

	return vCross;
}