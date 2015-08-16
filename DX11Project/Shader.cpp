#include "Shader.h"
#include "Device.h"

CShader::CShader(void)
	: m_pFX(NULL)
{
}


CShader::~CShader(void)
{
	Clear();
}

HRESULT CShader::Init(const LPCTSTR pFileName)
{
	if(FAILED(CreateEffect(pFileName)))
	{
		return E_FAIL;
	}

	CreateTech();

	if(FAILED(CreateInputLayout()))
	{
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CShader::CreateEffect(const LPCTSTR pFileName)
{
	DWORD shaderFlags = 0;
#if defined( DEBUG ) || defined( _DEBUG )
	shaderFlags |= D3D10_SHADER_DEBUG;
	shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif

	ID3D10Blob* pShader = NULL;
	ID3D10Blob* pErrorMsg = NULL;

	TCHAR szDir[MAX_PATH];

	GetCurrentDirectory(MAX_PATH,  szDir);

	TCHAR szPath[256];
	_tcscpy(szPath, szDir);
	_tcscat(szPath, L"\\");
	_tcscat(szPath, pFileName);

	HRESULT hr = D3DCompileFromFile(szPath, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, NULL, "fx_5_0", shaderFlags,
		0, &pShader, &pErrorMsg);

	if(pErrorMsg)
	{
		MessageBoxA(0, (char*)pErrorMsg->GetBufferPointer(), 0, 0);
		Safe_Release(pErrorMsg);
	}

	if(FAILED(hr))
	{
		MessageBeep(0);
	}

	HR(D3DX11CreateEffectFromMemory(pShader->GetBufferPointer(), pShader->GetBufferSize(),
		0, _DEVICE(), &m_pFX));

	Safe_Release(pShader);

	

	return S_OK;
}

void CShader::CreateTech()
{
	//효과 객체 생성
	ID3DX11EffectTechnique* pTech = NULL;
	for(int i = 0; i < ST_MAX; ++i)
	{
		pTech = m_pFX->GetTechniqueByIndex(i);
		if(!pTech)
			continue;

		m_vecTech.push_back(pTech);
	}
	
}



HRESULT CShader::InitInputLayout(const D3D11_INPUT_ELEMENT_DESC* pDesc, 
						const UINT& numElements,
						const TECH_TYPE& eTech,
						const PASS_TYPE& ePass)
{
	//필요한 테크닉
	ID3DX11EffectTechnique* pTech = m_vecTech[eTech];

	D3DX11_PASS_DESC passDesc;
	pTech->GetPassByIndex(ePass)->GetDesc(&passDesc);


	//input layout
	ID3D11InputLayout* pInputLayout = NULL;

	if(FAILED(_DEVICE()->CreateInputLayout(pDesc, numElements, passDesc.pIAInputSignature, 
		passDesc.IAInputSignatureSize, &pInputLayout)))
	{
		return E_FAIL;
	}

	m_vecInputLayout.push_back(pInputLayout);

	return S_OK;
}

void CShader::Clear()
{
	Safe_Release(m_pFX);
	Safe_Release_VecList(m_vecInputLayout);
}

ID3DX11EffectMatrixVariable* CShader::GetMatrix(LPCSTR pName)
{
	return m_pFX->GetVariableByName(pName)->AsMatrix();
}

ID3DX11EffectVariable*		CShader::GetValue(LPCSTR pName)
{
	return m_pFX->GetVariableByName(pName);
}

ID3DX11EffectVectorVariable* CShader::GetVector(LPCSTR pName)
{
	return m_pFX->GetVariableByName(pName)->AsVector();
}

ID3DX11EffectTechnique*		CShader::GetTech(const TECH_TYPE& eTech)
{
	return m_vecTech[eTech];
}


ID3D11InputLayout*			CShader::GetInputLayout(const INPUTLAYOUT_TYPE& eInputLaytout)
{
	return m_vecInputLayout[eInputLaytout];
}

ID3DX11EffectScalarVariable*			CShader::GetScalar(LPCSTR pName)
{
	return m_pFX->GetVariableByName(pName)->AsScalar();
}

ID3DX11EffectShaderResourceVariable*	CShader::GetShaderRes(LPCSTR pName)
{
	return m_pFX->GetVariableByName(pName)->AsShaderResource();
}