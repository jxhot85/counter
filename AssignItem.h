// 保险公司赔偿款分配表项

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
	//交强险赔付合计
	double SumJQX(void){
		return m_dAssignM + m_dAssignD + m_dAssignP;
	}
	//保险内合计
	double SumInsurance(void){
		return SumJQX() + m_dAssignB;
	}
	//赔付总计
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
	CThird *m_pThird;					//第三者
	double m_dAssignM;					//医疗费用赔付部分
	double m_dAssignD;					//死亡伤残赔付部分
	double m_dAssignP;					//财产损失赔付部分
	double m_dAssignB;					//商业险赔付部分
	double m_dAssignI;					//被保险人赔付部分

	friend class CCompany;
	//friend class CCase;
};

