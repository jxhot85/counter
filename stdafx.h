
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持

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




//颜色
#define TITLE_COLOR		RGB(0,50,120)		//标题栏颜色
#define TABLE_HD_COLOR	RGB(240,240,200)	//表头填充色
#define TABLE_BK_COLOR	RGB(255,255,255)	//表项背景色
#define CLT_BK_COLOR	RGB(255,255,255)	//客户区背景色
#define UNDER_COLOR		RGB(240,240,200)	//主对话框控件底色
//标题栏参数
#define TITLE_HEIGHT	50					//标题栏高度
#define SYSMENU_RECT	20					//最大化最小化关闭按钮尺寸
//表参数
#define COL_WIDTH	135						//列宽度
#define COL_NUM		8						//列数
#define ROW_HEIGHT  30						//行高度
#define HEAD_HEIGHT 80						//表头高度
#define TABLE_GAP	50						//表间间隔
#define TABLE_BOTTOM_GAP 50					//最后一张表末尾留底
//滚动条参数
#define SCROLL_WIDTH 30						//滚动条宽度
#define SCROLL_PIX	10						//一次滚动范围
#define RESIZE_GAP	2						//窗口边缘可以改变大小的范围

#define WM_USER_DESTROY WM_USER + 1
