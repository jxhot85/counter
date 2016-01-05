
// CounterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Counter.h"
#include "CounterDlg.h"
#include "afxdialogex.h"
#include "Case.h"
#include "PrintDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TITLE_HEIGHT 50						//窗口标题栏高度
// CCounterDlg 对话框 

CCounterDlg::CCounterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCounterDlg::IDD, pParent)
	, m_nItem(0)
	, m_nSubItem(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCounterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_COMPANY, m_ListctrlComp);
	DDX_Control(pDX, IDC_COMBO_COMPANY, m_ComboBoxComp);
	DDX_Control(pDX, IDC_LIST_THIRD, m_ListctrlThird);
	DDX_Control(pDX, IDC_EDIT_INSURED, m_EditInsured);
	DDX_Control(pDX, IDC_EDIT_THIRD, m_EditThird);
	DDX_Control(pDX, IDC_COMBO_SELFCOMP, m_ComboBoxExcept);
	DDX_Control(pDX, IDC_EDIT_DAMAGEM, m_EditDamageM);
	DDX_Control(pDX, IDC_EDIT_DAMAGED, m_EditDamageD);
	DDX_Control(pDX, IDC_EDIT_DAMAGEP, m_EditDamageP);
	DDX_Control(pDX, IDC_EDIT_NONINSURANCE, m_EditNonInsurance);
	DDX_Control(pDX, IDC_STATIC_MSG, m_StaticMsg);
	DDX_Control(pDX, IDC_CHECK_NOPAY, m_CheckNoPay);
	DDX_Control(pDX, IDC_STATIC_MSG2, m_StaticMsg2);
	DDX_Control(pDX, IDC_OUTM, m_CheckOutM);
	DDX_Control(pDX, IDC_OUTD, m_CheckOutD);
	DDX_Control(pDX, IDC_OUTP, m_CheckOutP);
}

BEGIN_MESSAGE_MAP(CCounterDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ADDCOMPANY, &CCounterDlg::OnBnClickedButtonAddcompany)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_COMPANY, &CCounterDlg::OnNMDblclkListCompany)
	ON_EN_KILLFOCUS(IDC_EDIT_NUMBER, &CCounterDlg::OnKillfocusEditNumber)
	ON_EN_KILLFOCUS(IDC_EDIT_NAME, &CCounterDlg::OnKillfocusEditName)
	ON_NOTIFY(NM_CLICK, IDC_LIST_COMPANY, &CCounterDlg::OnClickListCompany)
	ON_BN_CLICKED(IDC_BUTTON_DELCOMPANY, &CCounterDlg::OnBnClickedButtonDelcompany)
	ON_BN_CLICKED(IDC_BUTTON_ADDTHIRD, &CCounterDlg::OnBnClickedButtonAddthird)
	ON_BN_CLICKED(IDC_BUTTON_MODTHIRD, &CCounterDlg::OnBnClickedButtonModthird)
	ON_BN_CLICKED(IDC_BUTTON_DELTHIRD, &CCounterDlg::OnBnClickedButtonDelthird)
	ON_NOTIFY(NM_CLICK, IDC_LIST_THIRD, &CCounterDlg::OnClickListThird)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CCounterDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_CALCULATE, &CCounterDlg::OnBnClickedCalculate)
	ON_BN_CLICKED(IDC_END, &CCounterDlg::OnBnClickedEnd)
	ON_BN_CLICKED(IDC_BUTTON_MODCOM, &CCounterDlg::OnBnClickedButtonModcom)
	ON_BN_CLICKED(IDC_BUTTON_CLEARCOM, &CCounterDlg::OnBnClickedButtonClearcom)
	ON_WM_NCHITTEST()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_MESSAGE(WM_USER_DESTROY, &CCounterDlg::OnPrintDlgDestroy)
END_MESSAGE_MAP()


// CCounterDlg 消息处理程序

BOOL CCounterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//创建两种临时编辑框
	CreateEditNumber();
	CreateEditName();
	
	//关联CheckEdit子类,约束输入
	m_EditPercent.SubclassDlgItem(IDC_EDIT_PERCENT, this);
	m_EditQuota.SubclassDlgItem(IDC_EDIT_QUOTA, this);
	m_EditExempt.SubclassDlgItem(IDC_EDIT_EXEMPT, this);

	//设置列表视图（全行选中 栅格风格）
	m_ListctrlComp.SetExtendedStyle(m_ListctrlComp.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListctrlComp.InsertColumn(0, _T("保险公司"), LVCFMT_CENTER, 130, -1);
	m_ListctrlComp.InsertColumn(1, _T("被保险人"), LVCFMT_CENTER, 130, -1);
	m_ListctrlComp.InsertColumn(2, _T("责任比例"), LVCFMT_CENTER, 80, -1);
	m_ListctrlComp.InsertColumn(3, _T("商业险保额"), LVCFMT_CENTER, 100, -1);
	m_ListctrlComp.InsertColumn(4, _T("加扣免赔率"), LVCFMT_CENTER, 80, -1);
	m_ListctrlComp.InsertColumn(5, _T("财产不赔"), LVCFMT_CENTER, 80, -1);

	m_ListctrlThird.SetExtendedStyle(m_ListctrlComp.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListctrlThird.InsertColumn(0, _T("姓名"), LVCFMT_CENTER, 100, -1);
	m_ListctrlThird.InsertColumn(1, _T("总损失"), LVCFMT_CENTER, 120, -1);
	m_ListctrlThird.InsertColumn(2, _T("医疗费用(医保内)"), LVCFMT_CENTER, 120, -1);
	m_ListctrlThird.InsertColumn(3, _T("死亡伤残损失"), LVCFMT_CENTER, 120, -1);
	m_ListctrlThird.InsertColumn(4, _T("财产损失"), LVCFMT_CENTER, 120, -1);
	m_ListctrlThird.InsertColumn(5, _T("保险外损失"), LVCFMT_CENTER, 120, -1);
	m_ListctrlThird.InsertColumn(6, _T("非赔付方"), LVCFMT_CENTER, 130, -1);
	m_ListctrlThird.InsertColumn(7, _T("不参与计算"), LVCFMT_CENTER, 150, -1);

	//设置下拉组合框（添加保险公司）
	m_ComboBoxComp.SetMinVisibleItems(5);
	m_ComboBoxComp.AddString(_T("人民保险"));
	m_ComboBoxComp.AddString(_T("平安保险"));
	m_ComboBoxComp.AddString(_T("阳光保险"));
	m_ComboBoxComp.AddString(_T("大地保险"));
	m_ComboBoxComp.AddString(_T("人寿保险"));
	m_ComboBoxComp.AddString(_T("天安保险"));
	m_ComboBoxComp.AddString(_T("太平洋保险"));
	m_ComboBoxComp.AddString(_T("中华联合保险"));
	((CComboBox *)GetDlgItem(IDC_COMBO_SELFCOMP))->AddString(_T(""));

	//使删除、修改按钮不可用
	GetDlgItem(IDC_BUTTON_DELCOMPANY)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_MODCOM)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DELTHIRD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_MODTHIRD)->EnableWindow(FALSE);
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCounterDlg::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	CRect rect;
	GetClientRect(&rect);
	if (IsIconic())
	{

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		dc.BitBlt(0,0,rect.right,rect.bottom, &m_mdc,0,0,SRCCOPY);
		CBrush brush;
		brush.CreateSolidBrush(TITLE_COLOR);
		dc.FrameRect(&rect, &brush);
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCounterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///消息函数开始////////////////////////////////////////////////

//添加保险公司
//涉及5个字段 strCompany（）保险公司） strInsured（被保险人）, strPercent（责任比例）, strQuota（商业险保额）, strExempt（免赔率）
//保险公司、被保险人不能为空，责任比例空默认为100%   保额、免赔率空默认为0%
void CCounterDlg::OnBnClickedButtonAddcompany()
{
	//检查
	if(!CheckCompanyInput(-1)){
		m_StaticMsg.SetWindowTextW(strMsg);
		return ;
	}

	CString strCompany, strInsured, strPercent, strQuota, strExempt;
	m_ComboBoxComp.GetWindowTextW(strCompany);
	m_EditInsured.GetWindowTextW(strInsured);
	m_EditPercent.GetWindowTextW(strPercent);
	m_EditQuota.GetWindowTextW(strQuota);
	m_EditExempt.GetWindowTextW(strExempt);
	strCompany.Remove(_T(' '));
	strInsured.Remove(_T(' '));
	//给空值设置默认值
	if(strPercent.IsEmpty())
		strPercent = _T("100");
	if(strQuota.IsEmpty())
		strQuota = _T("0");
	if(strExempt.IsEmpty())
		strExempt = _T("0");
	////////////////////////////////////////////
	//插入
	int nIndex = m_ListctrlComp.InsertItem(m_ListctrlComp.GetItemCount(), strCompany);
	if( nIndex == -1){
		AfxMessageBox(_T("添加失败！"), MB_OK);
		return ;
	}
	m_ListctrlComp.SetItemText(nIndex, 1, strInsured);
	m_ListctrlComp.SetItemText(nIndex, 2, strPercent+_T("%"));
	m_ListctrlComp.SetItemText(nIndex, 3, strQuota+_T("万"));
	m_ListctrlComp.SetItemText(nIndex, 4, strExempt+_T("%"));
	if(m_CheckNoPay.GetCheck() == BST_CHECKED)
		m_ListctrlComp.SetItemText(nIndex, 5, _T("√"));
	//更新组合框（本车所属保险公司）
	m_ComboBoxExcept.AddString(strCompany);
	strMsg.Format(_T("添加 %s 成功！"), strCompany);
	m_StaticMsg.SetWindowTextW(strMsg);
	//清空
	m_ComboBoxComp.SetWindowTextW(NULL);
	m_EditInsured.SetWindowTextW(NULL);
	m_EditPercent.SetWindowTextW(NULL);
	m_EditQuota.SetWindowTextW(NULL);
	m_EditExempt.SetWindowTextW(NULL);
	m_CheckNoPay.SetCheck(BST_UNCHECKED);
	m_ComboBoxComp.SetFocus();
}

//列表视图双击修改
void CCounterDlg::OnNMDblclkListCompany(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	//击中subItem则设置临时编辑框覆盖到该subItem
	if(pNMItemActivate->iItem > -1 && pNMItemActivate->iSubItem < 5){
		CRect rect;
		m_nItem = pNMItemActivate->iItem;
		m_nSubItem = pNMItemActivate->iSubItem;
		m_ListctrlComp.GetSubItemRect(m_nItem, m_nSubItem, LVIR_LABEL, rect);
		rect.bottom -= 1;
		//选择临时编辑框（1.数字型  2.无限制型）
		CEdit *pEdit;
		if(m_nSubItem > 1)
			pEdit = &m_EditNumber;
		else
			pEdit = &m_EditName;
		//将临时编辑框覆盖到对应的子项位置
		pEdit->MoveWindow(&rect, FALSE);
		CString strSubItem = m_ListctrlComp.GetItemText(m_nItem, m_nSubItem);
		switch(m_nSubItem){
			case 2:
			case 4:
				strSubItem.Remove(_T('%'));
				break;
			case 3:
				strSubItem.Remove(_T('万'));
				break;
			default:
				break;
		}
		pEdit->SetWindowText(strSubItem);
		pEdit->ShowWindow(SW_SHOW);
		pEdit->SetFocus();
		pEdit->SetSel(0, -1);
	}

	*pResult = 0;
}

//单击列表视图，如果选中则使删除、修改按钮可用，反之使不可用
void CCounterDlg::OnClickListCompany(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	int nSel = pNMItemActivate->iItem;
	CButton *pBtnDel = (CButton *)GetDlgItem(IDC_BUTTON_DELCOMPANY);
	CButton *pBtnMod = (CButton *)GetDlgItem(IDC_BUTTON_MODCOM);
	if(nSel >= 0){
		CString strCompany = m_ListctrlComp.GetItemText(nSel, 0);
		CString strInsured = m_ListctrlComp.GetItemText(nSel, 1);
		CString strPercent = m_ListctrlComp.GetItemText(nSel,2);
		CString strQuota = m_ListctrlComp.GetItemText(nSel,3);
		CString strExempt = m_ListctrlComp.GetItemText(nSel,4);
		CString strNoPay = m_ListctrlComp.GetItemText(nSel,5);
		strPercent.Remove(_T('%'));
		strQuota.Remove(_T('万'));
		strExempt.Remove(_T('%'));
		pBtnDel->EnableWindow(TRUE);
		pBtnMod->EnableWindow(TRUE);
		m_ComboBoxComp.SetWindowTextW(strCompany);
		m_EditInsured.SetWindowTextW(strInsured);
		m_EditPercent.SetWindowTextW(strPercent);
		m_EditQuota.SetWindowTextW(strQuota);
		m_EditExempt.SetWindowTextW(strExempt);
		m_CheckNoPay.SetCheck(strNoPay.IsEmpty() ? BST_UNCHECKED : BST_CHECKED);
		//选中关联的第三者列表项
		for(int i=0;i<m_ListctrlThird.GetItemCount();i++){
			if(m_ListctrlThird.GetItemText(i,6) == strCompany){
				m_ListctrlThird.SetItemState(i,LVIS_SELECTED, LVIS_SELECTED);
				m_ListctrlThird.SetSelectionMark(i);
				//m_ListctrlThird.SetFocus();
			}
			else
				m_ListctrlThird.SetItemState(i,0, LVIS_SELECTED);
		}
	}
	else{
		pBtnDel->EnableWindow(FALSE);
		pBtnMod->EnableWindow(FALSE);
		for(int i=0;i<m_ListctrlThird.GetItemCount();i++)
			m_ListctrlThird.SetItemState(i,0, LVIS_SELECTED);
	}

	*pResult = 0;
}

//移动编辑框失去焦点,检查 修改
void CCounterDlg::OnKillfocusEditNumber()
{
	CString strEdit;
	m_EditNumber.GetWindowTextW(strEdit);
	//空值不改变列表项内容
	if(strEdit.IsEmpty()){
		m_EditNumber.ShowWindow(SW_HIDE);
		return ;
	}
	strMsg.Empty();
	//先检查数字格式
	if(CheckFormat(strEdit)){
		//再检查数字范围
		switch(m_nSubItem){
		case 2:
		case 4:
			if(_ttof(strEdit) > 100.0)
				strMsg = _T("请输入100以内的数！");
			else
				strEdit += _T("%");
			break;
		case 3:
			strEdit += _T("万");
			break;
		default:
			break;
		}
	}
	else
		strMsg = _T("请检查格式！");
	if(!strMsg.IsEmpty()){
		AfxMessageBox(strMsg, MB_OK);
		m_EditNumber.SetFocus();
		m_EditNumber.SetSel(0, -1);
		//因鼠标点击导致临时编辑框失去焦点会使得鼠标释放消息没有被处理，因此这里发送一个UP消息，避免消息框结束后拉出一个虚线框
		PostMessage(WM_LBUTTONUP);
		return ;
	}
	m_EditNumber.ShowWindow(SW_HIDE);
	//修改
	m_ListctrlComp.SetItemText(m_nItem, m_nSubItem, strEdit);
	
	strMsg = _T("修改成功！");
	m_StaticMsg.SetWindowTextW(strMsg);
}

//移动编辑框失去焦点，检查，添加
void CCounterDlg::OnKillfocusEditName()
{   
	CString strEdit;
	m_EditName.GetWindowTextW(strEdit);
	strEdit.Remove(_T(' '));
	//只对除当前行外的所有行的第一列进行唯一性检查
	if(m_nSubItem == 0 && IsExisted(m_ListctrlComp, strEdit, m_nItem)){
		AfxMessageBox(strEdit + _T("已经存在！"), MB_OK);
		strEdit = m_ListctrlComp.GetItemText(m_nItem, m_nSubItem);
		m_EditName.SetWindowTextW(strEdit);
		m_EditName.SetFocus();
		m_EditName.SetSel(0, -1);
		PostMessage(WM_LBUTTONUP);
		return;
	}
	m_EditName.ShowWindow(SW_HIDE); 
	//空值不改变列表项内容
	if(strEdit.IsEmpty())
		return;
	//修改
	m_ListctrlComp.SetItemText(m_nItem, m_nSubItem, strEdit);
	strMsg = _T("修改成功！");
	m_StaticMsg.SetWindowTextW(strMsg);
}

//删除选中的表项
void CCounterDlg::OnBnClickedButtonDelcompany()
{
	POSITION pos = m_ListctrlComp.GetFirstSelectedItemPosition();
	if(pos == NULL){
		AfxMessageBox(_T("请先选中一行！"), MB_OK);
		return;
	}
	
	//取得表项首字段
	int nSel = m_ListctrlComp.GetNextSelectedItem(pos);
	CString strDel = m_ListctrlComp.GetItemText(nSel, 0);
	//判断是否有关联
	int nNum = IsAssociated(strDel);
	if(nNum > 0){
		CString strMsg;
		strMsg.Format(_T("%s关联着 %d 个第三者，是否全部删除？"), strDel, nNum);
		if( IDCANCEL == AfxMessageBox(strMsg, MB_OKCANCEL))
			return ;
		else{
			DelAssociation(strDel);
			if( m_ListctrlThird.GetSelectionMark() != NULL){
				GetDlgItem(IDC_BUTTON_DELTHIRD)->EnableWindow(FALSE);
				GetDlgItem(IDC_BUTTON_MODTHIRD)->EnableWindow(FALSE);
			}
		}
	}
	//从组合框中删除
	int i = m_ComboBoxExcept.FindString(0, strDel);
	m_ComboBoxExcept.DeleteString(i);
	m_ListctrlComp.DeleteItem(nSel);
	strMsg = _T("删除成功！");
	m_StaticMsg.SetWindowTextW(strMsg);
	GetDlgItem(IDC_BUTTON_DELCOMPANY)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_MODCOM)->EnableWindow(FALSE);
}

//添加第三者  
//涉及到7个字段：strThird（第三者名称） strSelfComp（本车保险公司） strDamageM（医疗费用）
//		strDamageD（死亡伤残损失） strDamageP（财产损失） strNonInsurance（保险外损失）
void CCounterDlg::OnBnClickedButtonAddthird()
{
	CString strThird, strSelfComp, strOut;
	CString *pDamages = (CString *)new CString[4];					//处理前的strDamageM, strDamageD, strDamageP, strNonInsurance
	CString strMsg;													//错误消息
	int nStrStart = -1, nStrEnd = -1;
	double dSumDamageM, dSumDamageD, dSumDamageP, dSumNonInsurance;
	double dTotal;				//总计，交强险总计

	//获取各字段
	m_EditThird.GetWindowTextW(strThird);
	m_ComboBoxExcept.GetWindowTextW(strSelfComp);
	m_EditDamageM.GetWindowTextW(pDamages[0]);
	m_EditDamageD.GetWindowTextW(pDamages[1]);
	m_EditDamageP.GetWindowTextW(pDamages[2]);
	m_EditNonInsurance.GetWindowTextW(pDamages[3]);
	strThird.Remove(_T(' '));
	//检查字段
	strMsg.Empty();
	if(strThird.IsEmpty()){
		strMsg = _T("请输入第三者名称！");
		m_EditThird.SetFocus();
	}
	//求和并检查
	else if( !CheckAndSum(pDamages[0], nStrStart, nStrEnd, dSumDamageM)){
		strMsg = _T("输入不合法！");
		m_EditDamageM.SetFocus();
		m_EditDamageM.SetSel(nStrStart, nStrEnd);
	}
	else if( !CheckAndSum(pDamages[1], nStrStart, nStrEnd, dSumDamageD)){
		strMsg = _T("输入不合法！");
		m_EditDamageD.SetFocus();
		m_EditDamageD.SetSel(nStrStart, nStrEnd);
	}
	else if( !CheckAndSum(pDamages[2], nStrStart, nStrEnd, dSumDamageP)){
		strMsg = _T("输入不合法！");
		m_EditDamageP.SetFocus();
		m_EditDamageP.SetSel(nStrStart, nStrEnd);
	}
	else if( !CheckAndSum(pDamages[3], nStrStart, nStrEnd, dSumNonInsurance)){
		strMsg = _T("输入不合法！");
		m_EditNonInsurance.SetFocus();
		m_EditNonInsurance.SetSel(nStrStart, nStrEnd);
	}
	//检查不通过
	if(!strMsg.IsEmpty()){	
		delete []pDamages;
		m_StaticMsg2.SetWindowTextW(strMsg);
		return ;
	}

	//修剪
	CString strDamageM, strDamageD, strDamageP, strNonInsurance;
	strDamageM = Format(dSumDamageM);
	strDamageD = Format(dSumDamageD);
	strDamageP = Format(dSumDamageP);
	strNonInsurance = Format(dSumNonInsurance);
	dTotal = _ttof(strDamageM) + _ttof(strDamageD) + _ttof(strDamageP) + _ttof(strNonInsurance);
	//插入
	int nIndex = m_ListctrlThird.InsertItem(m_ListctrlThird.GetItemCount(), strThird);
	if(nIndex == -1){
		delete []pDamages;
		AfxMessageBox(_T("添加失败!"), MB_OK);
		return ;
	}
	m_ListctrlThird.SetItemText(nIndex, 1, Format(dTotal));
	m_ListctrlThird.SetItemText(nIndex, 2, strDamageM);
	m_ListctrlThird.SetItemText(nIndex, 3, strDamageD);
	m_ListctrlThird.SetItemText(nIndex, 4, strDamageP);
	m_ListctrlThird.SetItemText(nIndex, 5, strNonInsurance);
	m_ListctrlThird.SetItemText(nIndex, 6, strSelfComp);
	if(m_CheckOutM.GetCheck() == BST_CHECKED)
		strOut += _T("医疗 ");
	if(m_CheckOutD.GetCheck() == BST_CHECKED)
		strOut += _T("死伤 ");
	if(m_CheckOutP.GetCheck() == BST_CHECKED)
		strOut += _T("财产 ");
	m_ListctrlThird.SetItemText(nIndex, 7, strOut);

	//保存原strDamageM（医疗费用）, strDamageD（死亡伤残损失）, strDamageP（财产损失）, strNonInsurance（保险外损失）输入的内容
	m_ListctrlThird.SetItemData(nIndex, (DWORD_PTR)pDamages);

	//清空输入框
	m_EditThird.SetWindowTextW(NULL);
	m_ComboBoxExcept.SetCurSel(-1);
	m_EditDamageM.SetWindowTextW(NULL);
	m_EditDamageD.SetWindowTextW(NULL);
	m_EditDamageP.SetWindowTextW(NULL);
	m_EditNonInsurance.SetWindowTextW(NULL);
	m_EditThird.SetFocus();

	strMsg.Format(_T("添加 %s 成功！"), strThird);
	m_StaticMsg2.SetWindowTextW(strMsg);
}

//修改第三者
void CCounterDlg::OnBnClickedButtonModthird()
{
	POSITION pos = m_ListctrlThird.GetFirstSelectedItemPosition();
	if(pos == NULL){
		AfxMessageBox(_T("请先选中一行！"), MB_OK);
		return ;
	}
	int nSel = m_ListctrlThird.GetNextSelectedItem(pos);

	CString strThird, strSelfComp, strOut;
	CString strDamageM, strDamageD, strDamageP, strNonInsurance;
	CString strMsg;		
	int nStrStart = -1, nStrEnd = -1;
	double dSumDamageM, dSumDamageD, dSumDamageP, dSumNonInsurance;
	double dTotal;				//总计，交强险总计

	//获取各字段
	m_EditThird.GetWindowTextW(strThird);
	m_ComboBoxExcept.GetWindowTextW(strSelfComp);
	m_EditDamageM.GetWindowTextW(strDamageM);
	m_EditDamageD.GetWindowTextW(strDamageD);
	m_EditDamageP.GetWindowTextW(strDamageP);
	m_EditNonInsurance.GetWindowTextW(strNonInsurance);
	strThird.Remove(_T(' '));
	//检查字段
	strMsg.Empty();
	if(strThird.IsEmpty()){
		strMsg = _T("请输入第三者名称！");
		m_EditThird.SetFocus();
	}
	//求和并检查
	else if( !CheckAndSum(strDamageM, nStrStart, nStrEnd, dSumDamageM)){
		strMsg = _T("修改失败！ 输入不合法！");
		m_EditDamageM.SetFocus();
		m_EditDamageM.SetSel(nStrStart, nStrEnd);
	}
	else if( !CheckAndSum(strDamageD, nStrStart, nStrEnd, dSumDamageD)){
		strMsg = _T("修改失败！ 输入不合法！");
		m_EditDamageD.SetFocus();
		m_EditDamageD.SetSel(nStrStart, nStrEnd);
	}
	else if( !CheckAndSum(strDamageP, nStrStart, nStrEnd, dSumDamageP)){
		strMsg = _T("修改失败！ 输入不合法！");
		m_EditDamageP.SetFocus();
		m_EditDamageP.SetSel(nStrStart, nStrEnd);
	}
	else if( !CheckAndSum(strNonInsurance, nStrStart, nStrEnd, dSumNonInsurance)){
		strMsg = _T("修改失败！ 输入不合法！");
		m_EditNonInsurance.SetFocus();
		m_EditNonInsurance.SetSel(nStrStart, nStrEnd);
	}
	//检查不通过
	if(!strMsg.IsEmpty()){	
		m_StaticMsg2.SetWindowTextW(strMsg);
		return ;
	}
	//更新
	CString *pDamages = (CString *)m_ListctrlThird.GetItemData(nSel);	
	pDamages[0] = strDamageM;
	pDamages[1] = strDamageD;
	pDamages[2] = strDamageP;
	pDamages[3] = strNonInsurance;
	//修剪后更新
	strDamageM = Format(dSumDamageM);
	strDamageD = Format(dSumDamageD);
	strDamageP = Format(dSumDamageP);
	strNonInsurance = Format(dSumNonInsurance);
	dTotal = _ttof(strDamageM) + _ttof(strDamageD) + _ttof(strDamageP) + _ttof(strNonInsurance);
	m_ListctrlThird.SetItemText(nSel, 0, strThird);
	m_ListctrlThird.SetItemText(nSel, 1, Format(dTotal));
	m_ListctrlThird.SetItemText(nSel, 2, strDamageM);
	m_ListctrlThird.SetItemText(nSel, 3, strDamageD);
	m_ListctrlThird.SetItemText(nSel, 4, strDamageP);
	m_ListctrlThird.SetItemText(nSel, 5, strNonInsurance);
	m_ListctrlThird.SetItemText(nSel, 6, strSelfComp);
	if(m_CheckOutM.GetCheck() == BST_CHECKED)
		strOut += _T("医疗 ");
	if(m_CheckOutD.GetCheck() == BST_CHECKED)
		strOut += _T("死伤 ");
	if(m_CheckOutP.GetCheck() == BST_CHECKED)
		strOut += _T("财产 ");
	m_ListctrlThird.SetItemText(nSel, 7, strOut);
	
	strMsg = _T("修改成功！");
	m_StaticMsg2.SetWindowTextW(strMsg);
}

//删除第三者
void CCounterDlg::OnBnClickedButtonDelthird()
{
	POSITION pos;
	while( pos = m_ListctrlThird.GetFirstSelectedItemPosition() ){
		int nSel = m_ListctrlThird.GetNextSelectedItem(pos);
		m_ListctrlThird.DeleteItem(nSel);
	}
	//列表项失去选中状态，修改及删除按钮不可用
	GetDlgItem(IDC_BUTTON_DELTHIRD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_MODTHIRD)->EnableWindow(FALSE);
}

//选中后使按钮可见，并将各字段回显
void CCounterDlg::OnClickListThird(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	int nSel = pNMItemActivate->iItem;
	CButton *pBtnDel = (CButton *)GetDlgItem(IDC_BUTTON_DELTHIRD);
	CButton *pBtnMod = (CButton *)GetDlgItem(IDC_BUTTON_MODTHIRD);
	//选中
	if(nSel >= 0){
		pBtnDel->EnableWindow(TRUE);
		pBtnMod->EnableWindow(TRUE);
		//回显
		m_EditThird.SetWindowTextW(m_ListctrlThird.GetItemText(nSel, 0));
		m_ComboBoxExcept.SetCurSel(m_ComboBoxExcept.FindString(-1, m_ListctrlThird.GetItemText(nSel, 6)));
		CString *pDamages = (CString *)m_ListctrlThird.GetItemData(nSel);
		m_EditDamageM.SetWindowTextW(pDamages[0]);
		m_EditDamageD.SetWindowTextW(pDamages[1]);
		m_EditDamageP.SetWindowTextW(pDamages[2]);
		m_EditNonInsurance.SetWindowTextW(pDamages[3]);
		CString str = m_ListctrlThird.GetItemText(nSel, 7);
		m_CheckOutM.SetCheck(str.Find(_T("医疗")) == -1 ? BST_UNCHECKED : BST_CHECKED);
		m_CheckOutD.SetCheck(str.Find(_T("死伤")) == -1 ? BST_UNCHECKED : BST_CHECKED);
		m_CheckOutP.SetCheck(str.Find(_T("财产")) == -1 ? BST_UNCHECKED : BST_CHECKED);
	}
	else{
		 pBtnDel->EnableWindow(FALSE);
		 pBtnMod->EnableWindow(FALSE);
	}
	*pResult = 0;
}

HBRUSH CCounterDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor == CTLCOLOR_STATIC){
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetBkColor(UNDER_COLOR);
		hbr = m_brush;
	}
	if(pWnd->GetDlgCtrlID() == IDC_STATIC_MSG || pWnd->GetDlgCtrlID() == IDC_STATIC_MSG2)
        pDC->SetTextColor(RGB(255, 0, 0));    // 设置消息静态框字体颜色 
	
	return hbr;
}

void CCounterDlg::OnOK()
{
	CWnd *pFocus = GetFocus();
	//焦点落在添加保险公司按钮上
	if(pFocus == GetDlgItem(IDC_BUTTON_ADDCOMPANY)){
		OnBnClickedButtonAddcompany();
	}
	//焦点落在添加第三者按钮上
	else if(pFocus == GetDlgItem(IDC_BUTTON_ADDTHIRD)){
		OnBnClickedButtonAddthird();
	}
	else{
		NextDlgCtrl();
	}
}

/*BOOL CCounterDlg::PreTranslateMessage(MSG* pMsg)
{
	//避免按回车直接退出
	if(pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return FALSE;

	return CDialogEx::PreTranslateMessage(pMsg);
}*/

//消息函数结束/////////////////////////////////////////////////////

//创建移动编辑框，只能接受数字值
void CCounterDlg::CreateEditNumber()
{
	m_EditNumber.Create(WS_CHILD | ES_RIGHT, CRect(0,0,0,0), this, IDC_EDIT_NUMBER);
	m_EditNumber.SetFont(GetFont(), FALSE);
	m_EditNumber.SetParent(&m_ListctrlComp);
	m_EditNumber.ShowWindow(SW_HIDE);
}

//创建移动编辑框
void CCounterDlg::CreateEditName()
{
	m_EditName.Create(WS_CHILD | ES_LEFT, CRect(0,0,0,0), this, IDC_EDIT_NAME);
	m_EditName.SetFont(GetFont(), FALSE);
	m_EditName.SetParent(&m_ListctrlComp);
	m_EditName.ShowWindow(SW_HIDE);
}

//只对由数字和小数点组成的字符串进行格式检查， 正确格式如123.45  最高位不能为0和小数点，最低位不能为小数点
//返回值 TRUE ＝ 检查通过
BOOL CCounterDlg::CheckFormat(const CString &str)
{
	if(str.IsEmpty())
		return TRUE;
	BOOL bRes = TRUE;
	int nIndex = str.Find(_T('.'));
	//小数点在最左边或者在最右边
	if(nIndex == 0 || nIndex == str.GetLength()-1)
		bRes = FALSE;
	else if(nIndex > 1 && str.Find(_T('0')) == 0)
		bRes = FALSE;
	//多个小数点
	else if(nIndex > 0 && str.Find(_T('.'), nIndex+1) != -1){
		bRes = FALSE;
	}
	//没有小数点, 超过1位，且最左边位为0
	else if(nIndex == -1 && (str.GetLength() > 1 && str.Find(_T('0')) == 0)){
		bRes = FALSE;
	}
	
	return bRes;
}

//检查赔付方各项输入内容
BOOL CCounterDlg::CheckCompanyInput(int nIndex)
{
	CString strCompany, strInsured, strPercent, strQuota, strExempt;
	m_ComboBoxComp.GetWindowTextW(strCompany);
	m_EditInsured.GetWindowTextW(strInsured);
	m_EditPercent.GetWindowTextW(strPercent);
	m_EditQuota.GetWindowTextW(strQuota);
	m_EditExempt.GetWindowTextW(strExempt);
	strCompany.Remove(_T(' '));
	strInsured.Remove(_T(' '));

	if( IsExisted(m_ListctrlComp, strCompany, nIndex)){
		strMsg.Format(_T("%s 已经存在！请重新输入"), strCompany);
		m_ComboBoxComp.SetFocus();
		return FALSE;
	}
	if( strCompany.IsEmpty() ){
		strMsg = _T("请输入保险公司！");
		m_ComboBoxComp.SetFocus();
		return FALSE;
	}
	if( strInsured.IsEmpty() ){
		strMsg = _T("请输入被保险人！");
		m_EditInsured.SetFocus();
		return FALSE;
	}
	if( !CheckFormat(strPercent) ){
		strMsg = _T("输入不合法！");
		m_EditPercent.SetFocus();
		m_EditPercent.SetSel(0, -1);
		return FALSE;
	}
	else if( _ttof(strPercent) > 100.0 ){
		strMsg = _T("责任比例 > 100了！");
		m_EditPercent.SetFocus();
		m_EditPercent.SetSel(0, -1);
		return FALSE;
	}
	if( !CheckFormat(strQuota) ){
		strMsg = _T("输入不合法！");
		m_EditQuota.SetFocus();
		m_EditQuota.SetSel(0, -1);
		return FALSE;
	}
	if( !CheckFormat(strExempt) ){
		strMsg = _T("输入不合法！");
		m_EditExempt.SetFocus();
		m_EditExempt.SetSel(0, -1);
		return FALSE;
	}
	else if( _ttof(strExempt) > 100.0){
		strMsg = _T("加扣免赔率 > 100了！");
		m_EditExempt.SetFocus();
		m_EditExempt.SetSel(0, -1);
		return FALSE;
	}
	return TRUE;
}

//判断要插入的表项是否重名
BOOL CCounterDlg::IsExisted(CListCtrl &thelist, const CString &strName, int nExcept)
{
	int nNum = thelist.GetItemCount();
	for(int i=0; i<nNum; i++){
		if(nExcept == i)
			continue;
		if(strName == thelist.GetItemText(i,0))
			return TRUE;
	}
	return FALSE;
}

//从字符串中提取数字并累加
BOOL CCounterDlg::CheckAndSum(const CString &strData, int &nStrStart, int &nStrEnd, double &dSum)
{
	int nStart = -1, nSublen = 0;
	dSum = 0.0;
	//从字符串中截取符合条件（只包含0~9及小数点）的子串，转换成double后累加
	for(int i=0; i< strData.GetLength(); i++){
		if((strData[i] >= _T('0') && strData[i] <= _T('9')) || strData[i] == _T('.')){
			if(nStart == -1)
				nStart = i;
			nSublen ++;
		}
		else if(nStart != -1){
			CString strSub = strData.Mid(nStart, nSublen);
			if( !CheckFormat(strSub)){
				nStrStart = nStart;
				nStrEnd = nStart + nSublen;
				return FALSE;
			}
			dSum += _ttof(strSub);
			nStart = -1;
			nSublen = 0;
		}
	}
	int i = strData.GetLength();
	if(nStart != -1){
		CString strSub = strData.Mid(nStart, nSublen);
		if( !CheckFormat(strSub)){
			nStrStart = nStart;
			nStrEnd = nSublen;
			return FALSE;
		}
		dSum += _ttof(strSub);
	}

	return TRUE;
}

//判断保险公司是否关联第三者,返回关联个数
int CCounterDlg::IsAssociated(const CString &strKey) const
{
	int nCount = 0;
	for(int i=0; i < m_ListctrlThird.GetItemCount(); i++){
		if(strKey == m_ListctrlThird.GetItemText(i,6))
			nCount ++;
	}
	return nCount;
}

//删除关联的第三者,返回删除的个数
int CCounterDlg::DelAssociation(const CString &strKey)
{
	int nCount = 0;
	int nNum = m_ListctrlThird.GetItemCount();
	for(int i=nNum-1; i>=0; i--){
		if(strKey == m_ListctrlThird.GetItemText(i,6)){
			m_ListctrlThird.DeleteItem(i);
			nCount ++;
		}
	}
	return nCount;
}

void CCounterDlg::ModAssociation(const CString &preStr, const CString newStr)
{
	int nCount = 0;
	int nNum = m_ListctrlThird.GetItemCount();
	for(int i=nNum-1; i>=0; i--){
		if(preStr == m_ListctrlThird.GetItemText(i,6))
			m_ListctrlThird.SetItemText(i,6,newStr);
	}
}


//小数部分为0则转为整数，否则保留2位小数
CString CCounterDlg::Format(double dNum)
{
	CString str;
	str.Format(_T("%.2lf"), dNum);
	if(str.Mid(str.GetLength() - 2, 2) == _T("00")){
		str.TrimRight(_T('0'));
		str.TrimRight(_T('.'));
	}
	return str;
}

void CCounterDlg::OnBnClickedButtonClear()
{
	//清空输入框
	m_EditThird.SetWindowTextW(NULL);
	m_ComboBoxExcept.SetCurSel(-1);
	m_EditDamageM.SetWindowTextW(NULL);
	m_EditDamageD.SetWindowTextW(NULL);
	m_EditDamageP.SetWindowTextW(NULL);
	m_EditNonInsurance.SetWindowTextW(NULL);
	m_CheckOutM.SetCheck(BST_UNCHECKED);
	m_CheckOutD.SetCheck(BST_UNCHECKED);
	m_CheckOutP.SetCheck(BST_UNCHECKED);

	m_EditThird.SetFocus();
}


void CCounterDlg::OnBnClickedCalculate()
{
	if(m_ListctrlComp.GetItemCount() == 0){
		AfxMessageBox(_T("请添加保险公司"), MB_OK);
		return ;
	}
	if(m_ListctrlThird.GetItemCount() == 0){
		AfxMessageBox(_T("请添加第三者"), MB_OK);
		return ;
	}
	double sumDuty = 0.0;
	for(int i=0;i<m_ListctrlComp.GetItemCount();i++)
	{
		CString strDuty = m_ListctrlComp.GetItemText(i,2);
		strDuty.Remove('%');
		sumDuty += _ttof(strDuty);
		if(sumDuty > 100.0)
		{
			AfxMessageBox(_T("责任比例总和超过100%"),MB_OK);
			return ;
		}
	}
	CCase *pCase = (CCase*)new CCase;
	int nCount = m_ListctrlComp.GetItemCount();
	for(int i=0; i<nCount; i++)
	{
		CString &strComp = m_ListctrlComp.GetItemText(i,0);
		CString &strName = m_ListctrlComp.GetItemText(i,1);
		double dDutyI = _ttof(m_ListctrlComp.GetItemText(i,2)) / 100.0;
		double dQuota = _ttof(m_ListctrlComp.GetItemText(i,3)) * 10000; 
		double dDutyC = (100.0 - _ttof(m_ListctrlComp.GetItemText(i,4))) / 100.0 * dDutyI;
		if(!pCase->AddCompany(strComp, strName, dDutyI, dQuota, dDutyC, !m_ListctrlComp.GetItemText(i,5).IsEmpty())){
			AfxMessageBox(_T("数据加载失败，不能计算！"),MB_OK);
			return ;
		}	
	}

	nCount = m_ListctrlThird.GetItemCount();
	for(int i=0; i<nCount; i++)
	{
		CString strThird = m_ListctrlThird.GetItemText(i,0);				   
		double dDamageM = _ttof(m_ListctrlThird.GetItemText(i,2));					
		double dDamageD = _ttof(m_ListctrlThird.GetItemText(i,3));				
		double dDamageP = _ttof(m_ListctrlThird.GetItemText(i,4));		
		double dDamageE = _ttof(m_ListctrlThird.GetItemText(i,5));	
		CString strCompany = m_ListctrlThird.GetItemText(i,6);
		CString strOut = m_ListctrlThird.GetItemText(i,7);
		unsigned char nState = 0;
		if( strOut.Find(_T("医疗")) > -1 )
			nState |= 1;
		if( strOut.Find(_T("死伤")) > -1 )
			nState |= 2;
		if( strOut.Find(_T("财产")) > -1 )
			nState |= 4;
		if(!pCase->AddThird(strThird, dDamageM, dDamageD, dDamageP, dDamageE, strCompany, nState)){
			AfxMessageBox(_T("数据加载失败，不能计算！"),MB_OK);
			return ;
		}
	}
	if(!pCase->LoadThird()){
		AfxMessageBox(_T("数据加载失败，不能计算！"),MB_OK);
		return ;
	}

	pCase->Calculate();

	CPrintDlg *pDlg = (CPrintDlg*)new CPrintDlg(pCase);
	pDlg->Create(IDD_PRINT_DIALOG,GetDesktopWindow());
	pDlg->ShowWindow(SW_SHOW);
}


//LRESULT CCounterDlg::OnNcHitTest(CPoint point)
//{
//	LRESULT hitTest = CDialogEx::OnNcHitTest(point);
//	ScreenToClient(&point);
//	if(point.y <= TITLE_HEIGHT)
//		hitTest = HTCAPTION;
//
//	return hitTest;
//}


void CCounterDlg::OnBnClickedEnd()
{
	CDialogEx::OnCancel();
}


void CCounterDlg::OnBnClickedButtonModcom()
{
	POSITION pos = m_ListctrlComp.GetFirstSelectedItemPosition();
	if(pos == NULL){
		AfxMessageBox(_T("请先选中一行！"), MB_OK);
		return ;
	}
	int nSel = m_ListctrlComp.GetNextSelectedItem(pos);

	//检查
	if(!CheckCompanyInput(nSel)){
		m_StaticMsg.SetWindowTextW(strMsg);
		return ;
	}
	CString strCompany, strInsured, strPercent, strQuota, strExempt;
	m_ComboBoxComp.GetWindowTextW(strCompany);
	strCompany.Remove(_T(' '));
	CString strCurComp = m_ListctrlComp.GetItemText(nSel, 0);
	if(strCompany != strCurComp){
		//判断是否有关联
		int nNum = IsAssociated(strCurComp);
		if(nNum > 0){
			CString strMsg;
			strMsg.Format(_T("%s关联着 %d 个第三者，是否继续修改？"), strCurComp, nNum);
			if( IDCANCEL == AfxMessageBox(strMsg, MB_OKCANCEL))
				return ;
			else{
				ModAssociation(strCurComp, strCompany);
				//更新组合框（本车所属保险公司）
				int i = m_ComboBoxExcept.FindString(0, strCurComp);
				m_ComboBoxExcept.DeleteString(i);
				m_ComboBoxExcept.InsertString(i, strCompany);
			}
		}
	}
	m_EditInsured.GetWindowTextW(strInsured);
	m_EditPercent.GetWindowTextW(strPercent);
	m_EditQuota.GetWindowTextW(strQuota);
	m_EditExempt.GetWindowTextW(strExempt);
	strInsured.Remove(_T(' '));
	//给空值设置默认值
	if(strPercent.IsEmpty())
		strPercent = _T("100");
	if(strQuota.IsEmpty())
		strQuota = _T("0");
	if(strExempt.IsEmpty())
		strExempt = _T("0");
	m_ListctrlComp.SetItemText(nSel, 0, strCompany);
	m_ListctrlComp.SetItemText(nSel, 1, strInsured);
	m_ListctrlComp.SetItemText(nSel, 2, strPercent+_T("%"));
	m_ListctrlComp.SetItemText(nSel, 3, strQuota+_T("万"));
	m_ListctrlComp.SetItemText(nSel, 4, strExempt+_T("%"));
	if(m_CheckNoPay.GetCheck() == BST_CHECKED)
		m_ListctrlComp.SetItemText(nSel, 5, _T("√"));
	else
		m_ListctrlComp.SetItemText(nSel, 5, NULL);
	strMsg.Format(_T("%s修改为%s成功！"), strCurComp, strCompany);
	m_StaticMsg.SetWindowTextW(strMsg);
}


void CCounterDlg::OnBnClickedButtonClearcom()
{
	m_ComboBoxComp.SetWindowTextW(NULL);
	m_EditInsured.SetWindowTextW(NULL);
	m_EditPercent.SetWindowTextW(NULL);
	m_EditQuota.SetWindowTextW(NULL);
	m_EditExempt.SetWindowTextW(NULL);
	m_CheckNoPay.SetCheck(BST_UNCHECKED);
}


LRESULT CCounterDlg::OnNcHitTest(CPoint point)
{
	LRESULT nHitTest = CDialogEx::OnNcHitTest(point);

	CRect rect;
	GetClientRect(&rect);
	ScreenToClient(&point);

	if(m_rtMin.PtInRect(point) || m_rtCls.PtInRect(point))
		nHitTest =  HTCLIENT;
	else if(point.y <= TITLE_HEIGHT)
		nHitTest = HTCAPTION;

	return nHitTest;
}


void CCounterDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	HCURSOR hCursor;
	if(m_rtCls.PtInRect(point) || m_rtMin.PtInRect(point))
		hCursor = ::LoadCursor(NULL, IDC_HAND);
	else
		hCursor = ::LoadCursor(NULL, IDC_ARROW);

	::SetCursor(hCursor);

	CDialogEx::OnMouseMove(nFlags, point);
}


void CCounterDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(m_rtCls.PtInRect(point))
		CDialogEx::OnCancel();
	else if(m_rtMin.PtInRect(point))
		ShowWindow(SW_SHOWMINIMIZED);

	CDialogEx::OnLButtonUp(nFlags, point);
}


int CCounterDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect;
	GetClientRect(&rect);
	int nGap = (TITLE_HEIGHT - SYSMENU_RECT)/2;
	m_rtCls.SetRect(rect.right - (SYSMENU_RECT + nGap), nGap, rect.right - nGap, SYSMENU_RECT + nGap);
	m_rtMin = m_rtCls;
	m_rtMin.OffsetRect(-(SYSMENU_RECT + nGap), 0);

	CClientDC dc(this);
	m_mdc.Create(rect.right, rect.bottom, &dc);
	m_mdc.FillSolidRect(0,0,rect.right,rect.bottom, RGB(255,255,255));
	//填充颜色
	m_mdc.FillSolidRect(0,0,rect.right,TITLE_HEIGHT, TITLE_COLOR);
	m_mdc.FillSolidRect(0,68,rect.right,170, UNDER_COLOR);
	m_mdc.FillSolidRect(0,265,rect.right,384, UNDER_COLOR);
	//标题字
	CFont font, *preFont;
	CRect rt(0,0,rect.right,TITLE_HEIGHT);
	int preMode = m_mdc.SetBkMode(TRANSPARENT);
	preFont = m_mdc.SetFont(font,15, FW_BOLD, _T("仿宋"));
	COLORREF preClr = m_mdc.SetTextColor(RGB(255,201,14));
	m_mdc.DrawText(_T(" 路桥法院民一庭"),&rt,DT_LEFT | DT_SINGLELINE | DT_VCENTER);
	m_mdc.SetTextColor(preClr);
	m_mdc.SetFont(font,30, FW_BOLD, _T("宋体"));
	m_mdc.DrawText(_T("交通事故计算器"),&rt,DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	m_mdc.SelectObject(preFont);
	m_mdc.SetBkMode(preMode);
	//画最小化关闭按钮
	CPen pen, *prePen;
	pen.CreatePen(PS_SOLID, 5, RGB(255,255,255));
	prePen = m_mdc.SelectObject(&pen);
	m_mdc.SelectStockObject(NULL_BRUSH);
	m_mdc.MoveTo(m_rtCls.left, m_rtCls.top);
	m_mdc.LineTo(m_rtCls.right, m_rtCls.bottom);
	m_mdc.MoveTo(m_rtCls.left, m_rtCls.bottom);
	m_mdc.LineTo(m_rtCls.right, m_rtCls.top);
	m_mdc.MoveTo(m_rtMin.left, TITLE_HEIGHT/2);
	m_mdc.LineTo(m_rtMin.right, TITLE_HEIGHT/2);
	m_mdc.SelectObject(prePen);
	//控件背景画刷
	m_brush.CreateSolidBrush(UNDER_COLOR);

	return 0;
}


BOOL CCounterDlg::OnEraseBkgnd(CDC* pDC)
{

	return TRUE;
}

LRESULT CCounterDlg::OnPrintDlgDestroy(WPARAM wParam, LPARAM lParam)
{
	delete (CPrintDlg *)wParam;
	return NULL;
}

