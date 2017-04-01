#ifndef __CSTATEPOSTER_H__
#define __CSTATEPOSTER_H__

#include "zero.h"

class CStatePoster : public GameTutor::CState
{
public:
	CStatePoster();
	~CStatePoster() {}

public:
	void Init();
	void Update();
	void Render();
	void Exit();

private:
	int m_iCount;
	//CSurface* m_pSurface;
	//CSurface* m_pSurface1;
	//CTexture* m_pTexture;
	CSprite* m_pSprite;
};

#endif