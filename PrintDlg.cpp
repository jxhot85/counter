// PrintDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Counter.h"
#include "PrintDlg.h"
#include "afxdialogex.h"
#include "Company.h"
#include "Third.h"	



const int g_nRowWidth = COL_WIDTH * COL_NUM;		//行宽度
const int g_nGap = (TITLE_HEIGHT - SYSMENU_RECT)/2;	//既是按钮间隔距离，也是按钮与标题栏的间隔距离
const UINT g_nFormat = DT_CENTER | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS;	//DrawText格式 水平垂直居中


// CPrintDlg 对话框

IMPLEMENT_DYNAMIC(CPrintDlg, CDialogEx)

CPrintDlg::CPrintDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPrintDlg::IDD, pParent)
{
	
}

CPrintDlg::CPrintDlg(CCase *pCase):m_pCase(pCase), m_bZoom(FALSE), m_nCurPos(0)
{
}

CPrintDlg::~CPrintDlg()
{
	m_pCase->Release();
}

void CPrintDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPrintDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_NCHITTEST()
	ON_WM_MOUSEMOVE()
	ON_WM_NCMOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_VSCROLL()
//	ON_WM_PAINTCLIPBOARD()
ON_WM_GETMINMAXINFO()
ON_WM_MOUSEWHEEL()
ON_WM_DESTROY()
//ON_WM_NCDESTROY()
END_MESSAGE_MAP()


// CPrintDlg 消息处理程序


BOOL CPrintDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CPrintDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rect;
	GetClientRect(&rect);
	dc.BitBlt(0,0,rect.right,rect.bottom,&m_mdcBuf,0,0,SRCCOPY);
	CBrush brush;
	brush.CreateSolidBrush(TITLE_COLOR);
	dc.FrameRect(&rect, &brush);
}


int CPrintDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	int nTable, nItem;
	m_pCase->GetCount(nTable,nItem);
	m_nLength = (TABLE_GAP + HEAD_HEIGHT) * nTable + ROW_HEIGHT * nItem + TABLE_BOTTOM_GAP;		//打印内容总长
	//创建m_mdcBuf m_mdcTitle  m_mdcTable
	m_mdcBuf.Create(rect.right, rect.bottom, &dc);
	m_mdcTitle.Create(rect.right, TITLE_HEIGHT, &dc);
	m_mdcTable.Create(g_nRowWidth, m_nLength, &dc);
	//画打印内容
	DrawTable(g_nRowWidth, m_nLength);

	//滚动条
	m_scrollBarV.Create(SBS_VERT | WS_CHILD | WS_VISIBLE | SIF_PAGE, CRect(0,0,0,0), this, IDC_SCROLLBARV);
	m_scrollBarV.SetScrollPos(0);
	
	return 0;
}


void CPrintDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if(cx ==0 && cy == 0)
		return;
	int nWidth = 0;
	//滚动条
	if(m_nLength > cy - TITLE_HEIGHT){
		m_scrollBarV.ShowScrollBar(TRUE);
		m_scrollBarV.MoveWindow(cx - SCROLL_WIDTH - RESIZE_GAP, TITLE_HEIGHT, SCROLL_WIDTH, cy - TITLE_HEIGHT - RESIZE_GAP, FALSE);
		m_scrollBarV.SetScrollRange(0, m_nLength - (cy - TITLE_HEIGHT));
		nWidth = SCROLL_WIDTH;
	}
	else{
		m_scrollBarV.ShowScrollBar(FALSE);
		m_nCurPos = 0;
	}
	m_scrollBarV.SetScrollPos(m_nCurPos);

	m_mdcBuf.ChangeBitmap(cx, cy);
	m_mdcBuf.FillSolidRect(0, 0, cx, cy, CLT_BK_COLOR);
	//重画标题栏
	DrawTitle(cx,TITLE_HEIGHT);
	m_mdcBuf.BitBlt(0, 0, cx, TITLE_HEIGHT, &m_mdcTitle, 0, 0, SRCCOPY);
	m_mdcBuf.BitBlt((cx - nWidth - g_nRowWidth)/2, TITLE_HEIGHT, g_nRowWidth, cy - TITLE_HEIGHT, &m_mdcTable, 0, m_nCurPos, SRCCOPY);

	
	/*SCROLLINFO info;
	m_scrollBarV.GetScrollInfo(&info, SIF_ALL);
	info.nPage = cy - TITLE_HEIGHT;
	m_scrollBarV.SetScrollInfo(&info);*/
	
	Invalidate(FALSE);
}


void CPrintDlg::SetSysmenuRect()
{
	CRect rect;
	GetClientRect(&rect);
	int nGap = SYSMENU_RECT + g_nGap;	
	m_rtCls.SetRect(rect.right - nGap, g_nGap, rect.right - g_nGap, nGap);
	m_rtMax = m_rtCls;
	m_rtMax.OffsetRect(-nGap, 0);
	m_rtMin = m_rtMax;
	m_rtMin.OffsetRect(-nGap, 0);
}


void CPrintDlg::DrawTitle(int cx, int cy)
{
	//调整位图大小
	m_mdcTitle.ChangeBitmap(cx, cy);
	//填充颜色
	CBrush brush;
	brush.CreateSolidBrush(TITLE_COLOR);
	m_mdcTitle.FillRect(CRect(0,0,cx,cy), &brush);
	//标题字
	CFont font, *preFont;
	CRect rect(0,0,cx,cy);
	int preMode = m_mdcTitle.SetBkMode(TRANSPARENT);
	preFont = m_mdcTitle.SetFont(font,15, FW_BOLD, _T("仿宋"));
	COLORREF preClr = m_mdcTitle.SetTextColor(RGB(255,201,14));
	m_mdcTitle.DrawText(_T(" 路桥法院民一庭"),&rect,DT_LEFT | DT_SINGLELINE | DT_VCENTER);
	m_mdcTitle.SetTextColor(preClr);
	m_mdcTitle.SetFont(font,30, FW_BOLD, _T("宋体"));
	m_mdcTitle.DrawText(_T("计算结果表"),&rect,DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	m_mdcTitle.SelectObject(preFont);
	m_mdcTitle.SetBkMode(preMode);
	//最大化最小化关闭按钮
	SetSysmenuRect();	//设置最大化最小化关闭按钮位置
	CPen pen, *prePen;
	pen.CreatePen(PS_SOLID, 5, RGB(255,255,255));
	prePen = m_mdcTitle.SelectObject(&pen);
	m_mdcTitle.SelectStockObject(NULL_BRUSH);
	m_mdcTitle.MoveTo(m_rtCls.left, m_rtCls.top);
	m_mdcTitle.LineTo(m_rtCls.right, m_rtCls.bottom);
	m_mdcTitle.MoveTo(m_rtCls.left, m_rtCls.bottom);
	m_mdcTitle.LineTo(m_rtCls.right, m_rtCls.top);
	m_mdcTitle.MoveTo(m_rtMax.left, m_rtMax.top);
	m_mdcTitle.Rectangle(&m_rtMax);
	m_mdcTitle.MoveTo(m_rtMin.left, cy/2);
	m_mdcTitle.LineTo(m_rtMin.right, cy/2);
	m_mdcTitle.SelectObject(prePen);
}


void CPrintDlg::DrawTable(int cx, int cy)
{
	m_mdcTable.FillSolidRect(0, 0, cx, cy, TABLE_BK_COLOR);
	//提示内容
	CFont font, *preFt;
	font.CreatePointFont(120,_T("Arial"));
	int preColor = m_mdcTable.SetTextColor(RGB(255,0,0));
	preFt = m_mdcTable.SelectObject(&font);
	m_mdcTable.SetBkMode(TRANSPARENT);
	m_mdcTable.TextOutW(0,10,_T("注意：医疗、死伤、财产是四舍五入后的结果，与后面合计的值会在某些时候出现不一致"));
	m_mdcTable.SelectObject(preFt);
	m_mdcTable.SetTextColor(preColor);
	m_mdcTable.SelectStockObject(BLACK_PEN);
	///////////////////画表//////////////////////////
	//第一张表起点坐标
	int x = 0;		
	int y = TABLE_GAP;
	//获取保险公司链表
	list<CCompany *> &listcom = m_pCase->GetListCompany();
	list<CCompany *>::iterator com_Iter = listcom.begin();
	for( ; com_Iter!=listcom.end(); com_Iter++)
	{
		CCompany *pCom = *com_Iter;
		//画表头
		DrawHeader(x, y, pCom);
		//画表项
		//设置首行右上角起点
		int rx = x;
		int ry = y + HEAD_HEIGHT;
		//获取每个保险公司对象的分配链表
		list<CAssignItem *> &listAssign = pCom->GetListAssign();
		list<CAssignItem *>::iterator asgn_Iter = listAssign.begin();
		for(int i=0; asgn_Iter != listAssign.end(); asgn_Iter++, i++)
		{
			CAssignItem *pItem = *asgn_Iter;
			//画表项
			DrawItem(rx, ry, pItem);
			//更新下一行的右上角坐标(rx不变，ry递增一行）
			ry += ROW_HEIGHT;
		}
		//画垂直分隔线,直线起点：x1,y1　　终点：x2,y2
		int x1 = x + COL_WIDTH; 
		int y1 = y + HEAD_HEIGHT/2;
		int x2 = x1;
		int y2 = ry;
		for(int i=0;i<COL_NUM-1;i++)
		{
			m_mdcTable.MoveTo(x1, y1);
			m_mdcTable.LineTo(x2, y2);
			x1 += COL_WIDTH;
			x2 += COL_WIDTH;
		}
		//更新下一张表的右上角坐标
		y = ry + TABLE_GAP;
	}
}


void CPrintDlg::DrawHeader(int x, int y, CCompany *pCom)
{
	//设置字体、画刷
	CFont font, *preFont;
	CBrush brush, *preBrush;
	preFont = m_mdcTable.SetFont(font, 20, FW_BOLD, _T("宋体"));
	preBrush = m_mdcTable.SetBrush(brush, TABLE_HD_COLOR);
	//画表头框架
	CRect rectCell;     //单元格矩形
	m_mdcTable.Rectangle(x, y, x + g_nRowWidth, y + HEAD_HEIGHT);
	m_mdcTable.Rectangle(x + COL_WIDTH, y, x + g_nRowWidth - COL_WIDTH+1, y + HEAD_HEIGHT / 2);
	//填写表项
	rectCell.SetRect(x, y, x + COL_WIDTH, y + HEAD_HEIGHT);
	m_mdcTable.DrawText(_T("第三者"), &rectCell, g_nFormat);
	rectCell.SetRect(x + COL_WIDTH, y, x + g_nRowWidth - COL_WIDTH, y + HEAD_HEIGHT / 2);
	CString str;
	if(pCom->GetDutyC() == 0.0)
		str = _T(" (无责)");
	else if(pCom->GetDutyC() == 100.0)
		str = _T(" (全责)");
	else
		str.Format(_T(" (%s%%)"), Format(pCom->GetDutyC()*100));
	m_mdcTable.DrawText(pCom->GetCompany()+str, &rectCell, g_nFormat);
	rectCell.SetRect(x + COL_WIDTH, y + HEAD_HEIGHT/2, x + 2*COL_WIDTH, y + HEAD_HEIGHT);
	m_mdcTable.DrawText(_T("医疗费用"), &rectCell, g_nFormat);
	rectCell.OffsetRect(COL_WIDTH,0);
	m_mdcTable.DrawText(_T("死亡伤残"), &rectCell, g_nFormat);
	rectCell.OffsetRect(COL_WIDTH,0);
	m_mdcTable.DrawText(_T("财产损失"), &rectCell, g_nFormat);
	rectCell.OffsetRect(COL_WIDTH,0);
	m_mdcTable.DrawText(_T("交强险"), &rectCell, g_nFormat);
	rectCell.OffsetRect(COL_WIDTH,0);
	m_mdcTable.DrawText(_T("商业险"), &rectCell, g_nFormat);
	rectCell.OffsetRect(COL_WIDTH,0);
	m_mdcTable.DrawText(_T("保险合计"), &rectCell, g_nFormat);
	rectCell.SetRect(x + g_nRowWidth - COL_WIDTH, y, x + g_nRowWidth, y + HEAD_HEIGHT);
	m_mdcTable.DrawText(pCom->GetInsured(), &rectCell, g_nFormat);
	//恢复字体、画刷
	m_mdcTable.SelectObject(preFont);
	m_mdcTable.SelectObject(preBrush);
}


//小数部分为0则转为整数，否则保留4位小数
CString CPrintDlg::Format(double dNum)
{
	CString str;
	str.Format(_T("%.2lf"), dNum);
	if(str.Mid(str.GetLength() - 2, 2) == _T("00")){
		str.TrimRight(_T('0'));
		str.TrimRight(_T('.'));
	}
	return str;
}


void CPrintDlg::DrawItem(int rx, int ry, CAssignItem *pItem)
{
	//设置字体、画刷
	CFont font, *preFont;
	preFont = m_mdcTable.SetFont(font, 15, FW_REGULAR, _T("宋体"));
	m_mdcTable.SelectStockObject(HOLLOW_BRUSH);
	//画行
	CRect rectCell;     //单元格矩形
	m_mdcTable.Rectangle(rx, ry, rx + g_nRowWidth, ry + ROW_HEIGHT);
	//取数据
	AssignItem item = {0.0};
	pItem->GetItem(item);
	//填入数据
	CString str;		//格式化字符串用
	rectCell.SetRect(rx, ry, rx + COL_WIDTH, ry + ROW_HEIGHT);		//行的首列
	m_mdcTable.DrawText(pItem->getThird()->GetName(), &rectCell, g_nFormat);					//填写第三者
	rectCell.OffsetRect(COL_WIDTH,0);				//第二列医疗费用
	//str.Format(_T("%.2lf"), item.dAssignM);		
	m_mdcTable.DrawText(Format(item.dAssignM), &rectCell, g_nFormat);
	rectCell.OffsetRect(COL_WIDTH,0);				//第三列死亡伤残
	//str.Format(_T("%.2lf"), item.dAssignD);							
	m_mdcTable.DrawText(Format(item.dAssignD), &rectCell, g_nFormat);
	rectCell.OffsetRect(COL_WIDTH,0);				//第四列财产损失
	//str.Format(_T("%.2lf"), item.dAssignP);							
	m_mdcTable.DrawText(Format(item.dAssignP), &rectCell, g_nFormat);
	rectCell.OffsetRect(COL_WIDTH,0);				//第五列交强险小计
	//str.Format(_T("%.2lf"), pItem->SumJQX());				
	m_mdcTable.DrawText(Format(pItem->SumJQX()), &rectCell, g_nFormat);
	rectCell.OffsetRect(COL_WIDTH,0);				//第六列商业险				
	//str.Format(_T("%.2lf"), item.dAssignB);
	m_mdcTable.DrawText(Format(item.dAssignB), &rectCell, g_nFormat);
	rectCell.OffsetRect(COL_WIDTH,0);				//第七列保险合计				
	//str.Format(_T("%.2lf"), pItem->SumInsurance());
	m_mdcTable.DrawText(Format(pItem->SumInsurance()), &rectCell, g_nFormat);
	rectCell.OffsetRect(COL_WIDTH,0);
	//str.Format(_T("%.2lf"), item.dAssignI);
	m_mdcTable.DrawText(Format(item.dAssignI), &rectCell, g_nFormat);
	//恢复字体、画刷
	m_mdcTable.SelectObject(preFont);
}

LRESULT CPrintDlg::OnNcHitTest(CPoint point)
{
	LRESULT nHitTest = CDialogEx::OnNcHitTest(point);

	CRect rect;
	GetClientRect(&rect);
	ScreenToClient(&point);

	if(m_rtMin.PtInRect(point) || m_rtMax.PtInRect(point) || m_rtCls.PtInRect(point))
		nHitTest =  HTCLIENT;
	else if(point.x >= rect.right - RESIZE_GAP && point.y >= rect.bottom - RESIZE_GAP)
		nHitTest = HTBOTTOMRIGHT;
	else if(point.x >= rect.right - RESIZE_GAP)
		nHitTest = HTRIGHT;
	else if(point.y >= rect.bottom - RESIZE_GAP)
		nHitTest = HTBOTTOM;
	else if(point.y <= TITLE_HEIGHT)
		nHitTest = HTCAPTION;

	return nHitTest;
}


void CPrintDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	HCURSOR hCursor;
	if(m_rtCls.PtInRect(point) || m_rtMax.PtInRect(point) || m_rtMin.PtInRect(point))
		hCursor = ::LoadCursor(NULL, IDC_HAND);
	else
		hCursor = ::LoadCursor(NULL, IDC_ARROW);

	::SetCursor(hCursor);

	CDialogEx::OnMouseMove(nFlags, point);
}


void CPrintDlg::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	HCURSOR hCursor; 
    if(nHitTest == HTBOTTOMRIGHT)
        hCursor = LoadCursor(NULL, IDC_SIZENWSE);
    else if(nHitTest == HTRIGHT)
        hCursor = LoadCursor(NULL, IDC_SIZEWE);
    else if(nHitTest == HTBOTTOM)
        hCursor = LoadCursor(NULL, IDC_SIZENS);
	else
		hCursor = LoadCursor(NULL,IDC_ARROW);
	::SetCursor(hCursor);

	CDialogEx::OnNcMouseMove(nHitTest, point);
}


void CPrintDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(m_rtCls.PtInRect(point))
		this->DestroyWindow();
		//CDialogEx::OnCancel();
	else if(m_rtMax.PtInRect(point))
	{
		if(m_bZoom)
		{
			MoveWindow(&m_preRt);
			m_bZoom = FALSE;
		}
		else
		{
			CRect rect;
			GetWindowRect(&rect);
			m_preRt = rect;
			::SystemParametersInfo(SPI_GETWORKAREA,0,&rect,0);
			MoveWindow(&rect);
			m_bZoom = TRUE;
		}
	}
	else if(m_rtMin.PtInRect(point))
		ShowWindow(SW_SHOWMINIMIZED);

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CPrintDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CPrintDlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	if(!m_bZoom){
		if (nHitTest == HTBOTTOM)
			PostMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOM, MAKELPARAM(point.x, point.y));
		else if (nHitTest == HTRIGHT)
			PostMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_RIGHT, MAKELPARAM(point.x, point.y));
		else if (nHitTest == HTBOTTOMRIGHT)
			PostMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMRIGHT, MAKELPARAM(point.x, point.y));
	}

	CDialogEx::OnNcLButtonDown(nHitTest, point);
}


void CPrintDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int minPos, maxPos;
	m_scrollBarV.GetScrollRange(&minPos, &maxPos);  
	int curPos = m_scrollBarV.GetScrollPos();
	switch(nSBCode)
	{
	case SB_LINEUP:
		if(curPos > minPos)
			curPos = max(minPos, curPos - SCROLL_PIX);
		break;
	case SB_LINEDOWN:
		if(curPos < maxPos)
			curPos = min(maxPos, curPos + SCROLL_PIX);
		break;
	case SB_PAGEUP:
		if (curPos > minPos)
			curPos = max(minPos, 3*SCROLL_PIX);
		break;
	case SB_PAGEDOWN:
		if (curPos < maxPos)
			curPos = min(maxPos, 3*SCROLL_PIX);
		break;
	case SB_TOP:
		curPos = minPos;
		break;
	case SB_BOTTOM:
		curPos = maxPos;
		break;
	case SB_THUMBPOSITION:
		curPos = nPos;
		break;
	default:
		return;
	}
	// 设置滚动块位置   
	m_nCurPos = curPos;
    m_scrollBarV.SetScrollPos(m_nCurPos); 

	CRect rect;
	GetClientRect(&rect);
	m_mdcBuf.FillSolidRect(0, TITLE_HEIGHT, rect.right, rect.bottom - TITLE_HEIGHT, CLT_BK_COLOR);
	m_mdcBuf.BitBlt((rect.right - SCROLL_WIDTH - g_nRowWidth)/2, TITLE_HEIGHT, g_nRowWidth, rect.bottom - TITLE_HEIGHT, 
								&m_mdcTable, 0, m_nCurPos, SRCCOPY);
	
	Invalidate(FALSE);

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


//void CPrintDlg::OnPaintClipboard(CWnd* pClipAppWnd, HGLOBAL hPaintStruct)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	CDialogEx::OnPaintClipboard(pClipAppWnd, hPaintStruct);
//}


void CPrintDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = 1150;
	lpMMI->ptMinTrackSize.y = 450;

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


BOOL CPrintDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if(m_scrollBarV.IsWindowVisible())
	{
		int nPos = m_scrollBarV.GetScrollPos();
		int min,max;
		m_scrollBarV.GetScrollRange(&min,&max);
		if(zDelta == 120)
			nPos = max(min, nPos - 50);
		else if(zDelta == -120)
			nPos = min(max, nPos + 50);
		// 设置滚动块位置   
		m_nCurPos = nPos;
		m_scrollBarV.SetScrollPos(m_nCurPos); 
		CRect rect;
		GetClientRect(&rect);
		m_mdcBuf.FillSolidRect(0, TITLE_HEIGHT, rect.right, rect.bottom - TITLE_HEIGHT, CLT_BK_COLOR);
		m_mdcBuf.BitBlt((rect.right - SCROLL_WIDTH - g_nRowWidth)/2, TITLE_HEIGHT, g_nRowWidth, rect.bottom - TITLE_HEIGHT, 
									&m_mdcTable, 0, m_nCurPos, SRCCOPY);
		Invalidate(FALSE);
	}

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


void CPrintDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	::PostMessageW(AfxGetApp()->m_pMainWnd->GetSafeHwnd(),WM_USER_DESTROY,(WPARAM)this,NULL);
	// TODO: 在此处添加消息处理程序代码
}


//void CPrintDlg::OnNcDestroy()
//{
//	CDialogEx::OnNcDestroy();
//
//	// TODO: 在此处添加消息处理程序代码
//}
