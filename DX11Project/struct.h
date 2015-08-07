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
	int			iKey;		//key�� �ƽ�Ű�ڵ�
	bool		bDown;		//��~~
	bool		bPush;		//1��
	bool		bUp;		//�����ٰ� ���� ��
}KEYINFO;

typedef struct _tagMaterial
{
	XMFLOAT4	vAmbient;
	XMFLOAT4	vDiffuse;
	XMFLOAT4	vSpecular;	//w == SpecPower(�ݿ�����)
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
	XMFLOAT4	vSpecular;	//w == SpecPower(�ݿ�����)
	XMFLOAT3	vDir;

	//pad�� �߰��ϴ� ������ C++�� packing ��Ģ�� hlsl�� packing ��Ģ�� ��ġ��Ű���� �ϱ� ����
	//hlsl�� �����͸� vec4 Ÿ������ ä��������, �ϳ��� ���Ͱ� 2���� 4���� ���Ϳ� �ɰ��� ��� ���� ������� �ʴ´�
	//float3 vPos, float2 vTex�� ���� ��
	//v1(vPos.x, vPos.y, vPos.z, vTex.x) / v2(vTex.y, ����, ����, ����)�� �ƴ϶�
	//v1(vPos.x, vPos.y, vPos.z, ����) / v2(vTex.x, vTex.y, ����, ����) �̷��� ä����
	float		Pad; //�ʿ��ϴٸ� ���� �迭�� ������ �� �ֵ���, �������� float �� �ڸ��� ���ܵд�

	_tagDirectionalLight()
	{
		memset(this, 0, sizeof(_tagDirectionalLight));
	}
}DIRECTIONALLIGHT;

typedef struct _tagPointLight
{
	XMFLOAT4	vAmbient;
	XMFLOAT4	vDiffuse;
	XMFLOAT4	vSpecular;	//w == SpecPower(�ݿ�����)
	XMFLOAT3	vPos;
	float		fRange;		//���� ���� (�Ÿ�)
	XMFLOAT3	vAtt;		//���� ���Ⱑ �Ÿ��� ���� �����ϴ� ����� �����ϴ� �� ���� ���� ����� ����
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
	XMFLOAT4	vSpecular;	//w == SpecPower(�ݿ�����)
	XMFLOAT3	vPos;
	float		fRange;
	XMFLOAT3	vDir;
	float		fSpot;		//������ ������ �����ϴ� �� ���̴� ����
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
	int				iFrame;		//�ؽ�ó �ִϸ��̼��� ���� ������ ��ȣ
}TEXINFO;