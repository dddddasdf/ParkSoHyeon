#include "BitMap.h"


BitMap::BitMap()
{
	//
	//std::string FileNametmp = "./ImageResource/image.bmp";
	//const char* FileNameTmp = FileNametmp.c_str();


	//m_BitMap = (HBITMAP)LoadImage(NULL, FileNameTmp, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);

	//DWORD LastError;
	//if (m_BitMap == NULL)
	//{
	//	LastError = GetLastError();
	//}

	//¾È ¾¸ ¹é¾÷¿ëÀ¸·Î ³²°ÜµÒ
}

BitMap::BitMap(std::string FileName)
{
	std::string FileNametmp = "./ImageResource/" + FileName + ".bmp";
	const char* FileNameTmp = FileNametmp.c_str();

	m_BitMap = (HBITMAP)LoadImage(NULL, FileNameTmp, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);

	DWORD LastError;
	if (m_BitMap == NULL)
	{
		LastError = GetLastError();
	}

	BITMAP BitMapSizeTmp;
	GetObject(m_BitMap, sizeof(BITMAP), &BitMapSizeTmp);
	m_SizeWidth = BitMapSizeTmp.bmWidth;
	m_SizeHeight  = BitMapSizeTmp.bmHeight;
}

HBITMAP BitMap::ReturnBitMap()
{
	return m_BitMap;
}
