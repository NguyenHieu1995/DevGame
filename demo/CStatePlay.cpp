#include "CStatePlay.h"
#include "CStatePoster.h"

CStatePlay::CStatePlay() : GameTutor::CState()
{
	m_iCount = 0;
}

void CStatePlay::Init()
{
	//printf("\nState Logo: Init!");
	Log("\nState Play: Init");
	m_iCount = 0;
}

void CStatePlay::Update()
{
	m_iCount++;
	if (m_iCount >= 150)
	{
		//GameTutor::CStateManagement::GetInstance()->SwitchState(new CStatePoster());
		GameTutor::CGame::GetInstance()->Exit();
	}
}

void CStatePlay::Render()
{
	Log("\nState Play: Render");
}

void CStatePlay::Exit()
{
	Log("\nState Play: Exit!");
}
