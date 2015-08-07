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
	Vertex vertices[] = 
	{
		{XMFLOAT3(-1.f, -1.f, -1.f), XMFLOAT3(0.f, 0.f, 0.f),(XMFLOAT4)(const float*)&COLOR_WHITE, XMFLOAT2(0.f, 1.f)},
		{XMFLOAT3(-1.f, 1.f, -1.f), XMFLOAT3(0.f, 0.f, 0.f),(XMFLOAT4)(const float*)&COLOR_BLACK, XMFLOAT2(0.f, 0.f)},
		{XMFLOAT3(1.f, 1.f, -1.f), XMFLOAT3(0.f, 0.f, 0.f),(XMFLOAT4)(const float*)&COLOR_RED, XMFLOAT2(1.f, 0.f)},
		{XMFLOAT3(1.f, -1.f, -1.f), XMFLOAT3(0.f, 0.f, 0.f),(XMFLOAT4)(const float*)&COLOR_GREEN, XMFLOAT2(1.f, 1.f)},
		{XMFLOAT3(-1.f, -1.f, 1.f), XMFLOAT3(0.f, 0.f, 0.f),(XMFLOAT4)(const float*)&COLOR_BLUE, XMFLOAT2(0.f, 1.f)},
		{XMFLOAT3(-1.f, 1.f, 1.f), XMFLOAT3(0.f, 0.f, 0.f),(XMFLOAT4)(const float*)&COLOR_YELLOW, XMFLOAT2(0.f, 0.f)},
		{XMFLOAT3(1.f, 1.f, 1.f), XMFLOAT3(0.f, 0.f, 0.f),(XMFLOAT4)(const float*)&COLOR_CYAN, XMFLOAT2(1.f, 0.f)},
		{XMFLOAT3(1.f, -1.f, 1.f), XMFLOAT3(0.f, 0.f, 0.f),(XMFLOAT4)(const float*)&COLOR_MAGENTA, XMFLOAT2(1.f, 1.f)},

	};

	D3D11_BUFFER_DESC desc;
	//memset(&desc, 0, sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = sizeof(Vertex) * 8;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    desc.MiscFlags = 0;
	//desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA data;

	data.pSysMem = vertices;

	if(FAILED(_DEVICE()->CreateBuffer(&desc, &data, &m_pVB)))
	{
		MessageBeep(0);
		return ;
	}
}

void CBoxGeometry::CreateIndexBuffer()
{
	UINT indices[] = 
	{
		0, 1, 2,
		0, 2, 3,

		// back face
		4, 6, 5,
		4, 7, 6,

		// left face
		4, 5, 1,
		4, 1, 0,

		// right face
		3, 2, 6,
		3, 6, 7,

		// top face
		1, 5, 6,
		1, 6, 2,

		// bottom face
		4, 0, 3, 
		4, 3, 7
	};


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

	data.pSysMem = indices;

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