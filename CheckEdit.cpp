// CheckEdit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Counter.h"
#include "CheckEdit.h"


// CCheckEdit

IMPLEMENT_DYNAMIC(CCheckEdit, CEdit)

	CCheckEdit::CCheckEdit()
{

}

CCheckEdit::~CCheckEdit()
{
}


BEGIN_MESSAGE_MAP(CCheckEdit, CEdit)
	ON_WM_CHAR()
END_MESSAGE_MAP()



// CCheckEdit ��Ϣ�������

//ֻ������������ С����
void CCheckEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//ֻ���� ���֡�С���㡢�˸�
	if( (nChar < '0' || nChar > '9') && nChar != '.' && nChar != VK_BACK )
		return ;

	CString strCheck;
	CEdit *pEdit = (CEdit*)GetFocus();
	pEdit->GetWindowTextW(strCheck);
	DWORD dwSel = pEdit->GetSel();

	//����������  1.����������С����	2.���˸�λΪ0�⣬���λ����Ϊ 0
	if(dwSel == 0){
		if(nChar == '.' || (nChar == '0' && !strCheck.IsEmpty()))
			return ;
	}
	//��겻�������  1.ֻ��������һ��С����	2.ֻ��һ��0������£�����С�������κ����־����ǵ�0������Ҫ���ľ�����գ�
	else{
		if(nChar == '.' && strCheck.Find(_T('.')) != -1)
			return ;
		if(strCheck.Compare(_T("0")) == 0 && (nChar != '.'&& nChar != VK_BACK))
			pEdit->SetWindowTextW(NULL);
	}

	CEdit::OnChar(nChar, nRepCnt, nFlags);
}

/*BOOL CCheckEdit::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN){
		UINT nChar = pMsg->wParam;
		if( (nChar == 'C' || nChar == 'X' || nChar == 'V') && ::GetKeyState(VK_CONTROL) < 0 )
			return CEdit::PreTranslateMessage(pMsg);
		else{
			if( (nChar < '0' || nChar > '9') && nChar != VK_DECIMAL && nChar != VK_BACK )
				return TRUE;
			CString strCheck;
			CEdit *pEdit = (CEdit*)GetFocus();
			pEdit->GetWindowTextW(strCheck);
			DWORD dwSel = pEdit->GetSel();
			//����������  1.����������С����	2.���˸�λΪ0�⣬���λ����Ϊ 0
			if(dwSel == 0){
				if(nChar == '.' || (nChar == '0' && !strCheck.IsEmpty()))
					return TRUE;
			}
			//��겻�������  1.ֻ��������һ��С����	2.ֻ��һ��0������£�����С�������κ����־����ǵ�0������Ҫ���ľ�����գ�
			else{
				if(nChar == '.' && strCheck.Find(_T('.')) != -1)
					return TRUE;
				if(strCheck.Compare(_T("0")) == 0 && (nChar != '.'&& nChar != VK_BACK)){
					pEdit->SetWindowTextW(NULL);
					return FALSE;
				}
			}
		}	
	}

	return CEdit::PreTranslateMessage(pMsg);
}*/