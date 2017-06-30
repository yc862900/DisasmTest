// TestX64DbgDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestX64Dbg.h"
#include "TestX64DbgDlg.h"
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#ifdef _WIN64
extern "C" {
#include "include64/xed-interface.h"
#include "include64/xed-portability.h"
#include "xed-examples-util.h"
};
#else
extern "C" {
#include "include/xed-interface.h"
#include "include/xed-portability.h"
};
#endif

#ifdef _WIN64
#include "YCDisasm64.h"

#pragma comment(lib,"YCDisasm64.lib")

#include "XEDParse.h"

#pragma comment(lib,"XEDParse_x64.lib")
#else
#include "YCDisasm64.h"

#pragma comment(lib,"YCDisasm32.lib")

#include "XEDParse.h"

#pragma comment(lib,"XEDParse_x86.lib")

#endif
#define GETVALUE(name) m_##name.GetWindowText(name)
#define CONVERTVALUE(name) c##name = _tcstol(name,NULL,2)

#ifdef _WIN64
#pragma comment(lib,"lib64/libxed.lib")
#pragma comment(lib,"lib64/libxed-ild.lib")
#else
#pragma comment(lib,"lib/libxed.lib")
#pragma comment(lib,"lib/libxed-ild.lib")
#endif
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTestX64DbgDlg �Ի���




CTestX64DbgDlg::CTestX64DbgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestX64DbgDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestX64DbgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DISASM_BIN, m_disasmBin);
	DDX_Control(pDX, IDC_DISASM_NOM, m_disasmNom);
	DDX_Control(pDX, IDC_ASM_NOM, m_asmNom);
	DDX_Control(pDX, IDC_ASM_BIN, m_asmBin);
	DDX_Control(pDX, IDC_C4, m_c4);
	DDX_Control(pDX, IDC_C5, m_c5);
	DDX_Control(pDX, IDC_R, m_r);
	DDX_Control(pDX, IDC_X, m_x);
	DDX_Control(pDX, IDC_B, m_b);
	DDX_Control(pDX, IDC_MMMMM, m_mmmmm);
	DDX_Control(pDX, IDC_W, m_w);
	DDX_Control(pDX, IDC_VVVV, m_vvvv);
	DDX_Control(pDX, IDC_L, m_l);
	DDX_Control(pDX, IDC_PP, m_pp);
	DDX_Control(pDX, IDC_REX, m_rex);
	DDX_Control(pDX, IDC_DISASM_YC, m_disasmYC);
	DDX_Control(pDX, IDC_LEN, m_len);
	DDX_Control(pDX, IDC_CHECK1, m_zeroPrefix);
}

BEGIN_MESSAGE_MAP(CTestX64DbgDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_DISASM_BIN, &CTestX64DbgDlg::OnEnChangeDisasmBin)
	ON_EN_CHANGE(IDC_ASM_NOM, &CTestX64DbgDlg::OnEnChangeAsmNom)
	ON_BN_CLICKED(IDC_C5, &CTestX64DbgDlg::OnBnClickedC5)
	ON_BN_CLICKED(IDC_C4, &CTestX64DbgDlg::OnBnClickedC4)
	ON_EN_CHANGE(IDC_R, &CTestX64DbgDlg::OnEnChangeR)
	ON_EN_CHANGE(IDC_X, &CTestX64DbgDlg::OnEnChangeX)
	ON_EN_CHANGE(IDC_B, &CTestX64DbgDlg::OnEnChangeB)
	ON_EN_CHANGE(IDC_MMMMM, &CTestX64DbgDlg::OnEnChangeMmmmm)
	ON_EN_CHANGE(IDC_W, &CTestX64DbgDlg::OnEnChangeW)
	ON_EN_CHANGE(IDC_VVVV, &CTestX64DbgDlg::OnEnChangeVvvv)
	ON_EN_CHANGE(IDC_L, &CTestX64DbgDlg::OnEnChangeL)
	ON_EN_CHANGE(IDC_PP, &CTestX64DbgDlg::OnEnChangePp)
	ON_EN_CHANGE(IDC_REX, &CTestX64DbgDlg::OnEnChangeRex)
END_MESSAGE_MAP()


// CTestX64DbgDlg ��Ϣ�������

BOOL CTestX64DbgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	xed_tables_init();
	m_c5.SetCheck(BST_CHECKED);
	m_x.EnableWindow(FALSE);
	m_b.EnableWindow(FALSE);
	m_mmmmm.EnableWindow(FALSE);
	m_w.EnableWindow(FALSE);
	m_r.LimitText(1);
	m_x.LimitText(1);
	m_b.LimitText(1);
	m_mmmmm.LimitText(5);
	m_w.LimitText(1);
	m_vvvv.LimitText(4);
	m_l.LimitText(1);
	m_pp.LimitText(2);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTestX64DbgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestX64DbgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CTestX64DbgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


unsigned char *GetBin(TCHAR *buf,int &size)
{
	size = 0;
	unsigned char *bin = new unsigned char[100];
	TCHAR *p = buf;
	while (p &&*p)
	{
		bin[size++] = _tcstol(p,NULL,16);
		p = _tcschr(p,' ');
		if (p)
		{
			p++;
		}
	}
	return bin;
}


using namespace std;


unsigned int CTestX64DbgDlg::encode(TCHAR* text,unsigned char *array) 
{
	char encode_text[100];
#ifdef UNICODE
	WideCharToMultiByte(CP_ACP,0,text,-1,encode_text,100,NULL,NULL);
#else
	strcpy(encode_text,text);
#endif
	XEDPARSE xed={0};
#ifdef _WIN64
	xed.x64 = true;
#else
	xed.x64 = false;
#endif
	strcpy(xed.instr,encode_text);
	if (XEDPARSE_ERROR==XEDParseAssemble(&xed))
	{
		return 0;
	}
	memcpy(array,xed.dest,xed.dest_size);
	return xed.dest_size;
}

void CTestX64DbgDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
}

void CTestX64DbgDlg::OnEnChangeDisasmBin()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDisasm();

	
}

void CTestX64DbgDlg::OnEnChangeAsmNom()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_asmBin.SetWindowText(TEXT(""));
	CString disasmBinStr,asmNomStr;
	m_disasmBin.GetWindowText(disasmBinStr);
	m_asmNom.GetWindowText(asmNomStr);
	TCHAR buf[100];
	unsigned char res[XED_MAX_INSTRUCTION_BYTES];
	TCHAR temp[100];
	_tcscpy(temp,asmNomStr);
	unsigned int len = 0;
	if(asmNomStr.GetLength()!=0)
		len = encode(temp,res);
	memset(buf,0,100*sizeof TCHAR);
	for (int i=0;i<len;i++)
	{
		_stprintf(buf + _tcslen(buf),TEXT("%.2X "),res[i]);
	}
	m_asmBin.SetWindowText(buf);
}

void CTestX64DbgDlg::OnBnClickedC5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_x.EnableWindow(FALSE);
	m_b.EnableWindow(FALSE);
	m_mmmmm.EnableWindow(FALSE);
	m_w.EnableWindow(FALSE);
	UpdateValue();
}

void CTestX64DbgDlg::OnBnClickedC4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_x.EnableWindow(1);
	m_b.EnableWindow(1);
	m_mmmmm.EnableWindow(1);
	m_w.EnableWindow(1);
	UpdateValue();
}

void CTestX64DbgDlg::OnEnChangeR()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateValue();
}


void CTestX64DbgDlg::UpdateValue()
{
	CString r,x,b,mmmmm,w,vvvv,l,pp;
	GETVALUE(r);
	GETVALUE(x);
	GETVALUE(b);
	GETVALUE(mmmmm);
	GETVALUE(w);
	GETVALUE(vvvv);
	GETVALUE(l);
	GETVALUE(pp);
	unsigned char cr,cx,cb,cmmmmm,cw,cvvvv,cl,cpp;
	CONVERTVALUE(r);
	CONVERTVALUE(x);
	CONVERTVALUE(b);
	CONVERTVALUE(mmmmm);
	CONVERTVALUE(w);
	CONVERTVALUE(vvvv);
	CONVERTVALUE(l);
	CONVERTVALUE(pp);
	if (m_c5.GetCheck()==BST_CHECKED)
	{
		// 2 bytes
		unsigned char b1,b2;
		b1 = 0xc5;
		b2 = (cr<<7)|(cvvvv<<3)|(cl<<2)|cpp;
		CString t;
		t.Format(TEXT("%.2X %.2X"),b1,b2);
		m_rex.SetWindowText(t);
	}
	else
	{
		// 3 bytes
		unsigned char b1,b2,b3;
		b1 = 0xc4;
		b2 = (cr<<7)|(cx<<6)|(cb<<5)|(cmmmmm);
		b3 = (cw<<7)|(cvvvv<<3)|(cl<<2)|cpp;
		CString t;
		t.Format(TEXT("%.2X %.2X %.2X"),b1,b2,b3);
		m_rex.SetWindowText(t);
	}
}

void CTestX64DbgDlg::OnEnChangeX()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateValue();
}

void CTestX64DbgDlg::OnEnChangeB()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateValue();
}

void CTestX64DbgDlg::OnEnChangeMmmmm()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateValue();

}

void CTestX64DbgDlg::OnEnChangeW()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateValue();
}

void CTestX64DbgDlg::OnEnChangeVvvv()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateValue();
}

void CTestX64DbgDlg::OnEnChangeL()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateValue();
}

void CTestX64DbgDlg::OnEnChangePp()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateValue();
}

void CTestX64DbgDlg::OnEnChangeRex()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDisasm();
}

void CTestX64DbgDlg::GetDisasm()
{
	m_disasmNom.SetWindowText(TEXT(""));
	CString disasmBinStr,rexStr;
	m_disasmBin.GetWindowText(disasmBinStr);
	m_disasmYC.SetWindowText(TEXT(""));
	m_rex.GetWindowText(rexStr);
	TCHAR buf[100];
	if(rexStr.GetLength()==0)
		_stprintf(buf,TEXT("%s"),disasmBinStr);
	else
		_stprintf(buf,TEXT("%s %s"),rexStr,disasmBinStr);
	int size;
	unsigned char * bin = GetBin(buf,size);

	xed_decoded_inst_t inst;
	xed_decoded_inst_zero(&inst);
#ifdef _WIN64
	xed_decoded_inst_set_mode(&inst,XED_MACHINE_MODE_LONG_64, XED_ADDRESS_WIDTH_64b);
#else
	xed_decoded_inst_set_mode(&inst,XED_MACHINE_MODE_LONG_COMPAT_32, XED_ADDRESS_WIDTH_32b);
#endif
	xed_error_enum_t error = xed_decode(&inst,bin, size);
	if (error!=XED_ERROR_NONE)
	{
		TCHAR mes[100];
		_stprintf(mes,TEXT("errorNumber:%d"),int(error));
		//AfxMessageBox(mes);
	}
	else
	{
		char res[100];
		xed_format_context(XED_SYNTAX_INTEL,&inst,res,100,NULL,NULL,NULL);
		SetWindowTextA(m_disasmNom.GetSafeHwnd(),res);
	}
	YCDISASM dis;
	memset(&dis,0,sizeof dis);
	dis.ZeroPrefix = m_zeroPrefix.GetCheck() == BST_CHECKED;
	dis.Rip = bin;
	dis.Size = size;
	int len = YCDisasm(&dis);
	CString strLen;
	strLen.Format(TEXT("%d"),len);
	m_len.SetWindowText(strLen);
	if (len>0)
	{
		for (int i=0;i<strlen(dis.decodedString);i++)
		{
			if (dis.decodedString[i]>='A' &&dis.decodedString[i]<='Z')
			{
				dis.decodedString[i] = dis.decodedString[i] - 'A' + 'a';
			}
		}
		SetWindowTextA(m_disasmYC.GetSafeHwnd(),dis.decodedString);
	}
	delete []bin;
}
