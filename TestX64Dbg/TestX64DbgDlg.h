// TestX64DbgDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CTestX64DbgDlg 对话框
class CTestX64DbgDlg : public CDialog
{
// 构造
public:
	CTestX64DbgDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TESTX64DBG_DIALOG };

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
	afx_msg void OnBnClickedOk();
	CEdit m_disasmBin;
	CEdit m_disasmNom;
	unsigned int encode(TCHAR* text,unsigned char *array);
public:
	CEdit m_asmNom;
public:
	CEdit m_asmBin;
public:
	afx_msg void OnEnChangeDisasmBin();
public:
	afx_msg void OnEnChangeAsmNom();
public:
	CButton m_c4,m_c5;
public:
	CEdit m_r;
	CEdit m_x;
	CEdit m_b;
	CEdit m_mmmmm;
	CEdit m_w;
	CEdit m_vvvv;
	CEdit m_l;
	CEdit m_pp;
public:
	afx_msg void OnBnClickedC5();
public:
	afx_msg void OnBnClickedC4();
public:
	afx_msg void OnEnChangeR();
	void UpdateValue();
public:
	afx_msg void OnEnChangeX();
public:
	afx_msg void OnEnChangeB();
public:
	afx_msg void OnEnChangeMmmmm();
public:
	afx_msg void OnEnChangeW();
public:
	afx_msg void OnEnChangeVvvv();
public:
	afx_msg void OnEnChangeL();
public:
	afx_msg void OnEnChangePp();
public:
	CEdit m_rex;
public:
	afx_msg void OnEnChangeRex();
	void GetDisasm();
public:
	CEdit m_disasmYC;
public:
	CEdit m_len;
public:
	CButton m_zeroPrefix;
};
