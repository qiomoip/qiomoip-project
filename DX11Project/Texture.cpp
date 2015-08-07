#include "Texture.h"
#include "Device.h"
#include "Shader.h"

CTexture::CTexture(void)
{
	memset(&m_tTexInfo, 0, sizeof(m_tTexInfo));
}


CTexture::~CTexture(void)
{
	Safe_Release(m_tTexInfo.pShaderRes);
	Safe_Release(m_tTexInfo.pTex);

}

HRESULT CTexture::CreateTexture(LPCWSTR pFileName, LPCWSTR pFileType)
{
	CreateShaderResourceViewFromFile(pFileName, pFileType, &m_tTexInfo.pShaderRes);
	return S_OK;
}

HRESULT CTexture::CreateShaderResourceViewFromFile(LPCWSTR pFileName, LPCWSTR pFileType,
		ID3D11ShaderResourceView** pResView)
{
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
			hr = CreateShaderResourceView( 
				_DEVICE(), 
				pScratchImage->GetImages(), 
				pScratchImage->GetImageCount(), 
				imageMetadata, 
				pResView );
		}

		delete pScratchImage;

		return hr;
	return S_OK;
}

void CTexture::SetTexture(CShader* pShader)
{
	pShader->GetShaderRes("g_texDifuseMap")->SetResource(m_tTexInfo.pShaderRes);
}