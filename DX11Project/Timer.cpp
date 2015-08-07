#include "Timer.h"


CTimer::CTimer(void)
	: m_dSecondsPreCount(0.0)
	, m_dDeltaTime(-1.0)
	, m_dBaseTime(0)
	, m_dPausedTime(0)
	, m_dStopTime(0)
	, m_dPrevTime(0)
	, m_dCurrTime(0)
	, m_bStopped(false)
	, m_iFPSCnt(0)
	, m_fElapsedTime(0.f)

{
	
}

CTimer::~CTimer(void)
{
}


bool CTimer::Init()
{
	__int64 cntPerSec;

	//���� Ÿ�̸ӷκ��� ���� ������ ���� �ð��� ���� �� ����ϴ� �Լ�
	//��ȯ���� �ƴ� �Ű������� ���� ���� return

	//���ػ� Ÿ�̸Ӹ� ����� �� �ý����� �� Ÿ�̸Ӹ� �����ϴ��� �����ؾ� �Ѵ�
		//������ �� �ϸ� Frequency �Լ� return false, 
		//�Ķ���� ���� 0

	//CPU�� ���ļ� ���� �˾Ƴ��� ���ҵ� �Ѵ�
		//���ļ��� ���ϴ� ������ 
			//������ 1�ʿ� �� �Լ��� ��ȯ�ϴ� ��, ���ļ���ŭ �����ϴµ�
			//�� ���� CPU���� ���̰� �����Ƿ� ��ǻ�͸��� ������ �ð��� ��� ���ؼ� ���簡 �ʿ��ϴ�
	QueryPerformanceFrequency((LARGE_INTEGER*)&cntPerSec);

	if(!cntPerSec)
		return false;

	//���ļ�(�ʴ� ����)�� ������ ���� ���� �� �ʸ� ����
	m_dSecondsPreCount = 1.0 / (double)cntPerSec;

	return true;
}

const float& CTimer::GetDeltaTime() const
{
	return m_dDeltaTime;
}

const float& CTimer::GetFPS() const
{
	return m_fFPS;
}

void CTimer::Reset()
{
	__int64 currTime;

	//���� �ð��� ���ϴ� ����
	//timeGetTime()���� ��Ȯ�ϰ� ���س���
	//64��Ʈ�� �Ű������� ���� �ð��� ����
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	m_dBaseTime = currTime;
	m_dPrevTime = currTime;
	m_dStopTime = 0;
	m_bStopped = false;
}
void CTimer::Restart()
{
	__int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

	//�ߴܰ� ����(�簳) ������ �ð��� ����
	//
	//                     |<-------d------->|
	// ----*---------------*-----------------*------------> time
	//  mBaseTime       mStopTime        startTime     

	//�ߴܵ� ���¿��� �ٽ� �簳�ϴ� �����
	if(m_bStopped)
	{
		//�Ͻ����� �ð��� ����
		m_dPausedTime += (startTime - m_dStopTime);

		//Ÿ�̸Ӹ� �ٽ� �����ϴ� ���̹Ƿ� PrevTime�� ���� ���� ��ȿ���� �ʴ�
		//(�Ͻ����� ���� ���ŵǾ����Ƿ�)
		//���� ���� �ð����� �ٽ� ����
		m_dPrevTime = startTime;

		//���� �ߴ� ����
		m_dStopTime = 0;
		m_bStopped = false;

	}
}

float CTimer::CaculateTotalTime() const
{
	//���� Ÿ�̸Ӱ� �ߴ� �����̸� �ߴܵ� �ķκ��� �帥 �ð��� ������� ���ƾ� �Ѵ�
	//���� ������ �Ͻ������� ���� �ִٸ� �� �ð��� ��ü �ð��� ���Խ�Ű�� ���ƾ� �Ѵ�
	//�̸� ���� StopTime���� �Ͻ����� �ð��� ����
	//                     |<--paused time-->|
	// ----*---------------*-----------------*------------*------------*------> time
	//  mBaseTime       mStopTime        startTime     mStopTime    mCurrTime

	if(m_bStopped)
	{
		return (float)(((m_dStopTime - m_dPausedTime)-m_dBaseTime)*m_dSecondsPreCount);
	}

	//�ð��� CurrTime - BaseTime���� �Ͻ������� �ð��� ���ԵǾ� �ִ�
	//�Ͻ������� �ð��� ���Ѵ�

	//(CurrTime - PausedTime) - BaseTime

	//                     |<--paused time-->|
	// ----*---------------*-----------------*------------*------> time
	//  mBaseTime       mStopTime        startTime     mCurrTime

	else
	{
		return (float)(((m_dCurrTime-m_dPausedTime)-m_dBaseTime)*m_dSecondsPreCount);
	}
}

void CTimer::Stop()
{
	//�̹� ���� �����̸� �ƹ��͵� ���� �ʴ´�
	if(!m_bStopped)
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		//�׷��� �ʴٸ� �ߴ� �ð�(�Ͻ������� ���� �ð�)�� �����ϰ�,
		//Ÿ�̸Ӱ� �ߴܵǾ��� ���ϴ� �÷��� ����
		m_dStopTime = currTime;
		m_bStopped = true;
	}

}

void CTimer::Tick()
{
	if(m_bStopped)
	{
		m_dDeltaTime = 0.0;
		return;
	}

	//�̹� �������� �ð��� ��´�
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	m_dCurrTime = currTime;

	//�� �ð��� ���� �������� �ð��� ���̸� ���Ѵ�
	//�ݵ�� ���ļ��� ������ �־�� �Ѵ�
	//��Ȯ�� �� �ʰ� �ɷȴ��� �˷� �ִ� �Լ�
	m_dDeltaTime = (m_dCurrTime - m_dPrevTime) * m_dSecondsPreCount;

	//���� �������� �غ��Ѵ�

	m_dPrevTime = m_dCurrTime;

	//������ ���� �ʰ� �Ѵ�
	//sdk ����ȭ�� CDXUTTimer�׸� ������, 
	//���μ����� ���� ���� ���ų� �ٸ� ���μ����� ��Ű�� ���
	//m_dDeltaTime�� ������ �� �� �Ӥ�����
	if(m_dDeltaTime < 0.0)
	{
		m_dDeltaTime = 0.0;
	}

}


void CTimer::CalculateFrameStats(const std::tstring& strCaption, const HWND& hWnd)
{
	// Code computes the average frames per second, and also the 
	// average time it takes to render one frame.  These stats 
	// are appended to the window caption bar.

	m_iFPSCnt++;

	// Compute averages over one second period.
	if( (CaculateTotalTime() - m_fElapsedTime) >= 1.0f )
	{
		float fFPSCnt = (float)m_iFPSCnt; // fps = frameCnt / 1
		m_fFPS = 1000.0f / fFPSCnt;


		std::wostringstream outs;   
		outs.precision(6);
		outs << strCaption << L"    "
			 << L"FPS: " << fFPSCnt << L"    " 
			 << L"Frame Time: " << m_fFPS << L" (ms)";
		SetWindowText(hWnd, outs.str().c_str());

		// Reset for next average.
		m_iFPSCnt = 0;
		m_fElapsedTime += 1.0f;
	}
}