#include "CExample.h"
#include "CStateLogo.h"
#include <stdio.h>

void CExample::Init()
{
	//Init Game
	printf("\nInit Game!");

	CFpsController::GetInstance();

	// Init State
	CStateManagement::GetInstance()->GetInstance()->SwitchState(new CStateLogo());
	m_isInit = true;
}

void CExample::Destroy()
{
	//Destroy Game
	printf("\nDestroy Game!");

	CFpsController::FreeInstance();

	// Destroy State
	if(CStateManagement::IsAvailable())
		CStateManagement::FreeInstance();
}
