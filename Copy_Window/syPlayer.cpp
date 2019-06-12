#include "syPlayer.h"



syPlayer::syPlayer()
{
	m_fAlpha = 0.1f;
	m_fAngle = 0.0f;

}


syPlayer::~syPlayer()
{
}

bool syPlayer::AlphaBlendRender
(
	int iWidth, int iHeight,
	HDC hOffScreenDC,
	HDC hColorDC,
	HDC hMaskDC,
	float fAlpha
)
{
	////source copy
	void     *pvBits =0;
	HBITMAP hBitmap = CreateDIBSection(g_hScreenDC,
		&bmi, DIB_RGB_COLORS, &pvBits, NULL, 0);
	HDC dc = CreateCompatibleDC(NULL);
	SelectObject(dc, hBitmap);
	BitBlt(dc, 0,0, iWidth, iHeight,
		hColorDC,
		0,0, SRCCOPY);
	DeleteDC(dc);

	//masksource copy
	void     *pvMaskBits =0;
	HBITMAP hMaskBitmap = CreateDIBSection(g_hScreenDC,
		&bmi, DIB_RGB_COLORS, &pvMaskBits, NULL, 0);
	HDC Maskdc = CreateCompatibleDC(NULL);
	SelectObject(Maskdc, hMaskBitmap);

	BitBlt(Maskdc, 0,0, iWidth, iHeight,
		hMaskDC,
	0,0, SRCCOPY);
	DeleteDC(Maskdc);

	// offscreen copy
	void     *pvOffBits = 0;
	HBITMAP hOffBitmap = CreateDIBSection(g_hScreenDC,
		&bmi, DIB_RGB_COLORS, &pvOffBits, NULL, 0);

	HDC offdc = CreateCompatibleDC(NULL);
	SelectObject(offdc, hOffBitmap);
	BitBlt(offdc, 0,0,  iWidth, iHeight,
		g_hOffScreenDC, m_rtDraw.left, m_rtDraw.top, SRCCOPY);
	DeleteDC(offdc);

	for (int y = 0; y < iHeight; y++)
	{
		// 한줄의 시작주소
		byte* pRGB = (byte*)&((DWORD*)pvBits)[y*iWidth];
	    byte* pOffRGB = (byte*)&((DWORD*)pvOffBits)[y*iWidth];
		byte* pMaskRGB = (byte*)&((DWORD*)pvMaskBits)[y*iWidth];

		for (int x = 0; x < iWidth; x++)
		{
			// 한 픽쉘의 RGBA 값 0xaarrggbb
			byte  A = pRGB[3];
			byte  R = pRGB[2];
			byte  G = pRGB[1];
			byte  B = pRGB[0];
			byte  MaskA = pMaskRGB[3];
			byte  MaskR = pMaskRGB[2];
			byte  MaskG = pMaskRGB[1];
			byte  MaskB = pMaskRGB[0];
			byte  offA = pOffRGB[3];
			byte  offR = pOffRGB[2];
			byte  offG = pOffRGB[1];
			byte  offB = pOffRGB[0];

			if (MaskR == 255 && MaskG == 255 && MaskB == 255)
			{
				pRGB[3] = 0xff;// fAlpha; 
				pRGB[2] = offR;// *m_fFactor; // 0~1
				pRGB[1] = offG;// *m_fFactor;
				pRGB[0] = offB;// *m_fFactor;		
			}

			//else
			{
				if (  m_pos.x > 350 && m_pos.x < 450   )
				{
					pRGB[3] = 0xff;// fAlpha; 
					pRGB[2] = R;// *m_fFactor; // 0~1
					pRGB[1] = G;// *m_fFactor;
					pRGB[0] = B;// *m_fFactor;	
				}
				else
				{
					pRGB[3] = 0xff;// fAlpha; 
					pRGB[2] = R;//offR * (1.0f - fAlpha) + ((int)m_pos.x % 255) * fAlpha;// 0~1
					pRGB[1] = G;//offG * (1.0f - fAlpha) + ((int)m_pos.y % 255)  * fAlpha;
					pRGB[0] = B;//offB * (1.0f - fAlpha) + ((int)(m_pos.x+ m_pos.y) % 255)  * fAlpha;
				}
			}			  
			pRGB += 4;
			//pOffRGB += 4;
			pMaskRGB += 4;
		}
	}


	dc = CreateCompatibleDC(NULL);
	SelectObject(dc, hBitmap);

	SetStretchBltMode(g_hOffScreenDC, HALFTONE);

	StretchBlt(g_hOffScreenDC,
		m_rtColl.left, m_rtColl.top, iWidth, iHeight,
		dc, 0, 0, iWidth, iHeight,
		SRCCOPY);

	

	DeleteDC(dc);
	DeleteObject(hOffBitmap);
	DeleteObject(hBitmap);
	DeleteObject(hMaskBitmap);

	return true;

}






bool syPlayer::Init()
{


	syObject::Init();
	m_hMaskDC = CreateCompatibleDC(NULL);
	m_hColorDC = CreateCompatibleDC(NULL);


	return true;
}

void syPlayer::Set(syObjectInfo info)
{
	syObject::Set(info);
	ZeroMemory(&bmi, sizeof(BITMAPINFO));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = m_irtSize;// m_fish.m_rtObj.right;
	bmi.bmiHeader.biHeight = m_irtSize;// m_fish.m_rtObj.bottom;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = m_irtSize * m_irtSize * 4;//m_fish.m_rtObj.right * m_fish.m_rtObj.bottom * 4;

}

void syPlayer::Set(syPoint pos, RECT rt, float fSpeed)
{
	syObject::Set(pos, rt, fSpeed);
	ZeroMemory(&bmi, sizeof(BITMAPINFO));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = m_irtSize;// m_fish.m_rtObj.right;
	bmi.bmiHeader.biHeight = m_irtSize;// m_fish.m_rtObj.bottom;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = m_irtSize * m_irtSize * 4;//m_fish.m_rtObj.right * m_fish.m_rtObj.bottom * 4;

}

bool syPlayer::Render()
{
	//RotateBlt();

	syObject::Render();


	return true;
}

bool syPlayer::Release()
{
	syObject::Release();
	DeleteDC(m_hMaskDC);
	DeleteDC(m_hColorDC);
	return true;
}




bool syPlayer::RotateBlt()
{
	//1)

	
	GetRotationBimap(
		m_pBitmap->m_hMemDC,
		m_hColorDC, m_fAngle, m_irtSize, m_irtSize);
	GetRotationBimap(
		m_pBitmapMask->m_hMemDC,
		m_hMaskDC, m_fAngle, m_irtSize, m_irtSize);

	AlphaBlendRender(
		m_irtSize, m_irtSize,
		g_hOffScreenDC,
		m_hColorDC,
		m_hMaskDC,
		m_fAlpha);
	/*BitBlt(g_hOffScreenDC, m_Pos.x, m_Pos.y,
		m_irtSize, m_irtSize,	m_hMaskDC, 0, 0, SRCAND);
	BitBlt(g_hOffScreenDC, m_Pos.x, m_Pos.y,
		m_irtSize, m_irtSize, m_hColorDC, 0, 0, SRCINVERT);
	BitBlt(g_hOffScreenDC, m_Pos.x, m_Pos.y,
		m_irtSize, m_irtSize, m_hMaskDC, 0, 0, SRCINVERT);*/
	return true;
}

void syPlayer::GetRotationBimap(
	HDC dcSrc,
	HDC dcDesk,
	float fAngle, int w, int h)
{
	HBITMAP bitmap = CreateCompatibleBitmap(g_hScreenDC, w, h);
	if (bitmap == NULL)
		return;
	SelectObject(dcDesk, bitmap);

	HBRUSH hbrBrush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(dcDesk, hbrBrush);
	PatBlt(dcDesk,0,0, w,h, PATCOPY);

	//PatBlt(dcDesk, m_rtObj.left, m_rtObj.top, w, h, PATCOPY);
	DeleteObject(hbrBrush);

	// 2)
	//m_fAngle=180; // degree
	float fRadian = fAngle * 3.141592f / 180.0f;
	float fCosine = cos(fRadian);
	float fSine = sin(fRadian);
	// 3)
	XFORM  xform;
	xform.eM11 = fCosine; xform.eM12 = fSine;
	xform.eM21 = -fSine; xform.eM22 = fCosine;
	xform.eDx = w /2;
	xform.eDy = h /2;
	// 2D(x,y,z) * M(3X2) = new2D(1x2)
	int iOldGraphic = SetGraphicsMode(dcDesk, GM_ADVANCED);
	SetWorldTransform(dcDesk, &xform);


	BitBlt(dcDesk, -(m_rtObj.right / 2),
		-(m_rtObj.bottom / 2),
		m_rtObj.right, m_rtObj.bottom,
		dcSrc, m_rtObj.left, m_rtObj.top, SRCCOPY);


	xform.eM11 = 1; xform.eM12 = 0;
	xform.eM21 = 0; xform.eM22 = 1;
	xform.eDx = 0;  xform.eDy = 0;
	SetWorldTransform(dcDesk, &xform);
	SetGraphicsMode(dcDesk, iOldGraphic);

	DeleteObject(bitmap);
}