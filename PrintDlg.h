#pragma once
#include "Case.h"
#include "MemoryDC.h"
#include "AssignItem.h"
#include "afxwin.h"

// CPrintDlg �Ի���

class CPrintDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPrintDlg)

public:
	CPrintDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CPrintDlg(CCase *pCase);
	virtual ~CPrintDlg();

// �Ի�������
	enum { IDD = IDD_PRINT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	virtual BOOL OnInitDialog();

	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);

	DECLARE_MESSAGE_MAP()
	
protected:
	//��������
	void DrawTitle(int cx, int cy);
	//����ӡ������
	void DrawTable(int cx, int cy);
	//����ͷ
	void DrawHeader(int x, int y, CCompany *pCom);
	//������
	void DrawItem(int rx, int ry, CAssignItem *pItem);
	//������󻯡���С�����رհ�ťλ��
	void SetSysmenuRect();
	CString Format(double dNum);

	CCase *m_pCase;
	CMemoryDC m_mdcBuf;			//����mdc
	CMemoryDC m_mdcTitle;		//������mdc
	CMemoryDC m_mdcTable;		//��ӡ����mdc
	CRect m_rtCls;				//�رհ�ťλ��
	CRect m_rtMax;				//��󻯰�ťλ��
	CRect m_rtMin;				//��С����ťλ��
	CRect m_preRt;				//���ǰ��λ��
	BOOL  m_bZoom;				//�Ƿ����
	CScrollBar m_scrollBarV;	//��ֱ������
	int m_nLength;				//��ʾ�����ܳ�
	int m_nCurPos;				//��������ǰ����λ��
public:
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
//	afx_msg void OnPaintClipboard(CWnd* pClipAppWnd, HGLOBAL hPaintStruct);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnDestroy();
//	afx_msg void OnNcDestroy();
};
