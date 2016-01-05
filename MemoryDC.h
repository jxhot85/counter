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
	//����λͼ��С
	BOOL ChangeBitmap(int cx, int cy);
	//�������� fontΪ����������ã���Ϊ�ֲ��������ԭ��ᵼ���ⲿʧЧ
	CFont * SetFont(CFont &font, int nHeight,int nWeight,LPCTSTR lpszFacename);
	//���û�ˢ
	CBrush * SetBrush(CBrush &brush, COLORREF crColor);

	int GetWidth(); 
	int GetHeight();

	void BitTrans(int nXDest,				//Ŀ�����X Y
				  int nYDest, 
				  int nWidthDest,			//Ŀ���� �߶�
				  int nHeightDest, 
				  CDC *pDC,					//Ŀ��DC
				  int nXSrc,				//��Դ���X Y
				  int nYSrc,				
				  COLORREF crTrans			//͸��ɫ
				  );
	void StretchTrans(int nXDest,				//Ŀ�����X Y
					 int nYDest, 
					 int nWidthDest,			//Ŀ���� �߶�
					 int nHeightDest, 
					 CDC *pDC,					//Ŀ��DC
					 int nXSrc,					//��Դ���X Y
					 int nYSrc,				
					 int nWidthSrc,				//��Դ���  �߶�
					 int nHeightSrc,			
					 COLORREF crTrans			//͸��ɫ
				     );
private:
	CSize m_size;
};

#endif