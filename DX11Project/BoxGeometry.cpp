#include "BoxGeometry.h"
#include "Device.h"
#include "Shader.h"
#include "GeometryGenerator.h"
#include "Math.h"

const int VERTEXCOUNT = 24;
const int INDEXCOUNT = 36;

CBoxGeometry::CBoxGeometry(void)
{
}


CBoxGeometry::~CBoxGeometry(void)
{
	Clear();
}

void CBoxGeometry::Init()
{	
	GeometryGenerator::MeshData box;

	CreateVertexBuffer(box);
	CreateIndexBuffer(box);

//	CaculateNormal();
}


void CBoxGeometry::CreateVertexBuffer(GeometryGenerator::MeshData& box)
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

	//GeometryGenerator::MeshData box;

	GeometryGenerator geoGen;
	geoGen.CreateBox(1.0f, 1.0f, 1.0f, box);

	std::vector<VERTEXTEX> vertices(VERTEXCOUNT);

	UINT k = 0;
	for(size_t i = 0; i < box.Vertices.size(); ++i, ++k)
	{
		vertices[k].vPos    = box.Vertices[i].Position;
		vertices[k].vNormal = box.Vertices[i].Normal;
		vertices[k].vTex    = box.Vertices[i].TexC;
	}

    D3D11_BUFFER_DESC vbd;
	vbd.ByteWidth = sizeof(VERTEXTEX) * VERTEXCOUNT;
	vbd.Usage = D3D11_USAGE_DYNAMIC;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    vbd.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA vinitData;
    vinitData.pSysMem = &vertices[0];
	HR(_DEVICE()->CreateBuffer(&vbd, &vinitData, &m_pVB));

}

void CBoxGeometry::CreateIndexBuffer(GeometryGenerator::MeshData& box)
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


	std::vector<UINT> indices;
	indices.insert(indices.end(), box.Indices.begin(), box.Indices.end());

	D3D11_BUFFER_DESC ibd;
    ibd.Usage = D3D11_USAGE_DYNAMIC;
	ibd.ByteWidth = sizeof(UINT) * INDEXCOUNT;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;
    D3D11_SUBRESOURCE_DATA iinitData;
    iinitData.pSysMem = &indices[0];
    HR(_DEVICE()->CreateBuffer(&ibd, &iinitData, &m_pIB));

}

void CBoxGeometry::Render(CShader* pShader, const TECH_TYPE& eTech, const UINT& uPass)
{
	UINT uSize =  sizeof(VERTEXTEX);
	UINT offset = 0;

	ID3D11InputLayout* pInputLayout = pShader->GetInputLayout(m_eInputLayout);

	_ICONTEXT()->IASetInputLayout(pInputLayout);
	_ICONTEXT()->IASetVertexBuffers(0, 1, &m_pVB, &uSize, &offset);

	_ICONTEXT()->IASetIndexBuffer(m_pIB, DXGI_FORMAT_R32_UINT, 0);

	ID3DX11EffectTechnique* pTech = pShader->GetTech(eTech);

	
	pTech->GetPassByIndex(uPass)->Apply(0, _ICONTEXT());
	_ICONTEXT()->DrawIndexed(INDEXCOUNT, 0, 0);
	
}
//
//void CBoxGeometry::CaculateNormal()
//{
//	//버텍스, 인덱스 버퍼 lock
//	D3D11_MAPPED_SUBRESOURCE mappedResource;
//	D3D11_MAPPED_SUBRESOURCE mappedRes;
//	
//	_ICONTEXT()->Map(m_pVB, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &mappedResource);
//	_ICONTEXT()->Map(m_pIB, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &mappedRes);
//	
//	VERTEXTEX* pVtx = (VERTEXTEX*)mappedResource.pData;
//	UINT* pIdx = (UINT*)mappedRes.pData;
//	
//	for(int i = 0; i < 12; ++i)
//	{
//		UINT idx[3] = {0};
//		idx[0] = pIdx[i * 3 + 0];
//		idx[1] = pIdx[i * 3 + 1];
//		idx[2] = pIdx[i * 3 + 2];
//
//		VERTEXTEX v[3];
//		v[0] = pVtx[idx[0]];
//		v[1] = pVtx[idx[1]];
//		v[2] = pVtx[idx[2]];
//
//		//노멀 벡터 계산
//		XMVECTOR	vCross = _SINGLE(CMath)->CaculateNormal(XMLoadFloat3(&v[0].vPos), XMLoadFloat3(&v[1].vPos), XMLoadFloat3(&v[2].vPos));
//		
//		////면 법선 계산
//		//XMVECTOR a = XMLoadFloat3(&v[0].vPos);
//		//XMVECTOR b = XMLoadFloat3(&v[1].vPos);
//		//XMVECTOR c = XMLoadFloat3(&v[2].vPos);
//
//		//XMVECTOR e0 = b - a;
//		//XMVECTOR e1 = c - a;
//		//e0 = XMVector3Normalize(e0);
//		//e1 = XMVector3Normalize(e1);
//		//XMVECTOR vCross = XMVector3Cross(e0, e1);
//		//vCross = XMVector3Normalize(vCross);
//
//		XMVECTOR vAdd[3];
//
//		vAdd[0] = vCross + XMLoadFloat3(&pVtx[idx[0]].vNormal);
//		vAdd[1] = vCross + XMLoadFloat3(&pVtx[idx[1]].vNormal);
//		vAdd[2] = vCross + XMLoadFloat3(&pVtx[idx[2]].vNormal);
//
//		XMStoreFloat3(&pVtx[idx[0]].vNormal, vAdd[0]);
//		XMStoreFloat3(&pVtx[idx[1]].vNormal, vAdd[1]);
//		XMStoreFloat3(&pVtx[idx[2]].vNormal, vAdd[2]);
//	}
//
//	for(int i = 0; i < 8; ++i)
//	{
//		XMVECTOR vCrossNormal = XMLoadFloat3(&pVtx[i].vNormal);
//		vCrossNormal = XMVector3Normalize(vCrossNormal);
//		XMStoreFloat3(&pVtx[i].vNormal, vCrossNormal);
//	}
//
//	_ICONTEXT()->Unmap(m_pVB, 0);
//	_ICONTEXT()->Unmap(m_pIB, 0);
//}

void CBoxGeometry::Clear()
{
	Safe_Release(m_pIB);
	Safe_Release(m_pVB);
}