#ifndef __CGRAPHICS_H__
#define __CGRAPHICS_H__

#ifdef _DEBUG 
#define D3D_DEBUG_INFO 
#endif

#include "Header.h"
#include "CGameError.h"
#include "CSingleton.h"
#include "CFpscontroller.h"
// Color defines 
#define COLOR_ARGB DWORD 
#define SETCOLOR_ARGB(a,r,g,b) \ ((COLOR_ARGB)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff))) 

#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

struct CUSTOMVERTEX3D
{
	FLOAT x, y, z, rhw;    // from the D3DFVF_XYZRHW flag
	DWORD color;    // from the D3DFVF_DIFFUSE flag
};

struct CUSTOMVERTEX2D
{
	FLOAT x, y, z;   
};




class CGraphics : public CSingleton<CGraphics>
{

	friend class CSingleton<CGraphics>;

public:
	CGraphics();
	virtual ~CGraphics();

public:
	bool Init(__INT32 width, __INT32 height, HWND hwnd, bool fullScreen); //Khoi tao
	void Destroy(); // Huy
	HRESULT ShowBackbuffer(); //load buffer
	void ClearBackbuffer();
	bool IsAdapterCompatible();
	bool InitD3dpp();
	HRESULT GetDeviceState();
	LPDIRECT3DDEVICE9 GetDevice();
	HRESULT Reset();

	//Function Draw Triangle
	void DrawLine(D3DXVECTOR2 startPoint, D3DXVECTOR2 endPoint);
	void DrawLine(D3DXVECTOR2 startPoint, D3DXVECTOR2 endPoint, D3DCOLOR color);

	void DrawTriangle(D3DXVECTOR2 p1, D3DXVECTOR2 p2, D3DXVECTOR2 p3);
	void DrawTriangle(D3DXVECTOR2 p1, D3DXVECTOR2 p2, D3DXVECTOR2 p3, D3DCOLOR color);
	
	void DrawRectangle(RECT rect);
	void DrawRectangle(RECT rect, D3DCOLOR color);

	//Begin, End Draw Graphics 
	void BeginGraphic();
	void EndGraphics();

protected:
	LPDIRECT3DDEVICE9 m_lpDirect3DDevice;
	HRESULT result;
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE pMode;

	LPDIRECT3DVERTEXBUFFER9 v_buffer;

protected:
	__INT32 m_iWidth;
	__INT32 m_iHeight;
	bool m_isFullScreen;
	HWND m_hwnd;
	
};

#endif