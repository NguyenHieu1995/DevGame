#include "CStateMenu.h"
#include "Header.h"
#include "CStatePlay.h"
#include "CStateManagement.h"

CStateMenu::CStateMenu()
{
	Log("\nConstructor CStateMenu!");
}

CStateMenu::~CStateMenu()
{
	Log("\nDestructor CStateMenu!");
}

void CStateMenu::Init()
{
	Log("\nInit Menu");
}

void CStateMenu::Update()
{
	GameTutor::CStateManagement::GetInstance()->SwitchState(new CStatePlay());
}

void CStateMenu::Render()
{
	Log("\n Render Menu");
}

void CStateMenu::Exit()
{
	Log("\nExit Menu");
}