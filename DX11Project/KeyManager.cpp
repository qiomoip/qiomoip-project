#include "KeyManager.h"

CKeyManager::CKeyManager(void)
{
}


CKeyManager::~CKeyManager(void)
{
	Destroy();
}

void CKeyManager::Initialize()
{
	SetKeyData(KEY_VKRIGHT, VK_RIGHT);
	SetKeyData(KEY_VKLEFT, VK_LEFT);
	SetKeyData(KEY_VKUP, VK_UP);
	SetKeyData(KEY_VKDOWN, VK_DOWN);
}
void CKeyManager::SetKeyState()
{
	map<KEY, KEYINFO*>::iterator iter = m_mapKey.begin();
	for(; iter != m_mapKey.end() ; ++iter)
	{
		CheckKey(iter);
	}

	//_SINGLE(CMouse)->CaculateMousePos();
	//_SINGLE(CMouse)->CaculateRay();
}

bool CKeyManager::SetKeyData(const KEY eKeyName, const int& iKey)
{
	map<KEY, KEYINFO*>::iterator iter = m_mapKey.find(eKeyName);
	if(iter != m_mapKey.end())
	{
		return false;
	}
	KEYINFO* pKey = new KEYINFO;
	memset(pKey, 0, sizeof(KEYINFO));
	
	pKey->iKey = iKey;
	m_mapKey.insert(map<KEY, KEYINFO*>::value_type(eKeyName, pKey));
	return true;
}

const KEYINFO* CKeyManager::GetKey(const KEY eKey) const
{
	map<KEY, KEYINFO*>::const_iterator iter = m_mapKey.find(eKey);

	if(iter == m_mapKey.end())
	{
		return NULL;
	}
	return iter->second;
}

void CKeyManager::CheckKey(map<KEY, KEYINFO*>::iterator iter)
{
	if(GetAsyncKeyState(iter->second->iKey) & 0x8000)
	{
		iter->second->bUp = false;
		if(!iter->second->bPush)
		{
			if(!iter->second->bDown)
			{
				iter->second->bPush = true;
				iter->second->bDown = false;
			}
		}
		else
		{
			iter->second->bPush = false;
			iter->second->bDown = true;
		}
	}
	else
	{
		if(iter->second->bDown || iter->second->bPush)
		{
			iter->second->bUp = true;
		}
		else
		{
			iter->second->bUp = false;
		}
		iter->second->bPush = false;
		iter->second->bDown = false;
	}
}

void CKeyManager::Destroy()
{
	Safe_Delete_Array_Map(m_mapKey);
}