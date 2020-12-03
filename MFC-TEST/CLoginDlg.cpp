// CLoginDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFC-TEST.h"
#include "MFC-TESTDlg.h"
#include "CLoginDlg.h"
#include "afxdialogex.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LoginDig, pParent)
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LOGIN, login);
	DDX_Control(pDX, IDC_EDITNAME, name);
	DDX_Control(pDX, IDC_EDITPW, password);
	DDX_Control(pDX, IDC_CHECKPW, pwr);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_LOGIN, &CLoginDlg::OnBnClickedLogin)
	ON_BN_CLICKED(IDC_CHECKPW, &CLoginDlg::OnBnClickedCheckpw)
	ON_BN_CLICKED(IDCANCEL, &CLoginDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


void CLoginDlg::OnBnClickedLogin()
{
	// TODO: 在此添加控件通知处理程序代码
	CString Edit1, Edit2;
	name.GetWindowTextA(Edit1);
	password.GetWindowTextA(Edit2);
	if (Edit1.IsEmpty())
	{
		MessageBox(TEXT("用户名不能为空"));
		return;
	}
	else if (Edit2.IsEmpty())
	{
		MessageBox(TEXT("密码不能为空"));
		return;
	}

	//CString name, pwd;

	if (Edit1 == "shaoyuhui")
	{
		if (Edit2 == "1234")
		{
			CDialog::OnCancel();
			
		}
		else
		{
			MessageBox(TEXT("密码错误"));
		}
	}
	else
	{
		MessageBox(TEXT("用户名错误"));
	}
}


void CLoginDlg::OnBnClickedCheckpw()
{
	// TODO: 在此添加控件通知处理程序代码
	// 若在显示密码前打勾，则密码显示为明文，默认为密文（星号）
	UpdateData(TRUE); // 更新控件对应变量的值
	if (pwr.GetCheck() == 1)
	{
		CEdit* pmyEdit = (CEdit*)GetDlgItem(IDC_EDITPW); // 密码编辑框控件的指针
		pmyEdit->SetPasswordChar(0); // 显示格式为明文
		ASSERT(!(pmyEdit->GetStyle() & ES_PASSWORD));
		RedrawWindow();//动态刷新
	}
	else
	{
		CEdit* pmyEdit = (CEdit*)GetDlgItem(IDC_EDITPW); // 密码编辑框控件的指针
		pmyEdit->SetPasswordChar('*'); // 显示格式为星号
		RedrawWindow();
	}
}


void CLoginDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
