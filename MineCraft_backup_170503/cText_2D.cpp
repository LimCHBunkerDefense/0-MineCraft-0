#include "stdafx.h"
#include "cText_2D.h"


cText_2D::cText_2D()
{
	
}


cText_2D::~cText_2D()
{
}

void cText_2D::Render()
{
	LOGFONT lf;
	ZeroMemory(&lf, sizeof(LOGFONT));
	lf.lfHeight = 25;
	lf.lfWidth = 12;
	lf.lfWeight = 500;
	lf.lfItalic = false;
	lf.lfUnderline = false;
	lf.lfStrikeOut = false;
	lf.lfCharSet = DEFAULT_CHARSET;
	wcscpy_s(lf.lfFaceName, _countof(lf.lfFaceName), _T("Arial"));

	ID3DXFont* font = 0;
	D3DXCreateFontIndirect(g_pD3DDevice, &lf, &font);

}