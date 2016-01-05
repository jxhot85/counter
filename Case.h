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

	//计算
	void Calculate();
	//添加保险公司
	BOOL AddCompany(const CString &strCompany, const CString &strInsured, double dDutyI, double dQuotaB, double dDutyC, BOOL bFlag);
	//添加第三者
	BOOL AddThird(const CString &strThird, double dDamageM, double dDamageD, double dDamageP, double DamageE, const CString &strCompany, unsigned char nState);
	//添加保险公司分配表
	BOOL LoadThird();

	//查找保险公司
	CCompany* FindCompany(const CString &strCompany);
	
	list<CCompany *> & GetListCompany(){
		return m_ListCom;
	}
	//保险公司个数及保险公司分配对象之和，即分配表表项总和
	void GetCount(int &nTable, int &nItem);

	//释放堆
	void Release();

private:
	//计算所有保险公司分项限额总和
	void SumQuota(double &dQuotaM, double &dQuotaD, double &dQuotaP);

private:
	list<CCompany *> m_ListCom;
	list<CThird *> m_ListThird;
	list<CCompany *>::iterator com_Iter;
	list<CThird *>::iterator third_Iter;
};

