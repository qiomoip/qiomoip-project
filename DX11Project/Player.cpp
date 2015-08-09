#include "Player.h"
#include "KeyManager.h"

CPlayer::CPlayer(void)
{
}


CPlayer::~CPlayer(void)
{
}

void CPlayer::Input(float fTIme)
{
	//움직이기
	const KEYINFO* pKeyRight = _SINGLE(CKeyManager)->GetKey(KEY_VKRIGHT);

	if(pKeyRight)
	{
		if(pKeyRight->bDown || pKeyRight->bPush)
		{
			XMVECTOR	vPos = XMLoadFloat3(&m_vPos);
			XMVECTOR	vWorldX = XMLoadFloat3(&m_WorldAxis[AT_X]);

			vPos += vWorldX * m_fSmooth * fTIme;

			XMStoreFloat3(&m_vPos, vPos);
		}
	}

	const KEYINFO* pKeyLeft = _SINGLE(CKeyManager)->GetKey(KEY_VKLEFT);
		
	if(pKeyLeft)
	{
		if(pKeyLeft->bDown || pKeyLeft->bPush)
		{
			XMVECTOR	vPos = XMLoadFloat3(&m_vPos);
			XMVECTOR	vWorldX = XMLoadFloat3(&m_WorldAxis[AT_X]);

			vPos -= vWorldX * m_fSmooth * fTIme;

			XMStoreFloat3(&m_vPos, vPos);
		}
	}

	const KEYINFO* pKeyUp = _SINGLE(CKeyManager)->GetKey(KEY_VKUP);
		
	if(pKeyUp)
	{
		if(pKeyUp->bDown || pKeyUp->bPush)
		{
			XMVECTOR	vPos = XMLoadFloat3(&m_vPos);
			XMVECTOR	vWorldX = XMLoadFloat3(&m_WorldAxis[AT_Z]);

			vPos += vWorldX * m_fSmooth * fTIme;

			XMStoreFloat3(&m_vPos, vPos);
		}
	}

	const KEYINFO* pKeyDown = _SINGLE(CKeyManager)->GetKey(KEY_VKDOWN);
		
	if(pKeyDown)
	{
		if(pKeyDown->bDown || pKeyDown->bPush)
		{
			XMVECTOR	vPos = XMLoadFloat3(&m_vPos);
			XMVECTOR	vWorldX = XMLoadFloat3(&m_WorldAxis[AT_Z]);

			vPos -= vWorldX * m_fSmooth * fTIme;

			XMStoreFloat3(&m_vPos, vPos);
		}
	}
}