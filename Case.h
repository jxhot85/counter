#pragma once

#include <list>
using namespace std;

class CCompany;
class CThird;

class CCase
{
public:
	CCase(void);
	~CCase(void);

	//����
	void Calculate();
	//��ӱ��չ�˾
	BOOL AddCompany(const CString &strCompany, const CString &strInsured, double dDutyI, double dQuotaB, double dDutyC, BOOL bFlag);
	//��ӵ�����
	BOOL AddThird(const CString &strThird, double dDamageM, double dDamageD, double dDamageP, double DamageE, const CString &strCompany, unsigned char nState);
	//��ӱ��չ�˾�����
	BOOL LoadThird();

	//���ұ��չ�˾
	CCompany* FindCompany(const CString &strCompany);
	
	list<CCompany *> & GetListCompany(){
		return m_ListCom;
	}
	//���չ�˾���������չ�˾�������֮�ͣ������������ܺ�
	void GetCount(int &nTable, int &nItem);

	//�ͷŶ�
	void Release();

private:
	//�������б��չ�˾�����޶��ܺ�
	void SumQuota(double &dQuotaM, double &dQuotaD, double &dQuotaP);

private:
	list<CCompany *> m_ListCom;
	list<CThird *> m_ListThird;
	list<CCompany *>::iterator com_Iter;
	list<CThird *>::iterator third_Iter;
};

