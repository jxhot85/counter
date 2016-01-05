// ���չ�˾�⳥��������

#pragma once

typedef struct tag_AssignItem{
	double dAssignM;
	double dAssignD;
	double dAssignP; 
	double dAssignB; 
	double dAssignI;
}AssignItem;

class CThird;

class CAssignItem
{
public:
	CAssignItem();
	CAssignItem(CThird *);
	~CAssignItem(void);
	//��ǿ���⸶�ϼ�
	double SumJQX(void){
		return m_dAssignM + m_dAssignD + m_dAssignP;
	}
	//�����ںϼ�
	double SumInsurance(void){
		return SumJQX() + m_dAssignB;
	}
	//�⸶�ܼ�
	double SumAll(void){
		return SumInsurance() + m_dAssignI;
	}
	//
	CThird * getThird(){
		return m_pThird;
	}
	void GetItem(AssignItem &item) const{
		item.dAssignM = m_dAssignM;
		item.dAssignD = m_dAssignD;
		item.dAssignP = m_dAssignP;
		item.dAssignB = m_dAssignB;
		item.dAssignI = m_dAssignI;
	}

private:
	CThird *m_pThird;					//������
	double m_dAssignM;					//ҽ�Ʒ����⸶����
	double m_dAssignD;					//�����˲��⸶����
	double m_dAssignP;					//�Ʋ���ʧ�⸶����
	double m_dAssignB;					//��ҵ���⸶����
	double m_dAssignI;					//���������⸶����

	friend class CCompany;
	//friend class CCase;
};

