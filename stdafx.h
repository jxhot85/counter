
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��

#include <list>////////////////////////////////







#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif




//��ɫ
#define TITLE_COLOR		RGB(0,50,120)		//��������ɫ
#define TABLE_HD_COLOR	RGB(240,240,200)	//��ͷ���ɫ
#define TABLE_BK_COLOR	RGB(255,255,255)	//�����ɫ
#define CLT_BK_COLOR	RGB(255,255,255)	//�ͻ�������ɫ
#define UNDER_COLOR		RGB(240,240,200)	//���Ի���ؼ���ɫ
//����������
#define TITLE_HEIGHT	50					//�������߶�
#define SYSMENU_RECT	20					//�����С���رհ�ť�ߴ�
//�����
#define COL_WIDTH	135						//�п��
#define COL_NUM		8						//����
#define ROW_HEIGHT  30						//�и߶�
#define HEAD_HEIGHT 80						//��ͷ�߶�
#define TABLE_GAP	50						//�����
#define TABLE_BOTTOM_GAP 50					//���һ�ű�ĩβ����
//����������
#define SCROLL_WIDTH 30						//���������
#define SCROLL_PIX	10						//һ�ι�����Χ
#define RESIZE_GAP	2						//���ڱ�Ե���Ըı��С�ķ�Χ

#define WM_USER_DESTROY WM_USER + 1
