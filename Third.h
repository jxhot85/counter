#pragma once

class CCompany;

class CThird
{
public:
	CThird();
	CThird(const CString &strThird, double dDamageM, double dDamageD, double dDamageP, double DamageE, const CCompany *pCompany);
	~CThird(void);

	//��������ʧ�ϼ�
	double SumInsurance(){
		return m_dDamageM + m_dDamageD + m_dDamageP;
	}
	//����ʧ
	double SumAll(){
		return SumInsurance() + m_dDamageE;
	}
	
	CString GetName(){
		return m_strThird;
	}
	//ҽ�Ʒ��ü�����ҵ����ʧ����
	void ShiftDamageM(){
		m_dDamageB += m_dDamageM;
		m_dDamageM = 0.0;
	}
	//�����˲���ʧ������ҵ����ʧ����
	void ShiftDamageD(){
		m_dDamageB += m_dDamageD;
		m_dDamageD = 0.0;
	}
	//�Ʋ���ʧ������ҵ����ʧ����
	void ShiftDamageP(){
		m_dDamageB += m_dDamageP;
		m_dDamageP = 0.0;
	}
private:
	CString m_strThird;				    //����������
	double m_dDamageM;					//ҽ�Ʒ��ã�ҽ���ڣ�
	double m_dDamageD;					//�����˲���ʧ
	double m_dDamageP;					//�Ʋ���ʧ
	double m_dDamageE;					//��������ʧ
	const CCompany *m_pCompany;			//���ڳ����ı��չ�˾��û����Ϊ��
	
	double m_dDamageB;					//������ҵ�յ���ʧ
	
	friend class CCompany;
	friend class CCase;
};

