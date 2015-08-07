#pragma once
#include <DirectXMath.h>


typedef struct _tagVertex
{
	XMFLOAT3 vPos;
	XMFLOAT3 vNormal;
	XMFLOAT4 vColor;
	XMFLOAT2 vTex;
}Vertex;

typedef struct _tagCamera
{
	XMFLOAT4X4	matView;
	XMFLOAT4X4	matProj;
}CAMERA;

typedef struct _tagKey
{
	int			iKey;		//key의 아스키코드
	bool		bDown;		//꾹~~
	bool		bPush;		//1번
	bool		bUp;		//눌렀다가 뗐을 때
}KEYINFO;

typedef struct _tagMaterial
{
	XMFLOAT4	vAmbient;
	XMFLOAT4	vDiffuse;
	XMFLOAT4	vSpecular;	//w == SpecPower(반영지수)
	XMFLOAT4	vReflect;
	_tagMaterial()
	{
		memset(this, 0, sizeof(_tagMaterial));
	}
}MATERIAL;

typedef struct _tagDirectionalLight
{
	XMFLOAT4	vAmbient;
	XMFLOAT4	vDiffuse;
	XMFLOAT4	vSpecular;	//w == SpecPower(반영지수)
	XMFLOAT3	vDir;

	//pad를 추가하는 이유는 C++의 packing 규칙과 hlsl의 packing 규칙을 일치시키도록 하기 위함
	//hlsl은 데이터를 vec4 타입으로 채워넣지만, 하나의 벡터가 2개의 4차원 벡터에 쪼개져 담는 것을 허용하지 않는다
	//float3 vPos, float2 vTex가 있을 때
	//v1(vPos.x, vPos.y, vPos.z, vTex.x) / v2(vTex.y, 여분, 여분, 여분)이 아니라
	//v1(vPos.x, vPos.y, vPos.z, 여분) / v2(vTex.x, vTex.y, 여분, 여분) 이렇게 채워짐
	float		Pad; //필요하다면 빛의 배열을 설정할 수 있도록, 마지막에 float 한 자리를 남겨둔다

	_tagDirectionalLight()
	{
		memset(this, 0, sizeof(_tagDirectionalLight));
	}
}DIRECTIONALLIGHT;

typedef struct _tagPointLight
{
	XMFLOAT4	vAmbient;
	XMFLOAT4	vDiffuse;
	XMFLOAT4	vSpecular;	//w == SpecPower(반영지수)
	XMFLOAT3	vPos;
	float		fRange;		//빛의 범위 (거리)
	XMFLOAT3	vAtt;		//빛의 세기가 거리에 따라 감소하는 방식을 제어하는 세 개의 감쇠 상수를 저장
	float		Pad;

	_tagPointLight()
	{
		memset(this, 0, sizeof(_tagPointLight));
	}
}POINTLIGHT;

typedef struct _tagSpotLight
{
	XMFLOAT4	vAmbient;
	XMFLOAT4	vDiffuse;
	XMFLOAT4	vSpecular;	//w == SpecPower(반영지수)
	XMFLOAT3	vPos;
	float		fRange;
	XMFLOAT3	vDir;
	float		fSpot;		//점적광 원뿔을 제어하는 데 쓰이는 지수
	XMFLOAT3	vAtt;
	float		Pad;

	_tagSpotLight()
	{
		memset(this, 0, sizeof(_tagSpotLight));
	}
}SPOTLIGHT;

typedef struct _tagTexture
{
	ID3D11Texture2D* pTex;
	ID3D11ShaderResourceView* pShaderRes;
	int				iFrame;		//텍스처 애니메이션을 위한 프레임 번호
}TEXINFO;