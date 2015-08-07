#pragma once
#include "Singleton.h"

class CDevice
	: public CSingleton<CDevice>
{
	friend CSingleton;

private:
	ID3D11Device*			m_pDevice;			//d3d11 디바이스 장치 (기능 지원 점검, 자원 할당)
	ID3D11DeviceContext*	m_pImmediateContext;//장치 문맥	(렌더 대상 설정, 자원을 그래픽 파이프라인에 묶고, GPU가 수행할 렌더링 명령을 지시하는 데 쓰임)
	IDXGISwapChain*			m_pSwapChain;		//페이지 전환을 위한 교환사슬
	ID3D11Texture2D*		m_pDepthStencilBuffer;//깊이, 스텐실 버퍼를 위한 2차원 텍스처
	ID3D11RenderTargetView*	m_pRendeTargetView;	//렌더 대상 뷰(자원에 대한 뷰를 생성하고, 이 뷰를 파이프라인에 묶는 것)
	ID3D11DepthStencilView*	m_pDepthStencilView;//깊이, 스텐실 버퍼 뷰	
	D3D11_VIEWPORT			m_ScreenViewport;	//뷰포트 (장면을 그려넣고자 하는 후면 버퍼의 부분 직사각형 영역)
	//4x mssa 사용 여부
	bool				m_bEnable4xMssa;

	D3D_DRIVER_TYPE		m_DriverType;	//구동기 종류
	UINT			m_u4XMSAAQuality;//4x msaa의 품질 수준

public:
	ID3D11Device*		GetDevice() const;
	ID3D11DeviceContext* GetContext() const;
	bool					Init(const HWND& hWnd, const int& iWidth, const int& iHeight);
	void					OnResize(const int& iWidth, const int& iHeight);
	void					BeginRender();
	void					EndRender();

	void					Clear();

private:
	CDevice(void);
	~CDevice(void);
};

