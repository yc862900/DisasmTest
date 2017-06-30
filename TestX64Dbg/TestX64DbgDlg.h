// TestX64DbgDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CTestX64DbgDlg �Ի���
class CTestX64DbgDlg : public CDialog
{
// ����
public:
	CTestX64DbgDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TESTX64DBG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
