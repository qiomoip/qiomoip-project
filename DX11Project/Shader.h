#pragma once
#include "include.h"

class CShader
{
private:
	ID3DX11Effect* m_pFX;
	vector<ID3DX11EffectTechnique*> m_vecTech;
	vector<ID3D11InputLayout*>		m_vecInputLayout;

public:
	HRESULT Init(const LPCTSTR pFileName);
	HRESULT CreateEffect(const LPCTSTR pFileName);
	void CreateTech();
	HRESULT CreateInputLayout();
	HRESULT InitInputLayout(const D3D11_INPUT_ELEMENT_DESC* pDesc,
						const UINT& numElements,
						const TECH_TYPE& eTech,
						const PASS_TYPE& ePass);
	void Clear();

public:
	ID3DX11EffectMatrixVariable* GetMatrix(LPCSTR pName);
	ID3DX11EffectVariable*		GetValue(LPCSTR pName);
	ID3DX11EffectVectorVariable* GetVector(LPCSTR pName);
	ID3DX11EffectTechnique*		GetTech(const TECH_TYPE& eTech);
	ID3D11InputLayout*			GetInputLayout(const INPUTLAYOUT_TYPE& eInputLaytout);
	ID3DX11EffectShaderResourceVariable*	GetShaderRes(LPCSTR pName);


public:
	CShader(void);
	~CShader(void);
};

