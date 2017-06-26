#include "CExample.h"
#include "CStatePoster.h"
#include <stdio.h>
#include "CGraphics.h"

void CExample::Init()
{
	//Init Game
	printf("\nInit Game!");

	// Init State
	CStateManagement::GetInstance()->GetInstance()->SwitchState(new CStatePoster());
	m_isInit = true;
}

void CExample::Destroy()
{
	//Destroy Game
	printf("\nDestroy Game!");

	// Destroy State
	if(CStateManagement::IsAvailable())
		CStateManagement::FreeInstance();
}
