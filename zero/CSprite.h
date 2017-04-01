#ifndef __CSPRITE_H__
#define __CSPRITE_H__

#include "Header.h"
#include "CTexture.h"
#include <string>

class CSprite
{
public:
	CSprite(std::string srcFile, int posX, int posY, int width = 0, int height = 0);
	~CSprite();

public:
	bool Init(int posX, int posY);
	void Destroy();
	void Render();
	void Update();

	//Set vi tri cho Sprite
	void SetPostion(int xx, int yy);
	//Tra ve vi tri hien tai cua Sprite
	D3DXVECTOR2* GetPostion();

protected:
	//Con tro sprite
	LPD3DXSPRITE m_lpSprite;
	
	//kich thuoc sprite
	int m_iWidth;
	int m_iHeight;
	
	//Vi tri Sprite
	D3DXVECTOR2* m_pPostion;

	//Texture cua Sprite
	CTexture* m_pTexture;

	//Variable Initialize sprite
	bool m_isInitialize;

	//So frame cua Sprite
	int m_iNumberSprite;

	//bien kiem tra 
	HRESULT m_hResult;

	//Duong dan chua texture cua sprite
	std::string m_strSrcFile;

	//Con tro kich thuoc anh lay ra tu texture nguon
	RECT* m_pRect;

};

#endif