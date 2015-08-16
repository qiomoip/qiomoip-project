#pragma once
#include "Singleton.h"
class CCollisionManager : public CSingleton<CCollisionManager>
{
	friend CSingleton;
private:
	CCollisionManager(void);
	~CCollisionManager(void);

	bool isCollision();
};

