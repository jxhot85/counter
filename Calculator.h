#pragma once

#include "MyList.h"
#include "Company.h"
#include "Third.h"
#include "MyListIterator.h"

class CCalculator
{
public:
	CCalculator(void);
	~CCalculator(void);

private:
	MyList<CCompany *> &m_CompanyList;
	MyList<CThird *> *m_ThirdList;
	MyListIterator<CCompany *> &m_CompanyIter;
	MyListIterator<CThird *> &m_ThirdItre;

};

