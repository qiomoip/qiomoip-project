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

	//성능 타이머로부터 개수 단위의 현재 시간을 얻을 때 사용하는 함수
	//반환값이 아닌 매개변수를 통해 값을 return

	//고해상도 타이머를 사용할 때 시스템이 이 타이머를 지원하는지 조사해야 한다
		//지원을 안 하면 Frequency 함수 return false, 
		//파라미터 값은 0

	//CPU의 주파수 값을 알아내는 역할도 한다
		//주파수를 구하는 이유는 
			//절대초 1초에 이 함수가 반환하는 값, 주파수만큼 증가하는데
			//그 값은 CPU마다 차이가 있으므로 컴퓨터마다 동일한 시간을 재기 위해서 조사가 필요하다
	QueryPerformanceFrequency((LARGE_INTEGER*)&cntPerSec);

	if(!cntPerSec)
		return false;

	//주파수(초당 개수)의 역수를 취해 개수 당 초를 얻음
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

	//현재 시간을 구하는 역할
	//timeGetTime()보다 정확하게 구해낸다
	//64비트의 매개변수에 현재 시간을 저장
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

	//중단과 시작(재개) 사이의 시간을 누적
	//
	//                     |<-------d------->|
	// ----*---------------*-----------------*------------> time
	//  mBaseTime       mStopTime        startTime     

	//중단된 상태에서 다시 재개하는 경우라면
	if(m_bStopped)
	{
		//일시정지 시간을 누적
		m_dPausedTime += (startTime - m_dStopTime);

		//타이머를 다시 시작하는 것이므로 PrevTime의 현재 값은 유효하지 않다
		//(일시정지 도중 갱신되었으므로)
		//따라서 현재 시간으로 다시 설정
		m_dPrevTime = startTime;

		//이제 중단 해제
		m_dStopTime = 0;
		m_bStopped = false;

	}
}

float CTimer::CaculateTotalTime() const
{
	//현재 타이머가 중단 상태이면 중단된 후로부터 흐른 시간은 계산하지 말아야 한다
	//또한 이전에 일시정지된 적이 있다면 그 시간도 전체 시간에 포함시키지 말아야 한다
	//이를 위해 StopTime에서 일시정지 시간을 뺀다
	//                     |<--paused time-->|
	// ----*---------------*-----------------*------------*------------*------> time
	//  mBaseTime       mStopTime        startTime     mStopTime    mCurrTime

	if(m_bStopped)
	{
		return (float)(((m_dStopTime - m_dPausedTime)-m_dBaseTime)*m_dSecondsPreCount);
	}

	//시간차 CurrTime - BaseTime에는 일시정지된 시간이 포함되어 있다
	//일시정지된 시간을 제한다

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
	//이미 정지 상태이면 아무것도 하지 않는다
	if(!m_bStopped)
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		//그렇지 않다면 중단 시간(일시정지된 시점 시간)을 저장하고,
		//타이머가 중단되었을 뜻하는 플래그 설정
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

	//이번 프레임의 시간을 얻는다
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	m_dCurrTime = currTime;

	//이 시간과 이전 프레임의 시간의 차이를 구한다
	//반드시 주파수를 나누어 주어야 한다
	//정확히 몇 초가 걸렸는지 알려 주는 함수
	m_dDeltaTime = (m_dCurrTime - m_dPrevTime) * m_dSecondsPreCount;

	//다음 프레임을 준비한다

	m_dPrevTime = m_dCurrTime;

	//음수가 되지 않게 한다
	//sdk 문서화의 CDXUTTimer항목에 따르면, 
	//프로세서가 절전 모드로 들어가거나 다른 프로세서와 엉키는 경우
	//m_dDeltaTime이 음수가 될 수 ㅣㅇㅆ다
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