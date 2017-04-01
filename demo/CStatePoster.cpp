#include "CStatePoster.h"
#include "CStateLogo.h"
#include "Header.h"

CStatePoster::CStatePoster() : GameTutor::CState()
{
	Log("\nCreate State Poster!");
	this->m_iCount = 0;
}

void CStatePoster::Init()
{
	Log("\nState Poster: Init");
	m_pSprite = new CSprite("resource/background1.jpg", 100, 100 , 64, 48);
	//m_pSurface = new CSurface("resource/background.jpg", 640, 480);

	//m_pTexture = new CTexture("resource/background.jpg");

	//m_pSurface1 = new CSurface("resource/background1.jpg", 640, 480);
	//m_pSurface->Init(640, 480);
}

void CStatePoster::Update()
{
	m_iCount++;
	m_pSprite->Update();

	if (m_iCount >= 500)
	{
		GameTutor::CGame::GetInstance()->Exit();
	}
}

void CStatePoster::Render()
{
	//if (m_iCount >= 150)
		//m_pSurface->LoadSurface(NULL, "resource/background1.jpg", NULL, D3DCOLOR_XRGB(0, 0, 0));
	/*{
		m_pSurface->Render();
	}
	else
	{
		m_pSurface1->Render();
	}*/


	//m_pSurface->Render(NULL, NULL);
	//m_pTexture->Render();
	m_pSprite->Render();

	Log("State Logo: %d Fps = %d FrameDT = %.9f",
		m_iCount,
		GameTutor::CFpsController::GetInstance()->GetRuntimeFps(),
		GameTutor::CFpsController::GetInstance()->GetFrameDt());
	Log("\nRender State Poster");
}

void CStatePoster::Exit()
{
	//SAFE_DELETE(m_pSurface);
	//SAFE_DELETE(m_pTexture);
	/*m_pSurface1->Destroy();
	SAFE_DELETE(m_pSurface1);*/
	SAFE_DELETE(m_pSprite);
	Log("\nState Poster: Exit");
}