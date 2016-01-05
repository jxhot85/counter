#include "StdAfx.h"
#include "Case.h"
#include "Company.h"
#include "Third.h"
#include "AssignItem.h"
#include <iterator>


CCase::CCase(void)
{
}


CCase::~CCase(void)
{
	Release();
}


void CCase::Calculate()
{
	/////////1.计算交强险/////////
	//计算交强险各分项限额总合
	double dSumQuotaM, dSumQuotaD, dSumQuotaP;		
	SumQuota(dSumQuotaM, dSumQuotaD, dSumQuotaP);
	for(com_Iter = m_ListCom.begin(); com_Iter!=m_ListCom.end(); com_Iter++)
	{
		CCompany *pCom = *com_Iter;
		//预分配交强险各分项
		pCom->AssignJQX(dSumQuotaM, dSumQuotaD, dSumQuotaP);	
		//如果预分配的金额总和超限额，按预分配金额所占比例重新分配
		double dSum;
		if((dSum = pCom->SumAssignM()) > pCom->m_dQuotaM)
		{
			pCom->ReAssignDamageM(dSum);
		}
		if((dSum = pCom->SumAssignD()) > pCom->m_dQuotaD)
		{
			pCom->ReAssignDamageD(dSum);
		}
		//交强险财产是否不赔，则预分配的财产项损失计入商业险部分
		if(pCom->m_bFlag)
			pCom->ShiftDamageP();
		else{
			if((dSum = pCom->SumAssignP()) > pCom->m_dQuotaP)
			{
				pCom->ReAssignDamageP(dSum);
			}
		}
	}
	/////////2.计算商业险/////////
	for(com_Iter = m_ListCom.begin(); com_Iter!=m_ListCom.end(); com_Iter++)
	{
		CCompany *pCom = *com_Iter;
		//预分配超出交强险部分
		pCom->AssignDamageB();
		//如果预分配总和超限额，按预分配金额所占比例重新分配
		double dSum = pCom->SumAssignB();
		if( dSum > pCom->m_dQuotaB)
			pCom->ReAssignDamageB(dSum);
	}
}


BOOL CCase::AddCompany(const CString &strCompany, const CString &strInsured, double dDutyI, double dQuotaB, double dDutyC, BOOL bFlag)
{
	CCompany *pCom = new CCompany(strCompany, strInsured, dDutyI, dQuotaB, dDutyC, bFlag);
	if(!pCom)
		return FALSE;
	m_ListCom.push_back(pCom);
	return TRUE;
}


BOOL CCase::AddThird(const CString &strThird, double dDamageM, double dDamageD, double dDamageP, double DamageE, const CString &strCompany, unsigned char nState)
{
	CCompany *pCompany = NULL;
	if(!strCompany.IsEmpty()){
		pCompany = FindCompany(strCompany);
		if(!pCompany)
			return FALSE;
	}
	CThird *pThird = new CThird(strThird, dDamageM, dDamageD, dDamageP, DamageE, pCompany);
	if(!pThird)
		return FALSE;
	if(nState & 1)
		pThird->ShiftDamageM();		//医疗损失不参与交强险计算
	if(nState & 2)
		pThird->ShiftDamageD();		//死亡伤残损失不参与交强险计算
	if(nState & 4)
		pThird->ShiftDamageP();		//财产损失不参与交强险计算

	m_ListThird.push_back(pThird);
	return TRUE;
}


CCompany* CCase::FindCompany(const CString &strCompany)
{
	for(com_Iter = m_ListCom.begin(); com_Iter != m_ListCom.end(); com_Iter++)
	{
		if(strCompany == (*com_Iter)->m_strCompany)
			return *com_Iter;
	}
	return NULL;
}


BOOL CCase::LoadThird()
{
	for(com_Iter = m_ListCom.begin(); com_Iter != m_ListCom.end(); com_Iter++){
		for(third_Iter = m_ListThird.begin(); third_Iter != m_ListThird.end(); third_Iter++){
			if((*third_Iter)->m_pCompany == *com_Iter)
				continue;
			CAssignItem *pItem = (CAssignItem*)new CAssignItem(*third_Iter);
			if( !(*com_Iter)->AddItem(pItem) )
				return FALSE;
		}
	}
	return TRUE;
}


void CCase::SumQuota(double &dQuotaM, double &dQuotaD, double &dQuotaP)
{
	dQuotaM = dQuotaD = dQuotaP = 0.0;
	for(com_Iter = m_ListCom.begin(); com_Iter != m_ListCom.end(); com_Iter++){
		dQuotaM += (*com_Iter)->m_dQuotaM;
		dQuotaD += (*com_Iter)->m_dQuotaD;
		dQuotaP += (*com_Iter)->m_dQuotaP;
	}
}


void CCase::Release()
{
	for(com_Iter = m_ListCom.begin(); com_Iter != m_ListCom.end(); com_Iter++)
	{
		//(*com_Iter)->Release();		//释放每个保险公司的分配表
		delete *com_Iter;
	}
	for(third_Iter = m_ListThird.begin(); third_Iter != m_ListThird.end(); third_Iter++)
	{
		delete *third_Iter;
	}
}


void CCase::GetCount(int &nTable, int &nItem)
{
	nTable = nItem = 0;
	for(com_Iter = m_ListCom.begin(); com_Iter != m_ListCom.end(); com_Iter++, nTable++)
		for(third_Iter = m_ListThird.begin(); third_Iter != m_ListThird.end(); third_Iter++, nItem++)
			;
}