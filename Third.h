#pragma once

class CCompany;

class CThird
{
public:
	CThird();
	CThird(const CString &strThird, double dDamageM, double dDamageD, double dDamageP, double DamageE, const CCompany *pCompany);
	~CThird(void);

	//保险内损失合计
	double SumInsurance(){
		return m_dDamageM + m_dDamageD + m_dDamageP;
	}
	//总损失
	double SumAll(){
		return SumInsurance() + m_dDamageE;
	}
	
	CString GetName(){
		return m_strThird;
	}
	//医疗费用计入商业险损失部分
	void ShiftDamageM(){
		m_dDamageB += m_dDamageM;
		m_dDamageM = 0.0;
	}
	//死亡伤残损失计入商业险损失部分
	void ShiftDamageD(){
		m_dDamageB += m_dDamageD;
		m_dDamageD = 0.0;
	}
	//财产损失计入商业险损失部分
	void ShiftDamageP(){
		m_dDamageB += m_dDamageP;
		m_dDamageP = 0.0;
	}
private:
	CString m_strThird;				    //第三者姓名
	double m_dDamageM;					//医疗费用（医保内）
	double m_dDamageD;					//死亡伤残损失
	double m_dDamageP;					//财产损失
	double m_dDamageE;					//保险外损失
	const CCompany *m_pCompany;			//所在车辆的保险公司，没有则为空
	
	double m_dDamageB;					//计入商业险的损失
	
	friend class CCompany;
	friend class CCase;
};

