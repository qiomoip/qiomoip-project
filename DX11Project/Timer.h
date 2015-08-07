#pragma once
#include "include.h"
class CTimer
{
private:
	double m_dSecondsPreCount;
	double m_dDeltaTime;

	//total time 계산하는 데 쓰이는 변수들
	__int64 m_dBaseTime;	//Reset 호출시 현재 시간으로 초기화
	__int64 m_dPausedTime;	//일시정지된 동안 누적되는 시간
	__int64 m_dStopTime;	//타이머가 중단된 시점의 시간 (누적 시간 계산시 사용)

	__int64 m_dPrevTime;
	__int64 m_dCurrTime;

	bool	m_bStopped;

	float	m_fFPS;
	int		m_iFPSCnt;
	float	m_fElapsedTime;

public:
	const float& GetDeltaTime() const;
	const float& GetFPS() const;

	bool Init();

	//PrevTime을 현재 시간으로 설정
	//메세지 루프 전에 이전 시간 값을 초기화
	void Reset();

	//타이머를 일시정지하거나 재개할 때 호출하는 메서드들
	void Restart();
	void Stop();

	//정지된 시간을 뺀 전체 누적 시간을 return
	float CaculateTotalTime() const;

	//프레임 간 경과 시간
	//프레임 사이에 흐른 시간
	void Tick();
	void CalculateFrameStats(const tstring& strCaption, const HWND& hWnd);

public:
	CTimer(void);	//생성자의 주된 임무는 성능 카운터의 주파수를 조회해 개수 당 초 수를 설정하는 것이다
	~CTimer(void);
};

