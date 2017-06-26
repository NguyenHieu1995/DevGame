#include "CText.h"
#include "CGraphics.h"

CText::CText()
{
	listText.clear();
}

CText::~CText()
{
	listText.clear();
}

bool CText::AddText(STEXT stext)
{
	listText.push_back(stext);
	return true;
}

bool CText::AddText(RECT rect, std::string text)
{
	STEXT stext;

	stext.text = text;

	stext.font = NULL;
	HRESULT hr = D3DXCreateFont(
		CGraphics::GetInstance()->GetDevice(), 
		20, 
		0, 
		FW_NORMAL, 
		1, 
		false,
		DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS, 
		ANTIALIASED_QUALITY, 
		FF_DONTCARE, 
		"Arial", 
		&stext.font
		);
	
	stext.fRectangle = rect;

	listText.push_back(stext);
	return true;
}

void CText::ShowMessage()
{
	while (!listText.empty())
	{
		listText.front().font->DrawTextA(
			NULL, 
			listText.front().text.c_str(), 
			-1, 
			&listText.front().fRectangle, 
			DT_LEFT, 
			D3DCOLOR_XRGB(255, 255, 255)
			);
		listText.pop_front();
	}
}