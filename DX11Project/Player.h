#pragma once
#include "entity.h"
class CPlayer :
	public CEntity
{
public:
	CPlayer(void);
	~CPlayer(void);

	void Input();
};

