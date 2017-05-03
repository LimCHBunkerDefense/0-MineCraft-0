#include "stdafx.h"
#include "cText_2D.h"


cText_2D::cText_2D()
{
	D3DXCreateSprite(g_pD3DDevice, &Sprite);
}


cText_2D::~cText_2D()
{
}

void cText_2D::Render()
{
	int Height = 30;
	int Width = 30;
	LPCWSTR FontName = TEXT("Arial");
	D3DXCreateFont(g_pD3DDevice, Height, Width, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, FontName, &this->Font);

	LPCWSTR Text = TEXT("가나다라");
	RECT rt = { 300,300,0,0 };
	Font->DrawText(Sprite, Text, -1, &rt, DT_NOCLIP, D3DCOLOR_XRGB(255, 0, 0));

}