#include "CSprite.h"
#include "CGraphics.h"

CSprite::CSprite(std::string srcFile, int posX, int posY, int width, int height)
{
	//Khoi gan cac gia tri ban dau cho cai bien
	this->m_lpSprite = NULL;
	this->m_pPostion = NULL;
	this->m_pTexture = NULL;
	this->m_pRect = NULL;
	this->m_isInitialize = false;
	this->m_iNumberSprite = 0;
	this->m_hResult = E_FAIL;
	this->m_iWidth = width;
	this->m_iHeight = height;

	//Khoi tao Sprite
	this->Init(posX, posY);
}

CSprite::~CSprite()
{
	//Huy sprite
	this->Destroy();
}

bool CSprite::Init(int posX, int posY)
{
	this->m_hResult = E_FAIL;
	
	m_hResult = D3DXCreateSprite(
		CGraphics::GetInstance()->GetDevice(), 
		&this->m_lpSprite);

	if (FAILED(this->m_hResult))
	{
		return false;
	}

	this->m_pPostion = new D3DXVECTOR2(posX, posY);
	this->m_pTexture = new CTexture("resource/background.jpg");

	this->m_isInitialize = true;
	
	//Khoi tao gia tri dau tien cho Rect
	

	return true;
}

void CSprite::Destroy()
{
	this->m_isInitialize = false;
	SAFE_DELETE(m_pPostion);
	SAFE_DELETE(m_pTexture);
	SAFE_RELEASE(m_lpSprite);
	SAFE_DELETE(m_pRect);
}

void CSprite::Update()
{
	//update lai thong tin cua Rect
}

void CSprite::Render()
{
	this->m_pTexture->Render(this->m_lpSprite, 
		D3DXVECTOR2(this->m_pPostion->x, this->m_pPostion->y),
		m_pRect);
}

void CSprite::SetPostion(int xx, int yy)
{
	this->m_pPostion->x = xx;
	this->m_pPostion->y = yy;
}

D3DXVECTOR2* CSprite::GetPostion()
{
	if (m_isInitialize == true)
	{
		return m_pPostion;
	}

	return NULL;
}
