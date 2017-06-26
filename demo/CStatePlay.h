#ifndef __CSTATEPLAY_H__
#define __CSTATEPLAY_H__

#include "zero.h"

class CStatePlay : public GameTutor::CState
{
public:
	CStatePlay();
	~CStatePlay() {}

	void Init();
	void Update();
	void Render();
	void Exit();

private:
	__INT32 m_iCount;
};

#endif 