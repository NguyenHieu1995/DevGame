//
// State Menu
// Function Quan ly menu cua Game
//

#ifndef __CSTATEMENU_H__
#define __CSTATEMUNU_H__

#include "CState.h"

class CStateMenu : public GameTutor::CState
{
public:
	CStateMenu();
	~CStateMenu();

public:
	void Init();
	void Update();
	void Render();
	void Exit();

};

#endif