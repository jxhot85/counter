
// CounterDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "CheckEdit.h"
#include "afxcmn.h"
#include "MemoryDC.h"


// CCounterDlg 对话框
class CCounterDlg : public CDialogEx
{
// 构造
public:
	CCounterDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_COUNTER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButtonAddcompany();
	afx_msg void OnNMDblclkListCompany(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnKillfocusEditNumber();   
	afx_msg void OnKillfocusEditName();
	afx_msg void OnClickListCompany(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonDelcompany();
	afx_msg void OnBnClickedButtonAddthird();
	afx_msg void OnBnClickedButtonModthird();
	afx_msg void OnBnClickedButtonDelthird();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedCalculate();
	afx_msg void OnBnClickedEnd();
	afx_msg void OnBnClickedButtonModcom();
	afx_msg void OnBnClickedButtonClearcom();
	afx_msg void OnClickListThird(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//自定义消息
	afx_msg LRESULT OnPrintDlgDestroy(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

	//检查赔付方各字段的内容
	BOOL CheckCompanyInput(int nIndex);
	//只对由数字和小数点组成的字符串进行格式检查
	BOOL CheckFormat(const CString &str);
	//判断要插入的表项是否重名
	BOOL IsExisted(CListCtrl &thelist, const CString &strName, int nExcept);
	//创建两种移动编辑框
	void CreateEditNumber();
	void CreateEditName();
	//从字符串中提取数字并累加
	BOOL CheckAndSum(const CString &strData, int &nStrStart, int &nStrEnd, double &dSum);
	//判断保险公司是否关联第三者,返回值＝关联个数
	int IsAssociated(const CString &strKey) const;
	//删除关联的第三者,返回删除的个数
	int DelAssociation(const CString &strKey);
	void ModAssociation(const CString &preStr, const CString newStr);
	//小数部分为0则转为整数，否则保留2位小数
	CString Format(double dNum);

//变量
protected:
	CListCtrl m_ListctrlComp;
	CListCtrl m_ListctrlThird;
	CComboBox m_ComboBoxComp;
	CComboBox m_ComboBoxExcept;
	CEdit m_EditInsured;
	CEdit m_EditThird;
	CEdit m_EditDamageM;
	CEdit m_EditDamageD;
	CEdit m_EditDamageP;
	CEdit m_EditNonInsurance;
	CEdit m_EditName;                     //移动编辑框，手动创建，关联IDC_EDIT_NAME, 输入内容不受限制
	CCheckEdit m_EditNumber;			  //移动编辑框，手动创建，关联IDC_EDIT_NUMBER, 只能输入数字
	CCheckEdit m_EditPercent;			  //关联IDC_EDIT_PERCENT    
	CCheckEdit m_EditQuota;			      //关联IDC_EDIT_QUOTA
	CCheckEdit m_EditExempt;	          //关联IDC_EDIT_EXEMPT
	CButton m_CheckNoPay;
	CStatic m_StaticMsg;
	CStatic m_StaticMsg2;
	CString strMsg;						  //错误提示消息

	int m_nItem;						  //列表视图的行
	int m_nSubItem;						  //列表视图的列
	
	CButton m_CheckOutM;				  //不参与交强险医疗损失的分配
	CButton m_CheckOutD;				  //不参与交强险死亡伤残损失的分配
	CButton m_CheckOutP;				  //不参与交强险财产损失的分配

	CMemoryDC m_mdc;			
	CRect m_rtCls;						//关闭按钮位置
	CRect m_rtMin;						//最小化按钮位置
	
	CBrush m_brush;						//控件背景画刷
};
