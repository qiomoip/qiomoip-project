#include "BoxGeometry.h"
#include "Device.h"
#include "Shader.h"

CBoxGeometry::CBoxGeometry(void)
{
}


CBoxGeometry::~CBoxGeometry(void)
{
	Clear();
}

void CBoxGeometry::Init()
{
	
	CreateIndexBuffer();
	CreateVertexBuffer();

	CaculateNormal();
}


void CBoxGeometry::CreateVertexBuffer()
{
	//Vertex v[] = 
	//{
	//	Vertex(XMFLOAT3(-1.f, -1.f, -1.f), XMFLOAT3(0.f, 0.f, 0.f),(XMFLOAT4)(const float*)&COLOR_WHITE, XMFLOAT2(0.5f, 1.f)),
	//	Vertex(XMFLOAT3(-1.f, 1.f, -1.f), XMFLOAT3(0.f, 0.f, 0.f),(XMFLOAT4)(const float*)&COLOR_BLACK, XMFLOAT2(0.5f, 0.5f)),
	//	Vertex(XMFLOAT3(1.f, 1.f, -1.f), XMFLOAT3(0.f, 0.f, 0.f),(XMFLOAT4)(const float*)&COLOR_RED, XMFLOAT2(1.f, 0.5f)),
	//	Vertex(XMFLOAT3(1.f, -1.f, -1.f), XMFLOAT3(0.f, 0.f, 0.f),(XMFLOAT4)(const float*)&COLOR_GREEN, XMFLOAT2(1.f, 1.f)),

	//	Vertex(XMFLOAT3(-1.f, -1.f, 1.f), XMFLOAT3(0.f, 0.f, 0.f),(XMFLOAT4)(const float*)&COLOR_BLUE, XMFLOAT2(0.f, 1.f)),
	//	Vertex(XMFLOAT3(-1.f, 1.f, 1.f), XMFLOAT3(0.f, 0.f, 0.f),(XMFLOAT4)(const float*)&COLOR_YELLOW, XMFLOAT2(0.f, 0.f)),
	//	Vertex(XMFLOAT3(1.f, 1.f, 1.f), XMFLOAT3(0.f, 0.f, 0.f),(XMFLOAT4)(const float*)&COLOR_CYAN, XMFLOAT2(1.f, 0.f)),
	//	Vertex(XMFLOAT3(1.f, -1.f, 1.f), XMFLOAT3(0.f, 0.f, 0.f),(XMFLOAT4)(const float*)&COLOR_MAGENTA, XMFLOAT2(1.f, 1.f)),

	//};

	Vertex v[24];

	float w2 = 1.f;
	float h2 = 1.f;
	float d2 = 1.f;
    
	// Fill in the front face vertex data.
	v[0] = Vertex(-w2, -h2, -d2, 0.0f, 0.0f, -1.0f,  (XMFLOAT4)(const float*)&COLOR_WHITE,0.0f, 1.0f);
	v[1] = Vertex(-w2, +h2, -d2, 0.0f, 0.0f, -1.0f,  (XMFLOAT4)(const float*)&COLOR_WHITE,0.0f, 0.0f);
	v[2] = Vertex(+w2, +h2, -d2, 0.0f, 0.0f, -1.0f,  (XMFLOAT4)(const float*)&COLOR_WHITE,1.0f, 0.0f);
	v[3] = Vertex(+w2, -h2, -d2, 0.0f, 0.0f, -1.0f,  (XMFLOAT4)(const float*)&COLOR_WHITE,1.0f, 1.0f);

	// Fill in the back face vertex data.
	v[4] = Vertex(-w2, -h2, +d2, 0.0f, 0.0f, 1.0f, (XMFLOAT4)(const float*)&COLOR_WHITE, 1.0f, 1.0f);
	v[5] = Vertex(+w2, -h2, +d2, 0.0f, 0.0f, 1.0f, (XMFLOAT4)(const float*)&COLOR_WHITE, 0.0f, 1.0f);
	v[6] = Vertex(+w2, +h2, +d2, 0.0f, 0.0f, 1.0f, (XMFLOAT4)(const float*)&COLOR_WHITE, 0.0f, 0.0f);
	v[7] = Vertex(-w2, +h2, +d2, 0.0f, 0.0f, 1.0f, (XMFLOAT4)(const float*)&COLOR_WHITE, 1.0f, 0.0f);

	// Fill in the top face vertex data.
	v[8]  = Vertex(-w2, +h2, -d2, 0.0f, 1.0f, 0.0f, (XMFLOAT4)(const float*)&COLOR_WHITE,0.0f, 1.0f);
	v[9]  = Vertex(-w2, +h2, +d2, 0.0f, 1.0f, 0.0f, (XMFLOAT4)(const float*)&COLOR_WHITE,0.0f, 0.0f);
	v[10] = Vertex(+w2, +h2, +d2, 0.0f, 1.0f, 0.0f,(XMFLOAT4)(const float*)&COLOR_WHITE, 1.0f, 0.0f);
	v[11] = Vertex(+w2, +h2, -d2, 0.0f, 1.0f, 0.0f, (XMFLOAT4)(const float*)&COLOR_WHITE,1.0f, 1.0f);

	// Fill in the bottom face vertex data.
	v[12] = Vertex(-w2, -h2, -d2, 0.0f, -1.0f, 0.0f,(XMFLOAT4)(const float*)&COLOR_WHITE, 1.0f, 1.0f);
	v[13] = Vertex(+w2, -h2, -d2, 0.0f, -1.0f, 0.0f, (XMFLOAT4)(const float*)&COLOR_WHITE,0.0f, 1.0f);
	v[14] = Vertex(+w2, -h2, +d2, 0.0f, -1.0f, 0.0f,(XMFLOAT4)(const float*)&COLOR_WHITE, 0.0f, 0.0f);
	v[15] = Vertex(-w2, -h2, +d2, 0.0f, -1.0f, 0.0f, (XMFLOAT4)(const float*)&COLOR_WHITE,1.0f, 0.0f);

	// Fill in the left face vertex data.
	v[16] = Vertex(-w2, -h2, +d2, -1.0f, 0.0f, 0.0f,(XMFLOAT4)(const float*)&COLOR_WHITE,0.0f, 1.0f);
	v[17] = Vertex(-w2, +h2, +d2, -1.0f, 0.0f, 0.0f,(XMFLOAT4)(const float*)&COLOR_WHITE,0.0f, 0.0f);
	v[18] = Vertex(-w2, +h2, -d2, -1.0f, 0.0f, 0.0f,(XMFLOAT4)(const float*)&COLOR_WHITE,1.0f, 0.0f);
	v[19] = Vertex(-w2, -h2, -d2, -1.0f, 0.0f, 0.0f,(XMFLOAT4)(const float*)&COLOR_WHITE,1.0f, 1.0f);

	// Fill in the right face vertex data.
	v[20] = Vertex(+w2, -h2, -d2, 1.0f, 0.0f, 0.0f,(XMFLOAT4)(const float*)&COLOR_WHITE, 0.0f, 1.0f);
	v[21] = Vertex(+w2, +h2, -d2, 1.0f, 0.0f, 0.0f,(XMFLOAT4)(const float*)&COLOR_WHITE, 0.0f, 0.0f);
	v[22] = Vertex(+w2, +h2, +d2, 1.0f, 0.0f, 0.0f,(XMFLOAT4)(const float*)&COLOR_WHITE, 1.0f, 0.0f);
	v[23] = Vertex(+w2, -h2, +d2, 1.0f, 0.0f, 0.0f,(XMFLOAT4)(const float*)&COLOR_WHITE, 1.0f, 1.0f);

	D3D11_BUFFER_DESC desc;
	//memset(&desc, 0, sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = sizeof(Vertex) * 8;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    desc.MiscFlags = 0;
	//desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA data;

	data.pSysMem = v;

	if(FAILED(_DEVICE()->CreateBuffer(&desc, &data, &m_pVB)))
	{
		MessageBeep(0);
		return ;
	}
}

void CBoxGeometry::CreateIndexBuffer()
{
	//UINT i[] = 
	//{
	//	0, 1, 2,
	//	0, 2, 3,

	//	// back face
	//	4, 6, 5,
	//	4, 7, 6,

	//	// left face
	//	4, 5, 1,
	//	4, 1, 0,

	//	// right face
	//	3, 2, 6,
	//	3, 6, 7,

	//	// top face
	//	1, 5, 6,
	//	1, 6, 2,

	//	// bottom face
	//	4, 0, 3, 
	//	4, 3, 7
	//};

	UINT i[36];

	// Fill in the front face index data
	i[0] = 0; i[1] = 1; i[2] = 2;
	i[3] = 0; i[4] = 2; i[5] = 3;

	// Fill in the back face index data
	i[6] = 4; i[7]  = 5; i[8]  = 6;
	i[9] = 4; i[10] = 6; i[11] = 7;

	// Fill in the top face index data
	i[12] = 8; i[13] =  9; i[14] = 10;
	i[15] = 8; i[16] = 10; i[17] = 11;

	// Fill in the bottom face index data
	i[18] = 12; i[19] = 13; i[20] = 14;
	i[21] = 12; i[22] = 14; i[23] = 15;

	// Fill in the left face index data
	i[24] = 16; i[25] = 17; i[26] = 18;
	i[27] = 16; i[28] = 18; i[29] = 19;

	// Fill in the right face index data
	i[30] = 20; i[31] = 21; i[32] = 22;
	i[33] = 20; i[34] = 22; i[35] = 23;

	//읽기 위해서 stagind, read로 만들려고 했으나
	//그렇게 하면 버퍼 생성이 안 되니까
	//일단 읽기용이더라도 dynamic, write로 생성...

	D3D11_BUFFER_DESC desc;
	//memset(&desc, 0, sizeof(D3D11_BUFFER_DESC));
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.ByteWidth = sizeof(UINT) * 36;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    desc.MiscFlags = 0;
	desc.StructureByteStride = 0;


	D3D11_SUBRESOURCE_DATA data;
	memset(&data, 0, sizeof(D3D11_SUBRESOURCE_DATA));

	data.pSysMem = i;

	if(FAILED(_DEVICE()->CreateBuffer(&desc, &data, &m_pIB)))
	{
		MessageBeep(0);
		return ;
	}
}

void CBoxGeometry::Render(CShader* pShader, const TECH_TYPE& eTech, const UINT& uPass)
{
	UINT uSize =  sizeof(Vertex);
	UINT offset = 0;

	ID3D11InputLayout* pInputLayout = pShader->GetInputLayout(m_eInputLayout);


	_ICONTEXT()->IASetInputLayout(pInputLayout);
	_ICONTEXT()->IASetVertexBuffers(0, 1, &m_pVB, &uSize, &offset);

	_ICONTEXT()->IASetIndexBuffer(m_pIB, DXGI_FORMAT_R32_UINT, 0);

	ID3DX11EffectTechnique* pTech = pShader->GetTech(eTech);

	
	pTech->GetPassByIndex(uPass)->Apply(0, _ICONTEXT());
	_ICONTEXT()->DrawIndexed(36, 0, 0);
	
}

void CBoxGeometry::CaculateNormal()
{
	//버텍스, 인덱스 버퍼 lock
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	D3D11_MAPPED_SUBRESOURCE mappedRes;
	
	_ICONTEXT()->Map(m_pVB, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &mappedResource);
	_ICONTEXT()->Map(m_pIB, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &mappedRes);
	
	Vertex* pVtx = (Vertex*)mappedResource.pData;
	UINT* pIdx = (UINT*)mappedRes.pData;
	
	for(int i = 0; i < 12; ++i)
	{
		UINT idx[3] = {0};
		idx[0] = pIdx[i * 3 + 0];
		idx[1] = pIdx[i * 3 + 1];
		idx[2] = pIdx[i * 3 + 2];

		Vertex v[3];
		v[0] = pVtx[idx[0]];
		v[1] = pVtx[idx[1]];
		v[2] = pVtx[idx[2]];

		//노멀 벡터 계산
		
		//면 법선 계산
		XMVECTOR a = XMLoadFloat3(&v[0].vPos);
		XMVECTOR b = XMLoadFloat3(&v[1].vPos);
		XMVECTOR c = XMLoadFloat3(&v[2].vPos);

		XMVECTOR e0 = b - a;
		XMVECTOR e1 = c - a;
		e0 = XMVector3Normalize(e0);
		e1 = XMVector3Normalize(e1);
		XMVECTOR vCross = XMVector3Cross(e0, e1);
		vCross = XMVector3Normalize(vCross);

		XMVECTOR vAdd[3];

		vAdd[0] = vCross + XMLoadFloat3(&pVtx[idx[0]].vNormal);
		vAdd[1] = vCross + XMLoadFloat3(&pVtx[idx[1]].vNormal);
		vAdd[2] = vCross + XMLoadFloat3(&pVtx[idx[2]].vNormal);

		XMStoreFloat3(&pVtx[idx[0]].vNormal, vAdd[0]);
		XMStoreFloat3(&pVtx[idx[1]].vNormal, vAdd[1]);
		XMStoreFloat3(&pVtx[idx[2]].vNormal, vAdd[2]);
	}

	for(int i = 0; i < 8; ++i)
	{
		XMVECTOR vCrossNormal = XMLoadFloat3(&pVtx[i].vNormal);
		vCrossNormal = XMVector3Normalize(vCrossNormal);
		XMStoreFloat3(&pVtx[i].vNormal, vCrossNormal);
	}

	_ICONTEXT()->Unmap(m_pVB, 0);
	_ICONTEXT()->Unmap(m_pIB, 0);
}

void CBoxGeometry::Clear()
{
	Safe_Release(m_pIB);
	Safe_Release(m_pVB);
}