#pragma once
#include "include.h"

class CShader;
class CTimer;

class CTexture
{
private:
	vector<TEXINFO*>	m_vecTexInfo;
	int					m_iFrame;
	int					m_iMaxCount;
	bool				m_bMultiTexture;
	
	CTimer*				m_pTimer;
	float				m_fElapsedTime;
public:
	HRESULT CreateTexture(const LPCWSTR pFileName, const LPCWSTR pFileType, const bool& bMulti = false);
	TEXINFO* CreateShaderResourceViewFromFile(LPCWSTR pFileName, LPCWSTR pFileType, const int& idx = 0);

	void SetTexture(CShader* pShader);
	void AddFrame();
	void ResetFrame();
	int GetTextureCnt() const;
	const int& GetCurFrame() const;

public:
	CTexture(void);
	~CTexture(void);
};

