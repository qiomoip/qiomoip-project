
struct Material
{
	float4 vAmb;
	float4 vDiff;
	float4 vSpec;
	float4 vReflect;
};

struct DirectionalLight
{
	float4 vAmb;
	float4 vDiff;
	float4 vSpec;

	float3 vDir;
	float pad;
};

struct PointLight
{
	float4 vAmb;
	float4 vDiff;
	float4 vSpec;

	float3 vPos;
	float fRange;
	float3 vAtt;
	float pad;
};

struct SpotLight
{
	float4 vAmb;
	float4 vDiff;
	float4 vSpec;

	float3 vPos;
	float fRange;
	float3 vDir;
	float fSpot;

	float3 vAtt;
	float pad;
};

void ComputeDirectionalLight(Material mat, DirectionalLight L,
							 float3 normal, float3 toEye,
							 out float4 ambient,
							 out float4 diffuse,
							 out float4 specular)
{
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float3 lightVec = -L.vDir;
	ambient = mat.vAmb * L.vAmb;

	float diffuseFactor = dot(lightVec, normal);

	[flatten]
	if(diffuseFactor > 0.0f)
	{
		float3 v = reflect(-lightVec, normal);
			float specFactor = pow(max(dot(v, toEye), 0.0f), mat.vSpec.w);

		diffuse = diffuseFactor * mat.vDiff * L.vDiff;
		specular = specFactor * mat.vSpec * L.vSpec;

	}
}

void ComputePointLight(Material mat, PointLight L, float3 pos, float3 normal, float3 toEye,
					   out float4 ambient, out float4 diffuse, out float4 specular)
{
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float3 lightVec = L.vPos - pos;

	float d = length(lightVec);

	if(d > L.fRange)
	{
		return;
	}

	lightVec /= d;

	ambient = mat.vAmb * L.vAmb;

	float diffuseFactor = dot(lightVec, normal);

	[flatten]
	if(diffuseFactor > 0.0f)
	{
		float3 v = reflect(-lightVec, normal);
		float specFactor = pow(max(dot(v, toEye), 0.0f), mat.vSpec.w);

		diffuse = diffuseFactor * mat.vDiff * L.vDiff;
		specular = specFactor * mat.vSpec * L.vSpec;
	}

	float att = 1.0f / dot(L.vAtt, float3(1.0f, d, d* d));

	diffuse *= att;
	specular *= att;
}

void ComputeSpotLight(Material mat, SpotLight L, float3 pos, float3 normal, float3 toEye,
					   out float4 ambient, out float4 diffuse, out float4 specular)
{
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float3 lightVec = L.vPos - pos;

	float d = length(lightVec);

	if(d > L.fRange)
	{
		return;
	}

	lightVec /= d;

	ambient = mat.vAmb * L.vAmb;

	float diffuseFactor = dot(lightVec, normal);

	[flatten]
	if(diffuseFactor > 0.0f)
	{
		float3 v = reflect(-lightVec, normal);
		float specFactor = pow(max(dot(v, toEye), 0.0f), mat.vSpec.w);

		diffuse = diffuseFactor * mat.vDiff * L.vDiff;
		specular = specFactor * mat.vSpec * L.vSpec;
	}

	float spot = pow(max(dot(-lightVec, L.vDir), 0.0f), L.fSpot);

	float att = spot / dot(L.vAtt, float3(1.0f, d, d* d));

	ambient *= spot;
	diffuse *= att;
	specular *= att;
}