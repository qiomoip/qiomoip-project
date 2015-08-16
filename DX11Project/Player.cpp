#include "Player.h"
#include "KeyManager.h"
#include "ObjectManager.h"
#include "Debug.h"
CPlayer::CPlayer(void)
{
}


CPlayer::~CPlayer(void)
{
}

void CPlayer::Update(float fTime)
{
	float MoveSmooth = fTime * m_tInputInfo.fMoveSpeed;
	float RoateSmooth = fTime * m_tInputInfo.fRotateSpeed;
	
	XMVECTOR vMove = XMLoadFloat3(&m_tInputInfo.fMove);;
		vMove *= MoveSmooth;
	XMStoreFloat3( &m_tInputInfo.fMove, vMove);

	//�浹 üũ 
	//CheckCollision();
	//�̵�
	if( m_tInputInfo.fMove.x  )
		Move( m_tInputInfo.fMove );
	if( m_tInputInfo.fMove.z )
		Move( m_tInputInfo.fMove );
	//ȸ��
	if( m_tInputInfo.fAngle.y )
		RotateY( m_tInputInfo.fAngle.y * RoateSmooth );

	
	//�Է� �ʱ�ȭ
	memset( &m_tInputInfo.fMove, 0, sizeof(XMFLOAT3) );
	memset( &m_tInputInfo.fAngle, 0, sizeof(XMFLOAT3) );
	

	CEntity::Update(fTime);
}

void CPlayer::Input()
{
	//�����̱�
	const KEYINFO* pKey = NULL;

	pKey = _SINGLE(CKeyManager)->GetKey(KEY_VKRIGHT);
	if(pKey)
		if(pKey->bDown || pKey->bPush)
			m_tInputInfo.fMove.x = 1.0f;

	pKey = _SINGLE(CKeyManager)->GetKey(KEY_VKLEFT);	
	if(pKey)
		if(pKey->bDown || pKey->bPush)
			m_tInputInfo.fMove.x = -1.0f;

	pKey = _SINGLE(CKeyManager)->GetKey(KEY_VKUP);
	if(pKey)
		if(pKey->bDown || pKey->bPush)
			m_tInputInfo.fMove.z = 1.0f;

	pKey = _SINGLE(CKeyManager)->GetKey(KEY_VKDOWN);
	if(pKey)
		if(pKey->bDown || pKey->bPush)
			m_tInputInfo.fMove.z = -1.f;


	////y�� �̵� ��
	//const KEYINFO* pKeyPlus = _SINGLE(CKeyManager)->GetKey(KEY_VKPGUP);
	//	
	//if(pKeyPlus)
	//{
	//	if(pKeyPlus->bDown || pKeyPlus->bPush)
	//	{
	//		XMVECTOR	vPos = XMLoadFloat3(&m_vPos);
	//		XMVECTOR	vWorldY = XMLoadFloat3(&m_WorldAxis[AT_Y]);

	//		vPos += vWorldY * m_fSmooth * fTIme;

	//		XMStoreFloat3(&m_vPos, vPos);
	//	}
	//}

	////y�� �̵� �Ʒ�
	//const KEYINFO* pKeyMinus = _SINGLE(CKeyManager)->GetKey(KEY_VKINSERT);
	//	
	//if(pKeyMinus)
	//{
	//	if(pKeyMinus->bDown || pKeyMinus->bPush)
	//	{
	//		XMVECTOR	vPos = XMLoadFloat3(&m_vPos);
	//		XMVECTOR	vWorldY = XMLoadFloat3(&m_WorldAxis[AT_Y]);

	//		vPos -= vWorldY * m_fSmooth * fTIme;

	//		XMStoreFloat3(&m_vPos, vPos);
	//	}
	//}
}

void CPlayer::Move(XMFLOAT3& fMove)
{
	XMVECTOR	vPos = XMLoadFloat3(&m_vPos);
	XMVECTOR	vMove = XMLoadFloat3(&fMove); 
	
	//vMove = XMVector3Normalize( vMove);
	vPos += vMove;
	XMStoreFloat3(&m_vPos, vPos);
}

void CPlayer::RotateY(float fAngle)
{
	XMMATRIX matRotY = XMMatrixRotationY(fAngle);
	//CXMMATRIX �������� �ٲ� �ʿ� ����.
	XMMATRIX matWorld = XMLoadFloat4x4( &m_matWorld );
	XMStoreFloat4x4( &m_matWorld , XMMatrixMultiply( matWorld , matRotY) );
}

void CPlayer::CheckCollision()
{
	map<tstring, CEntity*> mapObject = _SINGLE(CObjectManager)->GetMapObject();
	map<tstring, CEntity*>::iterator it = mapObject.begin();

	for( ; it != mapObject.end(); ++it)
	{	

	}
	
}