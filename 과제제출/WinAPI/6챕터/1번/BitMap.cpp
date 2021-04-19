#include "BitMap.h"


BitMap::BitMap(std::string FileName)
{
	FileName += ".bmp";
	char FileNameTmp[156];
	strcpy_s(FileNameTmp, FileName.c_str());
	
	m_BitMap = (HBITMAP)LoadImage(NULL, FileName.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

bool BitMap::DataNullCheck()
{
	if (m_BitMap == NULL)
		return false;
	else
		return true;
}

HBITMAP BitMap::ReturnBitMap()
{
	return m_BitMap;
}