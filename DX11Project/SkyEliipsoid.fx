cbuffer cbPerFrame
{
	float4x4 g_matWVP;

};

TextureCube g_CubeMap;

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
	outv.vPosH = mul(float4(inv.vPosL, 1.f), g_matWVP).xyww;
	
	//로컬 위치를 입방체 맵 조회 벡터로 사용
	outv.vPosL = inv.vPosL;

	return outv;
}

PS_OUT_SKY SkyPS(VS_OUT_SKY inp)
{
	PS_OUT_SKY outp = (PS_OUT_SKY)0;

	outp.vColor = g_CubeMap.Sample(smTriLinearSam, inp.vPosL);

	return outp;
}

RasterizerState NoCull
{
	CullMode = None;
};

DepthStencilState LessEqualDSS
{
	//깊이 함수를 LESS가 아니라 LESS_EQUAL로 해야 한다
	//그렇게 하지 않을 경우 깊이 버퍼롤 1로 지웠다고 할 때 z = 1의 
	//정규화된 깊이 값들이 깊이 판정에 실패한다
	//뭐라는 거야 어쨌든
	DepthFunc = LESS_EQUAL;
};

technique11 SkyTech
{
	pass SkyPass
	{
		SetVertexShader( CompileShader( vs_5_0, SkyVS() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_5_0, SkyPS() ) );

		SetRasterizerState(NoCull);
		SetDepthStencilState(LessEqualDSS, 0);
	}
}

