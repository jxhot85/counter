#pragma once


#include <list>
using namespace std;
class CAssignItem;


//����
#define Y_QUOTAM 10000.0;					//ҽ�Ʒ����⳥�޶�
#define Y_QUOTAD 110000.0;					//�����˲��⳥�޶�
#define Y_QUOTAP 2000.0;					//�Ʋ���ʧ�⳥�޶�
//����
#define N_QUOTAM 1000.0;					//ҽ�Ʒ����⳥�޶�
#define N_QUOTAD 11000.0;					//�����˲��⳥�޶�
#define N_QUOTAP 100.0;						//�Ʋ���ʧ�⳥�޶�


class CCompany
{
public:
	CCompany();
	CCompany(const CString &strCompany, const CString &strInsured, double dDutyI, double dQuotaB, double dDutyC, BOOL bFlag);
	~CCompany(void);

	//��ӷ������AssignItem
	BOOL AddItem(CAssignItem *pItem);

	//��ǿ��Ԥ���䣬�����չ�˾�޶�ȷ���,����Ϊ�������޶��ܺ�
	void AssignJQX(double dSumQuotaM, double dSumQuotaD, double dSumQuotaP);
	//������ǿ�ղ���Ԥ���䣬�����������˷���
	void AssignDamageB();

	//Ԥ�������ܺͳ��޶��Ԥ������ռ�����·���
	void ReAssignDamageM(double dSum);
	void ReAssignDamageD(double dSum);
	void ReAssignDamageP(double dSum);
	void ReAssignDamageB(double dSum);

	//����������ܺ�
	double SumAssignM();
	double SumAssignD();
	double SumAssignP();
	double SumAssignB();

	//������ĲƲ���ʧ��������߶�����ҵ����ʧ����
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

	//�ͷŶ�
	void Release();
private:
	CString m_strCompany;						//���չ�˾����
	CString m_strInsured;						//������������
	double m_dQuotaM;							//ҽ�Ʒ����޶�
	double m_dQuotaD;							//�����˲��޶�
	double m_dQuotaP;							//�Ʋ���ʧ�޶�
	double m_dQuotaB;							//��ҵ���޶�
	double m_dDutyI;  							//�������˳е������α���
	double m_dDutyC;							//���չ�˾�е������α���
	list <CAssignItem *> m_ListAssign;			//���չ�˾�⳥������
	list <CAssignItem *>::iterator asgn_Iter;
	BOOL m_bFlag;								//��ǿ�ղƲ�����

	friend class CCase;
};
