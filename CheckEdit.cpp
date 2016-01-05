// CheckEdit.cpp : 实现文件
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



// CCheckEdit 消息处理程序

//只允许输入数字 小数点
void CCheckEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//只接受 数字、小数点、退格
	if( (nChar < '0' || nChar > '9') && nChar != '.' && nChar != VK_BACK )
		return ;

	CString strCheck;
	CEdit *pEdit = (CEdit*)GetFocus();
	pEdit->GetWindowTextW(strCheck);
	DWORD dwSel = pEdit->GetSel();

	//光标在最左边  1.不允许输入小数点	2.除了个位为0外，最高位不能为 0
	if(dwSel == 0){
		if(nChar == '.' || (nChar == '0' && !strCheck.IsEmpty()))
			return ;
	}
	//光标不在最左边  1.只允许输入一个小数点	2.只有一个0的情况下，除了小数点外任何数字均覆盖掉0（这里要做的就是清空）
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
			//光标在最左边  1.不允许输入小数点	2.除了个位为0外，最高位不能为 0
			if(dwSel == 0){
				if(nChar == '.' || (nChar == '0' && !strCheck.IsEmpty()))
					return TRUE;
			}
			//光标不在最左边  1.只允许输入一个小数点	2.只有一个0的情况下，除了小数点外任何数字均覆盖掉0（这里要做的就是清空）
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