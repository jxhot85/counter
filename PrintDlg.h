#pragma once
#include "Case.h"
#include "MemoryDC.h"
#include "AssignItem.h"
#include "afxwin.h"

// CPrintDlg 对话框

class CPrintDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPrintDlg)

public:
	CPrintDlg(CWnd* pParent = NULL);   // 标准构造函数
	CPrintDlg(CCase *pCase);
	virtual ~CPrintDlg();

// 对话框数据
	enum { IDD = IDD_PRINT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
	//画标题栏
	void DrawTitle(int cx, int cy);
	//画打印表内容
	void DrawTable(int cx, int cy);
	//画表头
	void DrawHeader(int x, int y, CCompany *pCom);
	//画表项
	void DrawItem(int rx, int ry, CAssignItem *pItem);
	//设置最大化、最小化、关闭按钮位置
	void SetSysmenuRect();
	CString Format(double dNum);

	CCase *m_pCase;
	CMemoryDC m_mdcBuf;			//缓冲mdc
	CMemoryDC m_mdcTitle;		//标题栏mdc
	CMemoryDC m_mdcTable;		//打印内容mdc
	CRect m_rtCls;				//关闭按钮位置
	CRect m_rtMax;				//最大化按钮位置
	CRect m_rtMin;				//最小化按钮位置
	CRect m_preRt;				//最大化前的位置
	BOOL  m_bZoom;				//是否最大化
	CScrollBar m_scrollBarV;	//垂直滚动条
	int m_nLength;				//显示内容总长
	int m_nCurPos;				//滚动条当前所在位置
public:
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
//	afx_msg void OnPaintClipboard(CWnd* pClipAppWnd, HGLOBAL hPaintStruct);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnDestroy();
//	afx_msg void OnNcDestroy();
};
