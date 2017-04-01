#include "CTexture.h"
#include "CGraphics.h"

CTexture::CTexture(std::string srcFile)
{
	if (this->Init())
	{
		LoadTexture(srcFile);
	}
}

CTexture::~CTexture()
{
	this->Destroy();
}

bool CTexture::Init()
{
	//this->m_lpSprite = nullptr;
	//hr = D3DXCreateSprite(CGraphics::GetInstance()->GetDevice(),
	//	&this->m_lpSprite);

	if (FAILED(hr))
		return false;

	return true;
}

void CTexture::Destroy()
{
	SAFE_RELEASE(m_lpTexture);
	//SAFE_RELEASE(m_lpSprite);
}

void CTexture::LoadTexture(std::string srcFile)
{
	hr = E_FAIL;

	ZeroMemory(&m_infoTexture, sizeof(m_infoTexture));
	hr = D3DXGetImageInfoFromFile(srcFile.c_str(), &m_infoTexture); //Lay thong tin hinh anh

	if (FAILED(hr))
	{
		Trace("Load anh Texture Failed!");
		return;
	}

	hr = D3DXCreateTextureFromFileEx(
		CGraphics::GetInstance()->GetDevice(),
		srcFile.c_str(),
		m_infoTexture.Width,
		m_infoTexture.Height,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		NULL,
		NULL,
		&m_lpTexture);

	if (FAILED(hr))
	{
		Trace("Create Texture Failed!");
		return;
	}
}

void CTexture::Render(LPD3DXSPRITE sprite, D3DXVECTOR2 pos, RECT* rectSrc)
{
	hr = E_FAIL;

	if (SUCCEEDED(sprite->Begin(D3DXSPRITE_ALPHABLEND)))
	{
		if ((rectSrc == NULL) ||
			((int)(rectSrc->right - rectSrc->left) > (int)m_infoTexture.Width) ||
			((int)(rectSrc->bottom - rectSrc->top) > (int)m_infoTexture.Height))
		{
			Trace("\nKich thuoc sprite lon hon hinh anh goc (mac dinh lay anh goc)");

			posCenter.x = (float)m_infoTexture.Width / 2;
			posCenter.y = (float)m_infoTexture.Height / 2;
			posCenter.z = 0.0f;

			hr = sprite->Draw(
				this->m_lpTexture,
				NULL,
				&posCenter,
				&D3DXVECTOR3(pos.x, pos.y, 0),
				D3DCOLOR_ARGB(255, 255, 255, 255)
				);
		}
		else
		{
			posCenter.x = (float)(rectSrc->right - rectSrc->left) / 2;
			posCenter.y = (float)(rectSrc->bottom - rectSrc->top) / 2;
			posCenter.z = 0.0f;

			//hinh chu nhat trong anh nguon goc 
			hr = sprite->Draw(
				this->m_lpTexture,
				rectSrc,
				&posCenter,
				&D3DXVECTOR3(pos.x, pos.y, 0),
				D3DCOLOR_ARGB(255, 255, 255, 255)
				);
		}

		if (FAILED(hr))
			MessageBox(NULL, "Draw Texture Failed", NULL, NULL);

		sprite->End();
	}
}

LPDIRECT3DTEXTURE9 CTexture::GetTexture()
{
	return m_lpTexture;
}

D3DXIMAGE_INFO CTexture::GetInfoImage()
{
	return m_infoTexture;
}