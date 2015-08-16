#pragma once
#include "singleton.h"

class CEntity;
class CCollisionManager : public CSingleton<CCollisionManager>
{
	friend CSingleton;
private:
	CCollisionManager(void);
	~CCollisionManager(void);


	//두 오브젝트가 충돌하는지 판단.(레이는 1에서)
	bool isCollision(CEntity* pEtt1, CEntity* pEtt2);
	void MakeSlidingVector(XMVECOTR& vSlide, XMVERCTOR& vMove, XMVECTOR& vNormal);
};

