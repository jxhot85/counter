#include "stdafx.h"
#include "Third.h"


CThird::CThird()
{
}


CThird::CThird(const CString &strThird, double dDamageM, double dDamageD, double dDamageP,double DamageE, const CCompany *pCompany)
	:m_strThird(strThird), m_dDamageM(dDamageM), m_dDamageD(dDamageD),m_dDamageP(dDamageP), 
		m_dDamageE(DamageE), m_pCompany(pCompany), m_dDamageB(0.0)
{
}


CThird::~CThird(void)
{
}
