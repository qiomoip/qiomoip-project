#pragma once
#include "Singleton.h"

class CDevice
	: public CSingleton<CDevice>
{
	friend CSingleton;

private:
	ID3D11Device*			m_pDevice;			//d3d11 ����̽� ��ġ (��� ���� ����, �ڿ� �Ҵ�)
	ID3D11DeviceContext*	m_pImmediateContext;//��ġ ����	(���� ��� ����, �ڿ��� �׷��� ���������ο� ����, GPU�� ������ ������ ����� �����ϴ� �� ����)
	IDXGISwapChain*			m_pSwapChain;		//������ ��ȯ�� ���� ��ȯ�罽
	ID3D11Texture2D*		m_pDepthStencilBuffer;//����, ���ٽ� ���۸� ���� 2���� �ؽ�ó
	ID3D11RenderTargetView*	m_pRendeTargetView;	//���� ��� ��(�ڿ��� ���� �並 �����ϰ�, �� �並 ���������ο� ���� ��)
	ID3D11DepthStencilView*	m_pDepthStencilView;//����, ���ٽ� ���� ��	
	D3D11_VIEWPORT			m_ScreenViewport;	//����Ʈ (����� �׷��ְ��� �ϴ� �ĸ� ������ �κ� ���簢�� ����)
	//4x mssa ��� ����
	bool				m_bEnable4xMssa;

	D3D_DRIVER_TYPE		m_DriverType;	//������ ����
	UINT			m_u4XMSAAQuality;//4x msaa�� ǰ�� ����

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

