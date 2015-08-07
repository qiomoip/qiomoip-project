#pragma once
#include "Singleton.h"

class CMath
	: public CSingleton<CMath>
{
	friend CSingleton;
public:
	XMMATRIX	GetInverseTranspose(CXMMATRIX mat);
private:
	CMath(void);
	~CMath(void);
};

