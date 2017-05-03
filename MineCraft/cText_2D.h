#pragma once
class cText_2D
{
	ID3DXSprite*  Sprite;
	ID3DXFont*   Font;
public:
	cText_2D();
	~cText_2D();

	void Render();
};

