#include "stdafx.h"
#include "Company.h"
#include "Third.h"
#include "AssignItem.h"


CCompany::CCompany()
{
}


CCompany::CCompany(const CString &strCompany, const CString &strInsured, double dDutyI, double dQuotaB, double dDutyC, BOOL bFlag)
	:m_strCompany(strCompany), m_strInsured(strInsured), m_dDutyI(dDutyI), m_dQuotaB(dQuotaB), m_dDutyC(dDutyC), m_bFlag(bFlag)
{
	if(dDutyI){
		m_dQuotaM = Y_QUOTAM;
		m_dQuotaD = Y_QUOTAD;
		m_dQuotaP = Y_QUOTAP;
	}
	else{
		m_dQuotaM = N_QUOTAM;
		m_dQuotaD = N_QUOTAD;
		m_dQuotaP = N_QUOTAP;
	}
}


CCompany::~CCompany(void)
{
	Release();
}


BOOL CCompany::AddItem(CAssignItem *pItem)
{
	if(!pItem)
		return FALSE;
	m_ListAssign.push_back(pItem);
	return TRUE;
}


void CCompany::AssignJQX(double dSumQuotaM, double dSumQuotaD, double dSumQuotaP)
{
	double dCoefM, dCoefD, dCoefP;      //比例系数（当前保险公司限额占限额总合之比）
	for( asgn_Iter = m_ListAssign.begin(); asgn_Iter != m_ListAssign.end(); asgn_Iter++ )
	{
		CAssignItem *pItem = *asgn_Iter;
		CThird *pThird = pItem->m_pThird;
		if(pThird->m_pCompany)
		{
			dCoefM = m_dQuotaM / (dSumQuotaM - pThird->m_pCompany->m_dQuotaM);
			dCoefD = m_dQuotaD / (dSumQuotaD - pThird->m_pCompany->m_dQuotaD);
			dCoefP = m_dQuotaP / (dSumQuotaP - pThird->m_pCompany->m_dQuotaP);
		}
		else
		{
			dCoefM = m_dQuotaM / dSumQuotaM;
			dCoefD = m_dQuotaD / dSumQuotaD;
			dCoefP = m_dQuotaP / dSumQuotaP;
		}
		pItem->m_dAssignM = dCoefM * pThird->m_dDamageM;
		pItem->m_dAssignD = dCoefD * pThird->m_dDamageD;
		pItem->m_dAssignP = dCoefP * pThird->m_dDamageP;
	}
}


void CCompany::AssignDamageB()
{     
	//被保险人无责，不用分配
	if(m_dDutyI == 0.0)
		return;
	for( asgn_Iter = m_ListAssign.begin(); asgn_Iter != m_ListAssign.end(); asgn_Iter++ )
	{
		CAssignItem *pItem = *asgn_Iter;
		//有商业险
		if(m_dQuotaB){
			//保险公司赔付金额
			pItem->m_dAssignB = m_dDutyC * pItem->m_pThird->m_dDamageB;
			pItem->m_dAssignI = (m_dDutyI - m_dDutyC) * pItem->m_pThird->m_dDamageB +  pItem->m_pThird->m_dDamageE * m_dDutyI;
		}
		//没有商业险
		else
			pItem->m_dAssignI = (pItem->m_pThird->m_dDamageB + pItem->m_pThird->m_dDamageE) * m_dDutyI;
	}
}


void CCompany::ReAssignDamageM(double dSum)
{
	double dPreAssignM;
	for( asgn_Iter = m_ListAssign.begin(); asgn_Iter != m_ListAssign.end(); asgn_Iter++ )
	{
		CAssignItem *pItem = *asgn_Iter;
		dPreAssignM = pItem->m_dAssignM;
		pItem->m_dAssignM = m_dQuotaM * (pItem->m_dAssignM / dSum);
		//超出部分计入商业险部分损失 
		pItem->m_pThird->m_dDamageB += ( dPreAssignM - pItem->m_dAssignM );
	}
}


void CCompany::ReAssignDamageD(double dSum)
{
	double dPreAssignD;
	for( asgn_Iter = m_ListAssign.begin(); asgn_Iter != m_ListAssign.end(); asgn_Iter++ )
	{
		CAssignItem *pItem = *asgn_Iter;
		dPreAssignD = pItem->m_dAssignD;
		pItem->m_dAssignD = m_dQuotaD * (pItem->m_dAssignD / dSum);
		//超出部分计入商业险部分损失	
		pItem->m_pThird->m_dDamageB += ( dPreAssignD - pItem->m_dAssignD );
	}
}


void CCompany::ReAssignDamageP(double dSum)
{
	double dPreAssignP;
	for( asgn_Iter = m_ListAssign.begin(); asgn_Iter != m_ListAssign.end(); asgn_Iter++ )
	{
		CAssignItem *pItem = *asgn_Iter;
		dPreAssignP = pItem->m_dAssignP;
		pItem->m_dAssignP = m_dQuotaP * (pItem->m_dAssignP / dSum);
		//超出部分计入商业险部分损失
		pItem->m_pThird->m_dDamageB += ( dPreAssignP - pItem->m_dAssignP );
	}
}


void CCompany::ReAssignDamageB(double dSum)
{
	double dPreAssignB;
	for( asgn_Iter = m_ListAssign.begin(); asgn_Iter != m_ListAssign.end(); asgn_Iter++ )
	{
		CAssignItem *pItem = *asgn_Iter;
		dPreAssignB = pItem->m_dAssignB;
		pItem->m_dAssignB = m_dQuotaB * (pItem->m_dAssignB / dSum);
		//超出部分由被保险人承担
		pItem->m_dAssignI += ( dPreAssignB - pItem->m_dAssignB );
	}
}


double CCompany::SumAssignM()
{
	double dSum = 0.0;
	for( asgn_Iter = m_ListAssign.begin(); asgn_Iter != m_ListAssign.end(); asgn_Iter++ )
		dSum += (*asgn_Iter)->m_dAssignM;
	return dSum;
}


double CCompany::SumAssignD()
{
	double dSum = 0.0;
	for( asgn_Iter = m_ListAssign.begin(); asgn_Iter != m_ListAssign.end(); asgn_Iter++ )
		dSum += (*asgn_Iter)->m_dAssignD;
	return dSum;
}


double CCompany::SumAssignP()
{
	double dSum = 0.0;
	for( asgn_Iter = m_ListAssign.begin(); asgn_Iter != m_ListAssign.end(); asgn_Iter++ )
		dSum += (*asgn_Iter)->m_dAssignP;
	return dSum;
}


double CCompany::SumAssignB()
{
	double dSum = 0.0;
	for( asgn_Iter = m_ListAssign.begin(); asgn_Iter != m_ListAssign.end(); asgn_Iter++ )
		dSum += (*asgn_Iter)->m_dAssignB;
	return dSum;
}


void CCompany::ShiftDamageP()
{
	for( asgn_Iter = m_ListAssign.begin(); asgn_Iter != m_ListAssign.end(); asgn_Iter++ )
	{
		CAssignItem *pItem = (*asgn_Iter);
		pItem->m_pThird->m_dDamageB += pItem->m_dAssignP;
		pItem->m_dAssignP = 0.0;
	}
}


void CCompany::Release()
{
	for( asgn_Iter = m_ListAssign.begin(); asgn_Iter != m_ListAssign.end(); asgn_Iter++ )
		delete *asgn_Iter;
}
