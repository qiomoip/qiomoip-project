#pragma once
#include "entity.h"
class CPlayer :
	public CEntity
{
public:
	CPlayer(void);
	~CPlayer(void);
	
	virtual void Update(float fTime);
	virtual void Input();

	virtual void Move(XMFLOAT3& fMove);

	virtual void RotateY(float fAngle);

	virtual void CheckCollision();
};

