#pragma once


#include <list>
using namespace std;
class CAssignItem;


//有责
#define Y_QUOTAM 10000.0;					//医疗费用赔偿限额
#define Y_QUOTAD 110000.0;					//死亡伤残赔偿限额
#define Y_QUOTAP 2000.0;					//财产损失赔偿限额
//无责
#define N_QUOTAM 1000.0;					//医疗费用赔偿限额
#define N_QUOTAD 11000.0;					//死亡伤残赔偿限额
#define N_QUOTAP 100.0;						//财产损失赔偿限额


class CCompany
{
public:
	CCompany();
	CCompany(const CString &strCompany, const CString &strInsured, double dDutyI, double dQuotaB, double dDutyC, BOOL bFlag);
	~CCompany(void);

	//添加分配表项AssignItem
	BOOL AddItem(CAssignItem *pItem);

	//交强险预分配，按保险公司限额比分配,参数为各分项限额总合
	void AssignJQX(double dSumQuotaM, double dSumQuotaD, double dSumQuotaP);
	//超出交强险部分预分配，包括被保险人分配
	void AssignDamageB();

	//预分配金额总和超限额，按预分配金额占比重新分配
	void ReAssignDamageM(double dSum);
	void ReAssignDamageD(double dSum);
	void ReAssignDamageP(double dSum);
	void ReAssignDamageB(double dSum);

	//各分项分配总和
	double SumAssignM();
	double SumAssignD();
	double SumAssignP();
	double SumAssignB();

	//将分配的财产损失计入第三者对象商业险损失部分
	void ShiftDamageP();
	
	CString GetCompany(){
		return m_strCompany;
	}
	CString GetInsured(){
		return m_strInsured;
	}
	double GetDutyC(){
		return m_dDutyC;
	}
	double GetDutyI(){
		return m_dDutyI;
	}
	list<CAssignItem *> & GetListAssign(){
		return m_ListAssign;
	}

	//释放堆
	void Release();
private:
	CString m_strCompany;						//保险公司名称
	CString m_strInsured;						//被保险人名称
	double m_dQuotaM;							//医疗费用限额
	double m_dQuotaD;							//死亡伤残限额
	double m_dQuotaP;							//财产损失限额
	double m_dQuotaB;							//商业险限额
	double m_dDutyI;  							//被保险人承担的责任比例
	double m_dDutyC;							//保险公司承担的责任比例
	list <CAssignItem *> m_ListAssign;			//保险公司赔偿款分配表
	list <CAssignItem *>::iterator asgn_Iter;
	BOOL m_bFlag;								//交强险财产不赔

	friend class CCase;
};
