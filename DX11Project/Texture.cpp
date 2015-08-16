#include "Texture.h"
#include "Device.h"
#include "Shader.h"

#include "Timer.h"
#include "MainWnd.h"

CTexture::CTexture(void)
	: m_iFrame(0)
	, m_pTimer(NULL)
	, m_fElapsedTime(0.f)
	, m_iMaxCount(0)
	, m_pShaderTexName(NULL)
{
	m_vecTexInfo.reserve(10);
}


CTexture::~CTexture(void)
{
	for(vector<TEXINFO*>::iterator iter = m_vecTexInfo.begin(); iter != m_vecTexInfo.end(); ++iter)
	{
		Safe_Release((*iter)->pShaderRes);
//		Safe_Release((*iter)->pTex);
		Safe_Delete((*iter));
	}

	Safe_Delete(m_pTimer);

}

HRESULT CTexture::CreateTexture(const LPCWSTR pFileName, const LPCWSTR pFileType, const bool& bMulti)
{
	m_bMultiTexture = bMulti;
	if(m_bMultiTexture)
	{
		TEXINFO* pTexInfo = NULL;

		while(true)
		{
			//문자열 합치기
			TCHAR szFileName[MAX_PATH];
			_tcscpy(szFileName, pFileName);

			TCHAR szRet[5] = { 0 }; // "10"의 NULL 처리를 위한 3 count
			_stprintf_s(szRet, _countof(szRet), _T("%d"), m_iMaxCount); // Buffer overflow 방지를 위한 가급적 safe 함수를 사용하자.

			_tcscat(szFileName, szRet);
			_tcscat(szFileName, pFileType);

			pTexInfo = CreateShaderResourceViewFromFile(szFileName, pFileType, m_iMaxCount);
			if(!pTexInfo)
			{
				break;
			}
			m_vecTexInfo.push_back(pTexInfo);
			++m_iMaxCount;
		}
		m_pTimer = new CTimer();
		m_pTimer->Init();
		m_pTimer->Reset();
	}

	else
	{
		TEXINFO* pTexInfo = CreateShaderResourceViewFromFile(pFileName, pFileType);
		if(!pTexInfo)
		{
			return E_FAIL;
		}
		m_vecTexInfo.push_back(pTexInfo);
	}
	
	return S_OK;
}

TEXINFO* CTexture::CreateShaderResourceViewFromFile(LPCWSTR pFileName, LPCWSTR pFileType, const int& idx)
{
		TEXINFO* pTexInfo = NULL;

		TexMetadata imageMetadata;
		ScratchImage* pScratchImage = new ScratchImage();

		
		HRESULT hr;
		if ( _wcsicmp( pFileType, L".dds" ) == 0 )
		{
			hr = LoadFromDDSFile( pFileName, DDS_FLAGS_NONE, &imageMetadata, *pScratchImage );
		}
		else if ( _wcsicmp( pFileType, L".tga" ) == 0 )
		{
			hr = LoadFromTGAFile( pFileName, &imageMetadata, *pScratchImage );
		}
		else
		{
			hr = LoadFromWICFile( pFileName, WIC_FLAGS_NONE, &imageMetadata, *pScratchImage );
		}

		if( SUCCEEDED(hr) )
		{
			pTexInfo = new TEXINFO;
			//pTexInfo->pTex = NULL;
			pTexInfo->strTextureName = pFileName;

			hr = CreateShaderResourceView( 
				_DEVICE(), 
				pScratchImage->GetImages(), 
				pScratchImage->GetImageCount(), 
				imageMetadata, 
				&pTexInfo->pShaderRes );

			pTexInfo->iFrame = idx;
		}

		delete pScratchImage;

		return pTexInfo;
}

void CTexture::SetTexture(CShader* pShader)
{
	if(m_bMultiTexture)
	{
		m_pTimer->Tick();

		m_pTimer->CalculateFrameStats(_SINGLE(CMainWnd)->GetCaption(), _SINGLE(CMainWnd)->GetMainWnd());
		float fDeltaTime = m_pTimer->GetDeltaTime();

		m_fElapsedTime += fDeltaTime;

		if(m_fElapsedTime > 0.03f)
		{
			if(m_iFrame >= m_iMaxCount - 1)
			{
				ResetFrame();
			}
			else
				AddFrame();
			m_fElapsedTime = 0.f;
		}

	}

	//if(m_iFrame >= m_iMaxCount - 1)
	//{
	//	m_iFrame = 120;
	//}
	pShader->GetShaderRes(m_pShaderTexName)->SetResource(m_vecTexInfo[m_iFrame]->pShaderRes);
}

void CTexture::SetShaderTextureName(const LPCSTR pShaderTexName)
{
	m_pShaderTexName = pShaderTexName;
}

void CTexture::AddFrame()
{
	++m_iFrame;
}

void CTexture::ResetFrame()
{
	m_iFrame = 0;
}

int CTexture::GetTextureCnt() const
{
	return m_vecTexInfo.size();
}

const int& CTexture::GetCurFrame() const
{
	return m_iFrame;
}