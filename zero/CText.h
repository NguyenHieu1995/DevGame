//Class Text
//Quan ly hien thi text tren cua so

#ifndef __CTEXT_H__
#define __CTEXT_H__

#include <d3dx9.h>
#include <iostream>
#include <list>

struct SMESSAGE
{
	ID3DXFont *font;
	RECT fRectangle;
	std::string message;
};

class CText
{
public:
	CText();
	virtual ~CText();


protected:
	std::list<SMESSAGE> listMessgage;

public:


};

#endif