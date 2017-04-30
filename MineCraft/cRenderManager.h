#pragma once

enum TEXT_ALIGN
{
	TEXT_ALIGN_LEFT = 0, TEXT_ALIGN_RIGHT = 1, TEXT_ALIGN_CENTER = 2,
};

// ����
struct Line
{
	D3DXVECTOR2 point;
	D3DXVECTOR2 dir;
	float length;

	Line(D3DXVECTOR2 startPos, D3DXVECTOR2 endPos)
	{
		point = startPos;
		D3DXVec2Normalize(&dir, &(endPos - startPos));
		length = D3DXVec2Length(&(endPos - startPos));
	}

	void SetEndPoint(D3DXVECTOR2 endPoint)
	{
		D3DXVec2Normalize(&dir, &(endPoint - point));
		length = D3DXVec2Length(&(endPoint - point));
	}

	D3DXVECTOR2 StartPoint() { return point; }
	D3DXVECTOR2 EndPoint() { return point + dir * length; }
	float Slope() { return (EndPoint().y - StartPoint().y) / (EndPoint().x - StartPoint().x); }
};

// ��
struct Circle
{
	D3DXVECTOR2 center;
	float radius;

	Circle(D3DXVECTOR2 center, float radius)
	{
		this->center = center;
		this->radius = radius;
	}

	void SetCenter(D3DXVECTOR2 center) { this->center = center; }
	D3DXVECTOR2 Center() { return center; }
	float Radius() { return radius; }
};

// �簢��
struct Box
{
	D3DXVECTOR2 center, size;
	D3DXVECTOR2 dirX, dirY;

	Box(D3DXVECTOR2 center, D3DXVECTOR2 size, float angle = 0)
	{
		this->center = center;
		this->size = size;
		SetAngle(angle);
	}

	void SetSize(D3DXVECTOR2 size) { this->size = size; }
	void SetCenter(D3DXVECTOR2 center) { this->center = center; }
	void SetAngle(float angle)
	{
		dirX = D3DXVECTOR2(cosf(angle * ANGLE_TO_RADIAN), -sinf(angle * ANGLE_TO_RADIAN));
		dirY = D3DXVECTOR2(cosf((angle - 90) *ANGLE_TO_RADIAN), -sinf((angle - 90) * ANGLE_TO_RADIAN));
	}

	void SetLeftTop(D3DXVECTOR2 leftTop)
	{
		center = leftTop + Width() * 0.5f + Height() * 0.5f;
	}

	D3DXVECTOR2 Width() { return dirX * size.x; }
	D3DXVECTOR2 Height() { return dirY * size.y; }

	D3DXVECTOR2 Left() { return center - Width() * 0.5f; }
	D3DXVECTOR2 Right() { return center + Width() * 0.5f; }
	D3DXVECTOR2 Top() { return center - Height() * 0.5f; }
	D3DXVECTOR2 Down() { return center + Height() * 0.5f; }
	D3DXVECTOR2 LeftTop() { return center - Width() * 0.5f - Height() * 0.5f; }
	D3DXVECTOR2 LeftBottom() { return LeftTop() + Height(); }
	D3DXVECTOR2 RightTop() { return LeftTop() + Width(); }
	D3DXVECTOR2 RightBottom() { return LeftTop() + Width() + Height(); }
};

// �ﰢ��
struct Triangle
{
	D3DXVECTOR2 p0, p1, p2;

	Triangle(D3DXVECTOR2 point0, D3DXVECTOR2 point1, D3DXVECTOR2 point2)
	{
		p0 = point0;
		p1 = point1;
		p2 = point2;
	}
};

class IGraphics
{
public:
	virtual void Render(ID2D1RenderTarget* pRenderTarget) {}
};

class GText : public IGraphics
{
	IDWriteTextFormat* m_pFormat;
	wstring m_text;
	D3DXVECTOR2 m_leftTop;
	D3DXVECTOR2 m_size;
	ColorF m_color;

public:
	GText(IDWriteTextFormat* pFormat, wstring text, D3DXVECTOR2 leftTop
		, D3DXVECTOR2 size, ColorF color) : m_color(color)
	{
		m_pFormat = pFormat;
		m_text = text;
		m_leftTop = leftTop;
		m_size = size;
	}

	~GText() { SAFE_RELEASE(m_pFormat); }

	void Render(ID2D1RenderTarget* pRenderTarget)
	{
		D2D1_RECT_F rect = RectF(m_leftTop.x, m_leftTop.y, m_leftTop.x + m_size.x, m_leftTop.y + m_size.y);

		ID2D1SolidColorBrush* pBrush;
		pRenderTarget->CreateSolidColorBrush(m_color, &pBrush);
		pRenderTarget->DrawTextW(m_text.c_str(), m_text.length(), m_pFormat, rect, pBrush);
		SAFE_RELEASE(pBrush);
	}
};

class GLine : public IGraphics
{
	D3DXVECTOR2 m_start, m_end;
	ColorF m_color;
	float m_lineSize;

public:
	GLine(D3DXVECTOR2 start, D3DXVECTOR2 end, ColorF color, float lineSize) : m_color(color)
	{
		m_start = start;
		m_end = end;
		m_lineSize = lineSize;
	}

	void Render(ID2D1RenderTarget* pRenderTarget)
	{
		ID2D1SolidColorBrush* pBrush;
		pRenderTarget->CreateSolidColorBrush(m_color, &pBrush);

		D2D1_POINT_2F startPos = Point2F(m_start.x, m_start.y);
		D2D1_POINT_2F endPos = Point2F(m_end.x, m_end.y);
		pRenderTarget->DrawLine(startPos, endPos, pBrush, m_lineSize);

		SAFE_RELEASE(pBrush);
	}
};

class GRect : public IGraphics
{
	D3DXVECTOR2 m_center, m_size;
	ColorF m_color;
	float m_lineSize;

public:
	GRect(D3DXVECTOR2 center, D3DXVECTOR2 size, ColorF color, float lineSize) : m_color(color)
	{
		m_center = center;
		m_size = size;
		m_lineSize = lineSize;
	}

	void Render(ID2D1RenderTarget* pRenderTarget)
	{
		ID2D1SolidColorBrush* pBrush;
		pRenderTarget->CreateSolidColorBrush(m_color, &pBrush);

		D3DXVECTOR2 leftTop = m_center - m_size * 0.5f;
		D3DXVECTOR2 rightBottom = m_center + m_size * 0.5f;
		D2D1_RECT_F rect = RectF(leftTop.x, leftTop.y, rightBottom.x, rightBottom.y);

		if (m_lineSize == 0) pRenderTarget->FillRectangle(rect, pBrush);
		else pRenderTarget->DrawRectangle(rect, pBrush, m_lineSize);

		SAFE_RELEASE(pBrush);
	}
};

class GCircle : public IGraphics
{
	D3DXVECTOR2 m_center;
	float m_radius;
	ColorF m_color;
	float m_lineSize;

public:
	GCircle(D3DXVECTOR2 center, float radius, ColorF color, float lineSize) : m_color(color)
	{
		m_center = center;
		m_radius = radius;
		m_lineSize = lineSize;
	}

	void Render(ID2D1RenderTarget* pRenderTarget)
	{
		ID2D1SolidColorBrush* pBrush;
		pRenderTarget->CreateSolidColorBrush(m_color, &pBrush);

		D2D1_POINT_2F center = Point2F(m_center.x, m_center.y);
		D2D1_ELLIPSE ellipse = Ellipse(center, m_radius, m_radius);

		if (m_lineSize == 0) pRenderTarget->FillEllipse(ellipse, pBrush);
		else pRenderTarget->DrawEllipse(ellipse, pBrush, m_lineSize);

		SAFE_RELEASE(pBrush);
	}
};

class GSprite : public IGraphics
{
	ID2D1Bitmap* m_pImage;
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 m_size;
	D3DXVECTOR2 m_anchor;
	D3DXVECTOR2 m_sourcePos;
	D3DXVECTOR2 m_sourceSize;
	float m_angle;
	float m_scale;
	float m_opacity;
	int m_dir;

public:
	GSprite(ID2D1Bitmap* pImage, D3DXVECTOR2 pos, D3DXVECTOR2 anchor = D3DXVECTOR2(0.5f, 0.5f))
	{
		m_pImage = pImage;
		m_pos = pos;
		m_size = D3DXVECTOR2(pImage->GetSize().width, pImage->GetSize().height);
		m_sourcePos = D3DXVECTOR2(0, 0);
		m_sourceSize = m_size;
		m_anchor = anchor;
		m_angle = 0;
		m_scale = 1.0f;
		m_opacity = 1.0f;
		m_dir = 1;
	}

	GSprite(ID2D1Bitmap* pImage, D3DXVECTOR2 pos, D3DXVECTOR2 sourcePos, D3DXVECTOR2 sourceSize, D3DXVECTOR2 anchor = D3DXVECTOR2(0.5f, 0.5f))
		: GSprite(pImage, pos, anchor)
	{
		m_size = sourceSize;
		m_sourcePos = sourcePos;
		m_sourceSize = sourceSize;
	}

	void SetPosition(D3DXVECTOR2 pos) { m_pos = pos; }
	void SetSize(D3DXVECTOR2 size) { m_size = size; }
	void SetAnchor(D3DXVECTOR2 anchor) { m_anchor = anchor; }
	void SetAngle(float angle) { m_angle = angle; }
	void SetScale(float scale) { m_scale = scale; }
	void SetOpacity(float opacity) { m_opacity = opacity; }

	D3DXVECTOR2 Position() { return m_pos; }
	D3DXVECTOR2 Size() { return m_size * m_scale; }
	D3DXVECTOR2 Anchor() { return m_anchor; }
	D3DXVECTOR2 LeftTop() { return Position() - D3DXVECTOR2(Size().x * Anchor().x, Size().y * Anchor().y); }
	D3DXVECTOR2 RightBottom() { return LeftTop() + Size(); }
	D3DXVECTOR2 Center() { return LeftTop() + Size() * 0.5f; }
	float Scale() { return m_scale; }
	float Opacity() { return m_opacity; }
	float ImageWidth() { return m_pImage->GetSize().width; }
	float ImageHeight() { return m_pImage->GetSize().height; }

	//bool IsCollided(D3DXVECTOR2 point) { return MATH->IsCollided(point, Box(Center(), Size())); }

	void Render(ID2D1RenderTarget* pRenderTarget)
	{
		// ������ ���� (�¿����)
		pRenderTarget->SetTransform(Matrix3x2F::Scale(m_dir, 1.0f, Point2F(Center().x, Center().y)));

		D2D1_RECT_F targetRect = RectF(LeftTop().x, LeftTop().y, RightBottom().x, RightBottom().y);
		D2D1_RECT_F sourceRect = RectF(m_sourcePos.x, m_sourcePos.y, m_sourcePos.x + m_sourceSize.x, m_sourcePos.y + m_sourceSize.y);

		// ��Ʈ�� ��ο�
		pRenderTarget->DrawBitmap(m_pImage, targetRect, m_opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, sourceRect);

		// ������ �ʱ�ȭ
		pRenderTarget->SetTransform(Matrix3x2F::Identity());
	}
};

#define RENDER cRenderManager::GetInstance()

class cRenderManager
{
public:
	SINGLETONE(cRenderManager);

	ID2D1Factory*			m_pFactory;
	ID2D1HwndRenderTarget*	m_pRenderTarget;
	IDWriteFactory*			m_pWriteFactory;
	IWICImagingFactory*		m_pImageFactory;

	queue<IGraphics*>		m_queGraphics;
	map<wstring, ID2D1Bitmap*> m_images;

public:
	void Init(HWND hWnd)
	{
		// ID2D1Factory ����
		D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory);

		// HwndRenderTarget ����
		m_pFactory->CreateHwndRenderTarget(
			RenderTargetProperties(),
			HwndRenderTargetProperties(hWnd, SizeU(VIEW_WIDTH, VIEW_HEIGHT)),
			&m_pRenderTarget);

		// DWriteFactory ����
		DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(*m_pWriteFactory),
			(IUnknown**)&m_pWriteFactory);

		// WICImagingFactory ����
		CoInitialize(NULL);
		CoCreateInstance(CLSID_WICImagingFactory, NULL,
			CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pImageFactory));
	}

	void Release()
	{
		SAFE_RELEASE(m_pImageFactory);
		SAFE_RELEASE(m_pWriteFactory);
		SAFE_RELEASE(m_pRenderTarget);
		SAFE_RELEASE(m_pFactory);
	}

	//Camera* CreateCamera(int tag, float maxSizeX, float maxSizeY, float sizeX, float sizeY)
	//{
	//	if (m_pCameras.find(tag) != m_pCameras.end()) return NULL;
	//
	//	ID2D1BitmapRenderTarget* pCameraTarget = NULL;
	//	m_pRenderTarget->CreateCompatibleRenderTarget(D2D1::SizeF(maxSizeX, maxSizeY), &pCameraTarget);
	//	m_pCameras[tag] = new Camera(pCameraTarget, sizeX, sizeY);
	//	return m_pCameras[tag];
	//}

	bool LoadImageFile(wstring key, wstring filename)
	{
		IWICBitmapDecoder* pDecoder = NULL;
		IWICBitmapFrameDecode* pFrameDecode = NULL;
		IWICFormatConverter* pConverter = NULL;
		ID2D1Bitmap* pBitmap = NULL;

		if (m_images.find(key) == m_images.end())
		{
			// �̹��� ������ Decoding
			m_pImageFactory->CreateDecoderFromFilename(filename.c_str(), NULL,
				GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pDecoder);
			if (pDecoder == NULL) return false;

			pDecoder->GetFrame(0, &pFrameDecode);

			// Converter ���� �� �ʱ�ȭ
			m_pImageFactory->CreateFormatConverter(&pConverter);
			pConverter->Initialize(pFrameDecode, GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone, NULL, 0, WICBitmapPaletteTypeCustom);

			// Bitmap���� ��ȯ �� ����
			m_pRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, &pBitmap);
			m_images[key] = pBitmap;
		}
		return true;
	}

	map<wstring, ID2D1Bitmap*> GetImageMap() { return m_images; }

	void DeleteImageFile()
	{
		m_images.clear();
	}

	ID2D1Bitmap* GetImage(wstring key)
	{
		if (m_images.find(key) == m_images.end()) return NULL;
		return m_images[key];
	}

	void Draw(wstring text, D3DXVECTOR2 pos, D3DXVECTOR2 size, float fontSize = 10, ColorF color = ColorF::White,
		TEXT_ALIGN align = TEXT_ALIGN_LEFT, wstring font = TEXT("Arial"))
	{
		IDWriteTextFormat* pFormat = NULL;
		m_pWriteFactory->CreateTextFormat(font.c_str(), 0,
			DWRITE_FONT_WEIGHT_REGULAR,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			fontSize, TEXT("ko"), &pFormat);

		pFormat->SetTextAlignment((DWRITE_TEXT_ALIGNMENT)align);
		m_queGraphics.push(new GText(pFormat, text, pos, size, color));
	}

	void Draw(GSprite* pSprite)
	{
		m_queGraphics.push(new GSprite(*pSprite));
	}

	void Draw(GSprite* pSprite, D3DXVECTOR2 pos)
	{
		GSprite* pNewSprite = new GSprite(*pSprite);
		pNewSprite->SetPosition(pos);
		m_queGraphics.push(pNewSprite);
	}

	void Draw(Line line, ColorF color, float lineSize = 1)
	{
		DrawLine(line.StartPoint(), line.EndPoint(), color, lineSize);
	}

	void Draw(Circle circle, ColorF color, float lineSize = 0)
	{
		DrawCircle(circle.center, circle.radius, color, lineSize);
	}

	void Draw(Box box, ColorF color, float lineSize = 1)
	{
		DrawLine(box.LeftTop(), box.RightTop(), color, lineSize);
		DrawLine(box.LeftTop(), box.LeftBottom(), color, lineSize);
		DrawLine(box.RightBottom(), box.RightTop(), color, lineSize);
		DrawLine(box.RightBottom(), box.LeftBottom(), color, lineSize);
	}

	void Draw(Triangle triangle, ColorF color, float lineSize = 1)
	{
		DrawLine(triangle.p0, triangle.p1, color, lineSize);
		DrawLine(triangle.p1, triangle.p2, color, lineSize);
		DrawLine(triangle.p2, triangle.p0, color, lineSize);
	}

	void DrawLine(D3DXVECTOR2 startPos, D3DXVECTOR2 endPos, ColorF color = ColorF::White, float lineSize = 1)
	{
		m_queGraphics.push(new GLine(startPos, endPos, color, lineSize));
	}

	void FillRect(D3DXVECTOR2 center, D3DXVECTOR2 size, ColorF color = ColorF::White)
	{
		m_queGraphics.push(new GRect(center, size, color, 0));
	}

	void DrawRect(D3DXVECTOR2 center, D3DXVECTOR2 size, ColorF color = ColorF::White, float lineSize = 1)
	{
		m_queGraphics.push(new GRect(center, size, color, lineSize));
	}

	void FillCircle(D3DXVECTOR2 center, float radius, ColorF color = ColorF::White)
	{
		m_queGraphics.push(new GCircle(center, radius, color, 0));
	}

	void DrawCircle(D3DXVECTOR2 center, float radius, ColorF color = ColorF::White, float lineSize = 1)
	{
		m_queGraphics.push(new GCircle(center, radius, color, lineSize));
	}

	//void Render()
	//{
	//	m_pRenderTarget->BeginDraw();
	//	m_pRenderTarget->Clear();
	//
	//	// ī�޶� ���
	//	map<int, Camera*>::iterator it;
	//	for (it = m_pCameras.begin(); it != m_pCameras.end(); it++)
	//	{
	//		it->second->Render(m_pRenderTarget);
	//	}
	//
	//	// ���� ���
	//	while (m_queGraphics.size() > 0)
	//	{
	//		m_queGraphics.front()->Render(m_pRenderTarget);
	//		delete m_queGraphics.front();
	//		m_queGraphics.pop();
	//	}
	//
	//	m_pRenderTarget->EndDraw();
	//}
};

