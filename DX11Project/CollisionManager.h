#pragma once
#include "singleton.h"

class CEntity;
class CCollisionManager : public CSingleton<CCollisionManager>
{
	friend CSingleton;
private:
	CCollisionManager(void);
	~CCollisionManager(void);


	//�� ������Ʈ�� �浹�ϴ��� �Ǵ�.(���̴� 1����)
	bool isCollision(CEntity* pEtt1, CEntity* pEtt2);
	void MakeSlidingVector(XMVECOTR& vSlide, XMVERCTOR& vMove, XMVECTOR& vNormal);
};

