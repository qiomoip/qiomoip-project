#include "Terrain.h"
#include "GeometryGenerator.h"
#include "Device.h"
#include "Shader.h"
#include "ShaderManager.h"

CTerrain::CTerrain(void) 
	:mVB(0), mIB(0), /*mFX(0), mTech(0),
	mfxWorldViewProj(0),*/ mGridIndexCount(0)
{}

CTerrain::~CTerrain(void)
{
	Safe_Release(mVB);
	Safe_Release(mIB);
	//Safe_Release(mFX);
	//Safe_Release(mInputLayout);
}

void CTerrain::Init()
{	
	BuildGeometryBuffers();
	//BuildFX();
	//BuildVertexLayout();
}

void CTerrain::Render(CShader* pShader, const TECH_TYPE& eTech, const UINT& uPass)
{
	/*_ICONTEXT()->ClearRenderTargetView(
		mRenderTargetView, reinterpret_cast<const float*>(&Colors::LightSteelBlue));
	_ICONTEXT()->ClearDepthStencilView(
		mDepthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);*/

	ID3D11InputLayout* pInputLayout = pShader->GetInputLayout(m_eInputLayout);

	_ICONTEXT()->IASetInputLayout(pInputLayout);
    _ICONTEXT()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
 
	UINT stride = sizeof(Vertex);
    UINT offset = 0;
    _ICONTEXT()->IASetVertexBuffers(0, 1, &mVB, &stride, &offset);
	_ICONTEXT()->IASetIndexBuffer(mIB, DXGI_FORMAT_R32_UINT, 0);

	// Set constants
	
	/*XMMATRIX view  = XMLoadFloat4x4(&mView);
	XMMATRIX proj  = XMLoadFloat4x4(&mProj);
	XMMATRIX world = XMLoadFloat4x4(&mGridWorld);
	XMMATRIX worldViewProj = world*view*proj;*/
	ID3DX11EffectTechnique* pTech = pShader->GetTech(eTech);

	
	pTech->GetPassByIndex(uPass)->Apply(0, _ICONTEXT());
	_ICONTEXT()->DrawIndexed(mGridIndexCount, 0, 0);
  //  D3DX11_TECHNIQUE_DESC techDesc;
  //  mTech->GetDesc( &techDesc );
  //  for(UINT p = 0; p < techDesc.Passes; ++p)
  //  {
		//// Draw the grid.
		////mfxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProj));
		//mTech->GetPassByIndex(p)->Apply(0, _ICONTEXT());
		//_ICONTEXT()->DrawIndexed(mGridIndexCount, 0, 0);
  //  }
}

void CTerrain::BuildGeometryBuffers()
{	
	GeometryGenerator::MeshData grid;
 
	GeometryGenerator geoGen;

	geoGen.CreateGrid(10.0f, 10.0f, 50, 50, grid);

	mGridIndexCount = grid.Indices.size();

	//
	// Extract the vertex elements we are interested and apply the height function to
	// each vertex.  In addition, color the vertices based on their height so we have
	// sandy looking beaches, grassy low hills, and snow mountain peaks.
	//

	std::vector<Vertex> vertices(grid.Vertices.size());
	for(size_t i = 0; i < grid.Vertices.size(); ++i)
	{
		XMFLOAT3 p = grid.Vertices[i].Position;

		p.y = 0.f/*GetHeight(p.x, p.z)*/;

		vertices[i].vPos   = p;
		
		// Color the vertex based on its height.
		if( p.y < -10.0f )
		{
			// Sandy beach color.
			vertices[i].vColor = XMFLOAT4(1.0f, 0.96f, 0.62f, 1.0f);
		}
		else if( p.y < 5.0f )
		{
			// Light yellow-green.
			vertices[i].vColor = XMFLOAT4(0.48f, 0.77f, 0.46f, 1.0f);
		}
		else if( p.y < 12.0f )
		{
			// Dark yellow-green.
			vertices[i].vColor = XMFLOAT4(0.1f, 0.48f, 0.19f, 1.0f);
		}
		else if( p.y < 20.0f )
		{
			// Dark brown.
			vertices[i].vColor = XMFLOAT4(0.45f, 0.39f, 0.34f, 1.0f);
		}
		else
		{
			// White snow.
			vertices[i].vColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

    D3D11_BUFFER_DESC vbd;
    vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex) * grid.Vertices.size();
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vbd.CPUAccessFlags = 0;
    vbd.MiscFlags = 0;
    D3D11_SUBRESOURCE_DATA vinitData;
    vinitData.pSysMem = &vertices[0];
    HR(_DEVICE()->CreateBuffer(&vbd, &vinitData, &mVB));

	//
	// Pack the indices of all the meshes into one index buffer.
	//

	D3D11_BUFFER_DESC ibd;
    ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * mGridIndexCount;
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd.CPUAccessFlags = 0;
    ibd.MiscFlags = 0;
    D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &grid.Indices[0];
    HR(_DEVICE()->CreateBuffer(&ibd, &iinitData, &mIB));
}

void CTerrain::BuildFX()
{	
	//_SINGLE(CShaderManager)->CreateShader( _T("Color"), _T("color.fxo") );
	/*std::ifstream fin("fx/color.fxo", std::ios::binary);

	fin.seekg(0, std::ios_base::end);
	int size = (int)fin.tellg();
	fin.seekg(0, std::ios_base::beg);
	std::vector<char> compiledShader(size);

	fin.read(&compiledShader[0], size);
	fin.close();
	
	HR(D3DX11CreateEffectFromMemory(&compiledShader[0], size, 
		0, _DEVICE(), &mFX));

	mTech    = mFX->GetTechniqueByName("ColorTech");
	mfxWorldViewProj = mFX->GetVariableByName("gWorldViewProj")->AsMatrix();*/
}

void CTerrain::BuildVertexLayout()
{
	//// Create the vertex input layout.
	//D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
	//{
	//	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	//	{"COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	//};

	//// Create the input layout
 //   D3DX11_PASS_DESC passDesc;
 //   mTech->GetPassByIndex(0)->GetDesc(&passDesc);
	//HR(_DEVICE()->CreateInputLayout(vertexDesc, 2, passDesc.pIAInputSignature, 
	//	passDesc.IAInputSignatureSize, &mInputLayout));
}
