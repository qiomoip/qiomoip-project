#pragma once
#include "Singleton.h"

class CMath
	: public CSingleton<CMath>
{
	friend CSingleton;
public:
	XMMATRIX	GetInverseTranspose(CXMMATRIX mat);
	CXMVECTOR	CaculateNormal(FXMVECTOR vPos1, FXMVECTOR vPos2, FXMVECTOR vPos3);
private:
	CMath(void);
	~CMath(void);
};

