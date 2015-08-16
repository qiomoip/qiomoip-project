#include "light.fx"

cbuffer cbPerObject
{
	float4x4 matWVP;
	float4x4 matWorld;
	float4x4 matWorldInvTranspose;
	Material material;
};


cbuffer cbPerFrame
{
	DirectionalLight gDirLight;
	PointLight gPointLight;
	SpotLight gSpotLight;
	float3 gEyePosW;
};

Texture2D g_texDiffuseMap;
TextureCube g_texCube;

SamplerState SamplerLinear
{
	Filter = ANISOTROPIC;
	MaxAnisotropy = 4;

	AddressU = WRAP;
	AddressV = WRAP;
};


struct VS_IN_DEFAULT
{
	float3 vPosL : POSITION0;
	float3 vNormalL : NORMAL;
	float4 vColor : COLOR0;
	float2 vTex : TEXCOORD0;
};

struct VS_IN_LIGHT
{
	float3 vPosL : POSITION0;
	float3 vNormalL : NORMAL;
	float2 vTex : TEXCOORD0;
};

struct VS_OUT_DEFAULT
{
	float4 vPosH : SV_POSITION;
	float3 vNormalH : NORMAL;
	float4 vColor : COLOR0;
};

struct VS_OUT_LIGHT
{
	float4 vPosH : SV_POSITION;
	float3 vPosW : POSITION;
	float3 vNormalW : NORMAL;
	float2 vTex : TEXCOORD0;
};

struct PS_OUT_DEFAULT
{
	float4 vColor : SV_TARGET;
};

VS_OUT_DEFAULT DefaultVS(VS_IN_DEFAULT inv)
{
	VS_OUT_DEFAULT outv = (VS_OUT_DEFAULT)0;

	outv.vPosH = mul(float4(inv.vPosL, 1.0f), matWVP);
	outv.vNormalH = mul(inv.vNormalL, (float3x3)matWVP);
	outv.vColor = inv.vColor;

	return outv;
}

VS_OUT_LIGHT LightVS(VS_IN_LIGHT inv)
{
	VS_OUT_LIGHT outv = (VS_OUT_LIGHT)0;

	outv.vPosW = mul(float4(inv.vPosL, 1.0f), matWorld).xyz;
	outv.vNormalW = mul(inv.vNormalL, (float3x3)matWorldInvTranspose);

	outv.vPosH = mul(float4(inv.vPosL, 1.0f), matWVP);

	outv.vTex = inv.vTex;

	return outv;
}

PS_OUT_DEFAULT DefaultPS(VS_OUT_DEFAULT inp)
{
	PS_OUT_DEFAULT outp = (PS_OUT_DEFAULT)0;

	outp.vColor = inp.vColor;

	//outp.vColor = float4(1.f, 1.f, 1.f, 1.f);
	return outp;
}

PS_OUT_DEFAULT LightPS(VS_OUT_LIGHT inp)
{
	PS_OUT_DEFAULT outp = (PS_OUT_DEFAULT)0;

	float4 texColor = g_texDiffuseMap.Sample(SamplerLinear, inp.vTex);

	//outp.vColor = texColor;
	//return outp;

	inp.vNormalW = normalize(inp.vNormalW);

	float3 toEyeW = normalize(gEyePosW - inp.vPosW);

	float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float4 A, D, S;

	ComputeDirectionalLight(material, gDirLight, inp.vNormalW, toEyeW, A, D, S);

	ambient += A;
	diffuse += D;
	specular += S;

	ComputePointLight(material, gPointLight, inp.vPosW, inp.vNormalW, toEyeW, A, D, S);

	ambient += A;
	diffuse += D;
	specular += S;

	ComputeSpotLight(material, gSpotLight, inp.vPosW, inp.vNormalW, toEyeW, A, D, S);

	ambient += A;
	diffuse += D;
	specular += S;

	outp.vColor = texColor * (ambient + diffuse) + specular;

	outp.vColor.a = material.vDiff.a;

	//outp.vColor = float4(0.f, 0.f, 0.f, 1.f);
	//outp.vColor = D;
	//outp.vColor.a = 1.f;
	return outp;
}

PS_OUT_DEFAULT SkyReflectPS(VS_OUT_LIGHT inp)
{
	PS_OUT_DEFAULT outp = (PS_OUT_DEFAULT)0;

	float4 texColor = g_texDiffuseMap.Sample(SamplerLinear, inp.vTex);

	//outp.vColor = texColor;
	//return outp;

	inp.vNormalW = normalize(inp.vNormalW);

	float3 toEyeW = normalize(gEyePosW - inp.vPosW);

	float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float4 A, D, S;

	ComputeDirectionalLight(material, gDirLight, inp.vNormalW, toEyeW, A, D, S);

	ambient += A;
	diffuse += D;
	specular += S;

	ComputePointLight(material, gPointLight, inp.vPosW, inp.vNormalW, toEyeW, A, D, S);

	ambient += A;
	diffuse += D;
	specular += S;

	ComputeSpotLight(material, gSpotLight, inp.vPosW, inp.vNormalW, toEyeW, A, D, S);

	ambient += A;
	diffuse += D;
	specular += S;

	outp.vColor = texColor * (ambient + diffuse) + specular;

	float3 incident = -toEyeW;
	float3 vReflect = reflect(incident, inp.vNormalW);
	float4 vReflectColor = g_texCube.Sample(SamplerLinear, vReflect);

	outp.vColor += material.vReflect * vReflectColor;


	outp.vColor.a = material.vDiff.a;

	//outp.vColor = float4(0.f, 0.f, 0.f, 1.f);
	//outp.vColor = D;
	//outp.vColor.a = 1.f;
	return outp;
}


//


SamplerState smTriLinearSam
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

struct VS_IN_SKY
{
	float3 vPosL : POSITION;
};

struct VS_OUT_SKY
{
	float4 vPosH : SV_POSITION;
	float3 vPosL : POSITION;
};

struct PS_OUT_SKY
{
	float4 vColor : SV_TARGET;
};

VS_OUT_SKY SkyVS(VS_IN_SKY inv)
{
	VS_OUT_SKY outv = (VS_OUT_SKY)0;

	//s / w = 1이 되도록 (즉 하늘 돔이 항상 먼 평면에 있도록) z = w로 설정
	outv.vPosH = mul(float4(inv.vPosL, 1.f), matWVP).xyww;
	
	//로컬 위치를 입방체 맵 조회 벡터로 사용
	outv.vPosL = inv.vPosL;

	return outv;
}

PS_OUT_SKY SkyPS(VS_OUT_SKY inp)
{
	PS_OUT_SKY outp = (PS_OUT_SKY)0;

	outp.vColor = g_texCube.Sample(smTriLinearSam, inp.vPosL);

	return outp;
}

RasterizerState NoCull
{
	CullMode = None;
	//FillMode = WireFrame;
};

DepthStencilState LessEqualDSS
{
	//깊이 함수를 LESS가 아니라 LESS_EQUAL로 해야 한다
	//그렇게 하지 않을 경우 깊이 버퍼롤 1로 지웠다고 할 때 z = 1의 
	//정규화된 깊이 값들이 깊이 판정에 실패한다
	//뭐라는 거야 어쨌든
	DepthFunc = LESS_EQUAL;
};

technique11 DefaultTech
{
	pass DefaultPass
	{
		SetVertexShader( CompileShader( vs_5_0, DefaultVS() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_5_0, DefaultPS() ) );
	}

	pass LightPass
	{
		SetVertexShader( CompileShader( vs_5_0, LightVS() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_5_0, SkyReflectPS() ) );
	}

	pass SkyPass
	{
		SetVertexShader( CompileShader( vs_5_0, LightVS() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_5_0, SkyPS() ) );

		SetRasterizerState(NoCull);
		SetDepthStencilState(LessEqualDSS, 0);
	}

	pass SkyReflectPass
	{
		SetVertexShader( CompileShader( vs_5_0, LightVS() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_5_0, LightPS() ) );
	}
}

