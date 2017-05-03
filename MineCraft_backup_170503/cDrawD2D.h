#pragma once

#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>		// IWICImaging
#include <wincodecsdk.h>	// IWICImaging
#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "dwrite.lib")
using namespace D2D1;

#define DRAWD2D cDrawD2D::GetInstance()

#define ANGLE_TO_RADIAN		0.0174533f
#define RADIAN_TO_ANGLE		57.2958f

enum TEXT_ALIGN
{
	TEXT_ALIGN_LEFT = 0, TEXT_ALIGN_RIGHT = 1, TEXT_ALIGN_CENTER = 2,
};

// 선분
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

// 원
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

// 사각형
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

// 삼각형
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
	D3DXVECTOR2 LeftTop() { return (Position() - D3DXVECTOR2(Size().x * Anchor().x, Size().y * Anchor().y)); }
	D3DXVECTOR2 RightBottom() { return LeftTop() + Size(); }
	D3DXVECTOR2 Center() { return LeftTop() + Size() * 0.5f; }
	float Scale() { return m_scale; }
	float Opacity() { return m_opacity; }
	float ImageWidth() { return m_pImage->GetSize().width; }
	float ImageHeight() { return m_pImage->GetSize().height; }

	//bool IsCollided(D3DXVECTOR2 point) { return MATH->IsCollided(point, Box(Center(), Size())); }

	void Render(ID2D1RenderTarget* pRenderTarget)
	{
		// 스케일 적용 (좌우반전)
		pRenderTarget->SetTransform(Matrix3x2F::Scale(m_dir, 1.0f, Point2F(Center().x, Center().y)));

		D2D1_RECT_F targetRect = RectF(LeftTop().x, LeftTop().y, RightBottom().x, RightBottom().y);
		D2D1_RECT_F sourceRect = RectF(m_sourcePos.x, m_sourcePos.y, m_sourcePos.x + m_sourceSize.x, m_sourcePos.y + m_sourceSize.y);

		// 비트맵 드로우
		pRenderTarget->DrawBitmap(m_pImage, targetRect, m_opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, sourceRect);

		// 스케일 초기화
		pRenderTarget->SetTransform(Matrix3x2F::Identity());
	}
};

class Camera
{
	ID2D1BitmapRenderTarget* m_pBitmapTarget;
	D3DXVECTOR2 m_size;
	D3DXVECTOR2 m_center;
	float m_opacity;
	D2D1_RECT_F m_screenRect;

public:
	Camera(ID2D1BitmapRenderTarget* pBitmapTarget, float sizeX, float sizeY)
	{
		m_pBitmapTarget = pBitmapTarget;
		m_pBitmapTarget->BeginDraw();
		m_pBitmapTarget->Clear(ColorF(0, 0, 0, 0));
		m_pBitmapTarget->EndDraw();
		m_size = D3DXVECTOR2(sizeX, sizeY);
		m_opacity = 1.0f;

		SetCenterPos(D3DXVECTOR2(0, 0));
		SetScreenRect(0.0f, 0.0f, sizeX, sizeY);
	}

	D3DXVECTOR2 GetPos() { return m_center; }
	D3DXVECTOR2 GetLeftTop() { return m_center - m_size * 0.5f; }
	D3DXVECTOR2 GetRightBottom() { return m_center + m_size * 0.5f; }
	void SetOpacity(float opacity) { m_opacity = opacity; }
	void SetScreenRect(float x, float y, float width, float height)
	{
		m_screenRect = RectF(x, y, x + width, y + height);
	}
	void SetCenterPos(D3DXVECTOR2 center)
	{
		m_center = center;

		AlignLeftTop();
		AlignRightBottom();
	}

	void AlignLeftTop()
	{
		D2D1_SIZE_F bitmapSize = m_pBitmapTarget->GetSize();

		D3DXVECTOR2 leftTop = GetLeftTop();
		leftTop.x = (leftTop.x < 0) ? 0.0f : leftTop.x;
		leftTop.x = (leftTop.x > bitmapSize.width) ? bitmapSize.width : leftTop.x;
		leftTop.y = (leftTop.y < 0) ? 0.0f : leftTop.y;
		leftTop.y = (leftTop.y > bitmapSize.height) ? bitmapSize.height : leftTop.y;
		m_center = leftTop + m_size * 0.5f;
	}

	void AlignRightBottom()
	{
		D2D1_SIZE_F bitmapSize = m_pBitmapTarget->GetSize();

		D3DXVECTOR2 rightBottom = GetRightBottom();
		rightBottom.x = (rightBottom.x < 0) ? 0.0f : rightBottom.x;
		rightBottom.x = (rightBottom.x > bitmapSize.width) ? bitmapSize.width : rightBottom.x;
		rightBottom.y = (rightBottom.y < 0) ? 0.0f : rightBottom.y;
		rightBottom.y = (rightBottom.y > bitmapSize.height) ? bitmapSize.height : rightBottom.y;
		m_center = rightBottom - m_size * 0.5f;
	}

	void Draw(GSprite* sprite, D3DXVECTOR2 pos, int dir = -1, float opacity = 1.0f)
	{
		m_pBitmapTarget->BeginDraw();

		sprite->SetPosition(pos);
		sprite->Render(m_pBitmapTarget);

		m_pBitmapTarget->EndDraw();
	}

	void DrawRect(D3DXVECTOR2 leftTop, D3DXVECTOR2 size,
		ColorF color = ColorF::Black, float lineSize = 1)
	{
		m_pBitmapTarget->BeginDraw();

		GRect rect(leftTop + size * 0.5, size, color, lineSize);
		rect.Render(m_pBitmapTarget);

		m_pBitmapTarget->EndDraw();
	}

	void DrawFilledRect(D3DXVECTOR2 leftTop, D3DXVECTOR2 size, ColorF color = ColorF::Black)
	{
		m_pBitmapTarget->BeginDraw();
		GRect rect(leftTop + size * 0.5, size, color, 0);
		rect.Render(m_pBitmapTarget);

		m_pBitmapTarget->EndDraw();
	}

	void Render(ID2D1RenderTarget* pRenderTarget)
	{
		ID2D1Bitmap* pBitmap = NULL;
		m_pBitmapTarget->GetBitmap(&pBitmap);

		D3DXVECTOR2 leftTop = GetLeftTop();
		pRenderTarget->DrawBitmap(pBitmap,
			m_screenRect, m_opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			RectF(leftTop.x, leftTop.y, leftTop.x + m_size.x, leftTop.y + m_size.y));

		m_pBitmapTarget->BeginDraw();
		m_pBitmapTarget->Clear(ColorF(0, 0, 0, 0));
		m_pBitmapTarget->EndDraw();
	}
};

class cDrawD2D
{
public:
	SINGLETONE(cDrawD2D);

private:
	ID2D1Factory*			m_pFactory;
	ID2D1HwndRenderTarget*	m_pRenderTarget;
	IDWriteFactory*			m_pWriteFactory;
	IWICImagingFactory*		m_pImageFactory;

	queue<IGraphics*>		m_queGraphics;
	map<wstring, ID2D1Bitmap*> m_images;

	map<int, Camera*> m_pCameras;

public:
	void Init(HWND hWnd)
	{
		// ID2D1Factory 생성
		D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory);

		// HwndRenderTarget 생성
		m_pFactory->CreateHwndRenderTarget(
			RenderTargetProperties(),
			HwndRenderTargetProperties(hWnd, SizeU(VIEW_WIDTH, VIEW_HEIGHT)),
			&m_pRenderTarget);

		// DWriteFactory 생성
		DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(*m_pWriteFactory),
			(IUnknown**)&m_pWriteFactory);

		// WICImagingFactory 생성
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

	Camera* CreateCamera(int tag, float maxSizeX, float maxSizeY, float sizeX, float sizeY)
	{
		if (m_pCameras.find(tag) != m_pCameras.end()) return NULL;

		ID2D1BitmapRenderTarget* pCameraTarget = NULL;
		m_pRenderTarget->CreateCompatibleRenderTarget(D2D1::SizeF(maxSizeX, maxSizeY), &pCameraTarget);
		m_pCameras[tag] = new Camera(pCameraTarget, sizeX, sizeY);
		return m_pCameras[tag];
	}

	Camera* GetCamera(int tag)
	{
		if (m_pCameras.find(tag) == m_pCameras.end()) return NULL;
		return m_pCameras[tag];
	}

	void DestroyCamera(int tag)
	{
		Camera* pCamera = GetCamera(tag);
		if (pCamera != NULL)
		{
			m_pCameras.erase(tag);
			delete pCamera;
		}
	}

	bool LoadImageFile(wstring key, wstring filename)
	{
		IWICBitmapDecoder* pDecoder = NULL;
		IWICBitmapFrameDecode* pFrameDecode = NULL;
		IWICFormatConverter* pConverter = NULL;
		ID2D1Bitmap* pBitmap = NULL;

		if (m_images.find(key) == m_images.end())
		{
			// 이미지 파일을 Decoding
			m_pImageFactory->CreateDecoderFromFilename(filename.c_str(), NULL,
				GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pDecoder);
			if (pDecoder == NULL) return false;

			pDecoder->GetFrame(0, &pFrameDecode);

			// Converter 생성 및 초기화
			m_pImageFactory->CreateFormatConverter(&pConverter);
			pConverter->Initialize(pFrameDecode, GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone, NULL, 0, WICBitmapPaletteTypeCustom);

			// Bitmap으로 변환 및 생성
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

	void Render()
	{
		m_pRenderTarget->BeginDraw();
		m_pRenderTarget->Clear();

		// 카메라 출력
		map<int, Camera*>::iterator it;
		for (it = m_pCameras.begin(); it != m_pCameras.end(); it++)
		{
			it->second->Render(m_pRenderTarget);
		}

		// 도형 출력
		while (m_queGraphics.size() > 0)
		{
			m_queGraphics.front()->Render(m_pRenderTarget);
			delete m_queGraphics.front();
			m_queGraphics.pop();
		}

		m_pRenderTarget->EndDraw();
	}
};

