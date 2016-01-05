#include "stdafx.h"
#include "MemoryDC.h"

CMemoryDC::CMemoryDC()
{
	m_size.cx = m_size.cy = 0;
}


CMemoryDC::CMemoryDC(UINT nBitmap, CDC *pDC)
{
	LoadBitmap(nBitmap, pDC);
}


CMemoryDC::CMemoryDC(LPCWSTR szFile, CDC *pDC)
{
	LoadBitmap(szFile, pDC);
}


CMemoryDC::CMemoryDC(int cx, int cy, CDC *pDC)
{
	Create(cx, cy, pDC);
}


CMemoryDC::~CMemoryDC()
{	
	DeleteDC();
}


//创建空白位图DC
BOOL CMemoryDC::Create(int cx, int cy, CDC *pDC)
{
	if(!pDC)
		return FALSE;
	CBitmap bitmap;
	if(!bitmap.CreateCompatibleBitmap(pDC, cx, cy))
		return FALSE;
	CreateCompatibleDC(pDC);
	SelectObject(&bitmap);
	m_size.cx = cx;
	m_size.cy = cy;
	return TRUE;
}


BOOL CMemoryDC::LoadBitmap(UINT nBitmap, CDC *pDC)
{
	CBitmap bitmap;
	if(!bitmap.LoadBitmapW(nBitmap))
		return FALSE;
	CreateCompatibleDC(pDC);
	SelectObject(&bitmap);
	BITMAP bmp;
	bitmap.GetBitmap(&bmp);
	m_size.cx = bmp.bmWidth;
	m_size.cy = bmp.bmHeight;
	return TRUE;
}


BOOL CMemoryDC::LoadBitmap(LPCWSTR szFile, CDC *pDC)
{
	HBITMAP hBitmap = (HBITMAP)LoadImageW(NULL,szFile,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	if(!hBitmap)
		return FALSE;
	CreateCompatibleDC(pDC);
	SelectObject(hBitmap);
	BITMAP bmp;
	CBitmap::FromHandle(hBitmap)->GetBitmap(&bmp);
	m_size.cx = bmp.bmWidth;
	m_size.cy = bmp.bmHeight;
	return TRUE;
}

BOOL CMemoryDC::ChangeBitmap(int cx, int cy)
{
	if(!GetSafeHdc())
		return FALSE;
	CBitmap bitmap, *preBmp;
	if(!bitmap.CreateCompatibleBitmap(this, cx, cy))
		return FALSE;
	preBmp = SelectObject(&bitmap);
	m_size.cx = cx;
	m_size.cy = cy;
	preBmp->DeleteObject();
	return TRUE;
}


BOOL CMemoryDC::DeleteDC()
{
	if(!GetSafeHdc())
		return FALSE;
	CBitmap *pBitmap = GetCurrentBitmap();
	if(!CDC::DeleteDC())
		return FALSE;
	if(pBitmap)
		return pBitmap->DeleteObject();
	return TRUE;
}


CFont * CMemoryDC::SetFont(CFont &font, int nHeight,int nWeight,LPCTSTR lpszFacename)
{
	CFont *preFont;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));       
	lf.lfHeight = nHeight;            
	lf.lfWeight = nWeight;
	_tcsncpy_s(lf.lfFaceName, LF_FACESIZE, lpszFacename, 7);         
	if(font.GetSafeHandle())
		font.DeleteObject();
	font.CreateFontIndirect(&lf);
	preFont = SelectObject(&font);
	return preFont;
}


CBrush * CMemoryDC::SetBrush(CBrush &brush, COLORREF crColor)
{
	CBrush *preBrush;
	brush.CreateSolidBrush(crColor);
	preBrush = SelectObject(&brush);
	return preBrush;
}


int CMemoryDC::GetWidth()
{
	return m_size.cx;
}


int CMemoryDC::GetHeight()
{
	return m_size.cy;
}

void CMemoryDC::BitTrans(int nXDest,				//目标起点X Y
						 int nYDest, 
						 int nWidthDest,			//目标宽度 高度
						 int nHeightDest, 
						 CDC *pDC,					//目标DC
						 int nXSrc,				//来源起点X Y
						 int nYSrc,				
						 COLORREF crTrans			//透明色
						)
{
	//复制原图到临时DC
	CMemoryDC dcImage(nWidthDest,nHeightDest,pDC);
	dcImage.BitBlt(0,0,nWidthDest,nHeightDest,this,nXSrc,nYSrc,SRCCOPY);

	//构造与原图同等大小的黑白色位图，加入掩码DC中
	CBitmap bmpMask;
	bmpMask.CreateBitmap(nWidthDest,nHeightDest,1,1,NULL);
	CDC dcMask;
	dcMask.CreateCompatibleDC(pDC);
	dcMask.SelectObject(&bmpMask);	

	//复制临时DC到掩码DC，掩码DC的透明区域变成白色，其它区域变成黑色
	dcImage.SetBkColor(crTrans);
	dcMask.BitBlt(0,0,nWidthDest,nHeightDest,&dcImage,0,0,SRCCOPY);

	dcImage.SetBkColor(RGB(0,0,0));
	dcImage.SetTextColor(RGB(255,255,255));
	dcImage.BitBlt(0,0,nWidthDest,nHeightDest,&dcMask,0,0,SRCAND);

	//pDC->SetBkColor(RGB(255,255,255));
	//pDC->SetTextColor(RGB(0,0,0));
	pDC->BitBlt(nXDest,nYDest,nWidthDest,nHeightDest,&dcMask,0,0,SRCAND);
	pDC->BitBlt(nXDest,nYDest,nWidthDest,nHeightDest,&dcImage,0,0,SRCPAINT);
}

void CMemoryDC::StretchTrans(int nXDest,				//目标起点X Y
							 int nYDest, 
							 int nWidthDest,			//目标宽度 高度
							 int nHeightDest, 
							 CDC *pDC,					//目标DC
							 int nXSrc,					//来源起点X Y
							 int nYSrc,				
							 int nWidthSrc,				//来源宽度  高度
							 int nHeightSrc,			
							 COLORREF crTrans			//透明色
							)
{
	//复制原图到临时DC
	CMemoryDC dcImage(nWidthDest,nHeightDest,pDC);
	if(nWidthDest == nWidthSrc && nHeightDest == nHeightSrc)
		dcImage.BitBlt(0,0,nWidthDest,nHeightDest,this,nXSrc,nYSrc,SRCCOPY);
	else
		dcImage.StretchBlt(0,0,nWidthDest,nHeightDest,this,nXSrc,nYSrc,nWidthSrc,nHeightSrc,SRCCOPY);

	//构造与原图同等大小的黑白色位图，加入掩码DC中
	CBitmap bmpMask;
	bmpMask.CreateBitmap(nWidthDest,nHeightDest,1,1,NULL);
	CDC dcMask;
	dcMask.CreateCompatibleDC(pDC);
	dcMask.SelectObject(&bmpMask);	

	//复制临时DC到掩码DC，掩码DC的透明区域变成白色，其它区域变成黑色
	dcImage.SetBkColor(crTrans);
	dcMask.BitBlt(0,0,nWidthDest,nHeightDest,&dcImage,0,0,SRCCOPY);

	dcImage.SetBkColor(RGB(0,0,0));
	dcImage.SetTextColor(RGB(255,255,255));
	dcImage.BitBlt(0,0,nWidthDest,nHeightDest,&dcMask,0,0,SRCAND);

	//pDC->SetBkColor(RGB(255,255,255));
	//pDC->SetTextColor(RGB(0,0,0));
	pDC->BitBlt(nXDest,nYDest,nWidthDest,nHeightDest,&dcMask,0,0,SRCAND);
	pDC->BitBlt(nXDest,nYDest,nWidthDest,nHeightDest,&dcImage,0,0,SRCPAINT);
}