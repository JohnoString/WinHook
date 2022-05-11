
// CallAddDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "CallAdd.h"
#include "CallAddDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCallAddDlg 对话框
CCallAddDlg::CCallAddDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALLADD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCallAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCallAddDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCallAddDlg::OnAddBnClickedButton)
	ON_BN_CLICKED(IDC_BUTTON3, &CCallAddDlg::OnBnClickedButtonStartHook)
	ON_BN_CLICKED(IDC_BUTTON2, &CCallAddDlg::OnBnClickedButtonStopHook)
END_MESSAGE_MAP()


// CCallAddDlg 消息处理程序
BOOL CCallAddDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。 当应用程序主窗口不是对话框时，框架将自动
	// 执行此操作
	SetIcon(m_hIcon, TRUE);	 // 设置大图标
	SetIcon(m_hIcon, FALSE); // 设置小图标

	// TODO: 在此添加额外的初始化代码
	return TRUE; // 除非将焦点设置到控件，否则返回 TRUE
}

void CCallAddDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCallAddDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCallAddDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCallAddDlg::OnAddBnClickedButton()
{
	HINSTANCE hAddDll = NULL;
	typedef int (WINAPI* AddProc)(int a, int b); // 函数原型定义
	AddProc add;
	
	if (hAddDll == NULL)
	{
		hAddDll = ::LoadLibrary(_T("add.dll")); // 加载dll
	}
	
	if (hAddDll == NULL) {
		return;
	}

	add = (AddProc)::GetProcAddress(hAddDll, "_add@8"); // 获取函数add地址

	int a = 1;
	int b = 2;
	int c = add(a, b); // 调用函数

	CString tem;
	tem.Format(_T("%d+%d=%d"), a, b, c);
	AfxMessageBox(tem);
}

HINSTANCE hinst = NULL;
void CCallAddDlg::OnBnClickedButtonStartHook()
{
	typedef BOOL(CALLBACK* inshook)(); // 函数原型定义
	inshook insthook;

	hinst = LoadLibrary(_T("Hook.dll")); // 加载dll文件
	if (hinst == NULL)
	{
		AfxMessageBox(_T("no Hook.dll!"));
		return;
	}
	
	insthook = ::GetProcAddress(hinst, "InstallHook"); // 获取函数地址
	if (insthook == NULL)
	{
		AfxMessageBox(_T("func not found!"));
		return;
	}

	insthook(); // 开始HOOK
}

void CCallAddDlg::OnBnClickedButtonStopHook()
{
	if (hinst == NULL)
	{
		return;
	}

	typedef BOOL(CALLBACK* UnhookProc)(); // 函数原型定义
	UnhookProc UninstallHook;

	UninstallHook = ::GetProcAddress(hinst, "UninstallHook");// 获取函数地址
	if (UninstallHook != NULL)
	{
		UninstallHook();
	}

	if (hinst != NULL)
	{
		::FreeLibrary(hinst);
	}
}
