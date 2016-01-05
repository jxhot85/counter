#include "stdafx.h"
#include "AssignItem.h"


CAssignItem::CAssignItem()
{
}


CAssignItem::CAssignItem(CThird *pThird)
	:m_pThird(pThird), m_dAssignM(0.0),m_dAssignD(0.0), m_dAssignP(0.0), m_dAssignB(0.0), m_dAssignI(0.0)
{
	ASSERT(m_pThird);
}


CAssignItem::~CAssignItem(void)
{
}

