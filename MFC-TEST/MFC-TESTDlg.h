
// MFC-TESTDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include <vector>
#include <string>


// CMFCTESTDlg 对话框
class CMFCTESTDlg : public CDialogEx
{
// 构造
public:
	CMFCTESTDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	MYSQL m_mysql;			  //数据库结构
	MYSQL_RES* m_res;         //查询的返回结果集
	MYSQL_ROW m_row;          //获取每一条记录
	std::vector<std::string> m_data[100];  //存放数据库记录，最大为100条//vector是表示可以改变大小的数组的序列容器。(动态分配）
	int m_iRow;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_queryBook;
	CString m_queryAuthor;
	float m_priceMin;
	float m_priceMax;
	CString m_addBook;
	CString m_addAuthor;
	CString m_addPublisher;
	CString m_addTime;
	float m_addPrice;
	BOOL ConnectDB();		//连接MYSQL数据库
	BOOL SelectDB();		//查询数据
	BOOL InsertDB();		//插入数据
	BOOL DeleteDB();        //删除数据
	void GetDataFromDB();   //从数据库获取数据
	void ShowInfo();        //显示数据
	void ClearData();       //清空数据
	afx_msg void OnBnClickedBtnQuery();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnShowAll();
	afx_msg void OnBnClickedBtnAdd();
	CListCtrl m_list;
	afx_msg void OnDestroy();
};
