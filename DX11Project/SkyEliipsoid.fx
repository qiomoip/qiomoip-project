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

	//s / w = 1�� �ǵ��� (�� �ϴ� ���� �׻� �� ��鿡 �ֵ���) z = w�� ����
	outv.vPosH = mul(float4(inv.vPosL, 1.f), g_matWVP).xyww;
	
	//���� ��ġ�� �Թ�ü �� ��ȸ ���ͷ� ���
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
	//���� �Լ��� LESS�� �ƴ϶� LESS_EQUAL�� �ؾ� �Ѵ�
	//�׷��� ���� ���� ��� ���� ���۷� 1�� �����ٰ� �� �� z = 1�� 
	//����ȭ�� ���� ������ ���� ������ �����Ѵ�
	//����� �ž� ��·��
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

