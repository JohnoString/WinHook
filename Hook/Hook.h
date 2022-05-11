// Hook.h: Hook DLL 的主标头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号

//不同Instance共享的该变量
#pragma data_seg("SHARED")
static HHOOK  hhk = NULL; //鼠标钩子句柄
static HINSTANCE hinst = NULL; //本dll的实例句柄 (hook.dll) https://www.cnblogs.com/fzy456/p/14439422.html
#pragma data_seg()
#pragma comment(linker, "/section:SHARED,rws")
//以上的变量共享哦!

CString temp; //用于显示错误的临时变量
bool bHook = false; //是否Hook了函数
bool m_bInjected = false; //是否对API进行了Hook
BYTE OldCode[5]; //老的系统API入口代码
BYTE NewCode[5]; //要跳转的API代码 (jmp xxxx)
typedef int (WINAPI* AddProc)(int a, int b);//add.dll中的add函数定义
AddProc add; //add.dll中的add函数
HANDLE hProcess = NULL; //所处进程的句柄
FARPROC pfadd;  //指向add函数的远指针
DWORD dwPid;  //所处进程ID

// CHookApp
// 有关此类实现的信息，请参阅 Hook.cpp
//

class CHookApp : public CWinApp
{
public:
	CHookApp();

// 重写
public:
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()
};
