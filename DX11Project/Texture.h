#pragma once
#include "include.h"

class CShader;

class CTexture
{
private:
	TEXINFO	m_tTexInfo;

public:
	HRESULT CreateTexture(LPCWSTR pFileName, LPCWSTR pFileType);
	HRESULT CreateShaderResourceViewFromFile(LPCWSTR pFileName, LPCWSTR pFileType,
		ID3D11ShaderResourceView** pResView);

	void SetTexture(CShader* pShader);

public:
	CTexture(void);
	~CTexture(void);
};

