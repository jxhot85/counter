#pragma once


// CCheckEdit

class CCheckEdit : public CEdit
{
	DECLARE_DYNAMIC(CCheckEdit)

public:
	CCheckEdit();
	virtual ~CCheckEdit();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//BOOL PreTranslateMessage(MSG* pMsg);

protected:
	DECLARE_MESSAGE_MAP()
};


