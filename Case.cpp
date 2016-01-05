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
	/////////1.���㽻ǿ��/////////
	//���㽻ǿ�ո������޶��ܺ�
	double dSumQuotaM, dSumQuotaD, dSumQuotaP;		
	SumQuota(dSumQuotaM, dSumQuotaD, dSumQuotaP);
	for(com_Iter = m_ListCom.begin(); com_Iter!=m_ListCom.end(); com_Iter++)
	{
		CCompany *pCom = *com_Iter;
		//Ԥ���佻ǿ�ո�����
		pCom->AssignJQX(dSumQuotaM, dSumQuotaD, dSumQuotaP);	
		//���Ԥ����Ľ���ܺͳ��޶��Ԥ��������ռ�������·���
		double dSum;
		if((dSum = pCom->SumAssignM()) > pCom->m_dQuotaM)
		{
			pCom->ReAssignDamageM(dSum);
		}
		if((dSum = pCom->SumAssignD()) > pCom->m_dQuotaD)
		{
			pCom->ReAssignDamageD(dSum);
		}
		//��ǿ�ղƲ��Ƿ��⣬��Ԥ����ĲƲ�����ʧ������ҵ�ղ���
		if(pCom->m_bFlag)
			pCom->ShiftDamageP();
		else{
			if((dSum = pCom->SumAssignP()) > pCom->m_dQuotaP)
			{
				pCom->ReAssignDamageP(dSum);
			}
		}
	}
	/////////2.������ҵ��/////////
	for(com_Iter = m_ListCom.begin(); com_Iter!=m_ListCom.end(); com_Iter++)
	{
		CCompany *pCom = *com_Iter;
		//Ԥ���䳬����ǿ�ղ���
		pCom->AssignDamageB();
		//���Ԥ�����ܺͳ��޶��Ԥ��������ռ�������·���
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
		pThird->ShiftDamageM();		//ҽ����ʧ�����뽻ǿ�ռ���
	if(nState & 2)
		pThird->ShiftDamageD();		//�����˲���ʧ�����뽻ǿ�ռ���
	if(nState & 4)
		pThird->ShiftDamageP();		//�Ʋ���ʧ�����뽻ǿ�ռ���

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
		//(*com_Iter)->Release();		//�ͷ�ÿ�����չ�˾�ķ����
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