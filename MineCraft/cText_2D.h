#pragma once

struct cTextStruct
{
	RECT         m_Rect;
	string       m_message;
	int          m_size;
	cTextStruct(RECT rect, string message, int size) { m_Rect = rect; m_message = message; m_size = size; }
};
class cText_2D
{
	ID3DXFont*   m_Font;
	RECT         m_Rect;
	string       m_message;
	int          m_size;
	D3DXCOLOR    m_color;
public:
	cText_2D();
	~cText_2D();

	void Create(RECT rect, string message, int size, D3DXCOLOR color);
	void Render();
	void Delete(string message);
	void Clear();

	void SetColor(D3DXCOLOR color) { m_color = color; }
};

