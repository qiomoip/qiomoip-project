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