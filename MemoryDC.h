#ifndef _MEMORYDC_H
#define _MEMORYDC_H

class CMemoryDC : public CDC
{
public:
	CMemoryDC();
	CMemoryDC(UINT nBitmap, CDC *pDC = NULL);
	CMemoryDC(LPCWSTR szFile, CDC *pDC = NULL);
	CMemoryDC(int cx, int cy, CDC *pDC = NULL);
	~CMemoryDC();

	BOOL Create(int cx, int cy, CDC *pDC);
	BOOL LoadBitmap(UINT nBitmap, CDC *pDC = NULL);
	BOOL LoadBitmap(LPCWSTR szFile, CDC *pDC = NULL);
	BOOL DeleteDC();
	//调整位图大小
	BOOL ChangeBitmap(int cx, int cy);
	//设置字体 font为空字体的引用，因为局部作用域的原因会导致外部失效
	CFont * SetFont(CFont &font, int nHeight,int nWeight,LPCTSTR lpszFacename);
	//设置画刷
	CBrush * SetBrush(CBrush &brush, COLORREF crColor);

	int GetWidth(); 
	int GetHeight();

	void BitTrans(int nXDest,				//目标起点X Y
				  int nYDest, 
				  int nWidthDest,			//目标宽度 高度
				  int nHeightDest, 
				  CDC *pDC,					//目标DC
				  int nXSrc,				//来源起点X Y
				  int nYSrc,				
				  COLORREF crTrans			//透明色
				  );
	void StretchTrans(int nXDest,				//目标起点X Y
					 int nYDest, 
					 int nWidthDest,			//目标宽度 高度
					 int nHeightDest, 
					 CDC *pDC,					//目标DC
					 int nXSrc,					//来源起点X Y
					 int nYSrc,				
					 int nWidthSrc,				//来源宽度  高度
					 int nHeightSrc,			
					 COLORREF crTrans			//透明色
				     );
private:
	CSize m_size;
};

#endif