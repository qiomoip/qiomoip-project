#include "Device.h"

CDevice::CDevice(void)
	:m_pDevice(NULL),			
	m_pImmediateContext(NULL),
	m_pSwapChain(NULL),		
	m_pDepthStencilBuffer(NULL),
	m_pRendeTargetView(NULL),	
	m_pDepthStencilView(NULL),
	m_u4XMSAAQuality(0),
	m_DriverType(D3D_DRIVER_TYPE_HARDWARE),	
	m_bEnable4xMssa(false)
{
	memset(&m_ScreenViewport, 0, sizeof(D3D11_VIEWPORT));
}


CDevice::~CDevice(void)
{
	Clear();
}

ID3D11Device*		CDevice::GetDevice() const
{
	return m_pDevice;
}

ID3D11DeviceContext* CDevice::GetContext() const
{
	return m_pImmediateContext;
}

bool CDevice::Init(const HWND& hWnd, const int& iWidth, const int& iHeight)
{
	UINT uDeivceFlag = 0;
#if defined(DEBUG) || defined(_DEBUG)
	uDeivceFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevel;
	HRESULT hr = D3D11CreateDevice(0, m_DriverType, 0, uDeivceFlag,
		0, 0, D3D11_SDK_VERSION, &m_pDevice,
		&featureLevel, &m_pImmediateContext);

	if( FAILED(hr) )
	{
		MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
		return false;
	}

	if( featureLevel != D3D_FEATURE_LEVEL_11_0 )
	{
		MessageBox(0, L"Direct3D Feature Level 11 unsupported.", 0, 0);
		return false;
	}

	HR(m_pDevice->CheckMultisampleQualityLevels(
		DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_u4XMSAAQuality));
	assert(m_u4XMSAAQuality > 0);



	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width  = iWidth;
	sd.BufferDesc.Height = iHeight;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	if(m_bEnable4xMssa)
	{
		sd.SampleDesc.Count = 4;
		sd.SampleDesc.Quality = m_u4XMSAAQuality - 1;
	}

	else
	{
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
	}

	sd.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount  = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed     = true;
	sd.SwapEffect   = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags        = 0;

	// To correctly create the swap chain, we must use the IDXGIFactory that was
	// used to create the device.  If we tried to use a different IDXGIFactory instance
	// (by calling CreateDXGIFactory), we get an error: "IDXGIFactory::CreateSwapChain: 
	// This function is being called with a device from a different IDXGIFactory."

	IDXGIDevice* dxgiDevice = 0;
	HR(m_pDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));
	      
	IDXGIAdapter* dxgiAdapter = 0;
	HR(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));

	IDXGIFactory* dxgiFactory = 0;
	HR(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory));

	HR(dxgiFactory->CreateSwapChain(m_pDevice, &sd, &m_pSwapChain));
	
	Safe_Release(dxgiDevice);
	Safe_Release(dxgiAdapter);
	Safe_Release(dxgiFactory);

	// The remaining steps that need to be carried out for d3d creation
	// also need to be executed every time the window is resized.  So
	// just call the OnResize method here to avoid code duplication.
	
	OnResize(iWidth, iHeight);

	return true;
}

void CDevice::OnResize(const int& iWidth, const int& iHeight)
{
	assert(m_pImmediateContext);
	assert(m_pDevice);
	assert(m_pSwapChain);

	Safe_Release(m_pRendeTargetView);
	Safe_Release(m_pDepthStencilView);
	Safe_Release(m_pDepthStencilBuffer);

	HR(m_pSwapChain->ResizeBuffers(1, iWidth, iHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0));
	
	ID3D11Texture2D* pBackBuffer;

	HR(m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer)));

//	Safe_Release(m_pSwapChain);

	HR(m_pDevice->CreateRenderTargetView(pBackBuffer, 0, &m_pRendeTargetView));
	Safe_Release(pBackBuffer);

	D3D11_TEXTURE2D_DESC DepthStencilDesc;

	DepthStencilDesc.Width     = iWidth;
	DepthStencilDesc.Height    = iHeight;
	DepthStencilDesc.MipLevels = 1;
	DepthStencilDesc.ArraySize = 1;
	DepthStencilDesc.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT;

	if(m_bEnable4xMssa)
	{
		DepthStencilDesc.SampleDesc.Count = 4;
		DepthStencilDesc.SampleDesc.Quality = m_u4XMSAAQuality - 1;
	}

	else
	{
		DepthStencilDesc.SampleDesc.Count = 1;
		DepthStencilDesc.SampleDesc.Quality = 0;
	}

	DepthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	DepthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	DepthStencilDesc.CPUAccessFlags = 0;
	DepthStencilDesc.MiscFlags = 0;

	HR(m_pDevice->CreateTexture2D(&DepthStencilDesc, 0, &m_pDepthStencilBuffer));
	HR(m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer, 0, &m_pDepthStencilView));

	m_pImmediateContext->OMSetRenderTargets(1, &m_pRendeTargetView, m_pDepthStencilView);

	m_ScreenViewport.TopLeftY = 0;
	m_ScreenViewport.Width    = static_cast<float>(iWidth);
	m_ScreenViewport.Height   = static_cast<float>(iHeight);
	m_ScreenViewport.MinDepth = 0.0f;
	m_ScreenViewport.MaxDepth = 1.0f;

	m_pImmediateContext->RSSetViewports(1, &m_ScreenViewport);
}


void CDevice::BeginRender()
{
	assert(m_pImmediateContext);
	assert(m_pSwapChain);
	

	m_pImmediateContext->ClearRenderTargetView(m_pRendeTargetView, reinterpret_cast<const float*>(&COLOR_BLUE));
	m_pImmediateContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);

	D3D11_RASTERIZER_DESC desc;
	memset(&desc, 0, sizeof(D3D11_RASTERIZER_DESC));
	desc.CullMode = D3D11_CULL_NONE;
	desc.FillMode = D3D11_FILL_SOLID;
	desc.FrontCounterClockwise = false;
	desc.DepthClipEnable = true;


	ID3D11RasterizerState* pState;

	m_pDevice->CreateRasterizerState(&desc, &pState);

	m_pImmediateContext->RSSetState(pState);

	
}
void CDevice::EndRender()
{
	m_pSwapChain->Present(0, 0);
}

void CDevice::Clear()
{
	Safe_Release(m_pRendeTargetView);
	Safe_Release(m_pDepthStencilView);
	Safe_Release(m_pSwapChain);
	Safe_Release(m_pDepthStencilBuffer);

	if(m_pImmediateContext)
		m_pImmediateContext->ClearState();

	Safe_Release(m_pImmediateContext);
	Safe_Release(m_pDevice);
}