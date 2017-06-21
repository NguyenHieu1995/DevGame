//Class Text
//Quan ly hien thi text tren cua so

#ifndef __CTEXT_H__
#define __CTEXT_H__

#include <d3dx9.h>
#include <iostream>
#include <list>
#include "CSingleton.h"

struct STEXT
{
	ID3DXFont *font;
	RECT fRectangle;
	std::string text;
};

class CText : public CSingleton<CText>
{
	friend CSingleton<CText>;

public:
	CText();
	virtual ~CText();

protected:
	std::list<STEXT> listText;

public:
	bool AddText(STEXT);
	bool AddText(RECT, std::string);
	void ShowMessage();
};

#endif