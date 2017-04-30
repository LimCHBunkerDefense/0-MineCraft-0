#include "stdafx.h"
#include "cRenderManager.h"


cRenderManager::cRenderManager() :
	m_pFactory(NULL),
	m_pRenderTarget(NULL),
	m_pWriteFactory(NULL),
	m_pImageFactory(NULL)
{
}


cRenderManager::~cRenderManager()
{
	Release();
}

void cRenderManager::Init(HWND hWnd)
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

void cRenderManager::Release()
{
	SAFE_RELEASE(m_pImageFactory);
	SAFE_RELEASE(m_pWriteFactory);
	SAFE_RELEASE(m_pRenderTarget);
	SAFE_RELEASE(m_pFactory);
	// release 수정 중
	//queue<IGraphics*>		m_queGraphics;
	//map<wstring, ID2D1Bitmap*> m_images;
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
//
//Camera* GetCamera(int tag)
//{
//	if (m_pCameras.find(tag) == m_pCameras.end()) return NULL;
//	return m_pCameras[tag];
//}

bool cRenderManager::LoadImageFile(wstring key, wstring filename)
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

map<wstring, ID2D1Bitmap*> cRenderManager::GetImageMap() { return m_images; }

void cRenderManager::DeleteImageFile()
{
	m_images.clear();
}

ID2D1Bitmap* cRenderManager::GetImage(wstring key)
{
	if (m_images.find(key) == m_images.end()) return NULL;
	return m_images[key];
}

void cRenderManager::Draw(wstring text, D3DXVECTOR2 pos, D3DXVECTOR2 size, float fontSize = 10, ColorF color = ColorF::White,
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

void cRenderManager::Draw(GSprite* pSprite)
{
	m_queGraphics.push(new GSprite(*pSprite));
}

void cRenderManager::Draw(GSprite* pSprite, D3DXVECTOR2 pos)
{
	GSprite* pNewSprite = new GSprite(*pSprite);
	pNewSprite->SetPosition(pos);
	m_queGraphics.push(pNewSprite);
}

void cRenderManager::Draw(Line line, ColorF color, float lineSize = 1)
{
	DrawLine(line.StartPoint(), line.EndPoint(), color, lineSize);
}

void cRenderManager::Draw(Circle circle, ColorF color, float lineSize = 0)
{
	DrawCircle(circle.center, circle.radius, color, lineSize);
}

void cRenderManager::Draw(Box box, ColorF color, float lineSize = 1)
{
	DrawLine(box.LeftTop(), box.RightTop(), color, lineSize);
	DrawLine(box.LeftTop(), box.LeftBottom(), color, lineSize);
	DrawLine(box.RightBottom(), box.RightTop(), color, lineSize);
	DrawLine(box.RightBottom(), box.LeftBottom(), color, lineSize);
}

void cRenderManager::Draw(Triangle triangle, ColorF color, float lineSize = 1)
{
	DrawLine(triangle.p0, triangle.p1, color, lineSize);
	DrawLine(triangle.p1, triangle.p2, color, lineSize);
	DrawLine(triangle.p2, triangle.p0, color, lineSize);
}

void cRenderManager::DrawLine(D3DXVECTOR2 startPos, D3DXVECTOR2 endPos, ColorF color = ColorF::White, float lineSize = 1)
{
	m_queGraphics.push(new GLine(startPos, endPos, color, lineSize));
}

void cRenderManager::FillRect(D3DXVECTOR2 center, D3DXVECTOR2 size, ColorF color = ColorF::White)
{
	m_queGraphics.push(new GRect(center, size, color, 0));
}

void cRenderManager::DrawRect(D3DXVECTOR2 center, D3DXVECTOR2 size, ColorF color = ColorF::White, float lineSize = 1)
{
	m_queGraphics.push(new GRect(center, size, color, lineSize));
}

void cRenderManager::FillCircle(D3DXVECTOR2 center, float radius, ColorF color = ColorF::White)
{
	m_queGraphics.push(new GCircle(center, radius, color, 0));
}

void cRenderManager::DrawCircle(D3DXVECTOR2 center, float radius, ColorF color = ColorF::White, float lineSize = 1)
{
	m_queGraphics.push(new GCircle(center, radius, color, lineSize));
}

void cRenderManager::Render()
{
	m_pRenderTarget->BeginDraw();
	m_pRenderTarget->Clear();

	// 카메라 출력
	//map<int, Camera*>::iterator it;
	//for (it = m_pCameras.begin(); it != m_pCameras.end(); it++)
	//{
	//	it->second->Render(m_pRenderTarget);
	//}

	// 도형 출력
	while (m_queGraphics.size() > 0)
	{
		m_queGraphics.front()->Render(m_pRenderTarget);
		delete m_queGraphics.front();
		m_queGraphics.pop();
	}

	m_pRenderTarget->EndDraw();
}