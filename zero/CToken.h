// 01/04/2017 
// Nguyen Trung Hieu
// 
/*
Function: - Lop nay dam trach nhiem tach chuoi thanh chuoi con 
			phan biet boi cac ky tu khoang trang va tab

		- Cung cap cac phuong thuc tien ich xu ly chuoi
*/
//
#ifndef __CTOKEN_H__
#define __CTOKEN_H__

#include "Header.h"
#include "Utils.h"

// Kiem tra ki tu ref co phai la khoang trang hoac tab khong
// 32 : SPACE
// 9  : TAB
#define IS_MATCH_TOKEN(ref) (((ref)==32) || ((ref)==9)) 

namespace GameTutor
{
	struct STokenSegment //thong cua mot tu
	{
		int iOffset; // vi tri bat dau
		int iLength; // Do dai
	};

	class CToken
	{
	public:
		CToken(char* pointer); //Constructor
		CToken();				//Default constructor
		virtual ~CToken();		//Destructor

		//Giai phong chuoi
		void DeallocateStringPointer();
		
		//Lay 1 tu o vi tri index voi kich thuoc size ket qua tra ve ref
		void GetToken(int index, char * ref, int size = -1); 
		
		//Ham kiem tra 2 chuoi co bang nhau khong
		bool IsTokenEqual(int index, const char *st);
		
		//Gan gia tri string moi
		void SetStringPointer(char* pointer);
		
		// Tra ve so luong token
		int GetTokenCount();
		
		//Chuyen chuoi thanh so
		int GetTokenValueAsInt(int index);
	
	private:
		CList<STokenSegment>* m_Token; // Danh sach cac tu
		char* m_pString; //Chuoi ban dau
		void ParseToken(); //Phan tich chuoi thanh list
	};
}
#endif