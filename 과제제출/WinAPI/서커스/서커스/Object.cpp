#include "Object.h"

void Object::Draw(HDC MemDCBack)
{
	int SizeXTmp = m_ObjectBitMap.ReturnBitMapWidth();
	int SizeYTmp = m_ObjectBitMap.ReturnBitMapHeight();
	
	TransparentBlt(MemDCBack, CHARACTER_LOCATION_X, m_LocationY - SizeYTmp, SizeXTmp, SizeYTmp,
		MemDCCharacter, 0, 0, SizeXTmp, SizeYTmp, RGB(255, 0, 255));
}