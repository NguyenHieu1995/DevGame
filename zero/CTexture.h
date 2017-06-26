#ifndef __CTEXTURE_H__
#define __CTEXTURE_H__

#include "Header.h"
#include <string>
#include <d3dx9.h>

class CTexture
{
public:
	CTexture(std::string srcFile);
	~CTexture();

public:
	void LoadTexture(std::string srcFile);

	void Render(LPD3DXSPRITE sprite, //con tro sprite
		D3DXVECTOR2 pos, //vi tri anh duoc ve len
		RECT* rectSrc  //kich thuoc hinh chu nhat texture
		);

	LPDIRECT3DTEXTURE9 GetTexture();
	D3DXIMAGE_INFO GetInfoImage();

protected:
	bool Init();
	void Destroy();

protected:
	LPDIRECT3DTEXTURE9 m_lpTexture;
	D3DXIMAGE_INFO m_infoTexture;
	HRESULT hr;
	//RECT rect; //Kich thuoc anh hien thi lay ra tu anh nguon
	D3DXVECTOR3 posCenter; //Tam diem hien thi cua hinh(Mac dinh la vi tri trung tam khong thay doi duoc)
	//==> Thay doi update sau
	//LPD3DXSPRITE m_lpSprite;
};

#endif