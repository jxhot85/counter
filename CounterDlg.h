
// CounterDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "CheckEdit.h"
#include "afxcmn.h"
#include "MemoryDC.h"


// CCounterDlg �Ի���
class CCounterDlg : public CDialogEx
{
// ����
public:
	CCounterDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_COUNTER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	//�Զ�����Ϣ
	afx_msg LRESULT OnPrintDlgDestroy(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

	//����⸶�����ֶε�����
	BOOL CheckCompanyInput(int nIndex);
	//ֻ�������ֺ�С������ɵ��ַ������и�ʽ���
	BOOL CheckFormat(const CString &str);
	//�ж�Ҫ����ı����Ƿ�����
	BOOL IsExisted(CListCtrl &thelist, const CString &strName, int nExcept);
	//���������ƶ��༭��
	void CreateEditNumber();
	void CreateEditName();
	//���ַ�������ȡ���ֲ��ۼ�
	BOOL CheckAndSum(const CString &strData, int &nStrStart, int &nStrEnd, double &dSum);
	//�жϱ��չ�˾�Ƿ����������,����ֵ����������
	int IsAssociated(const CString &strKey) const;
	//ɾ�������ĵ�����,����ɾ���ĸ���
	int DelAssociation(const CString &strKey);
	void ModAssociation(const CString &preStr, const CString newStr);
	//С������Ϊ0��תΪ������������2λС��
	CString Format(double dNum);

//����
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
	CEdit m_EditName;                     //�ƶ��༭���ֶ�����������IDC_EDIT_NAME, �������ݲ�������
	CCheckEdit m_EditNumber;			  //�ƶ��༭���ֶ�����������IDC_EDIT_NUMBER, ֻ����������
	CCheckEdit m_EditPercent;			  //����IDC_EDIT_PERCENT    
	CCheckEdit m_EditQuota;			      //����IDC_EDIT_QUOTA
	CCheckEdit m_EditExempt;	          //����IDC_EDIT_EXEMPT
	CButton m_CheckNoPay;
	CStatic m_StaticMsg;
	CStatic m_StaticMsg2;
	CString strMsg;						  //������ʾ��Ϣ

	int m_nItem;						  //�б���ͼ����
	int m_nSubItem;						  //�б���ͼ����
	
	CButton m_CheckOutM;				  //�����뽻ǿ��ҽ����ʧ�ķ���
	CButton m_CheckOutD;				  //�����뽻ǿ�������˲���ʧ�ķ���
	CButton m_CheckOutP;				  //�����뽻ǿ�ղƲ���ʧ�ķ���

	CMemoryDC m_mdc;			
	CRect m_rtCls;						//�رհ�ťλ��
	CRect m_rtMin;						//��С����ťλ��
	
	CBrush m_brush;						//�ؼ�������ˢ
};
