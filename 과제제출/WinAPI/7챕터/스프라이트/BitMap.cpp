#include "BitMap.h"


BitMap::BitMap()
{
	
	std::string FileNametmp = "image";
	const char* FileNameTmp = FileNametmp.c_str();


	m_BitMap = (HBITMAP)LoadImage(NULL, FileNameTmp, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);

	DWORD LastError;
	if (m_BitMap == NULL)
	{
		LastError = GetLastError();
	}
}

HBITMAP BitMap::ReturnBitMap()
{
	return m_BitMap;
}
