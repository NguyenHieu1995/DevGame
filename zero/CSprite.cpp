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


//#include "CSprite.h"
//namespace GameTutor
//{
//	CSprite::CSprite(CSpriteDB* sprDB) : m_SpriteData(sprDB),
//		m_pCurrentAnimation(0),
//		m_iFps(25),
//		m_iElapsedTime(0),
//		m_pCurrentKeyFrame(0),
//		m_iCurrentFrameNo(-1),
//		m_isEndOfAnimtion(false),
//		m_Position(0, 0),
//		m_pCurrentFrame(0),
//		m_iLoop(0),
//		m_iLoopCounter(0),
//		m_pCurrentBitmap(0),
//		m_iCurrentAnimTotalFrame(0)
//	{
//		if (sprDB)
//		{
//			m_iFps = sprDB->m_Header.Fps;
//		}
//	}
//
//	CSprite::~CSprite()
//	{
//	}
//
//	void CSprite::SetAnimation(const char* anim_name, __INT32 loop)
//	{
//		ResetAnimation();
//		m_SpriteData->m_Anims.BeginTravel();
//		while (!m_SpriteData->m_Anims.IsEndOfTravel())
//		{
//			SSpriteDBAnimation *anim = m_SpriteData->m_Anims.Travel();
//			if (strcmp(anim_name, anim->Name) == 0)
//			{
//				m_pCurrentAnimation = anim;
//			}
//		}
//		m_iLoop = loop;
//		m_iCurrentAnimTotalFrame = 0;
//		m_iLoopCounter = loop;
//	}
//
//	void CSprite::ResetAnimation()
//	{
//		m_iElapsedTime = 0;
//		m_iCurrentFrameNo = -1;
//		m_isEndOfAnimtion = false;
//		m_iLoopCounter = m_iLoop;
//	}
//
//	void CSprite::UpdateAnimation(__UINT32 dt)
//	{
//		if (m_isEndOfAnimtion)
//		{
//			m_iElapsedTime = 0;
//			return;
//		}
//
//		m_isEndOfAnimtion = true;
//		if (m_pCurrentAnimation)
//		{
//			//Log("m_iElapsedTime %d", m_iElapsedTime);
//			// calculate frame number
//			m_iElapsedTime += dt;
//			int frameNo = __INT32((m_iElapsedTime*m_iFps) / 1000);
//			//Log("%d m_iElapsedTime %d frNo %d",dt, __INT32(m_iElapsedTime), frameNo);
//
//			// if move to new frame
//			m_isEndOfAnimtion = false;
//			if (frameNo != m_iCurrentFrameNo)
//			{
//				m_isEndOfAnimtion = true;
//				m_iCurrentFrameNo = frameNo;
//				// find suitable key frame
//				if (m_pCurrentAnimation->KeyFrameList)
//				{
//					m_pCurrentAnimation->KeyFrameList->BeginTravel();
//					int nf = 0;
//					while (!m_pCurrentAnimation->KeyFrameList->IsEndOfTravel())
//					{
//						SSpriteDBAnimKeyFrame* kf = m_pCurrentAnimation->KeyFrameList->Travel();
//						nf += kf->Loop;
//						if (nf > m_iCurrentAnimTotalFrame) { m_iCurrentAnimTotalFrame = nf; }
//
//						//Log("nf %d %d",nf, m_iCurrentFrameNo);
//						// if found
//						if (nf > m_iCurrentFrameNo)
//						{
//							m_isEndOfAnimtion = false;
//
//							//check if new KF
//							if (m_pCurrentKeyFrame != kf)
//							{
//								m_pCurrentKeyFrame = kf;
//								m_pCurrentFrame = 0;
//								//link from KF to Frame
//								if (m_pCurrentKeyFrame)
//								{
//									int frameID = m_pCurrentKeyFrame->FrameID;
//									m_SpriteData->m_Frames.BeginTravel();
//									while (!m_SpriteData->m_Frames.IsEndOfTravel())
//									{
//										SSpriteDBFrame *frame = m_SpriteData->m_Frames.Travel();
//										if (frame && frame->ID == frameID)
//										{
//											m_pCurrentFrame = frame;
//											//link to Bitmap if any
//											m_pCurrentBitmap = 0;
//											if (m_pCurrentFrame && m_pCurrentFrame->Type == ESPRFRAME_TYPE_RECT_IMG)
//											{
//												m_SpriteData->m_Bitmaps.BeginTravel();
//												while (!m_SpriteData->m_Bitmaps.IsEndOfTravel())
//												{
//													SSpriteDBBitmap *bitmap = m_SpriteData->m_Bitmaps.Travel();
//													if (bitmap && bitmap->ID == m_pCurrentFrame->RectImgFrame.ImgID)
//													{
//														m_pCurrentBitmap = bitmap;
//													}
//												}
//											}
//											break;
//										}
//									}
//								}
//							}
//							break;
//						}//if (nf > m_iCurrentFrameNo)
//					}//while (!m_pCurrentAnimation->KeyFrameList->IsEndOfTravel())
//				}//if (m_pCurrentAnimation->KeyFrameList)
//			}//if (frameNo != m_iCurrentFrameNo)
//
//			//Log("m_isEndOfAnimtion %d", m_isEndOfAnimtion);
//			if (m_isEndOfAnimtion)
//			{
//				if (m_iLoopCounter != 0)
//				{
//					if (m_iLoopCounter > 0) m_iLoopCounter--;
//					m_iElapsedTime = Math_Min<__UINT64>(m_iElapsedTime - m_iCurrentAnimTotalFrame*m_iFps, 0);
//					m_iCurrentFrameNo = -1;
//					m_isEndOfAnimtion = false;
//				}
//			}
//		}//if (m_pCurrentAnimation)
//	}
//
//	void CSprite::RenderAnimation(CGraphics2D *g)
//	{
//		if (m_pCurrentFrame)
//		{
//			CImage* img = 0;
//			switch (m_pCurrentFrame->Type)
//			{
//			case ESPRFRAME_TYPE_RECT_IMG:
//				img = CImageManager::GetInstance()->Get(m_pCurrentBitmap->Name);
//				g->DrawImageRegion(SPosition2D<__INT32>(m_pCurrentKeyFrame->OffsetX + this->m_Position.X, m_pCurrentKeyFrame->OffsetY + this->m_Position.Y),
//					img,
//					SRect<__INT32>(m_pCurrentFrame->RectImgFrame.OffsetX, m_pCurrentFrame->RectImgFrame.OffsetY, m_pCurrentFrame->RectImgFrame.Width, m_pCurrentFrame->RectImgFrame.Height)
//					);
//
//				break;
//			case ESPRFRAME_TYPE_RECT_COLOR:
//				g->SetColor(SColor<__UINT8>(m_pCurrentFrame->RectColorFrame.Red, m_pCurrentFrame->RectColorFrame.Green, m_pCurrentFrame->RectColorFrame.Blue, m_pCurrentFrame->RectColorFrame.Alpha));
//				g->FillRect(SRect<__INT32>(m_pCurrentKeyFrame->OffsetX + this->m_Position.X, m_pCurrentKeyFrame->OffsetY + this->m_Position.Y, m_pCurrentFrame->RectColorFrame.Width, m_pCurrentFrame->RectColorFrame.Height));
//				break;
//			}
//		}
//	}
//}