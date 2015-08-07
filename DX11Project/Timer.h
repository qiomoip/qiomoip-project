#pragma once
#include "include.h"
class CTimer
{
private:
	double m_dSecondsPreCount;
	double m_dDeltaTime;

	//total time ����ϴ� �� ���̴� ������
	__int64 m_dBaseTime;	//Reset ȣ��� ���� �ð����� �ʱ�ȭ
	__int64 m_dPausedTime;	//�Ͻ������� ���� �����Ǵ� �ð�
	__int64 m_dStopTime;	//Ÿ�̸Ӱ� �ߴܵ� ������ �ð� (���� �ð� ���� ���)

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

	//PrevTime�� ���� �ð����� ����
	//�޼��� ���� ���� ���� �ð� ���� �ʱ�ȭ
	void Reset();

	//Ÿ�̸Ӹ� �Ͻ������ϰų� �簳�� �� ȣ���ϴ� �޼����
	void Restart();
	void Stop();

	//������ �ð��� �� ��ü ���� �ð��� return
	float CaculateTotalTime() const;

	//������ �� ��� �ð�
	//������ ���̿� �帥 �ð�
	void Tick();
	void CalculateFrameStats(const tstring& strCaption, const HWND& hWnd);

public:
	CTimer(void);	//�������� �ֵ� �ӹ��� ���� ī������ ���ļ��� ��ȸ�� ���� �� �� ���� �����ϴ� ���̴�
	~CTimer(void);
};

