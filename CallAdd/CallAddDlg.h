
// CallAddDlg.h: 头文件
//

#pragma once


// CCallAddDlg 对话框
class CCallAddDlg : public CDialogEx
{
// 构造
public:
	CCallAddDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALLADD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAddBnClickedButton();
	afx_msg void OnBnClickedButtonStartHook();
	afx_msg void OnBnClickedButtonStopHook();
};
