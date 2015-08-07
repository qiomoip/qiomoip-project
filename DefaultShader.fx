
cbuffer cbPerObject
{
	float4x4 matWVP;
};


struct VS_IN_DEFAULT
{
	float3 vPosL : POSITION0;
	float4 vColor : COLOR0;
};

struct VS_OUT_DEFAULT
{
	float4 vPosH : SV_POSITION;
	float4 vColor : COLOR0;
};

struct PS_OUT_DEFAULT
{
	float4 vColor : SV_TARGET;
};

VS_OUT_DEFAULT DefaultVS(VS_IN_DEFAULT inv)
{
	VS_OUT_DEFAULT outv = (VS_OUT_DEFAULT)0;

	outv.vPosH = mul(float4(inv.vPosL, 1.0f), matWVP);
	outv.vColor = inv.vColor;

	return outv;
}

PS_OUT_DEFAULT DefaultPS(VS_OUT_DEFAULT inp)
{
	PS_OUT_DEFAULT outp = (PS_OUT_DEFAULT)0;

	outp.vColor = inp.vColor;

	return outp;
}

technique11 DefaultTech
{
	pass DefaultPass
	{
		SetVertexShader( CompileShader( vs_5_0, DefaultVS() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_5_0, DefaultPS() ) );
	}
}

